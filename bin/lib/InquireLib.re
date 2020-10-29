include Inquire.Make({
  open LTerm_style;
  open LTerm_text;

  let make_prompt = message =>
    eval([
      S(" 🔎  "),
      B_fg(blue),
      S(Printf.sprintf("%s\n ────", message)),
      E_fg,
    ]);

  let make_error = message =>
    eval([
      B_fg(green),
      S("X "),
      B_fg(white),
      S(Printf.sprintf("%s", message)),
      E_fg,
    ]);

  let make_select = (~current, options) =>
    Base.List.mapi(options, ~f=(index, option) =>
      if (current == index) {
        [
          S(" ✅ "),
          B_fg(white),
          S(Printf.sprintf("%s\n", option)),
          E_fg,
        ];
      } else {
        [
          S(" ⬜️ "),
          B_fg(white),
          S(Printf.sprintf("%s\n", option)),
          E_fg,
        ];
      }
    )
    |> List.concat
    |> eval;
});
