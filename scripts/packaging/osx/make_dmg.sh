#!/usr/bin/env bash

echo "Copying plugins to .app"

mkdir -p build/src/MellowPlayer.app/Contents/PlugIns/services
mkdir -p build/src/MellowPlayer.app/Contents/Resources

cp -R plugins/ build/src/MellowPlayer.app/Contents/PlugIns/services
cp scripts/packaging/osx/mellowplayer.icns build/src/MellowPlayer.app/Contents/Resources
cp scripts/packaging/osx/Info.plist build/src/MellowPlayer.app/Contents

$PWD/qt/bin/macdeployqt build/src/MellowPlayer.app -dmg -qmldir=$PWD/lib/MellowPlayer/Presentation/Views

mkdir -p dist
cp build/src/MellowPlayer.dmg dist/