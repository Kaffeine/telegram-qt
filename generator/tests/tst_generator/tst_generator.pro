TARGET = tst_generator

QT += core network testlib
TEMPLATE = app
CONFIG += c++11

CONFIG += link_pkgconfig
PKGCONFIG += zlib

INCLUDEPATH += $$PWD/../../

SOURCES += $${TARGET}.cpp
SOURCES += $$PWD/../../Generator.cpp
HEADERS += $$PWD/../../Generator.hpp
