# -*- coding: utf-8 -*-

$:.unshift File.expand_path('../lib', __FILE__)

require 'u/version'

Gem::Specification.new do |s|
  s.name = 'u'
  s.version = U::Version

  s.author = 'Nikolai Weibull'
  s.email = 'now@bitwi.se'
  s.homepage = 'https://github.com/now/u'

  s.description = IO.read(File.expand_path('../README', __FILE__))
  s.summary = s.description[/^[[:alpha:]]+.*?\./]

  s.extensions = %w[ext/u/extconf.rb]

  s.files = Dir['ext/**/{*.{c,h,rb},depend}'] +
    Dir['{lib,test}/**/*.rb'] +
    %w[README Rakefile]

  s.require_paths = %w[ext lib]

  s.add_development_dependency 'lookout', '~> 2.1.0'
  s.add_development_dependency 'yard', '~> 0.6.0'
end
