# -*- coding: utf-8 -*-

require 'u/build'
require 'set'

class NormalizationQuickCheck
  QC2I = {
    'Y' => 'U_NORMALIZED_YES',
    'N' => 'U_NORMALIZED_NO',
    'M' => 'U_NORMALIZED_MAYBE'
  }
  def initialize(data, props, io = $stdout)
    U::Build::Header.new(io) do
      t = Set.new
      table = U::Build::Header::Tables::Split.new(data, 'uint8_t', 'normalization_quick_check'){ |i|
        a = '%s%s%s%s' % ['NFKC_QC', 'NFKD_QC', 'NFC_QC', 'NFD_QC'].map{ |e| props[i][e] }
        t << a
        a
      }.to_s
      io.puts 'enum normalization_quick_check_table_values {'
      t.each do |v|
        io.puts "\t%s = (%s << 6) |\n\t\t(%s << 4) |\n\t\t(%s << 2) |\n\t\t%s," %
          ([v] + v.split('').map{ |e| QC2I[e] })
      end
      io.puts '};',
        ''
      io.puts table
    end
  end
end

NormalizationQuickCheck.new Marshal.load(File.open(ARGV[0], 'rb', &:read)), U::Build::Data::DerivedNormalizationProps.new(ARGV[1])
