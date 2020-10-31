open Cmdliner;
open FinderArgs;
open FinderTypes;

let exec_command = (text, maybe_folder, regex_mode) => {
  let folder = Optional.(maybe_folder @?> "./");
  UI.loading("Finding occurrences...");

  let matched_files =
    FinderLibrary.find_text(~match_mode=Find, ~regex_mode, text, folder);

  switch (matched_files) {
  | [] => UI.empty_state("No files found")
  | files =>
    UI.clear();
    FinderConsole.print_stats(matched_files, folder, text);
    files |> List.iteri(FinderConsole.print_file_matches(matched_files));
  };
};

let config =
  Term.(const(exec_command) $ text_arg $ folder_arg $ regex_mode_arg);

let command = (config, Term.info("finder"));
