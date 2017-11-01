TARGET = tst_GeneratorNG

QT += core network testlib
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/../../

SOURCES += $${TARGET}.cpp
SOURCES += $$PWD/../../GeneratorNG.cpp
HEADERS += $$PWD/../../GeneratorNG.hpp
