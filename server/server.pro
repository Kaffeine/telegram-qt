QT = core network
CONFIG += c++11

TEMPLATE = app
TARGET = TelegramQtServer
VERSION = 0.2.0

include(../options.pri)

LIBS += -L$$OUT_PWD/../TelegramQt
include(../TelegramQt/TelegramQt-internals.pri)

SOURCES += main.cpp
include(server.pri)

OTHER_FILES += CMakeLists.txt
