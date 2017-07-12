#!/usr/bin/env bash
set -e

# On Linux, compile in debug mode, run tests and measure coverage
# On OSX, compile in release mode and run all tests
echo "*************************** Performing a COMMIT build"

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  sudo pip install cpp-coveralls;
  ./scripts/build/linux/build.sh --debug --coverage;
  catchsegv ./scripts/build/linux/runtests.sh --debug;
  ./scripts/build/functional-tests.sh --debug;
  coveralls --exclude /opt --exclude /usr  --exclude tests/ --exclude 3rdparty -E '.*qrc_.*' -E '.*moc_.*'  -E '.*cmake-build-.*' -E '.*QQmlObjectListModel.*' -b 'cmake-build-debug' -r '.';
fi

if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  ./scripts/build/osx/build.sh --release;
  ./scripts/build/osx/runtests.sh --release;
  ./scripts/build/functional-tests.sh --release;
fi
