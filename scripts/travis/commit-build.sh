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

# build
qbs build -f ../ config:debug projects.MellowPlayer.buildTests:true projects.MellowPlayer.enableCoverage:true

# run all tests
qbs build -f ../ config:debug -p tests

