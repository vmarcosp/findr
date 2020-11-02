module Checkbox = UICheckbox;
module Select = UISelect;

let clear = () => {
  let _ = Sys.command("clear");
  ();
};

let loading = text =>
  Console.log(<Pastel color=Green bold=true> {"⏳ " ++ text} </Pastel>);

let empty_state = message =>
  Console.log(<Pastel> {"\n🔍 " ++ message} </Pastel>);
