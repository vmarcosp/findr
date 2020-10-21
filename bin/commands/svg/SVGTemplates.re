let content_key = Re.Perl.compile_pat("SvgContent");
let component_name_key = Re.Perl.compile_pat("ComponentName");

let reasonReact = {|[@react.component]
let make = () => {
  SvgContent
};
|};

let react = {|import React from 'react'

function ComponentName () {
  return (
    SvgContent
  )
}
|};
