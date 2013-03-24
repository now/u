# -*- coding: utf-8 -*-

class U::String
  # YARD can’t handle aliases in C code.
  # @see #==
  alias === ==
  # @see #each_byte
  alias bytes each_byte
  # @see #each_char
  alias chars each_char
  # @see #each_codepoint
  alias codepoints each_codepoint
  # TODO: Do we really want to provide this for backward compatibility?
  # @see #each_line
  alias each each_line
  # @see #%
  alias format %
  # @see #to_sym
  alias intern to_sym
  # @see #each_line
  alias lines each_line
  # @see #length
  alias size length
  # @see #[]
  alias slice []
  # @see #to_str
  alias to_s to_str
end
