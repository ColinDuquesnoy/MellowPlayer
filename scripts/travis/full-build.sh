#!/usr/bin/env bash
#
# Compile in release mode, run all tests, create a package and upload it to github.
#
echo "*************************** Performing a FULL build"

set -e;

mkdir -p build;
pushd build;

tagName='Continuous';
if [[ -n "$TRAVIS_TAG" ]]; then
    tagName="$TRAVIS_TAG";
fi

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DBUILD_INTEGRATION_TESTS=ON -DCMAKE_INSTALL_PREFIX=/usr ..;
    make;

    # run all tests
    ctest -V;
    src/MellowPlayer --auto-quit-delay 10000 --log-level 1;
    src/MellowPlayer --auto-quit-delay 10000 --log-level 1 --service Deezer;

    # create AppImage
    ../scripts/packaging/make_appimage.sh /opt/qt59;
    pip install github3.py;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    # build
    export CMAKE_PREFIX_PATH=$PWD/../qt;
    cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON -DBUILD_INTEGRATION_TESTS=ON ..;
    make;

    # run all tests
    ctest -V;

    # create DMG
    ../scripts/packaging/osx/make_dmg.sh;
fi

# upload build artifacts to github
python ../scripts/upload.py ${tagName} dist/*;
