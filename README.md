TelegramQt [![Build Status](https://travis-ci.org/Kaffeine/telegram-qt.svg?branch=master)](https://travis-ci.org/Kaffeine/telegram-qt)
=======================

Telegram binding for Qt

Requirements
============

* CMake-2.8.12+
* Qt 5.5.0+

Installation
============

    tar -xvf telegram-qt-x.y.z.tar.bz2
    mkdir telegram-qt-build
    cd telegram-qt-build
    cmake ../telegram-qt-x.y.z -DCMAKE_INSTALL_PREFIX=/usr
    make -j4
    make install

Default CMake installation prefix is /usr/local. Use CMAKE_INSTALL_PREFIX parameter to set a different prefix (e.g. -DCMAKE_INSTALL_PREFIX=/usr).

License
=======

This application is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License,
or (at your option) any later version.
