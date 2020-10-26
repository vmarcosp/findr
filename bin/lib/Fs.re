type lineContent = {mutable lines: string};

type loopFlag = {mutable content: bool};

let concat_lines = inChannel => {
  let content = {lines: ""};
  let continue = {content: true};

  try(
    while (continue.content) {
      let line = input_line(inChannel);
      content.lines = content.lines ++ "\n" ++ line;
    }
  ) {
  | End_of_file => continue.content = false
  };
  close_in(inChannel);
  Ok(content.lines);
};

let read_content = filename =>
  try({
    let inChannel = open_in(filename);
    concat_lines(inChannel);
  }) {
  | Sys_error(_) as e => Error(e)
  };

let write_file = (~filename, content) => {
  let outChannel = open_out(filename);

  Printf.fprintf(outChannel, "%s", content);

  close_out(outChannel);
};

let make_path = (path, name) => path ++ "/" ++ name;