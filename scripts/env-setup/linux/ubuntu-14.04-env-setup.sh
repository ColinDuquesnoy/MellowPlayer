#!/usr/bin/env bash
# Setup dev environment for Ubuntu 14.04
QT_VERSION=59
QT_VERSION_PATCH=4
sudo apt-add-repository ppa:beineri/opt-qt${QT_VERSION}${QT_VERSION_PATCH}-trusty -y
sudo apt-add-repository ppa:george-edison55/cmake-3.x -y
sudo apt-get update
sudo apt-get install build-essential qt59base qt59declarative qt59quickcontrols2 qt59graphicaleffects qt59svg qt59creator qt59translations mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev --fix-missing -y

source /opt/qt${QT_VERSION}/bin/qt${QT_VERSION}-env.sh;
