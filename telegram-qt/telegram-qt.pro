
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt
CONFIG  += dll

DEFINES += TELEGRAMQT_LIBRARY

SOURCES = CTelegramCore.cpp \
    CAppInformation.cpp \
    CTelegramDispatcher.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    Utils.cpp \
    CTcpTransport.cpp \
    TelegramNamespace.cpp \
    CTelegramConnection.cpp \
    TLValues.cpp

HEADERS = CTelegramCore.hpp \
    CAppInformation.hpp \
    CTelegramDispatcher.hpp \
    CTelegramStream.hpp \
    CRawStream.hpp \
    Utils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    TLTypes.hpp \
    TLNumbers.hpp \
    crypto-aes.hpp \
    crypto-rsa.hpp \
    CTelegramConnection.hpp \
    TelegramNamespace.hpp \
    telegramqt_export.h \
    TLValues.hpp

LIBS += -lssl -lcrypto
LIBS += -lz
