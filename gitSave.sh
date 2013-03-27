#!/bin/bash


# TIMESTAMP=$(date +%m%d%y%H%M%S)

source gitMood.log

git add .
git commit -m "Gitdive_autolog | MOOD:$(MOOD) | COFFEE:$(COFFEE) | LOCATION:$(LOCATION)"