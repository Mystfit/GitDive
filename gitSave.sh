#!/bin/bash

TIMESTAMP=$(date +%m%d%y%H%M%S)

git add .
git commit -m "${TIMESTAMP}--Gitdive autolog"