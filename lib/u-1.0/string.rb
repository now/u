# -*- coding: utf-8 -*-

class U::String
  # @return [self] The receiver; mostly for completeness, but allows you to
  #   always call #u on something that’s either a String or a U::String
  def u
    self
  end
end
