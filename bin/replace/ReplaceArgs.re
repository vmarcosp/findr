open Cmdliner;

let text_arg =
  Arg.(
    value
    & pos(0, string, "")
    & info([], ~doc="The text that you want to replace")
  );

let by_arg = Arg.(value & pos(1, string, "") & info([], ~doc="New value"));
