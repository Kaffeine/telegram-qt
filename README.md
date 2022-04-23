TelegramQt [![](https://github.com/Kaffeine/telegram-qt/workflows/Build/badge.svg)](https://github.com/Kaffeine/telegram-qt/actions?query=workflow%3ABuild+event%3Apush+branch%3Amaster)
=======================

TelegramQt provides C++ API for developing custom Telegram clients and servers.
The project is inspired by Qt and QXmpp with some ideas from Telepathy.
TelegramQt focuses on the best possible developer experience.

See also README.md in the 'server' directory.

Requirements
============

* CMake 3.6+
* Qt 5.6+
* OpenSSL
* ZLib
* A C++11 compliant compiler

Building
========

Build from command line:

    mkdir build
    cd build
    cmake ..
    cmake --build .

Installing
==========

Install from command line (after building):

    cmake --build . --target install

Default CMake installation prefix is `/usr/local`. Use CMAKE_INSTALL_PREFIX
parameter to set a different prefix (e.g. `-DCMAKE_INSTALL_PREFIX=/usr`).



License
=======

This application is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License,
or (at your option) any later version.
