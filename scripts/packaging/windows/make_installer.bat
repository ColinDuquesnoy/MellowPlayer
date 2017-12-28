cd ..\..\..

set QTDIR=C:\Qt\5.9\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%;
set BUILD_DIR=build

mkdir %BUILD_DIR%\bin
mkdir %BUILD_DIR%\bin\plugins
xcopy /S /C /Y %BUILD_DIR%\src\main\Release\MellowPlayer.exe %BUILD_DIR%\bin
xcopy /S /E /D /C /Y src\plugins %BUILD_DIR%\bin\plugins

%QTDIR%\bin\windeployqt %BUILD_DIR%\bin\MellowPlayer.exe -qmldir=src

"C:\Program Files (x86)\Inno Setup 5\iscc" /Q %BUILD_DIR%/setup.iss


mkdir dist
xcopy /S /C /Y %BUILD_DIR%\dist\MellowPlayer_Setup.exe dist
