#!/usr/bin/env bash

if [[ -n "$TRAVIS_TAG" ]] || [[ "$TRAVIS_BRANCH" == release* ]] || [[ "$TRAVIS_EVENT_TYPE" == "cron" ]]; then
    ./scripts/travis/full-build.sh;
else
    ./scripts/travis/commit-build.sh;
fi
