# -*- coding: utf-8 -*-

class U::Build::Header
  require 'u/build/header/table'

  def initialize(name, io = $stdout)
    header_h = name.upcase.gsub(/[^A-Z0-9]/, '_')
    io.puts <<EOH
/* Automatically generated file */

#ifndef #{header_h}
#define #{header_h}


EOH
    yield
    io.puts <<EOF


#endif /* #{header_h} */
EOF
  end
end
