open ReplaceArgs;
open Cmdliner;
open FinderTypes;
open LetSyntax;
open Infix.Optional;

module List = Base.List;
module ConfirmReplace = ReplaceUI.ConfirmReplace;

let file_of_option = UI.Checkbox.(({value, _}) => value);

let replace_occurrences = (text, regex_mode, new_text, files) => {
  let make_replace = ({filename, _}) => {
    let text_regex = FinderLibrary.create_regex(regex_mode, text);
    let read_result = Fs.read_content(filename);

    switch (read_result) {
    | Error(_) => false
    | Ok(file_content) =>
      let updated_content =
        Re.replace_string(~by=new_text, ~all=true, text_regex, file_content);
      Fs.write_file(~filename, updated_content);
      true;
    };
  };

  files
  |> List.map(~f=make_replace)
  |> List.filter(~f=updated => updated)
  |> List.length
  |> ReplaceConsole.replaced_message;
};

let file_to_option = ({filename, matches}) =>
  UI.Checkbox.{
    label: filename,
    value: {
      filename,
      matches,
    },
    checked: false,
  };

let rec select_files_to_replace = (text, regex_mode, new_text, files) => {
  UI.clear();
  let options = files |> List.map(~f=file_to_option);
  let.lwt selected_options =
    UI.Checkbox.render(~options, "Select one or more files:");

  if (selected_options == []) {
    select_files_to_replace(text, regex_mode, new_text, files);
  } else {
    let selected_files = selected_options |> List.map(~f=file_of_option);
    let total_matches = FinderLibrary.count_matches(selected_files);
    let total_files = List.length(selected_files);

    UI.clear();
    FinderConsole.print_all_matches(selected_files);
    let.lwt {value, _} = ConfirmReplace.render(total_files, total_matches);

    switch (value) {
    | Confirm =>
      selected_files |> replace_occurrences(text, regex_mode, new_text);
      Lwt.return();
    | SelectFiles =>
      select_files_to_replace(text, regex_mode, new_text, files)
    };
  };
};

let find_occurrences = (regex_mode, text, new_text, maybe_folder) => {
  let folder = maybe_folder @?> "./";

  UI.loading("Finding occurrences...");

  let files =
    FinderLibrary.find_text(
      ~match_mode=Replace(new_text),
      ~regex_mode,
      text,
      folder,
    );

  let total_matches = FinderLibrary.count_matches(files);
  let total_files = List.length(files);

  if (total_files > 0) {
    UI.clear();
    ReplaceConsole.replace_stats(total_matches, total_files, text, new_text);
    FinderConsole.print_all_matches(files);
    let.lwt {value, _} = ReplaceUI.Actions.render();

    switch (value) {
    | ReplaceAll =>
      files |> replace_occurrences(text, regex_mode, new_text);
      Lwt.return();
    | SelectFiles =>
      select_files_to_replace(text, regex_mode, new_text, files)
    | Cancel => Lwt.return()
    };
  } else {
    Printf.sprintf(
      "No matches found for \"%s\"",
      <Pastel color=Green> text </Pastel>,
    )
    |> UI.empty_state;
    Lwt.return();
  };
};

let exec_command = (text, new_text, folder, regex_mode) =>
  find_occurrences(regex_mode, text, new_text, folder) |> Lwt_main.run;

let config =
  Term.(
    const(exec_command)
    $ text_arg
    $ by_arg
    $ FinderArgs.folder_arg
    $ FinderArgs.regex_mode_arg
  );

let command = (config, Term.info("replace"));
