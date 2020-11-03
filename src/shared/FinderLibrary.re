open FinderTypes;

let new_line_regex = Re.Str.regexp("\n");

let rec get_files = (parent, files) =>
  switch (files) {
  | [] => []
  | [item] =>
    let path = Fs.(parent +/ item);
    Fs.is_file(path) ? [path] : path |> Fs.read_dir |> get_files(path);
  | [item, ...others] =>
    let path = Fs.(parent +/ item);
    let other_items = get_files(parent, others);
    Fs.is_file(path)
      ? [path, ...other_items]
      : {
        let children = path |> Fs.read_dir |> get_files(path);
        List.concat([children, other_items]);
      };
  };

let create_line = (index, line) => {
  let line_number =
    <Pastel color=Green> {index + 1 |> Int.to_string} </Pastel>;
  Printf.sprintf(" %s %s ", line_number, line);
};

let create_additional_line = (line_number, maybe_content) =>
  switch (maybe_content) {
  | None => ""
  | Some(line_content) =>
    Printf.sprintf(
      " %d %s ",
      {
        line_number + 1;
      },
      line_content,
    )
  };

let add_lines = content =>
  content
  |> Re.Str.split(new_line_regex)
  |> List.mapi(create_line)
  |> Helpers.join("\n");

let create_hightlight_text = (match_mode, text) =>
  switch (match_mode) {
  | Find => <Pastel bold=true underline=true color=Green> text </Pastel>
  | Replace(new_value) =>
    <Pastel dim=false>
      <Pastel strikethrough=true bold=true color=Red> text </Pastel>
      <Pastel bold=true underline=true color=Green> new_value </Pastel>
    </Pastel>
  };

let get_file_matches = (match_mode, lines, text_regex, index, matches, line) => {
  let line_matches = Re.matches(text_regex, line);
  let previous_line_number = index - 1;
  let next_line_number = index + 1;

  if (lines == [] || line_matches == []) {
    matches;
  } else {
    let previous_line =
      Base.List.nth(lines, previous_line_number)
      |> create_additional_line(previous_line_number);

    let next_line =
      Base.List.nth(lines, next_line_number)
      |> create_additional_line(next_line_number);

    let highlight_text =
      line_matches |> Base.List.hd_exn |> create_hightlight_text(match_mode);

    let line_content =
      Re.replace_string(~by=highlight_text, ~all=true, text_regex, line);

    let current_line = create_line(index, line_content);

    let match = Helpers.join("\n", [previous_line, current_line, next_line]);

    List.concat([matches, [match]]);
  };
};

let create_regex = (regex_mode, text) => {
  let value = regex_mode ? text : Helpers.escape_text(text);
  Re.Perl.compile_pat(value);
};

let extract_matches = (match_mode, regex_mode, text, files, filename) => {
  let result = Fs.read_content(filename);
  switch (result) {
  | Error(_) => files
  | Ok(file_content) =>
    let lines = file_content |> Re.Str.split(new_line_regex);
    let text_regex = create_regex(regex_mode, text);
    let matches =
      lines
      |> Base.List.foldi(
           ~init=[],
           ~f=get_file_matches(match_mode, lines, text_regex),
         );
    [{filename, matches}, ...files];
  };
};

let filter_by_extensions = (maybe_extensions, files) =>
  switch (maybe_extensions) {
  | None => files
  | Some(extensions) =>
    Base.List.filter(
      files,
      ~f=filename => {
        let extension =
          String.split_on_char('.', filename)
          |> Base.List.last
          |> Infix.Optional.with_default(_, "");

        Base.List.mem(extensions, extension, ~equal=(==));
      },
    )
  };

let count_matches =
  Base.List.fold(_, ~init=0, ~f=(total, {matches, _}) =>
    total + List.length(matches)
  );

let find_text = (~match_mode, ~regex_mode, text, folder, extensions) =>
  folder
  |> Fs.read_dir
  |> get_files(folder)
  |> filter_by_extensions(extensions)
  |> Base.List.fold(
       ~init=[],
       ~f=extract_matches(match_mode, regex_mode, text),
     )
  |> Base.List.filter(~f=file => List.length(file.matches) > 0);
