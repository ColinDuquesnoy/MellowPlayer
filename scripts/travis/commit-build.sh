#!/usr/bin/env bash
#
# Compile in debug mode, run unit tests only, measure code coverage and upload results
#
echo "*************************** Performing a COMMIT build"
set -e;

mkdir -p build;
pushd build;

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # build
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON -DCMAKE_INSTALL_PREFIX=/usr ..;
    make;

    # run tests
    ctest -V;

    # upload code coverage results
    popd;
    sudo pip install cpp-coveralls;
    coveralls --exclude /opt --exclude /usr  --exclude tests/ --exclude 3rdparty -E '.*qrc_.*' -E '.*moc_.*'  -E '.*cmake-build-.*' -E '.*QQmlObjectListModel.*' -b 'build' -r '.';
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    # build
    export CMAKE_PREFIX_PATH=$PWD/../qt;
    export QT_PLUGIN_PATH=$PWD/qt/plugins;
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DCMAKE_INSTALL_PREFIX=/usr ..;
    make;

    # run tests
    ctest -V;
fi
