#!/usr/bin/env bash
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    source ./scripts/travis/linux-setup.sh;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    source ./scripts/travis/osx-setup.sh;
    pip2 install github3.py
    pip2 --version
fi
