# -*- coding: utf-8 -*-

require 'u/build'

class CaseFolding
  def initialize(casefolding, io = $stdout)
    U::Build::Header.new(io) do
      io.puts CasefoldTable.new(casefolding)
    end
  end

private

  class CasefoldTable < U::Build::Header::Table
    def initialize(casefolding)
      super "/*
 * Table of casefolding cases that can't be derived by lowercasing.
 */
static const struct {
\tuint16_t ch;
\tchar data[#{casefolding.map{ |c| c.to_s.bytesize }.max + 1}];
} casefold_table[]"
      # TODO: Check that this sort_by will be needed.  (Or should be sorted by
      # Casefolds
      casefolding.sort_by{ |c| c.char }.each do |casefold|
        raise RuntimeError,
          'casefold_table.ch field too short; upgrade to uint32_t to fit values beyond 0xffff: %s' %
            casefold.char if
              casefold.char > 0xffff
        self << U::Build::Header::Table::Row.new('%#06x' % casefold.char, '"%s"' % casefold.to_escaped_s)
      end
    end
  end
end

data = Marshal.load(File.open(ARGV[0], 'rb', &:read))
CaseFolding.new(U::Build::Data::CaseFolding.new(data,
                                                U::Build::Data::SpecialCasing.new(data, ARGV[1]),
                                                ARGV[2]))
