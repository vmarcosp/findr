open Cmdliner;
open FinderArgs;
open FinderTypes;
open Infix.Optional;

let exec_command = (text, maybe_folder, regex_mode, extensions) => {
  let folder = maybe_folder <?> "./";
  UI.loading("Finding occurrences...");

  let matched_files =
    FinderLibrary.find_text(
      ~match_mode=Find,
      ~regex_mode,
      text,
      folder,
      extensions,
    );

  switch (matched_files) {
  | [] => UI.empty_state("No files found")
  | files =>
    UI.clear();
    FindConsole.print_stats(matched_files, folder, text);
    files |> List.iteri(FindConsole.print_file_matches(matched_files));
  };
};

let config =
  Term.(
    const(exec_command)
    $ text_arg
    $ folder_arg
    $ regex_mode_arg
    $ extension_arg
  );

let command = (config, Term.info("findr"));
