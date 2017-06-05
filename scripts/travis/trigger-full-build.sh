#!/usr/bin/env bash
# Upon each run, this script will delete any pre-existing release and tag with the name "continuous" and create a
# new one, triggering a full build on both appveyor and travis-ci.
echo "*************************** Triggering a FULL build"

# todo use github API to delete pre-existing continuous tag and create a new one.
