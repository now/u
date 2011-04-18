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

task :extensions => %w[ext/u/data/break.h]
file 'ext/u/data/break.h' => %w[build/ext/u/data/break.rb
                                build/data/UnicodeData.txt
                                build/data/LineBreak.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ibuild/lib %s %s %s > %s' % [t.prerequisites.join(' '), t.name, UnicodeVersion, tmp]
  chmod 0444, tmp
  mv tmp, t.name
end

task :extensions => %w[ext/u/data/character-tables.h]
file 'ext/u/data/character-tables.h' => %w[build/ext/u/data/character-tables.rb
                                           build/data/UnicodeData.txt
                                           build/data/SpecialCasing.txt
                                           build/data/CaseFolding.txt
                                           build/data/BidiMirroring.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ibuild/lib %s %s %s > %s' % [t.prerequisites.join(' '), t.name, UnicodeVersion, tmp]
  chmod 0444, tmp
  mv tmp, t.name
end

task :extensions => %w[ext/u/data/compose.h]
file 'ext/u/data/compose.h' => %w[build/ext/u/data/compose.rb
                                  build/data/UnicodeData.txt
                                  build/data/CompositionExclusions.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ibuild/lib %s %s > %s' % [t.prerequisites.join(' '), t.name, tmp]
  chmod 0444, tmp
  mv tmp, t.name
end

task :extensions => %w[ext/u/data/decompose.h]
file 'ext/u/data/decompose.h' => %w[build/ext/u/data/decompose.rb
                                    build/data/UnicodeData.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ibuild/lib %s %s > %s' % [t.prerequisites.join(' '), t.name, tmp]
  chmod 0444, tmp
  mv tmp, t.name
end

CLEAN.include ["ext/**/{*.{o,so,#{Config::CONFIG['DLEXT']}},TAGS}"]
CLOBBER.include ['ext/**/Makefile']

task :test => %w[test/unit/case.rb test/unit/foldcase.rb] # test/unit/normalize.rb]

file 'test/unit/case.rb' => %w[build/test/unit/case.rb
                               build/data/SpecialCasing.txt
                               build/data/UnicodeData.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  chmod 0444, tmp
  mv tmp, t.name
end

file 'test/unit/foldcase.rb' => %w[build/test/unit/foldcase.rb
                                   build/data/CaseFolding.txt] do |t|
  tmp = '%s.tmp' % t.name
  rm([t.name, tmp], :force => true)
  ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  chmod 0444, tmp
  mv tmp, t.name
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
