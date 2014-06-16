
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt
CONFIG  += dll

DEFINES += TELEGRAMQT_LIBRARY

SOURCES = CTelegramCore.cpp \
    CAppInformation.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    Utils.cpp \
    CTcpTransport.cpp \
    CTelegramConnection.cpp
HEADERS = CTelegramCore.hpp \
    CAppInformation.hpp \
    CTelegramStream.hpp \
    CRawStream.hpp \
    Utils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    TLTypes.hpp \
    TLNumbers.hpp \
    crypto-aes.hpp \
    crypto-rsa.hpp \
    SDcInfo.hpp \
    CTelegramConnection.hpp \
    telegramqt_export.h

HEADERS += TLValues.h

LIBS += -lssl
