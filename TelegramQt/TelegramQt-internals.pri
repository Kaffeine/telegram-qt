
INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/Crypto

CONFIG += c++11
LIBS += -lssl -lcrypto -lz

LIBS += -lTelegramQt$${QT_MAJOR_VERSION}
