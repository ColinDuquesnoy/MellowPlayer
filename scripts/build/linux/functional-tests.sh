#!/usr/bin/env bash
set -e
build_type="Release"
build_dir="cmake-build-release"

if [ "$1" == "--debug" ]; then
    build_type="Debug";
    build_dir="cmake-build-debug";
fi

cd $build_dir

cd src

./MellowPlayer --auto-quit-delay 10000 --log-level 1
./MellowPlayer --auto-quit-delay 10000 --log-level 1 --service Deezer
