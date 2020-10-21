let with_default = (maybe, value) =>
  switch (maybe) {
  | Some(value) => value
  | None => value
  };

let (@?>) = with_default;
