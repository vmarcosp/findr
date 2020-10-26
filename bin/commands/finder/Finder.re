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
  let line_number = <Pastel dim=true> {index |> Int.to_string} </Pastel>;
  Printf.sprintf(" %5s %s    ", line_number, line);
};

let add_lines = content =>
  content
  |> Re.Str.split(new_line_regex)
  |> List.mapi(create_line)
  |> Helpers.join("\n");

let make_item = (text, accumulator, filename) => {
  let (total_matches, items) = accumulator;
  let result = Fs.read_content(filename);
  let text_regex = Re.Perl.compile_pat(text);
  let file_content = Infix.Result.(result @?> "") |> add_lines;

  let matches = count_matches(file_content, text_regex);
  let item = {file_content, filename, text_regex, matches, text};

  matches === 0
    ? (total_matches, items) : (matches + total_matches, [item, ...items]);
};

let find_text = (text, maybe_folder) => {
  let folder = Optional.(maybe_folder @?> "./");

  let (matches, files) =
    folder
    |> Fs.read_dir
    |> get_files(folder)
    |> Base.List.fold(~init=(0, []), ~f=make_item(text));

  FinderMessages.print_stats(matches, files, text);
  files |> List.iter(FinderMessages.print_content);
};

let config = Term.(const(find_text) $ text_arg $ folder_arg);

let command = (config, Term.info("finder"));
