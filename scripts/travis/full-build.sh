#!/usr/bin/env bash
#
# - Compile in release mode
# - Run unit tests, integration tests and functional tests
# - Create a package (AppImage on Linux, Dmg on OSX)
#
echo "*************************** Performing a FULL build"

set -e;

mkdir -p build
pushd build;

# build
qbs build -f ../ release projects.MellowPlayer.buildTests:true projects.MellowPlayer.enableCoverage:true

# run all tests
qbs build -f ../ -p tests release

popd;

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # create AppImage
    ./scripts/packaging/make_appimage.sh /opt/qt510;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    # create DMG
    ./scripts/packaging/osx/make_dmg.sh;
fi

