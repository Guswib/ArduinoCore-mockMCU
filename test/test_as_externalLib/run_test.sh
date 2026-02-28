#!/bin/bash

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
echo "Script location: ${SCRIPT_DIR}"

# cmake -G "MinGW Makefiles" -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/build" -D CMAKE_POLICY_VERSION_MINIMUM=3.5 -W no-dev
cmake -G "MinGW Makefiles" -S "$SCRIPT_DIR" -B "$SCRIPT_DIR/build" -W no-dev

cmake --build "$SCRIPT_DIR/build"

"$SCRIPT_DIR/build/UnitTest.exe" 