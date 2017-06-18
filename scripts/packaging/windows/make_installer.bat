cd ..\..\..

set QTDIR=C:\Qt\5.9\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set BUILD_DIR=build

mkdir %BUILD_DIR%\bin
mkdir %BUILD_DIR%\bin\plugins
xcopy /S /C /Y %BUILD_DIR%\src\Release\MellowPlayer.exe %BUILD_DIR%\bin
xcopy /S /E /D /C /Y plugins %BUILD_DIR%\bin\plugins

%QTDIR%\bin\windeployqt %BUILD_DIR%\bin\MellowPlayer.exe -qmldir=lib/MellowPlayer/Presentation

iscc /Q %BUILD_DIR%/setup.iss


mkdir dist
xcopy /S /C /Y %BUILD_DIR%\dist\MellowPlayer_Setup.exe dist
