open Cmdliner;

let text_arg =
  Arg.(
    value
    & pos(0, string, "")
    & info([], ~doc="The text that you want to search")
  );

let folder_arg =
  Arg.(
    value & opt(some(string), None) & info(["folder"], ~doc="The folder")
  );

let regex_mode_arg =
  Arg.(value & flag & info(["regex"], ~doc="Enable regex mode"));