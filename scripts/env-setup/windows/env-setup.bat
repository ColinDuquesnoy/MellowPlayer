cd ..\..\..
set QTDIR=C:\Qt\5.8\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%

git clone https://github.com/KDE/extra-cmake-modules.git
cd extra-cmake-modules
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=%QTDIR% ..
cmake --build . --config Release
cmake --build . --config Release --target install
cd ..\..

git clone hhttps://github.com/KDE/snorenotify.git
cd snorenotify
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=%QTDIR% ..
cmake --build . --config Release
cmake --build . --config Release --target install
cd ..\..
