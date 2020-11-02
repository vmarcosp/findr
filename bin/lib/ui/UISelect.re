open LetSyntax;
open LTerm_text;
open LTerm_style;
open UIShared;

type select_option('a) = {
  label: string,
  value: 'a,
};

let to_option = (current, index, {label, _}) => {
  let is_current = current == index;
  [
    B_fg(blue),
    S(is_current ? "▶︎ " : "  "),
    E_fg,
    B_fg(is_current ? green : white),
    S(" " ++ label ++ "\n"),
    E_fg,
  ];
};

let rec render_options = (term, options, current) => {
  let amount_options = List.length(options);
  let next = increment(amount_options, current);
  let previous = decrement(current);

  let.lwt () = LTerm.clear_line_prev(term);
  let.lwt () = LTerm.move(term, - amount_options, 0);

  let items =
    options |> Base.List.mapi(~f=to_option(current)) |> List.concat |> eval;

  let.lwt () = LTerm.fprints(term, items);
  let.lwt value = read_key(term);

  let value =
    switch (value) {
    | Left
    | Up => render_options(term, options, previous)
    | Right
    | Down => render_options(term, options, next)
    | Enter => Lwt.return(List.nth(options, current))
    | CtrlC => Lwt.fail(Failure("Interruption"))
    };

  value;
};

let render = (~options as items, label) => {
  let options =
    items |> Base.List.mapi(~f=to_option(0)) |> List.concat |> eval;

  let.lwt _ = LTerm_inputrc.load();
  let.lwt term = Lazy.force(LTerm.stdout);
  let.lwt raw_mode = LTerm.enter_raw_mode(term);
  let.lwt _ = LTerm.hide_cursor(term);

  let.lwt () = LTerm.printf("\n📌 %s\n", label);
  let.lwt () = LTerm.fprints(term, options);

  Lwt.finalize(
    () => {
      let.lwt current = render_options(term, items, 0);
      Lwt.return(current);
    },
    () => {
      let.lwt _ = LTerm.leave_raw_mode(term, raw_mode);
      LTerm.show_cursor(term);
    },
  );
};
