# -*- coding: utf-8 -*-

class U::Build::Header::Table
  require 'u/build/header/table/row'

  def initialize(declaration)
    @declaration = declaration
    @rows = []
  end

  def <<(row)
    @rows << row
    self
  end

  def to_s
    "\n\n%s = {\n%s\n};" % [@declaration, @rows.join(",\n")]
  end
end
