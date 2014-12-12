
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
    CTelegramConnection.cpp

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
    telegramqt_export.h

HEADERS += TLValues.h

win32 {
    INCLUDEPATH += ../3rdParty/zlib
    DEFINES += _CRT_SECURE_NO_WARNINGS
    LIBS += -lUser32 -lAdvapi32 -lGdi32
    SOURCES += ../3rdParty/zlib/inflate.c \
        ../3rdParty/zlib/adler32.c \
        ../3rdParty/zlib/crc32.c \
        ../3rdParty/zlib/zutil.c \
        ../3rdParty/zlib/inftrees.c \
        ../3rdParty/zlib/inffast.c
    CONFIG(debug) {
        DESTDIR = ../bin/debug
        LIBS += -lssleay32MDd -llibeay32MDd
    } else {
        DESTDIR = ../bin/release
        LIBS += -lssleay32MD -llibeay32MD
    }
} else {
    LIBS += -lssl
}
