<p align="center">
  <br />
  <img src="./assets/logo.svg" width="500" /> 
</p>
<p align="center">
   <a href="#preview">Preview</a> •
   <a href="#features">Features</a> •
   <a href="#commands">Commands</a> •
   <a href="#license">License</a> •
   <a href="https://github.com/lukinco/timerlab/blob/master/CONTRIBUTING.md">Contributing</a> •
</p>
<br/>

## Preview
<p align="center">
  <br />
  
  <p align="center"><b><i>Find command</i></b></p>
  <img src="./assets/find.gif" width="700" /> 
</p>
<br/>
<p align="center">
  <br />
 
  <p align="center"><b><i>Replace command + regex</i></b></p>
  <img src="./assets/replace.gif" width="700" /> 
</p>

## Installation
```
npm i -g @vmarcosp/findr
```

## OS Support
- :white_check_mark: &nbsp; Mac
- :white_check_mark: &nbsp; Linux
- :white_check_mark: &nbsp; Linux
- :gear: &nbsp; Windows *(WIP)*

## Features

- :white_check_mark: &nbsp; Find
- :white_check_mark: &nbsp; Replace
- :white_check_mark: &nbsp; Colorized output
- :white_check_mark: &nbsp; Highlight and preview occurrences
- :white_check_mark: &nbsp; Select files to replace
- :white_check_mark: &nbsp; Regex support
- ⚙️  &nbsp; Select ocurrences to replace *(WIP)*

## Commands

### Find command:
Positional arguments:
  - 1º *Text to find*

Named arguments:
  - `--folder` or `-f`
  - `--regex` or `-r` regex mode


Example:
```sh
  findr find "write_file" --folder src
```

### Replace command:
Positional arguments:
 - 1º *Text to replace*
 - 2º *New text*

Named arguments:
  - `--folder` or `-f`
  - `--regex` or `-r` *regex mode*


Example:
```sh
  findr replace "\bwrite_file" "create_file" --folder src --regex
```

## License

MIT
