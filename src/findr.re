open Cmdliner;

let default_command = (Term.const(), Term.info("findr"));

let _ =
  Term.(
    eval_choice(default_command, [Find.command, Replace.command]) |> exit
  );
