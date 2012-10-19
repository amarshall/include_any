require 'bundler'
Bundler.setup

require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rspec/core/rake_task'

Rake::ExtensionTask.new('include_any')
RSpec::Core::RakeTask.new(:spec)

task :default => :spec
task :spec => :compile
