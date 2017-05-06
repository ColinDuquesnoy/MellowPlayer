#!/usr/bin/env bash

build_type="Release"
build_dir="cmake-build-release"

if [ "$1" == "--debug" ]; then
    build_type="Debug";
    build_dir="cmake-build-debug";
fi

cd $build_dir

if [ "$2" == "--coverage" ]; then
    catchsegv make coverage;
else
    catchsegv ctest -V;
fi
