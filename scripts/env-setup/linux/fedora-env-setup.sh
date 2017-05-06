#!/usr/bin/env bash

dnf -y --quiet update
dnf -y --quiet install qt5-qtquickcontrols2-devel qt5-qtwebengine-devel qt5-svg-devel gcc-c++ cmake git lcov findutils libnotify-devel
