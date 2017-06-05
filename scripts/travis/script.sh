#!/usr/bin/env bash

if [ -n "$TRAVIS_TAG" ] || [ "$TRAVIS_BRANCH" == "release" ]; then
    ./scripts/travis/full-build.sh;
elif [ "$TRAVIS_EVENT_TYPE" == "cron" ]; then
    ./scripts/travis/trigger-full-build.sh;
else
    ./scripts/travis/commit-build.sh;
fi
