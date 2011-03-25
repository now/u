# -*- coding: utf-8 -*-

class U::Build::Data::CompositionExclusions
  def initialize(path)
    @exclusions = {}
    File.open(path, 'rb') do |file|
      file.each_line do |line|
        next if line =~ /\A(?:#|\s*\Z)/
        @exclusions[line.chomp.sub(/\A\s*(.*?)\s*(#.*)?\Z/, '\\1').hex] = true
      end
    end
  end

  def include?(code)
    @exclusions.include? code
  end
end
