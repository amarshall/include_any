# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'include_any/version'

Gem::Specification.new do |gem|
  gem.name          = "include_any"
  gem.version       = IncludeAny::VERSION
  gem.authors       = ["Andrew Marshall"]
  gem.email         = ["andrew@johnandrewmarshall.com"]
  gem.description   = %q{Allows including any object}
  gem.summary       = %q{Allows including any object}
  gem.homepage      = "http://johnandrewmarshall.com/projects/include_any"
  gem.license       = 'MIT'

  gem.files         = `git ls-files`.split($/)
  gem.executables   = gem.files.grep(%r{^bin/}).map{ |f| File.basename(f) }
  gem.test_files    = gem.files.grep(%r{^(test|spec|features)/})
  gem.require_paths = ["lib"]
  gem.extensions    = ['ext/include_any/extconf.rb']

  gem.add_development_dependency 'bundler', '>= 1.2'
  gem.add_development_dependency 'rake'
  gem.add_development_dependency 'rake-compiler'
  gem.add_development_dependency 'rspec', '>= 2.0.0'
end
