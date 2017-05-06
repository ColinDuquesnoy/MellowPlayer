cd ..\..\..\build\Publish\bin
set QTDIR=C:\Qt\5.8\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
MellowPlayer.UnitTests.exe
MellowPlayer.IntegrationTests.exe

