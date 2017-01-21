QT = core network
TEMPLATE = app

TARGET = generator-ng
CONFIG   += console c++11
CONFIG   -= app_bundle

SOURCES = GeneratorNG.cpp main.cpp
HEADERS = GeneratorNG.hpp

OTHER_FILES = *.tl
