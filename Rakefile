# -*- coding: utf-8 -*-

require 'inventory/rake-1.0'

load File.expand_path('../lib/u/version.rb', __FILE__)

Inventory::Rake::Tasks.define U::Version, :gem => proc{ |_, s|
  s.author = 'Nikolai Weibull'
  s.email = 'now@bitwi.se'
  s.homepage = 'https://github.com/now/u'
  # TODO Move to Inventory::Rake::Tasks::Gem.
  s.extensions = U::Version.extensions.map{ |e| e.extconf }
}

Inventory::Rake::Tasks.unless_installing_dependencies do
  require 'lookout/rake-3.0'
  Lookout::Rake::Tasks::Test.new

  require 'inventory/rake/tasks/yard-1.0'
  Inventory::Rake::Tasks::YARD.new do |t|
    t.files = %w'ext/u/rb_u_string.c' + t.files
    t.options += %w'--plugin yard-heuristics-1.0 --plugin yard-value-1.0'
    t.globals[:source_code_url] = 'https://github.com/now/%s/blob/v%s/%%s#L%%d' % [t.inventory.package, t.inventory]
  end

  # TODO Move to inventory-rake.
  class Inventory::Rake::Tasks::Compile
    include Rake::DSL

    def initialize(options = {})
      self.inventory = options.fetch(:inventory, Inventory::Rake::Tasks.inventory)
      yield self if block_given?
      define
    end

    def define
      desc 'Compile extensions' unless Rake::Task.task_defined? :compile
      task :compile

      @inventory.extensions.each do |extension|
        name = :"compile:#{extension}"
        makefile = '%s/Makefile' % extension.path
        ext_so = '%s/%s.%s' % [extension.path,
                               extension.name.delete('-'),
                               RbConfig::CONFIG['DLEXT']]
        lib_so = 'lib/%s/%s' % [@inventory.package_path, File.basename(ext_so)]
        task :compile => name
        task name => [makefile, lib_so]
        file makefile => [extension.extconf, extension.depend] do
          Dir.chdir extension.path do
            ENV['CFLAGS'] = '-Werror' unless ENV['CFLAGS']
            ruby File.basename(extension.extconf)
            sh 'make'
          end
        end
        file ext_so => extension.source_files do
          sh 'make -C %s' % extension.path
        end
        file lib_so => ext_so do
          install ext_so, lib_so
        end
        tags = '%s/TAGS' % extension.path
        file tags => extension.source_files do
          sh 'make -C %s tags' % extension.path
        end
        %w'clean distclean'.each do |rule|
          clean_name = :"#{rule}:#{extension}"
          task :clean => clean_name
          desc 'Clean files build for %s extension' % extension
          task clean_name do
            sh 'make -C %s' % rule
          end
        end
      end

      # TODO :check instead?  Argh, this is a bit complicated
      task :test => :compile if Rake::Task.task_defined? :test
    end

    attr_writer :inventory
  end

  Inventory::Rake::Tasks::Compile.new
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
    task :'compile:u' => path
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
                                           build/data/UnicodeData.txt] do |t|
  generate_data_header t, UnicodeVersion
end

data_header 'ext/u/data/decompose.h' => %w[build/ext/u/data/decompose.rb
                                           build/data/UnicodeData.txt]

data_header 'ext/u/data/script.h' => %w[build/ext/u/data/script.rb
                                        build/data/Scripts.txt]

data_header 'ext/u/data/soft-dotted.h' => %w[build/ext/u/data/soft-dotted.rb
                                             build/data/PropList.txt]

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

file 'test/unit/normalize.rb' => %w[build/test/unit/normalize.rb
                                    build/data/NormalizationTest.txt] do |t|
  generate_file t.name do |tmp|
    ruby '-w -Ilib %s > %s' % [t.prerequisites.join(' '), tmp]
  end
end
