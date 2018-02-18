cd ..\..
set QTDIR=C:\Qt\5.10.0\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;C:\Qt\Tools\QtCreator\bin;%PATH%
mkdir build
cd build
qbs build -f ../ release projects.MellowPlayer.buildTests:true
