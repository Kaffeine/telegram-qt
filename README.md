TelegramQt [![Build Status](https://travis-ci.org/Kaffeine/telegram-qt.svg?branch=master)](https://travis-ci.org/Kaffeine/telegram-qt)
=======================

Telegram binding for Qt

Requirements
============

* CMake-2.8.12+ or QMake
* Qt4 or Qt5

Installation
============

    git clone https://github.com/Kaffeine/telegram-qt.git

or

    tar -xf telegram-qt-0.1.0.tar.bz2

    mkdir telegram-qt-build
    cd telegram-qt-build
    
The library supports build with CMake and QMake build systems, so the next command would be

    cmake ../telegram-qt

or

    qmake ../telegram-qt

Information about CMake build:
* By default CMake looks for the Qt5 build. You can pass USE_QT4 option (-DUSE_QT4=true) to process Qt4 build.
* Default installation prefix is /usr/local. Use CMAKE_INSTALL_PREFIX parameter to set a different prefix (-DCMAKE_INSTALL_PREFIX=/usr).

<!-- markdown "code after list" workaround -->

Compilation:

    make -j4
    make install

License
=======

This application is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License,
or (at your option) any later version.
