#!/bin/bash

if [ ! -f platform.txt ]; then
  echo Launch this script from the root core folder as ./extras/package.sh
  exit 2
fi

if [ ! -d ../ArduinoCore-API ]; then
  git clone git@github.com:arduino/ArduinoCore-API.git ../ArduinoCore-API
fi


VERSION=`cat platform.txt | grep "version=" | cut -f2 -d"="`
echo $VERSION
