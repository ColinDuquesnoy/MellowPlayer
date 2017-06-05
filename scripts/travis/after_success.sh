#!/usr/bin/env bash

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    # create AppImage
    ./scripts/packaging/make_appimage.sh /opt/qt59;
    curl --upload-file ./MellowPlayer-x86_64.AppImage https://transfer.sh/MellowPlayer-x86_64.AppImage;

    # measure code coverage
    sudo pip install cpp-coveralls;
    ./scripts/build/linux/build.sh --debug --coverage;
    ./scripts/build/linux/runtests.sh --debug;
    coveralls --exclude /opt --exclude /usr  --exclude tests/ --exclude 3rdparty -E '.*qrc_.*' -E '.*moc_.*'  -E '.*cmake-build-.*' -b 'cmake-build-debug' -r '.';
fi
