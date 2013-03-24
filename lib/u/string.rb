# -*- coding: utf-8 -*-

class U::String
  # YARD can’t handle aliases in C code.
  alias === ==
  alias bytes each_byte
  alias chars each_char
  alias codepoints each_codepoint
  # TODO: Do we really want to provide this for backward compatibility?
  alias each each_line
  alias format %
  alias intern to_sym
  alias lines each_line
  alias size length
  alias slice []
  alias to_s to_str
end
