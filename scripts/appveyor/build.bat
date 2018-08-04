cd ..\..
set QTDIR=C:\Qt\5.11.1\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
mkdir build
cd build
qbs --version
qbs build -f ../ config:release projects.MellowPlayer.buildTests:true
