#!/usr/bin/env bash
# Require GCC-7 (from ppa:ubuntu-toolchain/test)
# Setup dev environment for Ubuntu 14.04
QT_VERSION_MAJOR=5
QT_VERSION_MINOR=10
QT_VERSION_PATCH=1
PACKAGE_VERSION=510
sudo apt-add-repository ppa:beineri/opt-qt-${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}-trusty -y
sudo apt-get update
sudo apt-get install build-essential qt${PACKAGE_VERSION}base qt${PACKAGE_VERSION}declarative qt${PACKAGE_VERSION}quickcontrols2 qt${PACKAGE_VERSION}graphicaleffects qt${PACKAGE_VERSION}svg qt${PACKAGE_VERSION}translations qt${PACKAGE_VERSION}script mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev --fix-missing -y

source /opt/qt${PACKAGE_VERSION}/bin/qt${PACKAGE_VERSION}-env.sh;

QBS_VERSION=1.10.1
wget https://download.qt.io/official_releases/qbs/${QBS_VERSION}/qbs-src-${QBS_VERSION}.tar.gz
tar -xf qbs-src-${QBS_VERSION}.tar.gz
pushd qbs-src-${QBS_VERSION}
qmake qbs.pro CONFIG+=Release CONFIG-=qbs_enable_unit_tests
make CC=gcc-7 CXX=g++-7
sudo make install
popd
