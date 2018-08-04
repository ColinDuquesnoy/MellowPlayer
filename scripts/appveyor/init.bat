set QTDIR=C:\Qt\5.11.1\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;%PATH%
qbs --version
qbs-setup-toolchains --detect
qbs-setup-qt --detect
qbs config profiles.qt-5-11-1.baseProfile MSVC2017-x64
qbs config defaultProfile qt-5-11-1
echo "qbs config:"
qbs config --list
