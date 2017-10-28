
QT += core network testlib
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += $$PWD/..

LIBS += -lssl -lcrypto

LIBS += -L$$OUT_PWD/../../../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}
