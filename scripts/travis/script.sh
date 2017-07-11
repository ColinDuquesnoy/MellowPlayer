#!/usr/bin/env bash
set -e

if [[ -n "$TRAVIS_TAG" ]] || [[ "$TRAVIS_BRANCH" == release* ]] || [[ "$TRAVIS_EVENT_TYPE" == "cron" ]] || [[ "$TRAVIS_EVENT_TYPE" == "api" ]]; then
    ./scripts/travis/full-build.sh;
else
    ./scripts/travis/commit-build.sh;
fi
