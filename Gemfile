# frozen_string_literal: true

source 'https://rubygems.org'

# Hello! This is where you manage which Jekyll version is used to run.
# When you want to use a different version, change it below, save the
# file and run `bundle install`. Run Jekyll with `bundle exec`, like so:
#
#     bundle exec jekyll serve
#
# This will help ensure the proper Jekyll version is running.
# Happy Jekylling!
gem 'jekyll', '~> 3.8.5'

group :development do
  # Check resulting HTML for dead links and other issues
  gem 'html-proofer', require: false

  # Allow running this with rake (especially for rake check)
  gem 'rake', require: false

  # Verify good coding practices in Ruby files
  gem 'rubocop', require: false
end

# This is the default theme for new Jekyll sites. You may change this to anything you like.
gem 'minima', '~> 2.0'

# If you want to use GitHub Pages, remove the 'gem 'jekyll'' above and
# uncomment the line below. To upgrade, run `bundle update github-pages`.
# gem 'github-pages', group: :jekyll_plugins

# If you have any plugins, put them here!
group :jekyll_plugins do
  gem 'jekyll-feed', '~> 0.6'
end

# Windows does not include zoneinfo files, so bundle the tzinfo-data gem
gem 'tzinfo-data', platforms: [:mingw, :mswin, :x64_mingw, :jruby]

# Needed by Nokogiri sometimes
gem 'pkg-config', '~> 1.1'

# Performance-booster for watching directories on Windows
gem 'wdm', '~> 0.1.0' if Gem.win_platform?

# Pinning this for now since macOS + default Ruby needs this
# Please use rbenv to pick Ruby versions; the next Jekyll release
# will not work with macOS's Ruby 2.3
gem 'ffi', '= 1.10.0'
