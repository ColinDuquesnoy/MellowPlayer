#!/usr/bin/env bash

body='{
"request": {
"branch":"develop"
}}'

curl -s -X POST \
   -H "Content-Type: application/json" \
   -H "Accept: application/json" \
   -H "Travis-API-Version: 3" \
   -H "Authorization: token ${TRAVIS_TOKEN}" \
   -d "$body" \
   https://api.travis-ci.org/repo/ColinDuquesnoy%2FMellowPlayer/requests
