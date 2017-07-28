#!/usr/bin/env bash
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    source ./scripts/env-setup/linux/ubuntu-14.04-env-setup.sh;
    sudo apt-get install python3
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    source ./scripts/env-setup/osx/env-setup.sh;
    pip3 install github3.py
fi
