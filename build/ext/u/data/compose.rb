# -*- coding: utf-8 -*-

require 'u/build'

class Compose
  def initialize(data, composition_exclusions, io = $stdout)
    compositions = Compositions.new(data, composition_exclusions)
    firsts = Firsts.new(compositions)
    seconds = Seconds.new(compositions, firsts)
    first_singletons, second_singletons, reversals = Singletons.create(compositions, firsts, seconds)
    values = Values.new(firsts, first_singletons, seconds, second_singletons)
    U::Build::Header.new(io) do
      io.puts <<EOH
#define COMPOSE_FIRST_START #{values.first_start}
#define COMPOSE_FIRST_SINGLE_START #{values.first_single_start}
#define COMPOSE_SECOND_START #{values.second_start}
#define COMPOSE_SECOND_SINGLE_START #{values.second_single_start}
#define COMPOSE_TABLE_LAST #{values.last / 256}
EOH
      io.puts Table.new(0, values.last, 'uint16_t compose_data', 'compose_table'){ |i|
        values.include?(i) ? values[i].to_s : '0'
      }
      io.puts SingletonTable.new(first_singletons, 'compose_first_single')
      io.puts SingletonTable.new(second_singletons, 'compose_second_single')
      io.puts ComposeArray.new(firsts, seconds, reversals)
    end
  end

private

  class Table
    def initialize(first, last, data, part1)
      rows = U::Build::Header::Tables::Split::Rows.new(0, last){ |c| yield(c) }
      @data = U::Build::Header::Tables::Split::Data.new(data, rows)
      @part1 = Part1.new(part1, first, last, rows, 0)
    end

    def to_s
      "%s\n%s\n" % [@data, @part1]
    end

    class Part1 < U::Build::Header::Tables::Split::Part1
      class << self
        def last_page
          'COMPOSE_TABLE_LAST'
        end
      end
    end
  end

  class Compositions
    include Enumerable

    def initialize(data, composition_exclusions)
      @entries = []
      data.each_with_index do |entry, code|
        next if composition_exclusions.include? code or
          entry.decomposition.length < 2 or
          not entry.decomposition.canonical? or
          data[code].cclass != Starter or
          data[entry.decomposition.first].cclass != Starter
        raise RuntimeError,
          'decomposition of %04X contains more than 2 elements: %d' %
            [code, entry.decomposition.length] unless
              entry.decomposition.length == 2
        @entries << [entry.decomposition.entries, code]
      end
    end

    def each_with_index
      @entries.each do |parts, code|
        yield parts[0], parts[1], code
      end
      self
    end

    def each
      @entries.each do |parts, code|
        yield parts
      end
      self
    end

  private

    Starter = 0
  end

  class Commons
    include Enumerable

    def initialize(compositions)
      @entries = Hash.new(0)
      compositions.each do |first, second|
        selection = yield(first, second) and @entries[selection] += 1
      end
    end

    def each
      @entries.keys.sort.each do |code|
        yield code if @entries[code] > 1
      end
      self
    end
  end

  class Firsts
    include Enumerable

    def initialize(compositions)
      self.commons = Commons.new(compositions){ |first, second| first }
    end

    def each
      @entries.each do |code, entry|
        yield code, entry
      end
      self
    end

    def size
      @entries.length
    end

    def include?(code)
      @entries.include?(code)
    end

    def [](code)
      @entries[code]
    end

  protected

    def commons=(commons)
      @entries = {}
      commons.each do |code|
        @entries[code] = @entries.size
      end
      commons
    end
  end

  class Seconds < Firsts
    def initialize(compositions, firsts)
      self.commons = Commons.new(compositions){ |first, second|
        second if firsts.include? first
      }
    end
  end

  class Singletons
    include Enumerable

    class << self
      def create(compositions, firsts, seconds)
        first_singletons = []
        second_singletons = []
        reversals = Reversals.new
        compositions.each_with_index do |first, second, code|
          if firsts.include? first and seconds.include? second
            reversals[firsts[first], seconds[second]] = code
          elsif not firsts.include? first
            first_singletons << Singleton.new(first, second, code)
          else
            second_singletons << Singleton.new(second, first, code)
          end
        end
        [new(first_singletons), new(second_singletons), reversals]
      end
    end

    def initialize(entries)
      @entries = entries.sort_by{ |a| a.first }
    end

    def each
      @entries.each do |entry|
        yield entry
      end
      self
    end

    def size
      @entries.size
    end
  end

  class Singleton
    def initialize(first, second, code)
      @first, @second, @code = first, second, code
    end

    attr_reader :first, :second, :code
  end

  # TODO: Can this be simplified?
  class Reversals
    def initialize
      @entries = {}
    end

    def []=(first, second, code)
      @entries[build(first, second)] = code
    end

    def include?(first, second)
      @entries.include? build(first, second)
    end

    def [](first, second)
      @entries[build(first, second)]
    end

  private

    def build(first, second)
      '%s|%s' % [first, second]
    end
  end

  class Values
    def initialize(firsts, first_singletons, seconds, second_singletons)
      @values = {}
      @total = 1

      @first_start = @total
      @first_single_start = @total += set(firsts).size
      @second_start = @total += singletons(first_singletons).size
      @second_single_start = @total += set(seconds).size
      singletons second_singletons
    end

    def last
      @values.keys.max
    end

    attr_reader :first_start, :first_single_start, :second_start, :second_single_start

    def include?(code)
      @values.include?(code)
    end

    def [](code)
      @values[code]
    end

  protected

    def []=(code, value)
      @values[code] = value + @total
    end

  private

    def set(fs)
      fs.each do |code, value|
        self[code] = value
      end
    end

    def singletons(singletons)
      singletons.each_with_index do |singleton, code|
        self[singleton.first] = code
      end
    end
  end

  class SingletonTable < U::Build::Header::Table
    def initialize(singletons, name)
      super 'static const uint16_t %s[][2]' % name
      singletons.each do |singleton|
        @declaration = 'static const unichar %s[][2]' % name if singleton.second > 0xffff or singleton.code > 0xffff
        self << U::Build::Header::Table::Row.new(*[singleton.second, singleton.code].map{ |c| '%#06x' % c })
      end
    end
  end

  class ComposeArray < U::Build::Header::Table
    def initialize(firsts, seconds, reversals)
      @firsts, @seconds, @reversals = firsts, seconds, reversals
      super 'static const uint16_t compose_array[%d][%d]' % [firsts.size, seconds.size]
      firsts.size.times do |i|
        row = U::Build::Header::Table::Row.new
        seconds.size.times do |j|
          row <<
            if reversals.include? i, j
              raise RuntimeError,
                'compose_array table field too short; upgrade to unichar to fit values beyond 0xffff: %04X' %
                  reversals[i, j] if
                    reversals[i, j] > 0xffff
              '%#06x' % reversals[i, j]
            else
              '     0'
            end
        end
        self << row
      end
    end
  end
end

Compose.new(Marshal.load(File.open(ARGV[0], 'rb', &:read)),
            U::Build::Data::CompositionExclusions.new(ARGV[1]))
