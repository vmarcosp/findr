module Result = {
  let withDefault = (maybe, default_value) =>
    switch (maybe) {
    | Error(_) => default_value
    | Ok(value) => value
    };

  let (@?>) = withDefault;
};

module Optional = {
  let with_default = (maybe, value) =>
    switch (maybe) {
    | Some(value) => value
    | None => value
    };

  let (@?>) = with_default;
};
