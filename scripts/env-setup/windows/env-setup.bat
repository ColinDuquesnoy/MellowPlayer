cd ..\..\..
set QTDIR=C:\Qt\5.9\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%

git clone https://github.com/KDE/extra-cmake-modules.git
cd extra-cmake-modules
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=%QTDIR% ..
cmake --build . --config Release
cmake --build . --config Release --target install
cd ..\..

git clone https://github.com/KDE/snorenotify.git
cd snorenotify
git checkout tags/v0.7.0
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_INSTALL_PREFIX=%QTDIR% ..
cmake --build . --config Release
cmake --build . --config Release --target install
cd ..\..
