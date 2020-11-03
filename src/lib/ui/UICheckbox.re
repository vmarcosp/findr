open LetSyntax;
open LTerm_text;
open LTerm_style;
open UIShared;
open UITypes;

type checkbox('a) = {
  label: string,
  checked: bool,
  value: 'a,
};

let to_checkbox = (current, index, {checked, label, _}) => {
  let is_current = current == index;
  [
    B_fg(blue),
    S(is_current ? "▶︎ " : "  "),
    E_fg,
    B_fg(white),
    S(checked ? "✅" : "⬜️"),
    E_fg,
    B_fg(checked ? green : white),
    S(" " ++ label ++ "\n"),
    E_fg,
  ];
};

let toggle_check = (current, checked, index, checkbox) =>
  index == current ? {...checkbox, checked} : checkbox;

let only_checked = items => items |> List.filter(item => item.checked);

let rec render_options = (term, options, current) => {
  let amount_options = List.length(options);
  let next = increment(amount_options, current);
  let previous = decrement(current);
  let checkboxes =
    options |> Base.List.mapi(~f=to_checkbox(current)) |> List.concat |> eval;

  let.lwt () = LTerm.clear_line_prev(term);
  let.lwt () = LTerm.move(term, - amount_options, 0);
  let.lwt () = LTerm.fprints(term, checkboxes);
  let.lwt value = read_key(term);

  switch (value) {
  | Up => render_options(term, options, previous)
  | Down => render_options(term, options, next)

  | Right =>
    options
    |> Base.List.mapi(~f=toggle_check(current, true))
    |> render_options(term, _, current)

  | Left =>
    options
    |> Base.List.mapi(~f=toggle_check(current, false))
    |> render_options(term, _, current)

  | Enter => Lwt.return(InputValue(options |> only_checked))
  | CtrlC => Lwt.return(Canceled)
  };
};

let render = (~options as items, label) => {
  let checkboxes =
    items |> Base.List.mapi(~f=to_checkbox(0)) |> List.concat |> eval;

  let.lwt () = LTerm_inputrc.load();
  let.lwt term = Lazy.force(LTerm.stdout);
  let.lwt raw_mode = LTerm.enter_raw_mode(term);
  let.lwt () = LTerm.hide_cursor(term);
  let.lwt () = LTerm.printf("✅ %s\n", label);
  let.lwt () = LTerm.fprints(term, checkboxes);

  Lwt.finalize(
    () => {
      let.lwt items = render_options(term, items, 0);
      Lwt.return(items);
    },
    () => {
      let.lwt _ = LTerm.leave_raw_mode(term, raw_mode);
      LTerm.show_cursor(term);
    },
  );
};
