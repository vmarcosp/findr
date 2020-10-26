module Result = {
  let withDefault = (maybe, default_value) =>
    switch (maybe) {
    | Error(_) => default_value
    | Ok(value) => value
    };

  let (@?>) = withDefault;
};
