#!/bin/sh
INSTALL_ROOT=$1

echo Install TelegramQt server to $INSTALL_ROOT

DESTDIR=$INSTALL_ROOT cmake -DCOMPONENT=Runtime -P cmake_install.cmake
