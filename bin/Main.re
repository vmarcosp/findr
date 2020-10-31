open Cmdliner;

let default_command = (Term.const(), Term.info("Susanoo CLI"));

let _ =
  Term.(
    eval_choice(default_command, [Finder.command, Replace.command]) |> exit
  );
