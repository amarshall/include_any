require 'bundler'
Bundler.setup

require 'bundler/gem_tasks'
require 'rake/extensiontask'
require 'rspec/core/rake_task'

Rake::ExtensionTask.new('include_any') do |config|
  config.lib_dir = 'lib/include_any'
end
RSpec::Core::RakeTask.new(:spec)

task :default => :spec
task :spec => :compile
