include(../tests.pri)

TARGET = tst_telegramdispatcher
SOURCES = tst_CTelegramDispatcher.cpp \
    CTestDispatcher.cpp \
    ../../Utils.cpp \
    ../../CTcpTransport.cpp \
    ../../CTelegramConnection.cpp \
    ../../CTelegramStream.cpp \
    ../../CTelegramDispatcher.cpp \
    ../../CRawStream.cpp \
    ../../TLValues.cpp

HEADERS += \
    CTestDispatcher.hpp \
    ../../Utils.hpp \
    ../../CTelegramConnection.hpp \
    ../../CTelegramTransport.hpp \
    ../../CTcpTransport.hpp \
    ../../CTelegramStream.hpp \
    ../../CTelegramDispatcher.hpp \
    ../../CRawStream.hpp \
    ../../TLValues.hpp

LIBS += -lz
