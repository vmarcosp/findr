let tap: ('a => unit, 'a) => unit = (fn, value) => fn(value);

let (->>) = tap;

let not = (fn, value) => !fn(value);
