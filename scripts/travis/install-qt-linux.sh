#!/bin/sh
chmod +x qtci/bin/extract-qt-installer

COMPILER_TYPE=gcc_64
QT_VERSION_MAJOR=5
QT_VERSION_MINOR=10
QT_VERSION_PATCH=1
QT_VERSION="${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}"
QT_COMPONENT_VERSION=${QT_VERSION_MAJOR}.${QT_VERSION_MAJOR}${QT_VERSION_MINOR}${QT_VERSION_PATCH}

export QT_CI_PACKAGES=qt.qt${QT_COMPONENT_VERSION}.${COMPILER_TYPE},qt.qt${QT_COMPONENT_VERSION}.qtwebengine,qt.tools.qtcreator

echo Downloading Qt
wget  -nv -c https://download.qt.io/archive/qt/$(echo $QT_VERSION |cut -d "." -f-2)/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run
INSTALLER=$PWD/qt-opensource-linux-x64-${QT_VERSION}.run

echo Installing Qt
sudo mkdir -p /opt/qt
sudo chown $USER /opt/qt
qtci/bin/extract-qt-installer $INSTALLER /opt/qt

export PATH=/opt/qt/${QT_VERSION}/gcc_64/bin:/opt/qt/Tools/QtCreator/bin:$PATH
