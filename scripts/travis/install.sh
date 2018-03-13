#!/usr/bin/env bash
pushd ./scripts/travis/;
if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    source ./linux-setup.sh;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    source ./install-qt-osx.sh;
    source ./osx-setup.sh;
fi

popd;
