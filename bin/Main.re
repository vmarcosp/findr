open Cmdliner;

let default_command = (Term.const(), Term.info("Susanoo CLI"));

let () = Term.(eval_choice(default_command, [SVG.command]) |> exit);
