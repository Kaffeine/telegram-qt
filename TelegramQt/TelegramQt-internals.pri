
INCLUDEPATH += $$PWD

CONFIG += c++11
LIBS += -lssl -lcrypto -lz

LIBS += -lTelegramQt$${QT_MAJOR_VERSION}
