#!/usr/bin/env bash
#
# This script takes one argument: the path to the qt installation directory.
#
# This script should be run from the root source directory:
#
#   ./scripts/packaging/make_appimage.sh PATH_TO_QT_INSTALL_DIR
#
# E.g., on openSUSE: ./scripts/packaging/make_appimage.sh /usr/lib64/qt5
#

# override path so that the correct qmake version is used
QT_DIR=$1
QMAKE_PATH=${QT_DIR}/bin
PATH=${QMAKE_PATH}:$PATH
export LD_LIBRARY_PATH=${QT_DIR}/lib
echo "checking qmake"
qmake -v

# download linuxdployqt
echo "downloading linuxdeployqt"
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage

mkdir -p build
mkdir -p appdir
pushd build
qbs resolve -f ../ release projects.MellowPlayer.staticLibCpp:true qbs.installRoot:../appdir/usr
qbs build -f ../ release projects.MellowPlayer.staticLibCpp:true qbs.installRoot:../appdir/usr
qbs --clean-install-root config:release
popd

ldd appdir/usr/bin/MellowPlayer

./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -qmldir=../
cp ${QT_DIR}/plugins/imageformats/libqsvg.so ./appdir/usr/plugins/imageformats/
cp -R ${QT_DIR}/qml/QtQuick/Controls ./appdir/usr/qml/QtQuick/
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -appimage

chmod +x MellowPlayer-x86_64.AppImage
mkdir -p dist
mv MellowPlayer-x86_64.AppImage dist
