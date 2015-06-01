
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt
target.path = $$PREFIX/lib
INSTALLS += target
CONFIG  += dll

include(../options.pri)

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
    TLValues.cpp \

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

contains(options, developer-build) {
    SOURCES += TLTypesDebug.cpp
    HEADERS += TLTypesDebug.hpp
    DEFINES += DEVELOPER_BUILD
}

LIBS += -lssl -lcrypto
LIBS += -lz
