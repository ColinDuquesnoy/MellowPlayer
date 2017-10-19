#!/usr/bin/env bash
# Setup dev environment for Ubuntu 17.10
apt-get update
apt-get install software-properties-common --fix-missing -y
apt-get install build-essential cmake qtbase5-dev qtdeclarative5-dev qtwebengine5-dev qtquickcontrols2-5-dev qtpositioning5-dev qtbase5-private-dev qtdeclarative5-qtquick2-plugin qml-module-qtquick-* qml-module-qtwebengine libqt5svg5-dev qttools5-dev-tools qttranslations5-l10n libnotify-dev qml-module-qt-labs-platform qtdeclarative5-models-plugin qml-module-qt-labs-settings qml-module-qt-labs-folderlistmodel
