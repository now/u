# -*- coding: utf-8 -*-

require 'inventory-rake-1.0'

load File.expand_path('../lib/u-1.0/version.rb', __FILE__)

Inventory::Rake::Tasks.define U::Version, :gem => proc{ |_, s|
  s.author = 'Nikolai Weibull'
  s.email = 'now@bitwi.se'
  s.homepage = 'https://github.com/now/u'
}

Inventory::Rake::Tasks.unless_installing_dependencies do
  require 'lookout-rake-3.0'
  Lookout::Rake::Tasks::Test.new
  Lookout::Rake::Tasks::Test.new :name => :'test:normalize', :files => %w[test/unit/normalize.rb]

  require 'inventory-rake-tasks-yard-1.0'
  Inventory::Rake::Tasks::YARD.new do |t|
    t.files = %w'ext/u/rb_u.c ext/u/rb_u_buffer.c ext/u/rb_u_string.c' + t.files
    t.options += %w'--plugin yard-heuristics-1.0 --plugin yard-value-1.0'
    t.globals[:source_code_url] = 'https://github.com/now/%s/blob/v%s/%%s#L%%d' % [t.inventory.package, t.inventory]
  end
end

file 'TAGS' => U::Version.extensions.map(&:source_files).flatten do
  rm_f 'TAGS'
  sh 'etags %s' % U::Version.extensions.map(&:source_files).flatten.join(' ')
end

# TODO: Move to U::Version::Unicode
UnicodeVersion = '6.2.0'

UnicodeBaseUrl = 'http://www.unicode.org/Public/%s/ucd' % UnicodeVersion
UnicodeAuxiliaryUrl = '%s/auxiliary' % UnicodeBaseUrl
UnicodeExtractedUrl = '%s/extracted' % UnicodeBaseUrl

def through_temporary_file(name)
  tmp = '%s.tmp' % name
  rm([name, tmp], :force => true)
  yield tmp
  mv tmp, name
end

def generate_file(name)
  through_temporary_file name do |tmp|
    yield tmp
    chmod 0444, tmp
  end
end

def data_file(name, url = UnicodeBaseUrl)
  path = 'build/data/%s' % name
  file path do
    mkdir_p File.dirname(path)
    generate_file path do |tmp|
      url_path = '%s/%s' % [url, name]
      rake_output_message 'wget -O%s %s' % [tmp, url_path] if verbose
      require 'open-uri'
      content = open(url_path, &:read)
      File.open(tmp, 'wb') do |f|
        f.write content
      end
    end
  end
end

def data_auxiliary_file(name)
  data_file name, UnicodeAuxiliaryUrl
end

def data_extracted_file(name)
  data_file name, UnicodeExtractedUrl
end

data_file 'BidiMirroring.txt'
data_file 'CaseFolding.txt'
data_file 'CompositionExclusions.txt'
data_file 'LineBreak.txt'
data_file 'NormalizationTest.txt'
data_file 'NormalizationTest.txt'
data_file 'PropList.txt'
data_file 'Scripts.txt'
data_file 'SpecialCasing.txt'
data_file 'UnicodeData.txt'
data_auxiliary_file 'GraphemeBreakProperty.txt'
data_auxiliary_file 'GraphemeBreakTest.txt'
data_auxiliary_file 'WordBreakProperty.txt'
data_auxiliary_file 'WordBreakTest.txt'
data_extracted_file 'DerivedEastAsianWidth.txt'

def generate_data_header(task, *arguments)
  generate_file task.name do |tmp|
    ruby '-w -Ibuild/lib %s > %s' % [[task.prerequisites + arguments].join(' '), tmp]
  end
end

desc 'Generate Unicode data files'
task :data

def data_header(headers, &block)
  block ||= proc{ |t| generate_data_header t }
  headers.each do |path, prerequisites|
    task :data => path
    file path => prerequisites, &block
  end
end

data_header 'ext/u/data/attributes.h' => %w[build/ext/u/data/attributes.rb
                                            build/data/UnicodeData.marshalled
                                            build/data/SpecialCasing.txt]

data_header 'ext/u/data/bidi-mirroring.h' => %w[build/ext/u/data/bidi-mirroring.rb
                                                build/data/BidiMirroring.txt]

