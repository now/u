# -*- coding: utf-8 -*-

class U::Build::Header::Tables::Intervals < U::Build::Header::Table
  def initialize(points, name)
    super 'static const struct unichar_interval %s[]' % name
    return if points.empty?
    sorted = points.sort
    first = sorted[0]
    last = first - 1
    sorted.each do |point|
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

  def to_s
    '%s%s' % [<<EOH, super]
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
  end

private

  def row(first, last)
    self << U::Build::Header::Table::Row.new('%#06x, %#06x' % [first, last])
  end
end
