#!/bin/sh
QT_INSTALL_DIR=/opt/qt
COMPILER_TYPE=gcc_64
QT_VERSION_MAJOR=5
QT_VERSION_MINOR=10
QT_VERSION_PATCH=1
QT_VERSION="${QT_VERSION_MAJOR}.${QT_VERSION_MINOR}.${QT_VERSION_PATCH}"
QT_COMPONENT_VERSION=${QT_VERSION_MAJOR}.${QT_VERSION_MAJOR}${QT_VERSION_MINOR}${QT_VERSION_PATCH}

echo Downloading Qt
travis_wait wget  -nv -c https://download.qt.io/archive/qt/$(echo $QT_VERSION |cut -d "." -f-2)/${QT_VERSION}/qt-opensource-linux-x64-${QT_VERSION}.run

echo Installing Qt
sudo mkdir -p ${QT_INSTALL_DIR}
sudo chown $USER ${QT_INSTALL_DIR}
chmod +x qtci/bin/extract-qt-installer
INSTALLER=$PWD/qt-opensource-linux-x64-${QT_VERSION}.run
export QT_CI_PACKAGES=qt.qt${QT_COMPONENT_VERSION}.${COMPILER_TYPE},qt.qt${QT_COMPONENT_VERSION}.qtwebengine,qt.tools.qtcreator
travis_wait qtci/bin/extract-qt-installer $INSTALLER ${QT_INSTALL_DIR}

echo Setting up qbs
export PATH=${QT_INSTALL_DIR}/${QT_VERSION}/gcc_64/bin:${QT_INSTALL_DIR}/Tools/QtCreator/bin:$PATH
QMAKE_PATH=`which qmake`
qbs --version
qbs-setup-toolchains --type gcc /usr/bin/gcc-7 gcc7
qbs config profiles.gcc7.cpp.cCompilerName gcc-7
qbs config profiles.gcc7.cpp.cxxCompilerName g++-7
qbs config profiles.gcc7.cpp.toolchainPrefix ""
qbs-setup-qt ${QMAKE_PATH} qt
qbs config profiles.qt.baseProfile gcc7
qbs config defaultProfile qt
echo "*** qbs config:"
qbs config --list