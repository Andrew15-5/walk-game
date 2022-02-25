#!/bin/sh

build() {
  cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON &&
  cmake --build build -j "$(nproc)"
}

cd "$(dirname "$0")" || exit 1

build "$@" || {
  rm -rf build
  build "$@"
}
