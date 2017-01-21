
QT = core network

TEMPLATE = lib
TARGET   = TelegramQt$${QT_MAJOR_VERSION}
VERSION = 0.2.0

include(../options.pri)

contains(options, static-lib) {
    CONFIG  += staticlib
} else {
    CONFIG  += dll
}

CONFIG += c++11
CONFIG += link_pkgconfig
PKGCONFIG += openssl zlib

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

PUBLIC_HEADERS += \
    telegramqt_global.h \
    CAppInformation.hpp \
    TelegramNamespace.hpp \
    CTelegramCore.hpp \
    TelegramQt/CAppInformation \
    TelegramQt/CTelegramCore \
    TelegramQt/TelegramNamespace

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
    telegramqt_global.h \
    TLValues.hpp

contains(options, developer-build) {
    SOURCES += TLTypesDebug.cpp
    HEADERS += TLTypesDebug.hpp
    DEFINES += DEVELOPER_BUILD
}

OTHER_FILES += CMakeLists.txt

# Installation
public_headers.files = $$PUBLIC_HEADERS
public_headers.path = $$INSTALL_INCLUDE_DIR/telegram-qt$${QT_MAJOR_VERSION}/TelegramQt

target.path = $$INSTALL_LIBDIR
INSTALLS += public_headers target

# pkg-config support
CONFIG += create_pc create_prl no_install_prl

QMAKE_PKGCONFIG_NAME = TelegramQt
QMAKE_PKGCONFIG_DESCRIPTION = Qt-based library for Telegram network
QMAKE_PKGCONFIG_PREFIX = $$INSTALL_PREFIX
QMAKE_PKGCONFIG_LIBDIR = $$INSTALL_LIBDIR
QMAKE_PKGCONFIG_INCDIR = $$INSTALL_INCLUDE_DIR/telegram-qt$${QT_MAJOR_VERSION}
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
unix:QMAKE_CLEAN += -r pkgconfig lib$${TARGET}.prl
