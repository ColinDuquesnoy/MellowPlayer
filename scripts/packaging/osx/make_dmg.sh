#!/usr/bin/env bash

echo "Copying plugins to .app"

build_dir=build

mkdir -p ${build_dir}/src/main/MellowPlayer.app/Contents/PlugIns/services
mkdir -p ${build_dir}/src/main/MellowPlayer.app/Contents/Resources

cp -R plugins/ ${build_dir}/src/main/MellowPlayer.app/Contents/PlugIns/services
cp scripts/packaging/osx/mellowplayer.icns ${build_dir}/src/main/MellowPlayer.app/Contents/Resources
cp scripts/packaging/osx/Info.plist ${build_dir}/src/main/MellowPlayer.app/Contents

mkdir -p  ${build_dir}/src/main/MellowPlayer.app/Contents/Resources/qml/QtQuick/
cp -R /usr/local/opt/qt/qml/QtQuick/Controls ${build_dir}/src/main/MellowPlayer.app/Contents/Resources/qml/QtQuick/

/usr/local/opt/qt/bin/macdeployqt ${build_dir}/src/main/MellowPlayer.app -dmg -qmldir=$PWD/src -verbose=3

mkdir -p dist
cp ${build_dir}/src/main/MellowPlayer.dmg dist/