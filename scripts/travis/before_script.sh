#!/usr/bin/env bash

# Setup qbs
qbs --version
qbs setup-toolchains --detect
qbs setup-qt --detect
profile="$(qbs config --list profiles | grep "qt-5-.*baseProfile" | cut -d'.' -f 2)"
echo "Default profile: ${profile}"
qbs config defaultProfile ${profile}

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  export DISPLAY=:99.0;
  sh -e /etc/init.d/xvfb start;
  sleep 3;
fi
