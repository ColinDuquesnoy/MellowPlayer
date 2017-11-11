#!/usr/bin/env bash
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    source ./scripts/env-setup/linux/ubuntu-14.04-env-setup.sh;
    sudo apt-get install python
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    source ./scripts/env-setup/osx/env-setup.sh;
    pip install github3.py
fi

export CXX="g++-7" CC="gcc-7";
