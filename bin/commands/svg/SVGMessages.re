let success = filename =>
  Console.log(
    <Pastel color=Green>
      "🚀 Created successfully: "
      <Pastel bold=true color=Blue> filename </Pastel>
    </Pastel>,
  );

let loading = svg_file =>
  Console.log(
    <Pastel color=Green>
      "⌛️  Converting "
      <Pastel bold=true color=Blue> svg_file </Pastel>
      " to a react component."
    </Pastel>,
  );

let invalid_svg = svg_file =>
  Console.log(
    <Pastel color=Red>
      "⚠️  The selected file: "
      <Pastel bold=true color=Blue> svg_file </Pastel>
      " is not a svg."
    </Pastel>,
  );

let unexpected_error = () =>
  Console.log(<Pastel color=Red> "⚠️  Unexpected error." </Pastel>);

let prettier_message = () => {
  let _ = Sys.command("clear");

  Console.log(
    <Pastel>
      "\n\n ⚠️  Global formatter not found. If you want to format the converted files automatically, you need to install prettier globally. \n\n"
      <Pastel color=Yellow> "📦  npm i -g prettier \n\n" </Pastel>
      <Pastel> "or\n\n" </Pastel>
      <Pastel color=Yellow> "📦  yarn global add prettier \n\n" </Pastel>
    </Pastel>,
  );
};

let bsrefmt_message = () => {
  let _ = Sys.command("clear");
  Console.log(
    <Pastel>
      "\n\n ⚠️  Global formatter not found. If you want to format the converted files automatically, you need to install bs-platform globally. \n\n"
      <Pastel color=Yellow> "📦  npm i -g bs-platform \n\n" </Pastel>
      <Pastel> "or\n\n" </Pastel>
      <Pastel color=Yellow> "📦  yarn global add bs-platform \n\n" </Pastel>
    </Pastel>,
  );
};

let formatted_message = () => {
  let _ = Sys.command("clear");
  Console.log(
    <Pastel color=Green> "🚀  Converted svg to jsx successfully." </Pastel>,
  );
};
