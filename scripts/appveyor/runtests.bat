@echo off
cd ..\..\build
set QTDIR=C:\Qt\5.11.0\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
qbs build -f ../ -p tests config:release projects.MellowPlayer.buildTests:true
