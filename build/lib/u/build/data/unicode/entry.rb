# -*- coding: utf-8 -*-

class U::Build::Data::Unicode::Entry
  require 'u/build/data/unicode/entry/decomposition'

  def initialize(code, fields)
    # TODO: Why not processes Nl?
    case @type = fields[U::Build::Data::Unicode::Category]
    when 'Nd'
      @value = fields[U::Build::Data::Unicode::DecimalValue].to_i
    when 'Ll'
      @value = fields[U::Build::Data::Unicode::Upper].hex
    when 'Lu'
      @value = fields[U::Build::Data::Unicode::Lower].hex
    when 'Lt'
      @value = nil
      @title_to_lower = fields[U::Build::Data::Unicode::Lower].hex
      @title_to_upper = fields[U::Build::Data::Unicode::Upper].hex
    else
      @value = nil
    end
    @cclass = fields[U::Build::Data::Unicode::CombiningClasses]
    @decomposition = Decomposition.new(fields[U::Build::Data::Unicode::Decomposition])
  end

  attr_reader :code, :type, :value, :title_to_lower, :title_to_upper, :cclass, :decomposition
end
