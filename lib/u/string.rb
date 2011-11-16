# -*- coding: utf-8 -*-

class U::String
  # YARD can’t handle aliases in C code.
  alias === ==
  alias bytes each_byte
  alias chars each_char
  alias codepoints each_codepoint
  alias digits? digit?
  # TODO: Do we really want to provide this for backward compatibility?
  alias each each_line
  alias ends_with? end_with?
  alias format %
  alias intern to_sym
  alias lines each_line
  alias newlines? newline?
  alias printable? print?
  alias size length
  alias slice []
  alias starts_with? start_with?
  alias to_s to_str
  alias xdigits? xdigit?
end
