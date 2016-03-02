
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt
VERSION = 0.1.0

include(../options.pri)

contains(options, static-lib) {
    CONFIG  += staticlib
} else {
    CONFIG  += dll
}

CONFIG += c++11

DEFINES += TELEGRAMQT_LIBRARY

SOURCES = CTelegramCore.cpp \
    CAppInformation.cpp \
    CTelegramDispatcher.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    Utils.cpp \
    TelegramUtils.cpp \
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
    TelegramUtils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    TLTypes.hpp \
    TLNumbers.hpp \
    crypto-aes.hpp \
    crypto-rsa.hpp \
    CTelegramConnection.hpp \
    TelegramNamespace.hpp \
    TelegramNamespace_p.hpp \
    telegramqt_export.h \
    TLValues.hpp

contains(options, developer-build) {
    SOURCES += TLTypesDebug.cpp
    HEADERS += TLTypesDebug.hpp
    DEFINES += DEVELOPER_BUILD
}

OTHER_FILES += CMakeLists.txt

LIBS += -lssl -lcrypto
LIBS += -lz
