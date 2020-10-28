let replace_stats = (total_matches, total_files, search_text, new_text) =>
  Console.log(
    <Pastel>
      <Pastel bold=true italic=true color=Blue> "\n Replace stats:\n" </Pastel>
      <Pastel>
        " 🔍 Search: "
        <Pastel color=Blue> {"\"" ++ search_text ++ "\""} </Pastel>
      </Pastel>
      <Pastel>
        "\n ✍️  Replace text: "
        <Pastel color=Blue> {"\"" ++ new_text ++ "\""} </Pastel>
      </Pastel>
      <Pastel>
        "\n 📦 Total files: "
        <Pastel color=Blue> {total_files |> Int.to_string} </Pastel>
      </Pastel>
      <Pastel>
        "\n ✅ Occurrences: "
        <Pastel color=Blue> {total_matches |> Int.to_string} </Pastel>
      </Pastel>
      "\n\n"
      "───────────────────────────────────────────────── \n"
    </Pastel>,
  );

let replaced_message = (total_files: int) => {
  Console.log(
    <Pastel>
      "\n"
      {Printf.sprintf("🚀  %d  file(s) updated.", total_files)}
      "\n"
    </Pastel>,
  );
};
