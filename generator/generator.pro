QT = core network
TEMPLATE = app

TARGET = generator
CONFIG += console c++11
CONFIG -= app_bundle

CONFIG += link_pkgconfig
PKGCONFIG += zlib

SOURCES = Generator.cpp main.cpp
HEADERS = Generator.hpp

OTHER_FILES = *.tl
