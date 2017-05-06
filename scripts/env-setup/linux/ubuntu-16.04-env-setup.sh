#!/usr/bin/env bash
# Setup dev environment for Ubuntu 16.04
apt-get update
apt-get install software-properties-common --fix-missing -y
apt-add-repository ppa:beineri/opt-qt571-xenial -y
apt-get update
apt-get install build-essential qt57base qt57declarative qt57quickcontrols2 qt57graphicaleffects qt57svg qt57creator mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev xvfb --fix-missing -y

# tool for code coverage reporting
tar -xvf 3rdparty/lcov-1.13.tar.gz
pushd lcov-1.13
make PREFIX="/usr" install
popd

source /opt/qt57/bin/qt57-env.sh
