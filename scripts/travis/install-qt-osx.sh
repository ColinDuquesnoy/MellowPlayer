#!/bin/sh
QT_INSTALL_DIR=/opt/qt
COMPILER_TYPE=clang_64
QT_VERSION_MAJOR=5
QT_VERSION_MINOR=10
QT_VERSION_PATCH=1
QT_VERSION="${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}"
QT_COMPONENT_VERSION=${QT_VERSION_MAJOR}.${QT_VERSION_MAJOR}${QT_VERSION_MINOR}${QT_VERSION_PATCH}

echo Downloading Qt
travis_wait wget  -nv -c https://download.qt.io/archive/qt/$(echo $QT_VERSION |cut -d "." -f-2)/${QT_VERSION}/qt-opensource-mac-x64-${QT_VERSION}.dmg

echo Mounting dmg
INSTALLER_DMG=qt-opensource-mac-x64-${QT_VERSION}.dmg
hdiutil attach -noverify $INSTALLER_DMG

echo Installing Qt
sudo mkdir -p ${QT_INSTALL_DIR}
sudo chown $USER ${QT_INSTALL_DIR}
chmod +x qtci/bin/extract-qt-installer
INSTALLER=/Volumes/qt-opensource-mac-x64-${QT_VERSION}/qt-opensource-mac-x64-${QT_VERSION}.app/Contents/MacOS/qt-opensource-mac-x64-5.10.1
export QT_CI_PACKAGES=qt.qt${QT_COMPONENT_VERSION}.${COMPILER_TYPE},qt.qt${QT_COMPONENT_VERSION}.qtwebengine,qt.tools.qtcreator
travis_wait qtci/bin/extract-qt-installer $INSTALLER ${QT_INSTALL_DIR}

echo Setting up qbs
export PATH=${QT_INSTALL_DIR}/${QT_VERSION}/${COMPILER_TYPE}/bin:${QT_INSTALL_DIR}/Qt\ Creator.app/Contents/MacOS:$PATH
QMAKE_PATH=`which qmake`
qbs --version
qbs-setup-toolchains --detect
qbs-setup-qt ${QMAKE_PATH} qt
qbs config defaultProfile qt
echo "*** qbs config:"
qbs config --list
