# -*- coding: utf-8 -*-

require 'u/build'

class Attributes
  def initialize(data, special_casing, io = $stdout)
    U::Build::Header.new(io) do
      io.puts U::Build::Header::Tables::Split.new(data, 'uint32_t', 'attr'){ |i|
        special_casing.include?(i) ?
          '0x%07x' % (0x1000000 + special_casing[i].offset) :
          '0x%04x' % (data[i].value or 0)
      }
      io.puts SpecialCaseTable.new(special_casing)
    end
  end

private

  class SpecialCaseTable < U::Build::Header::Table
    def initialize(special_casing)
      super '/*
 * Table of special cases for case conversion; each record contains
 * First, the best single character mapping to lowercase if Lu,
 * and to uppercase if Ll, followed by the output mapping for the two cases
 * other than the case of the codepoint, in the order Ll, Lu, Lt, encoded in
 * UTF-8, separated and terminated by a NUL character.
 */
static const char special_case_table[]'
      content = []
      special_casing.each do |special_case|
        content << (%( "%s\\0" /* offset %d */) % [special_case.to_escaped_s, special_case.offset])
      end
      self << content.join("\n")
    end
  end
end

data = Marshal.load(File.open(ARGV[0], 'rb', &:read))
Attributes.new(data, U::Build::Data::SpecialCasing.new(data, ARGV[1]))
