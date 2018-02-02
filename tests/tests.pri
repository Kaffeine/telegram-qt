
QT += core network testlib
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/../TelegramQt
INCLUDEPATH += $$PWD/../server

LIBS += -lssl -lcrypto

LIBS += -L$$OUT_PWD/../../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}

include($$PWD/../server/server.pri)
