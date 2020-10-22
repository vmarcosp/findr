open Cmdliner;
open SVGProps;

let svg_to_jsx = component_file => {
  let file_result = Fs.read_content(component_file);

  switch (file_result) {
  | Error(_) => SVGMessages.unexpected_error()
  | Ok(content) =>
    content
    |> normalize_props
    |> Fs.write_file(~filename=component_file)
    |> SVGMessages.formatted_message
  };

  ();
};
let config = Term.(const(svg_to_jsx) $ SVGArgs.component_file);

let command = (config, Term.info("svg-jsx"));
