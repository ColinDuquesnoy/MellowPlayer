#!/usr/bin/env bash

echo "Copying plugins to .app"

mkdir -p cmake-build-release/src/MellowPlayer.app/Contents/PlugIns/services
mkdir -p cmake-build-release/src/MellowPlayer.app/Contents/Resources

cp -R plugins/ cmake-build-release/src/MellowPlayer.app/Contents/PlugIns/services
cp scripts/packaging/osx/mellowplayer.icns cmake-build-release/src/MellowPlayer.app/Contents/Resources
cp scripts/packaging/osx/Info.plist cmake-build-release/src/MellowPlayer.app/Contents

$PWD/qt/bin/macdeployqt cmake-build-release/src/MellowPlayer.app -dmg -qmldir=$PWD/lib/MellowPlayer/Presentation/Views

mkdir -p dist
cp cmake-build-release/src/MellowPlayer.dmg dist/