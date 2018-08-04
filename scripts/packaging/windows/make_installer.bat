cd ..\..\..

set QTDIR=C:\Qt\5.11.1\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set INSTALL_DIR=build\release\install-root\

%QTDIR%\bin\windeployqt %INSTALL_DIR%\bin\MellowPlayer.exe -qmldir=src

cd build
qbs build -f ../ -p MellowPlayer_Setup config:release projects.MellowPlayer.buildTests:true

