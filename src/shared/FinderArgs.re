open Cmdliner;

let text_arg =
  Arg.(
    value
    & pos(0, string, "")
    & info([], ~doc="The text that you want to find")
  );

let folder_arg =
  Arg.(
    value & opt(some(string), None) & info(["f", "folder"], ~doc="folder")
  );

let regex_mode_arg =
  Arg.(value & flag & info(["r", "regex"], ~doc="Enable regex mode"));

let extension_arg =
  Arg.(
    value
    & opt(some(list(string)), None)
    & info(
        ["e", "extension"],
        ~doc="Filter files by extension, e.g: re,js,ml",
      )
  );
