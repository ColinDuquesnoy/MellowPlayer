#!/usr/bin/env bash
# Require GCC-7 (from ppa:ubuntu-toolchain/test)
# Setup dev environment for Ubuntu 14.04

QT_VERSION_MAJOR=5
QT_VERSION_MINOR=10
QT_VERSION_PATCH=1
PACKAGE_VERSION=${QT_VERSION_MAJOR}${QT_VERSION_MINOR}

# Install Qt from ppa
sudo apt-add-repository ppa:beineri/opt-qt-${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}-trusty -y
sudo apt-get update
sudo apt-get install build-essential qt${PACKAGE_VERSION}base qt${PACKAGE_VERSION}declarative qt${PACKAGE_VERSION}quickcontrols2 qt${PACKAGE_VERSION}graphicaleffects qt${PACKAGE_VERSION}svg qt${PACKAGE_VERSION}translations qt${PACKAGE_VERSION}script qt${PACKAGE_VERSION}tools qt${PACKAGE_VERSION}webengine mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev --fix-missing -y
source /opt/qt${PACKAGE_VERSION}/bin/qt${PACKAGE_VERSION}-env.sh;

# Download a precompiled version of qbs 1.10 (precompiled on trusty)
mkdir qbs-download
pushd qbs-download
wget https://www.dropbox.com/s/t85wczj6fa7ddbe/qbs.tar.gz
tar -xf qbs.tar.gz
sudo cp -R usr/ /
popd
rm -rf qbs-download

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

