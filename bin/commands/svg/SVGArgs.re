open Cmdliner;

let svg_file =
  Arg.(
    value
    & pos(0, file, "")
    & info([], ~docv="svgFile", ~doc="The .svg file")
  );

let converter_type =
  Arg.(
    value & opt(string, "react") & info(["type"], ~doc="Converter type")
  );

let component_name =
  Arg.(
    value
    & opt(string, "MyComponent")
    & info(["name"], ~doc="Component name")
  );

let output_dir =
  Arg.(
    value
    & opt(some(string), None)
    & info(["output"], ~doc="Output folder")
  );
