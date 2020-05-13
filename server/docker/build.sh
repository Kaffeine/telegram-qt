#!/bin/sh
echo Building TelegramQt server

SOURCE_DIR=/work/source
INSTALL_PREFIX=/usr

cmake \
    -DBUILD_SERVER=TRUE \
    -DBUILD_TESTS=TRUE \
    -DEXPORT_INTERNAL_API=TRUE \
    -DBUILD_QML_IMPORT=FALSE \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX \
    -DCMAKE_VERBOSE_MAKEFILE=TRUE \
    -G Ninja \
    "$SOURCE_DIR" || exit 1

cmake --build .
cmake -DCOMPONENT=Runtime -P cmake_install.cmake
