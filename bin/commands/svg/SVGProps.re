module List = Core.List;

let items = [
  ("accent-height", "accentHeight"),
  ("alignment-baseline", "alignmentBaseline"),
  ("arabic-form", "arabicForm"),
  ("baseline-shift", "baselineShift"),
  ("cap-height", "capHeight"),
  ("clip-path", "clipPath"),
  ("clip-rule", "clipRule"),
  ("color-interpolation", "colorInterpolation"),
  ("color-interpolation-filters", "colorInterpolationFilters"),
  ("color-profile", "colorProfile"),
  ("color-rendering", "colorRendering"),
  ("dominant-baseline", "dominantBaseline"),
  ("enable-background", "enableBackground"),
  ("fill-opacity", "fillOpacity"),
  ("fill-rule", "fillRule"),
  ("flood-color", "floodColor"),
  ("flood-opacity", "floodOpacity"),
  ("font-family", "fontFamily"),
  ("font-size", "fontSize"),
  ("font-size-adjust", "fontSizeAdjust"),
  ("font-stretch", "fontStretch"),
  ("font-style", "fontStyle"),
  ("font-variant", "fontVariant"),
  ("font-weight", "fontWeight"),
  ("glyph-name", "glyphName"),
  ("glyph-orientation-horizontal", "glyphOrientationHorizontal"),
  ("glyph-orientation-vertical", "glyphOrientationVertical"),
  ("horiz-adv-x", "horizAdvX"),
  ("horiz-origin-x", "horizOriginX"),
  ("image-rendering", "imageRendering"),
  ("letter-spacing", "letterSpacing"),
  ("lighting-color", "lightingColor"),
  ("marker-end", "markerEnd"),
  ("marker-mid", "markerMid"),
  ("marker-start", "markerStart"),
  ("overline-position", "overlinePosition"),
  ("overline-thickness", "overlineThickness"),
  ("panose-1", "panose1"),
  ("paint-order", "paintOrder"),
  ("pointer-events", "pointerEvents"),
  ("rendering-intent", "renderingIntent"),
  ("shape-rendering", "shapeRendering"),
  ("stop-color", "stopColor"),
  ("stop-opacity", "stopOpacity"),
  ("strikethrough-position", "strikethroughPosition"),
  ("strikethrough-thickness", "strikethroughThickness"),
  ("stroke-dasharray", "strokeDasharray"),
  ("stroke-dashoffset", "strokeDashoffset"),
  ("stroke-linecap", "strokeLinecap"),
  ("stroke-linejoin", "strokeLinejoin"),
  ("stroke-miterlimit", "strokeMiterlimit"),
  ("stroke-opacity", "strokeOpacity"),
  ("stroke-width", "strokeWidth"),
  ("text-anchor", "textAnchor"),
  ("text-decoration", "textDecoration"),
  ("text-rendering", "textRendering"),
  ("underline-position", "underlinePosition"),
  ("underline-thickness", "underlineThickness"),
  ("unicode-bidi", "unicodeBidi"),
  ("unicode-range", "unicodeRange"),
  ("units-per-em", "unitsPerEm"),
  ("v-alphabetic", "vAlphabetic"),
  ("v-hanging", "vHanging"),
  ("v-ideographic", "vIdeographic"),
  ("v-mathematical", "vMathematical"),
  ("vert-adv-y", "vertAdvY"),
  ("vert-origin-x", "vertOriginX"),
  ("vert-origin-y", "vertOriginY"),
  ("word-spacing", "wordSpacing"),
  ("writing-mode", "writingMode"),
  ("x-height", "xHeight"),
  ("xlink:actuate", "xlinkActuate"),
  ("xlink:arcrole", "xlinkArcrole"),
  ("xlink:href", "xlinkHref"),
  ("xlink:role", "xlinkRole"),
  ("xlink:show", "xlinkShow"),
  ("xlink:title", "xlinkTitle"),
  ("xlink:type", "xlinkType"),
  ("xml:base", "xmlBase"),
  ("xml:lang", "xmlLang"),
  ("xml:space", "xmlSpace"),
];

let replace_prop = (currentText, (key, value)) => {
  let regex = Re.Perl.compile_pat(key);
  Re.replace_string(~by=value, ~all=true, regex, currentText);
};

let normalize_props = text => items |> List.fold(~init=text, ~f=replace_prop);