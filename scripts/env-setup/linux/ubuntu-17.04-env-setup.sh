#!/usr/bin/env bash
# Setup dev environment for Ubuntu 17.04
apt-get update
apt-get install software-properties-common --fix-missing -y
apt-get install build-essential cmake qtbase5-dev qtdeclarative5-dev qtwebengine5-dev qtquickcontrols2-5-dev qtpositioning5-dev qtbase5-private-dev qtdeclarative5-qtquick2-streamingService qml-module-qtquick-* qml-module-qtwebengine
