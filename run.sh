#!/bin/sh

cd "$(dirname "$0")" || exit 1

./build.sh &&
bin/walk-game
