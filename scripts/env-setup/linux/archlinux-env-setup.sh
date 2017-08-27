#!/usr/bin/env bash

pacman --noconfirm --quiet -Syyu
pacman --noconfirm --quiet -S base-devel qt5-quickcontrols2 qt5-quickcontrols qt5-graphicaleffects qt5-translations qt5-webengine qt5-svg cmake git xorg-server-xvfb libnotify
