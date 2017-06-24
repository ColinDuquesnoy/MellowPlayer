#!/usr/bin/env bash

curl -L -o qt.zip https://www.dropbox.com/s/il5hin8teaf5liu/qt-5.9.0-osx.zip?dl=1
unzip -qq qt.zip
mv clang_64/ qt/