data_header 'ext/u/data/line-break.h' => %w[build/ext/u/data/line-break.rb
                                            build/data/UnicodeData.marshalled
                                            build/data/LineBreak.txt]

data_header 'ext/u/data/case-folding.h' => %w[build/ext/u/data/case-folding.rb
                                              build/data/UnicodeData.marshalled
                                              build/data/SpecialCasing.txt
                                              build/data/CaseFolding.txt]

data_header 'ext/u/data/cased.h' => %w[build/ext/u/data/cased.rb
                                       build/data/PropList.txt]

data_header 'ext/u/data/compose.h' => %w[build/ext/u/data/compose.rb
                                         build/data/UnicodeData.marshalled
                                         build/data/CompositionExclusions.txt]

data_header 'build/data/UnicodeData.marshalled' => %w[build/ext/u/data/marshalled.rb
                                                      build/data/UnicodeData.txt]

data_header 'ext/u/data/combining-class.h' => %w[build/ext/u/data/combining-class.rb
                                                 build/data/UnicodeData.marshalled]

data_header 'ext/u/data/constants.h' => %w[build/ext/u/data/constants.rb
                                           build/data/UnicodeData.marshalled] do |t|
  generate_data_header t, UnicodeVersion
end

data_header 'ext/u/data/decompose.h' => %w[build/ext/u/data/decompose.rb
                                           build/data/UnicodeData.marshalled]

data_header 'ext/u/data/script.h' => %w[build/ext/u/data/script.rb
                                        build/data/Scripts.txt]

data_header 'ext/u/data/soft-dotted.h' => %w[build/ext/u/data/soft-dotted.rb
                                             build/data/PropList.txt]

data_header 'ext/u/data/title-table.h' => %w[build/ext/u/data/title-table.rb
                                             build/data/UnicodeData.marshalled]

data_header 'ext/u/data/general-category.h' => %w[build/ext/u/data/general-category.rb
                                                  build/data/UnicodeData.marshalled]

data_header 'ext/u/data/wide.h' => %w[build/ext/u/data/wide.rb
                                      build/data/DerivedEastAsianWidth.txt] do |t|
  generate_data_header t, 'W', 'F'
end

data_header 'ext/u/data/wide-cjk.h' => %w[build/ext/u/data/wide.rb
                                          build/data/DerivedEastAsianWidth.txt] do |t|
  generate_data_header t, 'A'
end

data_header 'ext/u/data/word-break.h' => %w[build/ext/u/data/grapheme-word-break.rb
                                            build/data/UnicodeData.marshalled
                                            build/data/WordBreakProperty.txt] do |t|
  generate_data_header t, 'word'
end

data_header 'ext/u/data/grapheme-break.h' => %w[build/ext/u/data/grapheme-word-break.rb
                                                build/data/UnicodeData.marshalled
                                                build/data/GraphemeBreakProperty.txt] do |t|
  generate_data_header t, 'grapheme'
end

task :test => %w[test/unit/case.rb
                 test/unit/foldcase.rb
                 test/unit/graphemebreak.rb
                 test/unit/wordbreak.rb]

task :'test:normalize' => %w[test/unit/normalize.rb]

file 'test/unit/case.rb' => %w[build/test/unit/case.rb
                               build/data/SpecialCasing.txt
                               build/data/UnicodeData.txt] do |t|
  generate_file t.name do |tmp|
    ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  end
end

file 'test/unit/foldcase.rb' => %w[build/test/unit/foldcase.rb
                                   build/data/CaseFolding.txt] do |t|
  generate_file t.name do |tmp|
    ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  end
end

file 'test/unit/graphemebreak.rb' => %w[build/test/unit/break.rb
                                        build/data/GraphemeBreakTest.txt] do |t|
  generate_file t.name do |tmp|
    ruby '-w -Ilib %s grapheme_clusters > %s' % [t.prerequisites.join(' '), tmp]
  end
end

file 'test/unit/normalize.rb' => %w[build/test/unit/normalize.rb
                                    build/data/NormalizationTest.txt] do |t|
  generate_file t.name do |tmp|
    ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  end
end

file 'test/unit/wordbreak.rb' => %w[build/test/unit/break.rb
                                    build/data/WordBreakTest.txt] do |t|
  generate_file t.name do |tmp|
    ruby '-w -Ilib %s words > %s' % [t.prerequisites.join(' '), tmp]
  end
end
