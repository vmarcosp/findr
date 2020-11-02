module Actions = {
  type options_value =
    | ReplaceAll
    | SelectFiles
    | Cancel;
  let options =
    UI.Select.[
      {label: "Replace all occurrences in all files", value: ReplaceAll},
      {label: "Select files", value: SelectFiles},
      {label: "Cancel", value: Cancel},
    ];

  let render = () => UI.Select.render(~options, "Choose an action:");
};

module ConfirmReplace = {
  type options =
    | Confirm
    | SelectFiles;

  let options =
    UI.Select.[
      {label: "Yes", value: Confirm},
      {label: "No, go back to file selection", value: SelectFiles},
    ];

  let render = (total_files, total_matches) => {
    let label =
      Printf.sprintf(
        "Replace %d occurrence(s) in %d file(s)?",
        total_matches,
        total_files,
      );
    UI.Select.render(~options, label);
  };
};
