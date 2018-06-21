
QT += core network testlib
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/../server

LIBS += -L$$OUT_PWD/../../TelegramQt

include(../TelegramQt/TelegramQt-internals.pri)
include(../server/server.pri)
