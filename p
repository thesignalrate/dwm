#!/bin/bash
[ -f "config.h" ] && rm config.h
cp config.def.h config.h
git a
git c $1
git p
