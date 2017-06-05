#!/usr/bin/env bash

# go back to root directory
cd ../..

# change QT_DIR to point to your qt installation
QT_DIR=/home/colin/Qt/5.9/gcc_64/
QMAKE_PATH=$QT_DIR/bin

# override path so that the correct qmake version is used
PATH=$QMAKE_PATH:$PATH
echo "checking qmake"
qmake -v

echo "downloading linuxdeployqt"
wget -c "https://github.com/probonopd/linuxdeployqt/releases/download/continuous/linuxdeployqt-continuous-x86_64.AppImage"
chmod a+x linuxdeployqt*.AppImage

mkdir -p appdir

# build in release mode and install into appdir
pushd build
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=FALSE -DCMAKE_PREFIX_PATH=/home/colin/Qt/5.9/gcc_64/ ..
make -j$(nproc)
make DESTDIR=../appdir install
popd

export LD_LIBRARY_PATH=$QT_DIR/lib
ldd appdir/usr/bin/MellowPlayer

./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -bundle-non-qt-libs -qmldir=../
cp $QT_DIR/plugins/imageformats/libqsvg.so ./appdir/usr/plugins/imageformats/
./linuxdeployqt*.AppImage ./appdir/usr/share/applications/*.desktop -appimage
