# -*- coding: utf-8 -*-

class U::Build::Header
  require 'u/build/header/table'
  require 'u/build/header/tables'

  def initialize(io = $stdout)
    io.puts "/* Automatically generated file */\n\n"
    yield
  end
end
