#!/bin/bash
[ -f "config.h" ] && rm config.h
cp config.def.h config.h
git add .
git commit -m "$1"
git push origin master
