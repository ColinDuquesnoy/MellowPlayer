#!/usr/bin/env bash

pacman --noconfirm --quiet -Syyu
pacman --noconfirm --quiet -S base-devel qt5-quickcontrols2 qt5-webengine qt5-svg cmake git xorg-server-xvfb

tar -xvf 3rdparty/lcov-1.13.tar.gz
pushd lcov-1.13
make PREFIX="/usr" install
popd
