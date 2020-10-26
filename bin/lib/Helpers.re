let join = (divider, values) =>
  values
  |> Base.List.fold(~init="", ~f=(content, current) =>
       content ++ divider ++ current
     );
