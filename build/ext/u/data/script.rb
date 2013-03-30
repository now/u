# -*- coding: utf-8 -*-

require 'u/build'

class Script
  EasyRange = 0x0000...0x2000

  class << self
    def name(script)
      'U_SCRIPT_%s' % script.upcase
    end
  end

  def initialize(scripts, io = $stdout)
    U::Build::Header.new(io) do
      io.puts <<EOH
#define EASY_SCRIPTS_RANGE #{EasyRange.end}
EOH
      io.puts EasyTable.new(scripts)
      io.puts Table.new(scripts)
    end
  end

private

  class EasyTable < U::Build::Header::Table
    def initialize(scripts)
      super 'static const unsigned char script_easy_table[%d]' % EasyRange.end
      row = Row.new
      EasyRange.each do |i|
        row << Script.name(scripts[i])
      end
      self << row
    end

  private

    class Row < U::Build::Header::Table::Row
    private

      def multi_limit
        72
      end

      def multi_format
        single_format
      end

      def multi_joiner
        ",\n\t"
      end

      def single_format
        "\t%s"
      end
    end
  end

  class Table < U::Build::Header::Table
    def initialize(scripts)
      super "static const struct {
\tunichar start;
\tuint16_t chars;
\tuint16_t script;
} script_table[]"
      sorted = scripts.select{ |point, _script| point >= EasyRange.end }.sort
      first = sorted[0][0]
      last = first - 1
      current = sorted[0][1]
      sorted.each do |point, script|
        if point == last + 1 and script == current
          last += 1
        else
          row first, last, current
          first = point
          last = first
          current = script
        end
      end
      row first, last, current
    end

  private

    def row(first, last, script)
      self << U::Build::Header::Table::Row.new('%#06x, %5d, %s' % [first, last - first + 1, Script.name(script)])
    end
  end
end

Script.new(U::Build::Data::Scripts.new(ARGV[0]))
