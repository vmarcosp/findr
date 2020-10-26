open Cmdliner;
open FinderArgs;
open FinderTypes;

let is_file = Composable.not(Sys.is_directory);

let new_line_regex = Re.Str.regexp("\n");

let count_matches = (content, regex) =>
  Re.matches(regex, content) |> List.length;

let rec get_files = (parent, files) =>
  switch (files) {
  | [] => []
  | [item] =>
    let path = Fs.(parent +/ item);
    is_file(path) ? [path] : path |> Fs.read_dir |> get_files(path);
  | [item, ...others] =>
    let path = Fs.(parent +/ item);
    let other_items = get_files(parent, others);
    is_file(path)
      ? [path, ...other_items]
      : {
        let children = path |> Fs.read_dir |> get_files(path);
        List.concat([children, other_items]);
      };
  };

let create_line = (index, line) => {
  let line_number =
    <Pastel color=Green> {(index + 1 |> Int.to_string) ++ "  |"} </Pastel>;
  Printf.sprintf(" %5s %s ", line_number, line);
};

let create_additional_line = (line_number, maybe_content) =>
  switch (maybe_content) {
  | None => ""
  | Some(line_content) =>
    Printf.sprintf(
      " %5s  | %s ",
      <Pastel dim=true> {line_number + 1 |> Int.to_string} </Pastel>,
      line_content,
    )
  };

let add_lines = content =>
  content
  |> Re.Str.split(new_line_regex)
  |> List.mapi(create_line)
  |> Helpers.join("\n");

let get_file_matches = (lines, text, index, matches: list(string), line) => {
  let text_regex = Re.Perl.compile_pat(text);
  let has_matches = count_matches(line, text_regex);
  let previous_line_number = index - 1;
  let next_line_number = index + 1;

  if (List.length(lines) == 0 || has_matches == 0) {
    matches;
  } else {
    let previous_line =
      Base.List.nth(lines, previous_line_number)
      |> create_additional_line(previous_line_number);

    let next_line =
      Base.List.nth(lines, next_line_number)
      |> create_additional_line(next_line_number);

    let highlight_text =
      <Pastel bold=true underline=true color=Green> text </Pastel>;

    let line_content =
      Re.replace_string(~by=highlight_text, ~all=true, text_regex, line);

    let current_line = create_line(index, line_content);

    let match = Helpers.join("\n", [previous_line, current_line, next_line]);

    List.concat([matches, [match]]);
  };
};

let extract_matches = (text, files, filename) => {
  let result = Fs.read_content(filename);
  switch (result) {
  | Error(_) => files
  | Ok(file_content) =>
    let lines = file_content |> Re.Str.split(new_line_regex);
    let matches =
      lines |> Base.List.foldi(~init=[], ~f=get_file_matches(lines, text));
    [{filename, matches}, ...files];
  };
};

let find_text = (text, maybe_folder) => {
  let folder = Optional.(maybe_folder @?> "./");

  let matched_files =
    folder
    |> Fs.read_dir
    |> get_files(folder)
    |> Base.List.fold(~init=[], ~f=extract_matches(text))
    |> Base.List.filter(~f=file => List.length(file.matches) > 0);

  FinderConsole.print_stats(matched_files, folder, text);
  matched_files
  |> List.iteri(FinderConsole.print_file_matches(matched_files));
};

let config = Term.(const(find_text) $ text_arg $ folder_arg);

let command = (config, Term.info("finder"));
