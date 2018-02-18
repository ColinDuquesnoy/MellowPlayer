set QTDIR=C:\Qt\5.10.0\msvc2017_64
set PATH=%QTDIR%\bin;%QTDIR%\lib;C:\Qt\Tools\QtCreator\bin;%PATH%
qbs --version
qbs-setup-toolchains --detect
qbs-setup-qt --detect
qbs config profiles.qt-5-10-0.baseProfile MSVC2017-x64
qbs config defaultProfile qt-5-10-0
echo "qbs config:"
qbs config --list
