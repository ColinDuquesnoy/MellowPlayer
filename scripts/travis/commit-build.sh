#!/usr/bin/env bash
#
# - Compile in debug mode
# - Run unit and integration tests only
# - Measure code coverage
#
echo "*************************** Performing a COMMIT build"
set -e;

mkdir -p build;
pushd build;

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON -DCMAKE_INSTALL_PREFIX=/usr ..;
    make -j2;

    # run tests
    pushd src/tests;
    catchsegv ctest --output-on-failure;
    popd;
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..;
    make -j2;

    # run tests
    pushd src/tests;
    ctest --output-on-failure;
    popd;
fi
