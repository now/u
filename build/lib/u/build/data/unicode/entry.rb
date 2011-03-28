# -*- coding: utf-8 -*-

class U::Build::Data::Unicode::Entry
  def initialize(composition_exclusions, code, fields)
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
    decomposition = fields[U::Build::Data::Unicode::Decomposition]
    return if decomposition.empty?
    if decomposition =~ /\A<.*>\s*(.*)/
      @decompose_compat = true
      decomposition = $1
    else
      @decompose_compat = false
      @composition = decomposition unless composition_exclusions.include? code
    end
    @decomposition = decomposition
  end

  def decompose_compat?
    @decompose_compat
  end

  attr_reader :code, :type, :value, :title_to_lower, :title_to_upper, :cclass, :decomposition, :composition
  # TODO: SpecialCasing needs this at the moment.  Make it easy to update this
  # field in a copy instead.
  attr_writer :value
end
