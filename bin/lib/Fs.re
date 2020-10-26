type line_content = {mutable lines: string};

type loop_flag = {mutable content: bool};

let (+/) = (path, file) => path ++ "/" ++ file;

let concat_lines = in_channel => {
  let content = {lines: ""};
  let continue = {content: true};

  try(
    while (continue.content) {
      let line = input_line(in_channel);
      content.lines = content.lines ++ "\n" ++ line;
    }
  ) {
  | End_of_file => continue.content = false
  };
  close_in(in_channel);
  Ok(content.lines);
};

let read_content = filename =>
  try({
    let in_channel = open_in(filename);
    concat_lines(in_channel);
  }) {
  | Sys_error(_) as e => Error(e)
  };

let write_file = (~filename, content) => {
  let out_channel = open_out(filename);

  Printf.fprintf(out_channel, "%s", content);

  close_out(out_channel);
};

let read_dir = dir => dir |> Sys.readdir |> Array.to_list;

let make_path = (path, name) => path ++ "/" ++ name;
