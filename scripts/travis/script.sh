#!/usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  ./scripts/build/linux/build.sh --release;
  ./scripts/build/linux/runtests.sh --release;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  ./scripts/build/osx/build.sh --release;
  ./scripts/build/osx/runtests.sh --release;
fi
