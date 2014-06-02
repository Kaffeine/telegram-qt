
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt
CONFIG  += dll

SOURCES = CTelegramCore.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    Utils.cpp \
    CTcpTransport.cpp \
    CTelegramConnection.cpp
HEADERS = CTelegramCore.hpp \
    CTelegramStream.hpp \
    CRawStream.hpp \
    Utils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    TLTypes.hpp \
    crypto-aes.hpp \
    crypto-rsa.hpp \
    SDcInfo.hpp \
    CTelegramConnection.hpp

HEADERS += TLValues.h

LIBS += -lssl
