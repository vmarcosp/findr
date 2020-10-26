open Cmdliner;

let default_command = (Term.const(), Term.info("Susanoo CLI"));

let () =
  Term.(
    eval_choice(
      default_command,
      [SVG.svg_component_cmd, SVG.svg_jsx_cmd, Finder.command],
    )
    |> exit
  );
