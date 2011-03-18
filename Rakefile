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
  'utf-8'
].map{ |e| File.join('ext/encoding/character', e) }.each do |extension|
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
      File.open('Makefile', 'a') do |f|
        f.puts <<EOF
Makefile: extconf.rb

TAGS:
	@echo Running ‘ctags’ on source files…
	@ctags -f $@ -I UNUSED,HIDDEN,_ $(SRCS)

tags: TAGS

.PHONY: tags
EOF
      end
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

CLEAN.include ["ext/**/{*.{o,so,#{Config::CONFIG['DLEXT']}},TAGS}"]
CLOBBER.include ['ext/**/Makefile']
