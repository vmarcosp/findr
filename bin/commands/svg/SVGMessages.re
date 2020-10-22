let success = filename => {
  let message =
    Pastel.(
      <Pastel color=Green>
        "🚀 Created successfully: "
        <Pastel bold=true color=Blue> filename </Pastel>
      </Pastel>
    );

  Console.log(message);
};

let loading = svg_file => {
  let message =
    Pastel.(
      <Pastel color=Green>
        "⌛️  Converting "
        <Pastel bold=true color=Blue> svg_file </Pastel>
        " to a react component."
      </Pastel>
    );

  Console.log(message);
};

let invalid_svg = svg_file => {
  let message =
    Pastel.(
      <Pastel color=Red>
        "⚠️  The selected file: "
        <Pastel bold=true color=Blue> svg_file </Pastel>
        " is not a svg."
      </Pastel>
    );

  Console.log(message);
};
let unexpected_error = () => {
  let message =
    Pastel.(<Pastel color=Red> "⚠️  Something went wrong" </Pastel>);

  Console.log(message);
};

let prettier_message = () => {
  let _ = Sys.command("clear");

  let message =
    Pastel.(
      <Pastel>
        "\n\n ⚠️  Global formatter not found. If you want to format the converted files automatically, you need to install prettier globally. \n\n"
        <Pastel color=Yellow> "📦  npm i -g prettier \n\n" </Pastel>
        <Pastel> "or\n\n" </Pastel>
        <Pastel color=Yellow> "📦  yarn global add prettier \n\n" </Pastel>
      </Pastel>
    );

  Console.log(message);
};

let bsrefmt_message = () => {
  let _ = Sys.command("clear");

  let message =
    Pastel.(
      <Pastel>
        "\n\n ⚠️  Global formatter not found. If you want to format the converted files automatically, you need to install bs-platform globally. \n\n"
        <Pastel color=Yellow> "📦  npm i -g bs-platform \n\n" </Pastel>
        <Pastel> "or\n\n" </Pastel>
        <Pastel color=Yellow>
          "📦  yarn global add bs-platform \n\n"
        </Pastel>
      </Pastel>
    );

  Console.log(message);
};
