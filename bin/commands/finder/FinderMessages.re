open FinderTypes;

let divider = <Pastel dim=true> {|

|} </Pastel>;

let print_content = ({file_content, text_regex, text, filename, matches}) => {
  let file =
    <Pastel bold=true>
      "📦  File: "
      <Pastel color=Blue> filename </Pastel>
      "\n"
      <Pastel bold=true>
        "✅  Matches: "
        <Pastel color=Blue> {Int.to_string(matches)} </Pastel>
      </Pastel>
    </Pastel>;

  let highlight_text =
    <Pastel bold=true underline=true color=Green> text </Pastel>;

  let updated_content =
    Re.replace_string(
      ~by=highlight_text,
      ~all=true,
      text_regex,
      file_content,
    );

  Console.log(file);
  Console.log(updated_content);
  Console.log(divider);
  ();
};

let print_stats = (matches, files, text) =>
  Console.log(
    <Pastel>
      "\n"
      "🔍 Search: "
      <Pastel color=Blue> {"\"" ++ text ++ "\""} </Pastel>
      "\n"
      "📦 Total files: "
      <Pastel color=Blue> {matches |> Int.to_string} </Pastel>
      "\n"
      "✅ Total matches: "
      <Pastel color=Blue> {files |> List.length |> Int.to_string} </Pastel>
      "\n"
    </Pastel>,
  );
