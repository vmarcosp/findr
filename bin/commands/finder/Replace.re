open ReplaceArgs;
open Cmdliner;
open FinderTypes;
open Lwt.Syntax;
open Infix.Optional;

module List = Base.List;

let create_confirm_message = (total_matches, total_files) => {
  Printf.sprintf(
    "Replace %d occurrence(s) in %d file(s)?",
    total_matches,
    total_files,
  );
};

let replace_text_files = (text, new_text, {filename, _}) => {
  let text_regex = Re.Perl.compile_pat(text);
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

let replace_text = (regex_mode, text, new_text, maybe_folder) => {
  let folder = maybe_folder @?> "./";
  let files =
    FinderLibrary.find_text(
      ~match_mode=Replace(new_text),
      ~regex_mode,
      text,
      folder,
    );
  let total_matches = FinderLibrary.count_matches(files);
  let total_files = List.length(files);

  ReplaceConsole.replace_stats(total_matches, total_files, text, new_text);
  FinderConsole.print_all_matches(files);

  let* confirmation =
    create_confirm_message(total_matches, total_files) |> Inquire.confirm;

  if (confirmation) {
    files
    |> List.map(~f=replace_text_files(text, new_text))
    |> List.filter(~f=updated => updated)
    |> List.length
    |> ReplaceConsole.replaced_message;
    ();
  };

  Lwt.return();
};

let exec_command = (text, new_text, folder, regex_mode) =>
  replace_text(regex_mode, text, new_text, folder) |> Lwt_main.run;

let config =
  Term.(
    const(exec_command)
    $ text_arg
    $ by_arg
    $ FinderArgs.folder_arg
    $ FinderArgs.regex_mode_arg
  );

let command = (config, Term.info("replace"));
