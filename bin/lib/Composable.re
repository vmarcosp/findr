let tap: ('a => unit, 'a) => unit = (fn, value) => fn(value);

let (->>) = tap;
