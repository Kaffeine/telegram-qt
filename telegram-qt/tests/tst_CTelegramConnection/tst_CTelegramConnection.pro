include(../tests.pri)

TARGET = tst_telegramconnection
SOURCES = tst_CTelegramConnection.cpp \
    ../../Utils.cpp \
    ../../CTcpTransport.cpp \
    ../../CTelegramConnection.cpp \
    ../../CTelegramStream.cpp \
    ../../CRawStream.cpp \
    ../../TLValues.cpp \
    CTestConnection.cpp

HEADERS += \
    ../../Utils.hpp \
    ../../CTelegramConnection.hpp \
    ../../CTelegramTransport.hpp \
    ../../CTcpTransport.hpp \
    ../../CTelegramStream.hpp \
    ../../CRawStream.hpp \
    ../../TLValues.hpp \
    CTestConnection.hpp

LIBS += -lz
