cd ..\..\build\src\tests
set QTDIR=C:\Qt\5.9\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%

ctest --output-on-failure -C Release
