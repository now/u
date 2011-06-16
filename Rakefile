require 'lookout/rake/tasks'
require 'rake/clean'
require 'yard'

Lookout::Rake::Tasks::Test.new
Lookout::Rake::Tasks::Gem.new
Lookout::Rake::Tasks::Tags.new
YARD::Rake::YardocTask.new

task :test => :extensions

desc 'Build all C-based extensions'
task :extensions
[
  'u'
].map{ |e| File.join('ext', e) }.each do |extension|
  makefile = File.join(extension, 'Makefile')
  so = File.join(extension, File.basename(extension).delete('-') + '.' + Config::CONFIG['DLEXT'])
  tags = File.join(extension, 'TAGS')

  task :extensions => [makefile, so]

  begin
    sources = IO.read(makefile).grep(/^\s*SRCS/).first.sub(/^\s*SRCS\s*=\s*/, "").split(' ')
  rescue
    Dir.chdir(extension) do
      sources = FileList['*.c'].to_a
    end
  end

  file makefile => ['extconf.rb', 'depend'].map{ |tail| File.join(extension, tail) } do
    Dir.chdir(extension) do
      ruby 'extconf.rb'
      sh 'make'
    end
  end

  extension_sources = sources.map{ |source| File.join(extension, source) }

  file so => extension_sources do
    sh 'make -C %s' % extension
    # TODO: Perhaps copying the ‘so’ to “lib” could save us some trouble with
    # how libraries are loaded.
  end

  file tags => extension_sources do
    sh 'make -C %s tags' % extension
  end
end

# TODO: Move to U::Version::Unicode
UnicodeVersion = '6.0.0'

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

def generate_data_header(task, *arguments)
  generate_file task.name do |tmp|
    ruby '-w -Ibuild/lib %s > %s' % [[task.prerequisites + arguments].join(' '), tmp]
  end
end

def data_header(headers, &block)
  block ||= proc{ |t| generate_data_header t }
  headers.each do |path, prerequisites|
    task :extensions => path
    file path => prerequisites, &block
  end
end

data_header 'ext/u/data/attributes.h' => %w[build/ext/u/data/attributes.rb
                                            build/data/UnicodeData.txt
                                            build/data/SpecialCasing.txt]

data_header 'ext/u/data/bidi-mirroring.h' => %w[build/ext/u/data/bidi-mirroring.rb
                                                build/data/BidiMirroring.txt]

data_header 'ext/u/data/break.h' => %w[build/ext/u/data/break.rb
                                       build/data/UnicodeData.txt
                                       build/data/LineBreak.txt]

data_header 'ext/u/data/case-folding.h' => %w[build/ext/u/data/case-folding.rb
                                              build/data/UnicodeData.txt
                                              build/data/SpecialCasing.txt
                                              build/data/CaseFolding.txt]
data_header 'ext/u/data/compose.h' => %w[build/ext/u/data/compose.rb
                                         build/data/UnicodeData.txt
                                         build/data/CompositionExclusions.txt]

data_header 'ext/u/data/constants.h' => %w[build/ext/u/data/constants.rb
                                           build/data/UnicodeData.txt] do |t|
  generate_data_header t, UnicodeVersion
end

data_header 'ext/u/data/decompose.h' => %w[build/ext/u/data/decompose.rb
                                           build/data/UnicodeData.txt]

data_header 'ext/u/data/title-table.h' => %w[build/ext/u/data/title-table.rb
                                             build/data/UnicodeData.txt]

data_header 'ext/u/data/types.h' => %w[build/ext/u/data/types.rb
                                       build/data/UnicodeData.txt]

data_header 'ext/u/data/wide.h' => %w[build/ext/u/data/wide.rb
                                      build/data/DerivedEastAsianWidth.txt] do |t|
  generate_data_header t, 'W', 'F'
end

data_header 'ext/u/data/wide-cjk.h' => %w[build/ext/u/data/wide.rb
                                          build/data/DerivedEastAsianWidth.txt] do |t|
  generate_data_header t, 'A'
end

CLEAN.include ["ext/**/{*.{o,so,#{Config::CONFIG['DLEXT']}},TAGS}"]
CLOBBER.include ['ext/**/Makefile']

task :test => %w[test/unit/case.rb test/unit/foldcase.rb] # test/unit/normalize.rb]

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

=begin
file 'test/unit/normalize.rb' => %w[build/test/unit/normalize.rb
                                    build/data/NormalizationTest.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  chmod 0444, tmp
  mv tmp, t.name
end
=end
