#!/usr/bin/env bash
# Compile in release mode, run all tests and create a package and upload it to transfer.sh
# the built package may be uploaded to a github release if on a deployement build.
echo "*************************** Performing a FULL build"

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  # build and run tests
  ./scripts/build/linux/build.sh;
  ./scripts/build/linux/runtests.sh;
  # create package
  ./scripts/packaging/make_appimage.sh /opt/qt59;
  curl --upload-file ./dist/MellowPlayer-x86_64.AppImage https://transfer.sh/MellowPlayer-x86_64.AppImage;
  echo ""
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  ./scripts/build/osx/build.sh --release;
  ./scripts/build/osx/runtests.sh --release;
  # todo: create dmg image...
fi
