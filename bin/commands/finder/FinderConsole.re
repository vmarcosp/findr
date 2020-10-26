open FinderTypes;
module List = Base.List;

let divider = <Pastel dim=true> "\n" </Pastel>;

let file_divider =
  <Pastel dim=true>
    "\n\n ───────────────────────────────────────────────────────── \n"
  </Pastel>;

let render_match = (size, index, content, match) => {
  let render_divider = index != 0 && size != index;
  let divider =
    <Pastel> "\n" <Pastel dim=true> "\n      ..." </Pastel> "\n" </Pastel>;

  <Pastel> content {render_divider ? divider : ""} match </Pastel>;
};

let print_file_matches = (files, index, {filename, matches}) => {
  let matches_size = List.length(matches);
  let is_not_last = List.length(files) != index + 1;

  Console.log(
    <Pastel>
      "📦 File: "
      <Pastel color=Blue> filename </Pastel>
      "\n"
      "✅ Total matches: "
      <Pastel color=Blue> {matches_size |> Int.to_string} </Pastel>
      "\n"
      {matches |> List.foldi(~init="", ~f=render_match(matches_size))}
      {is_not_last ? file_divider : divider}
    </Pastel>,
  );
};

let count_matches = (total, {matches, _}) => total + List.length(matches);

let print_stats = (files, folder, text) => {
  let matches =
    files |> List.fold(~init=0, ~f=count_matches) |> Int.to_string;
  Console.log(
    <Pastel>
      <Pastel bold=true italic=true color=Blue> "\n Stats:\n" </Pastel>
      <Pastel>
        " 🔍 Search: "
        <Pastel color=Blue> {"\"" ++ text ++ "\""} </Pastel>
      </Pastel>
      <Pastel>
        "\n 📁 Directory: "
        <Pastel color=Blue> folder </Pastel>
      </Pastel>
      <Pastel>
        "\n 📦 Total files: "
        <Pastel color=Blue> {files |> List.length |> Int.to_string} </Pastel>
      </Pastel>
      <Pastel>
        "\n ✅ Total matches: "
        <Pastel color=Blue> matches </Pastel>
      </Pastel>
      "\n\n"
      "───────────────────────────────────────────────── \n"
    </Pastel>,
  );
};
