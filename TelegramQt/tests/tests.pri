
QT += core network testlib
TEMPLATE = app

LIBS += -L$$OUT_PWD/../../../TelegramQt

include(../TelegramQt-internals.pri)
