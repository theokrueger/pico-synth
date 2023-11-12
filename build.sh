#!/bin/bash
export PICO_SDK_PATH=/opt/pico-sdk/
export PICO_EXTRAS_PATH=/opt/pico-extras/

mkdir -p "build/" && cd "build/"
if [[ "$?" != 0 ]]; then
    echo 'directory error!'
    exit
fi

cmake -DCMAKE_BUILD_TYPE=Release .. && make
if [[ "$?" != 0 ]]; then
    echo 'build failed at make or cmake!'
    exit
fi
