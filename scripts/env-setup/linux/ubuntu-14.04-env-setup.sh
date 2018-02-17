#!/usr/bin/env bash
# Setup dev environment for Ubuntu 14.04
QT_VERSION_MAJOR=5
QT_VERSION_MINOR=10
QT_VERSION_PATCH=1
PACKAGE_VERSION=510
sudo apt-add-repository ppa:beineri/opt-qt-${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}-trusty -y
sudo apt-get update
sudo apt-get install build-essential qt${PACKAGE_VERSION}base qt${PACKAGE_VERSION}declarative qt${PACKAGE_VERSION}quickcontrols2 qt${PACKAGE_VERSION}graphicaleffects qt${PACKAGE_VERSION}svg qt${PACKAGE_VERSION}creator qt${PACKAGE_VERSION}translations mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev --fix-missing -y

source /opt/qt${PACKAGE_VERSION}/bin/qt${PACKAGE_VERSION}-env.sh;
