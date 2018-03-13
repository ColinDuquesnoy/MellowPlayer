@echo off
cd ..\..\build
set QTDIR=C:\Qt\5.10.0\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
qbs build -f ../ -p tests release projects.MellowPlayer.buildTests:true