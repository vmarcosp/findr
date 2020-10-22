open Cmdliner;

let svg_file =
  Arg.(
    value
    & pos(0, file, "")
    & info([], ~doc="The .svg file, e.g: src/assets/some-logo.svg")
  );

let converter_type =
  Arg.(
    value
    & opt(string, "react")
    & info(["type"], ~docv="react, reason", ~doc="Converter type")
  );

let component_name =
  Arg.(
    value
    & opt(string, "GeneratedComponent")
    & info(
        ["name"],
        ~docv="GeneratedComponent.js",
        ~doc="Name of your generated react component, e.g: MyLogo.js",
      )
  );

let output_dir =
  Arg.(
    value
    & opt(some(string), None)
    & info(
        ["output"],
        ~docv="./",
        ~doc="Output folder, e.g: src/components/",
      )
  );

let component_file =
  Arg.(
    value
    & pos(0, file, "")
    & info([], ~doc="React component file, e.g: components/Logo.jsx")
  );
