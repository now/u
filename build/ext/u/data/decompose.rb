# -*- coding: utf-8 -*-

require 'u/build'

class Decompose
  NotPresentOffset = 1 << 16 - 1

  def initialize(data, io = $stdout)
    # TODO: Defines should be made with a list, but we can’t match formatting
    # quite yet, so wait until we have stable tests.
    U::Build::Header.new(io) do
      io.puts <<EOD
#define UNICODE_NOT_PRESENT_OFFSET UINT16_MAX
EOD
      io.puts U::Build::Header::Tables::Split.
        new(0, data.last_char_part1_i, data.last,
            'static const uint8_t cclass_data[][256]',
            'static const int16_t combining_class_table_part1[%d]' %
            data.pages_before_e0000,
            'static const int16_t combining_class_table_part2[768]'){ |i|
        data[i].cclass
      }
      io.puts DecompositionTable.new(data)
    end
  end

private

  class DecompositionTable < U::Build::Header::Table
    def initialize(data)
      super "static const struct {
\tunichar ch;
\tuint16_t canon_offset;
\tuint16_t compat_offset;
} decomp_table[]"
      @data = data
      @decomp_offsets = {}
      @decomp_string = ''
      @decomp_string_offset = 0
      0.upto(data.last) do |i|
        next if data[i].decomposition.empty?
        canon_decomp = data[i].decomposition.canonical? ? make_decomp(i, false) : nil
        compat_decomp = make_decomp(i, true)
        compat_decomp = nil if canon_decomp and compat_decomp == canon_decomp
        canon_offset = handle_decomp(canon_decomp)
        compat_offset = handle_decomp(compat_decomp)
        raise RuntimeError,
          'decomposition string offset beyond not-present offset, upgrade value: offset: %d, max: %d' %
            [@decomp_string_offset, NotPresentOffset] if
              @decomp_string_offset > NotPresentOffset
        self << U::Build::Header::Table::Row.new('%#06x' % i, canon_offset.to_s, compat_offset.to_s)
      end
    end

    def to_s
      "%s\nstatic const char decomp_expansion_string[] = %s;" % [super, @decomp_string]
    end

  private

    def make_decomp(point, compatible)
      expand_decomp(point, compatible).flatten.pack('U*')
    end

    def expand_decomp(point, compatible)
      @data[point].decomposition.map{ |part|
        if not @data[part].decomposition.empty? and
            (compatible or @data[part].decomposition.canonical?)
          expand_decomp(part, compatible)
        else
          part
        end
      }
    end

    def handle_decomp(decomp)
      return 'UNICODE_NOT_PRESENT_OFFSET' unless decomp
      return @decomp_offsets[decomp] if @decomp_offsets.include? decomp
      @decomp_offsets[decomp] = @decomp_string_offset
      @decomp_string << "\n  \"%s\\0\" /* offset %d */" %
        [escape(decomp), @decomp_string_offset]
      result = @decomp_string_offset
      @decomp_string_offset += decomp.length + 1
      result
    end

    def escape(decomp)
      decomp.unpack('H*')[0].gsub(/(.{2})/, '\\x\1')
    end
  end
end

Decompose.new(U::Build::Data::Unicode.new(ARGV[0]))
