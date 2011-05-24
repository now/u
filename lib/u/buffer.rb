# -*- coding: utf-8 -*-

class U::Buffer
  def inspect
    u = to_u
    u.length < 12 ?
      ('#<%s %s>' % [self.class, u]) :
      ('#<%s %s…%s>' % [self.class, u[0...5], u[-5..-1]])
  end
end
