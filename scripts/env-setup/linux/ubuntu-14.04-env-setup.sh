#!/usr/bin/env bash
# Setup dev environment for Ubuntu 14.04
sudo apt-add-repository ppa:beineri/opt-qt59-trusty -y
sudo apt-add-repository ppa:george-edison55/cmake-3.x -y
sudo apt-get update
sudo apt-get install build-essential qt59base qt59declarative qt59quickcontrols2 qt59graphicaleffects qt59svg qt59creator mesa-common-dev libgl1-mesa-dev pkg-config cmake libnotify-dev --fix-missing -y

source /opt/qt*/bin/qt*-env.sh;
export CXX="g++-7" CC="gcc-7";
