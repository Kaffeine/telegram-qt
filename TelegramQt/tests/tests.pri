
QT += core network testlib
TEMPLATE = app

INCLUDEPATH += $$PWD/..

LIBS += -lssl -lcrypto

LIBS += -L$$OUT_PWD/../../../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}
