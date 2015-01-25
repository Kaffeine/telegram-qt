
QT += core network testlib
TEMPLATE = app

INCLUDEPATH += $$PWD/../telegram-qt

LIBS += -lTelegramQt
LIBS += -lssl
LIBS += -lz
LIBS += -L$$OUT_PWD/../../telegram-qt
