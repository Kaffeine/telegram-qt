QT = core network
TEMPLATE = app

TARGET = generator
CONFIG += console c++11
CONFIG -= app_bundle

SOURCES = Generator.cpp main.cpp
HEADERS = Generator.hpp

OTHER_FILES = *.tl
