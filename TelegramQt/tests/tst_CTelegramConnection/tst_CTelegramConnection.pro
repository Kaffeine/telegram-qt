include(../tests.pri)

TARGET = tst_telegramconnection
SOURCES = tst_CTelegramConnection.cpp \
    CTestConnection.cpp

HEADERS += \
    CTestConnection.hpp

LIBS += -lz
