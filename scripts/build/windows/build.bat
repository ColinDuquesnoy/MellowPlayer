cd ..\..\..
set QTDIR=C:\Qt\5.8\msvc2015_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
set CMAKE_PREFIX_PATH=%QTDIR%
mkdir build
cd build
cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=TRUE ..
cmake --build . --config Release
