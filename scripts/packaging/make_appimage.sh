#!/usr/bin/env bash
#
# This script takes one argument: the path to the qt installation directory.
#
# This script should be run from the root source directory:
#
#   ./scripts/packaging/make_appimage.sh PATH_TO_QT_INSTALL_DIR
#

# override path so that the correct qmake version is used
QT_DIR=$1
QMAKE_PATH=$QT_DIR/bin
PATH=$QMAKE_PATH:$PATH
export LD_LIBRARY_PATH=$QT_DIR/lib
echo "checking qmake"
qmake -v

# download linuxdployqt
echo "downloading linuxdeployqt"
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage

# build in release mode and install into appdir
mkdir -p appdir
mkdir -p cmake-build-release
pushd cmake-build-release
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=FALSE -DCMAKE_PREFIX_PATH=/home/colin/Qt/5.9/gcc_64/ ..
make -j$(nproc)
make DESTDIR=../appdir install
VERSION="$(cat CMakeCache.txt | grep MELLOWPLAYER_VERSION:STRING= | cut -d "=" -f2)"
popd

ldd appdir/usr/bin/MellowPlayer

./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -qmldir=../
cp $QT_DIR/plugins/imageformats/libqsvg.so ./appdir/usr/plugins/imageformats/
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -appimage

chmod +x MellowPlayer-x86_64.AppImage
