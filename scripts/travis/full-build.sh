#!/usr/bin/env bash
#
# - Compile in release mode
# - Run unit tests, integration tests and functional tests
# - Create a packag (AppImage on Linux, Dmg on OSX)
#
echo "*************************** Performing a FULL build"

set -e;

mkdir -p build;
pushd build;

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DBUILD_INTEGRATION_TESTS=ON -DCMAKE_INSTALL_PREFIX=/usr ..;
    make;

    # run all tests
    ctest --output-on-failure;
    src/MellowPlayer --auto-quit-delay 10000 --log-level 1;
    src/MellowPlayer --auto-quit-delay 10000 --log-level 1 --service Deezer;

    # create AppImage
    popd;
    ./scripts/packaging/make_appimage.sh /opt/qt59;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    # build
    export CMAKE_PREFIX_PATH=$PWD/../qt;
    export QT_PLUGIN_PATH=$PWD/../qt/plugins;
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DBUILD_INTEGRATION_TESTS=ON -DBUILD_INTEGRATION_TESTS=ON ..;
    make;

    # run all tests
    ctest --output-on-failure;

    # create DMG
    popd;
    ./scripts/packaging/osx/make_dmg.sh;
fi

