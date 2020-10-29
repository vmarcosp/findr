open Lwt.Syntax;
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

  let* () = LTerm.clear_line_prev(term);
  let* () = LTerm.move(term, - amount_options, 0);

  let items =
    options |> Base.List.mapi(~f=to_option(current)) |> List.concat |> eval;

  let* () = LTerm.fprints(term, items);
  let* value = read_key(term);

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

let render = (~items, label) => {
  let options =
    items |> Base.List.mapi(~f=to_option(0)) |> List.concat |> eval;

  let* _ = LTerm_inputrc.load();
  let* term = Lazy.force(LTerm.stdout);
  let* raw_mode = LTerm.enter_raw_mode(term);
  let* _ = LTerm.hide_cursor(term);

  let* () = LTerm.printf("📌 %s\n", label);
  let* () = LTerm.fprints(term, options);

  Lwt.finalize(
    () => {
      let* current = render_options(term, items, 0);
      Lwt.return(current);
    },
    () => {
      let* _ = LTerm.leave_raw_mode(term, raw_mode);
      LTerm.show_cursor(term);
    },
  );
};
