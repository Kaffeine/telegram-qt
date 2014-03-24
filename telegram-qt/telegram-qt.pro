
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt
CONFIG  += dll

SOURCES = CTelegramCore.cpp \
    CTelegramStream.cpp \
    Utils.cpp \
    CTcpTransport.cpp
HEADERS = CTelegramCore.hpp \
    CTelegramStream.hpp \
    Utils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    TLTypes.hpp \
    crypto-rsa.hpp

HEADERS += TLValues.h

LIBS += -lssl
