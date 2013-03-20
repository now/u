# -*- coding: utf-8 -*-

module U
  load File.expand_path('../u/version.rb', __FILE__)
  require File.expand_path('../u/u', __FILE__)
  Version.load
end

class String
  def u
    U::String.new(self)
  end
end
