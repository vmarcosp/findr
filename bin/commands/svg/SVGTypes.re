type converter =
  | React
  | ReasonReact;

let converter_of_string =
  fun
  | "react" => React
  | "reason" => ReasonReact
  | _ => React;
