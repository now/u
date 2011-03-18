# -*- coding: utf-8 -*-

module U
  require 'u/string'
  require 'u/version'
end

class String
  def u
    dup.u!
  end

  def u!
    self.extend(U::String)
  end
end
