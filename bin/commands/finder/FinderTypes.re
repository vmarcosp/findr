type finder_content = {
  file_content: string,
  filename: string,
  text_regex: Re.re,
  matches: int,
  text: string,
};

type file = {
  filename: string,
  matches: list(string),
};

type match_mode =
  | Find
  | Replace(string);
