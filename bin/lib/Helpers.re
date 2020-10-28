let join = (divider, values) =>
  values
  |> Base.List.fold(~init="", ~f=(content, current) =>
       content ++ divider ++ current
     );

let string_of_char = c => String.make(1, c);

let explode = str => {
  let rec explode_inner = (index, chars) =>
    if (index < String.length(str)) {
      let new_char = str.[index];
      explode_inner(index + 1, chars @ [new_char]);
    } else {
      chars;
    };
  explode_inner(0, []);
};

let escape_text = text => {
  let rec escape_char =
    fun
    | [] => ""
    | ['^'] => {|\^|}
    | ['.'] => {|\.|}
    | ['$'] => {|\$|}
    | ['|'] => {|\||}
    | ['('] => {|\(|}
    | [')'] => {|\)|}
    | ['['] => {|\[|}
    | [']'] => {|\]|}
    | ['*'] => {|\*|}
    | ['+'] => {|\+|}
    | ['?'] => {|\?|}
    | [a] => string_of_char(a)
    | [char, ...rest] => escape_char([char]) ++ escape_char(rest);

  text |> explode |> escape_char;
};
