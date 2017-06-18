cd ..\..\..
set QTDIR=C:\Qt\5.9\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%

%QTDIR%/bin/windeployqt build/src/MellowPlayer.exe
