#!/usr/bin/env bash
#
# Upload code coverage results if this is a commit build and we are on GNU/Linux otherwise upload package artifacts to github if this is a full build.
#
set -e

tagName='Continuous';
if [[ -n "$TRAVIS_TAG" ]]; then
    tagName="$TRAVIS_TAG";
fi


if [[ -n "$TRAVIS_TAG" ]] || [[ "$TRAVIS_BRANCH" == release* ]] || [[ "$TRAVIS_EVENT_TYPE" == "cron" ]] || [[ "$TRAVIS_EVENT_TYPE" == "api" ]]; then
    # Full Build
    if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
        pip install github3.py;
    fi
    # upload build artifacts to github
    python ./scripts/upload.py ${tagName} dist/*;
else
    # Commit Build
    if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
        sudo pip install "cpp-coveralls<0.4.0";
        coveralls --exclude /opt --exclude /usr  --exclude tests/ --exclude 3rdparty -E '.*qrc_.*' -E '.*moc_.*'  -E '.*QQmlObjectListModel.*' -b 'build' -r '.';
    fi
fi
