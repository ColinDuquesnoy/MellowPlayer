#!/usr/bin/env bash
export CMAKE_PREFIX_PATH=/usr/local/opt/qt5
build_type="Release"
build_dir="cmake-build-release"

if [ "$1" == "--debug" ]; then
    build_type="Debug";
    build_dir="cmake-build-debug";
fi

mkdir -p $build_dir
pushd $build_dir
cmake -DCMAKE_BUILD_TYPE=$build_type ..
if [ "$2" == "--coverage" ]; then
    cmake -DCMAKE_BUILD_TYPE=$build_type -DENABLE_COVERAGE=1 ..;
fi

make
