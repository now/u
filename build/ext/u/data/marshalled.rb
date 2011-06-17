# -*- coding: utf-8 -*-

require 'u/build'

Marshal.dump(U::Build::Data::Unicode.new(ARGV[0]), $stdout)
