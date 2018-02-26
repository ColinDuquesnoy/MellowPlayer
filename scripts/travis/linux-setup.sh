#!/usr/bin/env bash
# Require GCC-7 (from ppa:ubuntu-toolchain/test)

# Install additional packages
sudo apt-get update
sudo apt-get install build-essential libgl1-mesa-dev pkg-config libnotify-dev python --fix-missing -y

# Setup qbs profiles
QMAKE_PATH=`which qmake`
echo ${QMAKE_PATH}
qbs --version
qbs-setup-toolchains --type gcc /usr/bin/gcc-7 gcc7
qbs config profiles.gcc7.cpp.cCompilerName gcc-7
qbs config profiles.gcc7.cpp.cxxCompilerName g++-7
qbs config profiles.gcc7.cpp.toolchainPrefix ""
qbs-setup-qt ${QMAKE_PATH} qt
qbs config profiles.qt.baseProfile gcc7
qbs config defaultProfile qt
echo "*** qbs config:"
qbs config --list
