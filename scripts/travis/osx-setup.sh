#!/usr/bin/env bash

brew install qt5 qbs python
pip2 install github3.py
pip2 --version

# Setup qbs profiles
QMAKE_PATH=`which qmake`
echo ${QMAKE_PATH}
qbs --version
qbs-setup-toolchains --detect
qbs-setup-qt ${QMAKE_PATH} qt
qbs config defaultProfile qt
echo "*** qbs config:"
qbs config --list
