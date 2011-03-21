# -*- coding: utf-8 -*-

require 'encoding/character/utf-8/utf8'

module U::String
  def downcase!
    replace(downcase)
  end

  def reverse!
    replace(reverse)
  end

  def tr!(from, to)
    replace(tr(from, to))
  end

  def tr_s!(from, to)
    replace(tr_s(from, to))
  end

  def inspect
    'u%s' % super
  end

  def upcase!
    replace(upcase)
  end

  def capitalize
    self[0].upcase + self[1..-1].downcase
  end

  def capitalize!
    replace(capitalize)
  end

  def foldcase!
    replace(foldcase)
  end
end
