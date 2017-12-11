TARGET = tst_Generator

QT += core network testlib
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/../../

SOURCES += $${TARGET}.cpp
SOURCES += $$PWD/../../Generator.cpp
HEADERS += $$PWD/../../Generator.hpp
