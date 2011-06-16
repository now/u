# -*- coding: utf-8 -*-

require 'u/build'

class Wide
  def initialize(derived_east_asian_width, types, io = $stdout)
    U::Build::Header.new(io) do
      puts <<EOH
struct unichar_interval {
  unichar first;
  unichar last;
};

static int
unichar_interval_compare(const void *key, const void *element)
{
        unichar c = *(unichar *)key;
        struct unichar_interval *interval = (struct unichar_interval *)element;

        if (c < interval->first)
                return -1;
        else if (c > interval->last)
                return +1;
        else
                return 0;
}
EOH
      io.puts WideTable.new(derived_east_asian_width, types)
    end
  end

private

  class WideTable < U::Build::Header::Table
    def initialize(derived_east_asian_width, types)
      super 'static const struct unichar_interval wide[]'
      wide = derived_east_asian_width.
        select{ |point, width| types.include? width }.
        map{ |point, width| point }.
        sort
      return if wide.empty?
      first = wide[0]
      last = first - 1
      wide.each do |point|
        if point == last + 1
          last += 1
        else
          row first, last
          first = point
          last = first
        end
      end
      row first, last
    end

  private

    def row(first, last)
      self << U::Build::Header::Table::Row.new('%#06x, %#06x' % [first, last])
    end
  end
end

Wide.new(U::Build::Data::DerivedEastAsianWidth.new(ARGV[0]), ARGV[1..-1])
