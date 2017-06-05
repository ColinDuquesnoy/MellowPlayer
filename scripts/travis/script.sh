#!/usr/bin/env bash

if [ -n "TRAVIS_TAG" ] || [ "$TRAVIS_BRANCH" == "release" ]; then
    ./full-build.sh;
elif [ "$TRAVIS_EVENT_TYPE" == "cron" ]; then
    ./trigger-full-build.sh;
else
    ./commit-build.sh;
fi
