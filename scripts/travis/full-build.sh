#!/usr/bin/env bash
#
# - Compile in release mode
# - Run unit tests, integration tests and functional tests
# - Create a package (AppImage on Linux, Dmg on OSX)
#
echo "*************************** Performing a FULL build"

set -e;

mkdir -p build;
pushd build;

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=/usr ..;
    make -j2;

    # run all tests
    make test;
    src/main/MellowPlayer --auto-quit-delay 10000 --log-level 1;
    src/main/MellowPlayer --auto-quit-delay 10000 --log-level 1 --service Deezer;

    # create AppImage
    popd;
    ./scripts/packaging/make_appimage.sh /opt/qt59;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON ..;
    make -j2;

    # run all tests
    make test;

    # create DMG
    popd;
    ./scripts/packaging/osx/make_dmg.sh;
fi

