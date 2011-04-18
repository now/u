# -*- coding: utf-8 -*-

module U
  require 'u/u'
  require 'u/string'
  require 'u/version'
end

class String
  def u
    U::String.new(self)
  end
end
