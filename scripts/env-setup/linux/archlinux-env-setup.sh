#!/usr/bin/env bash

pacman --noconfirm --quiet -Syyu
pacman --noconfirm --quiet -S base-devel qt5-quickcontrols2 qt5-webengine cmake git

curl -L -O https://aur.archlinux.org/cgit/aur.git/snapshot/lcov.tar.gz
tar -xvf lcov.tar.gz
pushd lcov
makepkg -si
popd
