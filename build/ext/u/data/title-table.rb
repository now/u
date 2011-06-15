# -*- coding: utf-8 -*-

require 'u/build'

class TitleTable
  def initialize(data, name, io = $stdout)
    U::Build::Header.new(name, io) do
      io.puts TitleTable.new(data)
    end
  end

private

  class TitleTable < U::Build::Header::Table
    def initialize(data)
      super 'static const unichar title_table[][3]'
      # TODO: Add #code to Entry and use #select on data here.
      data.each_with_index do |entry, code|
        next unless entry.title_to_lower
        self << U::Build::Header::Table::Row.new(*[code, entry.title_to_upper, entry.title_to_lower].map{ |i| '%#06x' % i })
      end
    end
  end
end

TitleTable.new(U::Build::Data::Unicode.new(ARGV[0]), ARGV[1])
