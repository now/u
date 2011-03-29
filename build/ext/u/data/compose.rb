# -*- coding: utf-8 -*-

require 'u/build'

class Compose
  def initialize(data, composition_exclusions, name, io = $stdout)
    compositions = Compositions.new(data, composition_exclusions)
    firsts = Firsts.new(compositions)
    seconds = Seconds.new(compositions, firsts)
    first_singletons, second_singletons, reversals = Singletons.create(compositions, firsts, seconds)
    values = Values.new(firsts, first_singletons, seconds, second_singletons)
    U::Build::Header.new(name, io) do
      io.puts <<EOH
#define COMPOSE_FIRST_START #{values.first_start}
#define COMPOSE_FIRST_SINGLE_START #{values.first_single_start}
#define COMPOSE_SECOND_START #{values.second_start}
#define COMPOSE_SECOND_SINGLE_START #{values.second_single_start}
#define COMPOSE_TABLE_LAST #{values.last / 256}
EOH
      U::Build::Header::Table.
        new(0, values.last, values.last, io,
            'static const uint16_t compose_data[][256]',
            'static const int16_t compose_table[COMPOSE_TABLE_LAST + 1]') do |i|
        # TODO: Why #to_s?
        values.include?(i) ? values[i].to_s : '0'
      end
      SingletonTable.new first_singletons, 'compose_first_single'
      SingletonTable.new second_singletons, 'compose_second_single'
      ComposeArray.new firsts, seconds, reversals
    end
  end

private

  class Compositions
    include Enumerable

    def initialize(data, composition_exclusions)
      @entries = []
      data.each_with_index do |entry, code|
        next if composition_exclusions.include? code or
          entry.decomposition.length < 2 or
          not entry.decomposition.canonical? or
          data[entry.decomposition.first].cclass != Starter
        raise RuntimeError,
          'decomposition of %04X contains more than 2 elements: %d' %
            [code, entry.decomposition.length] unless entry.decomposition.length == 2
        @entries << [entry.decomposition.entries, code]
      end
    end

    def each_with_index
      @entries.each do |parts, code|
        yield parts, code
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

    # TODO: Move this to cclass
    Starter = '0'.freeze
  end

  class Firsts
    include Enumerable

    def initialize(compositions)
      entries = Hash.new(0)
      compositions.each do |first, second|
        entries[first] += 1
      end
      @entries, @size = enumerate_ordered(entries)
    end

    def each
      @entries.each do |code, entry|
        yield code, entry
      end
      self
    end

    def size
      # TODO: Is @size and @entries.length the same
      @size
    end

    def include?(code)
      @entries.include?(code)
    end

    def [](code)
      @entries[code]
    end

  private

    # TODO: Can we create a new one here instead of using #delete?
    def enumerate_ordered(entries)
      n = 0
      entries.keys.sort.each do |code|
        if entries[code] == 1
          entries.delete(code)
          next
        end
        entries[code] = n
        n += 1
      end
      [entries, n]
    end
  end

  class Seconds < Firsts
    def initialize(compositions, firsts)
      entries = Hash.new(0)
      compositions.each do |first, second|
        entries[second] += 1 if firsts.include? first
      end
      @entries, @size = enumerate_ordered(entries)
    end
  end

  class Singletons
    include Enumerable

    class << self
      def create(compositions, firsts, seconds)
        first_singletons = []
        second_singletons = []
        reversals = Reversals.new
        compositions.each_with_index do |composition, code|
          if firsts.include? composition[0] and seconds.include? composition[1]
            reversals[firsts[composition[0]], seconds[composition[1]]] = code
          elsif not firsts.include? composition[0]
            first_singletons << Singleton.new(composition[0], composition[1], code)
          else
            second_singletons << Singleton.new(composition[1], composition[0], code)
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
      @last = 0
      @total = 1

      @first_start = @total
      @first_single_start = @total += set(firsts).size
      @second_start = @total += singletons(first_singletons).size
      @second_single_start = @total += set(seconds).size
      singletons second_singletons
    end

    attr_reader :first_start, :first_single_start, :second_start, :second_single_start, :last

    def include?(code)
      @values.include?(code)
    end

    def [](code)
      @values[code]
    end

  protected

    def last=(last)
      @last = last if last > @last
    end

    def []=(code, value)
      @values[code] = value + @total
    end

  private

    def set(fs)
      fs.each do |code, value|
        self[code] = value
        self.last = code
      end
    end

    def singletons(singletons)
      singletons.each_with_index do |singleton, code|
        self[singleton.first] = code
        self.last = code
      end
    end
  end

  class SingletonTable
    def initialize(singletons, name)
      printf "\n\nstatic const uint16_t %s[][2] = {\n", name
      singletons.each_with_index do |singleton, i|
        raise RuntimeError,
          '%s table field too short; upgrade to unichar to fit values beyond 0xffff: %p' %
            [name, singleton] if
              singleton.second > 0xffff or singleton.code > 0xffff
	printf "\t{ %#06x, %#06x },\n", singleton.second, singleton.code
      end
      puts "};"
    end
  end

  class ComposeArray
    def initialize(firsts, seconds, reversals)
      @firsts, @seconds, @reversals = firsts, seconds, reversals
      printf "\n\nstatic const uint16_t compose_array[%d][%d] = {\n", firsts.size, seconds.size
      firsts.size.times do |i|
        row(i)
      end
      puts "};\n"
    end

  private

    def row(i)
      print "\t{\n\t\t"
      column = 16
      @seconds.size.times do |j|
        if column + 8 > 79
          print "\n\t\t"
          column = 16
        end
        cell(i, j)
        column += 8
      end
      puts "\n\t},\n"
    end

    def cell(i, j)
      if @reversals.include? i, j
        raise RuntimeError,
          'compose_array table field too short; upgrade to unichar to fit values beyond 0xffff: %d' %
            @reversals[i, j] if @reversals[i, j] > 0xffff
        printf '0x%04x, ', @reversals[i, j]
      else
        print '     0, '
      end
    end
  end
end

Compose.new(U::Build::Data::Unicode.new(ARGV[0]),
            U::Build::Data::CompositionExclusions.new(ARGV[1]),
            ARGV[2])
