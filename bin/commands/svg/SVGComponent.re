open Cmdliner;
open SVGArgs;
open SVGTypes;
open SVGProps;

module List = Core.List;

let create_react_component = (component_name, svg_content) =>
  SVGTemplates.(
    react
    |> Re.replace_string(~by=component_name, component_name_key)
    |> Re.replace_string(~by=svg_content, content_key)
  );

let create_reason_react_component = svg_content =>
  SVGTemplates.(
    reasonReact |> Re.replace_string(~by=svg_content, content_key)
  );

let add_extension = (name, converter) =>
  switch (converter) {
  | React => name ++ ".js"
  | ReasonReact => name ++ ".re"
  };

let create_template = (converter, component_name, svg_content) =>
  switch (converter) {
  | React => create_react_component(component_name, svg_content)
  | ReasonReact => create_reason_react_component(svg_content)
  };

let valid_svg_exntesion = filename =>
  filename
  |> String.split_on_char('.')
  |> Base.List.last
  |> Option.map(extension => extension == "svg")
  |> Optional.with_default(_, false);

let format_file = (converter, filename, _) => {
  let format_command =
    switch (converter) {
    | React => "prettier --write " ++ filename
    | ReasonReact => "bsrefmt --in-place " ++ filename
    };

  switch (converter, Sys.command(format_command)) {
  | (_, 0) =>
    let _ = Sys.command("clear");
    ();
  | (React, _) => SVGMessages.prettier_message()
  | (ReasonReact, _) => SVGMessages.bsrefmt_message()
  };
};

let svg_to_component =
    (svg_file, converter_type_raw, component_name, output_dir) => {
  let result = Fs.read_content(svg_file);
  let output = Optional.(output_dir @?> ".");
  let converter = converter_of_string(converter_type_raw);
  let filename =
    component_name |> add_extension(_, converter) |> Fs.make_path(output);

  let isSvgFile = valid_svg_exntesion(svg_file);

  switch (result, isSvgFile) {
  | (_, false) => SVGMessages.invalid_svg(svg_file)
  | (Error(_), _) => SVGMessages.unexpected_error()
  | (Ok(content), true) =>
    let _ = SVGMessages.loading(svg_file);

    content
    |> normalize_props
    |> create_template(converter, component_name)
    |> Fs.write_file(~filename)
    |> format_file(converter, filename);

    SVGMessages.success(filename);
  };
};

let config =
  Term.(
    const(svg_to_component)
    $ svg_file
    $ converter_type
    $ component_name
    $ output_dir
  );

let command = (config, Term.info("svg-component"));
