#!/bin/bash


# TIMESTAMP=$(date +%m%d%y%H%M%S)

source gitMood.sh

git add .
git add -u
git commit --quiet -m "Gitdive_autolog | MOOD:\"$MOOD\" | COFFEE:$COFFEE | LOCATION:\"$LOCATION\""