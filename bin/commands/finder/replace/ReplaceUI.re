module Actions = {
  type options_value =
    | ReplaceAll
    | SelectMatches
    | Cancel;
  let options =
    UI.Select.[
      {label: "Replace all ocurrences in all files.", value: ReplaceAll},
      {label: "Select ocurrences by file.", value: ReplaceAll},
      {label: "Cancel.", value: Cancel},
    ];

  let render = () => UI.Select.render(~items=options, "Choose an action:");
};
