QT += core network
CONFIG += c++11

TEMPLATE = app

LIBS += -L$$OUT_PWD/../TelegramQt
include(../TelegramQt/TelegramQt-internals.pri)

TARGET = testApp

SOURCES += main.cpp
include(server.pri)

OTHER_FILES += CMakeLists.txt
