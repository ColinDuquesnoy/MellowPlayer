#!/usr/bin/env bash

rvm install "ruby-2.3.4"
export HOMEBREW_RUBY_PATH="/Users/travis/.rvm/rubies/ruby-2.3.4/bin/ruby"
rvm use 2.3
brew update
brew install qt5
