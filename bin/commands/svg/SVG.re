open Cmdliner;
open SVGArgs;
open SVGTypes;

module List = Core.List;

let replace_prop = (currentText, (key, value)) => {
  let regex = Re.Perl.compile_pat(key);
  Re.replace_string(~by=value, ~all=true, regex, currentText);
};

let normalize_props = text =>
  SVGProps.items |> List.fold(~init=text, ~f=replace_prop);

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

let get_filename = (name, converter) =>
  switch (converter) {
  | React => name ++ ".js"
  | ReasonReact => name ++ ".re"
  };

let create_template = (converter, component_name, svg_content) =>
  switch (converter) {
  | React => create_react_component(component_name, svg_content)
  | ReasonReact => create_reason_react_component(svg_content)
  };

let validSvgExtension = filename =>
  filename
  |> String.split_on_char('.')
  |> Base.List.last
  |> Option.map(extension => extension == "svg")
  |> Optional.with_default(_, false);

let exec_command = (svg_file, converter_type_raw, component_name, output_dir) => {
  let result = Fs.read_content(svg_file);
  let output = Optional.(output_dir @?> ".");
  let converter = converter_of_string(converter_type_raw);
  let filename = get_filename(component_name, converter);

  let isSvgFile = validSvgExtension(svg_file);

  switch (result, isSvgFile) {
  | (_, false) => Console.log("Este arquivo não é .svg")
  | (Error(_), _) => Console.log("Ocorreu um erro ao ler o arquivo.")
  | (Ok(content), true) =>
    content
    |> normalize_props
    |> create_template(converter, component_name)
    |> Fs.write_file(~path=output, ~name=filename)
  };
};

let exec_command_config =
  Term.(
    const(exec_command)
    $ svg_file
    $ converter_type
    $ component_name
    $ output_dir
  );

let command = (exec_command_config, Term.info("svg"));
