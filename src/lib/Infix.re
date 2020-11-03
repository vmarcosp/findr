module Result = {
  let with_default = (maybe, default_value) =>
    switch (maybe) {
    | Error(_) => default_value
    | Ok(value) => value
    };

  let (<?>) = with_default;
};

module Optional = {
  let with_default = (maybe, value) =>
    switch (maybe) {
    | Some(value) => value
    | None => value
    };

  let (<?>) = with_default;
};
