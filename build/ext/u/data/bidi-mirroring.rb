# -*- coding: utf-8 -*-

require 'u/build'

class BidiMirroring
  def initialize(bidi_mirroring, io = $stdout)
    U::Build::Header.new(io) do
      io.puts BidiMirroringTable.new(bidi_mirroring)
    end
  end

private

  class BidiMirroringTable < U::Build::Header::Table
    def initialize(bidi_mirroring)
      super "static const struct {
\tuint32_t ch;
\tuint32_t mirrored_ch;
} bidi_mirroring_table[]"
      bidi_mirroring.each do |bidi_mirror|
        self << U::Build::Header::Table::Row.new('%#06x' % bidi_mirror.char, '%#06x' % bidi_mirror.mirrored)
      end
    end
  end
end

BidiMirroring.new(U::Build::Data::BidiMirroring.new(ARGV[0]))
