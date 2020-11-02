open LetSyntax;

let decrement = current =>
  switch (current) {
  | 0 => 0
  | value => value - 1
  };

let increment = (max, current) =>
  switch (current) {
  | value when max - 1 == value => current
  | value => value + 1
  };

type key =
  | Enter
  | Up
  | Down
  | Left
  | Right
  | CtrlC;

let rec read_key = term => {
  let.lwt event = LTerm.read_event(term);

  switch (event) {
  | LTerm_event.Key({
      LTerm_key.code: LTerm_key.Char(ch),
      LTerm_key.control: true,
      _,
    })
      when Uchar.equal(ch, Uchar.of_char('c')) =>
    Lwt.return(CtrlC)
  | LTerm_event.Key({code: LTerm_key.Enter, _}) => Lwt.return(Enter)
  | LTerm_event.Key({code: LTerm_key.Left, _}) => Lwt.return(Left)
  | LTerm_event.Key({code: LTerm_key.Up, _}) => Lwt.return(Up)
  | LTerm_event.Key({code: LTerm_key.Right, _}) => Lwt.return(Right)
  | LTerm_event.Key({code: LTerm_key.Down, _}) => Lwt.return(Down)
  | _ => read_key(term)
  };
};
