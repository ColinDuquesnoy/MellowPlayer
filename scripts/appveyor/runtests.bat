@echo off
cd ..\..\build
set QTDIR=C:\Qt\5.10.0\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;C:\Qt\Tools\QtCreator\bin;%PATH%
qbs build -f ../ -p tests release projects.MellowPlayer.buildTests:true
