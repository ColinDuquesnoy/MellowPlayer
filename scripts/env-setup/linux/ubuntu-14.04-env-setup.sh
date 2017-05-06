#!/usr/bin/env bash
# Setup dev environment for Ubuntu 14.04
sudo apt-add-repository ppa:beineri/opt-qt58-trusty -y
sudo apt-add-repository ppa:george-edison55/cmake-3.x -y
apt-get update 
apt-get install build-essential qt58base qt58declarative qt58quickcontrols2 qt58graphicaleffects qt58svg qt58creator mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev --fix-missing -y

tar -xvf 3rdparty/lcov-1.13.tar.gz
pushd lcov-1.13
make PREFIX="/usr" install
popd
