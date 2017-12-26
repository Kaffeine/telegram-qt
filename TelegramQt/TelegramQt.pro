
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

DEFINES += QT_NO_CAST_TO_ASCII
DEFINES += QT_NO_CAST_FROM_ASCII
DEFINES += QT_NO_URL_CAST_FROM_STRING
DEFINES += QT_NO_CAST_FROM_BYTEARRAY
DEFINES += QT_USE_FAST_OPERATOR_PLUS
DEFINES += QT_USE_QSTRINGBUILDER
DEFINES += QT_STRICT_ITERATORS

SOURCES = CTelegramCore.cpp \
    CAppInformation.cpp \
    CTelegramDispatcher.cpp \
    CTelegramModule.cpp \
    CTelegramAuthModule.cpp \
    CTelegramMediaModule.cpp \
    CTelegramTransportModule.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    Debug.cpp \
    Utils.cpp \
    FileRequestDescriptor.cpp \
    TelegramUtils.cpp \
    CTelegramTransport.cpp \
    CTcpTransport.cpp \
    CClientTcpTransport.cpp \
    TelegramNamespace.cpp \
    CTelegramConnection.cpp \
    RpcProcessingContext.cpp \
    TLValues.cpp

PUBLIC_HEADERS += \
    telegramqt_global.h \
    CAppInformation.hpp \
    Debug.hpp \
    TelegramNamespace.hpp \
    CTelegramCore.hpp \
    TelegramQt/CAppInformation \
    TelegramQt/CTelegramCore \
    TelegramQt/TelegramNamespace

HEADERS = CTelegramCore.hpp \
    CAppInformation.hpp \
    Debug.hpp \
    Debug_p.hpp \
    CTelegramDispatcher.hpp \
    CTelegramModule.hpp \
    CTelegramAuthModule.hpp \
    CTelegramMediaModule.hpp \
    CTelegramTransportModule.hpp \
    CTelegramStream.hpp \
    CTelegramStream_p.hpp \
    CRawStream.hpp \
    Utils.hpp \
    FileRequestDescriptor.hpp \
    TelegramUtils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    CClientTcpTransport.hpp \
    TLTypes.hpp \
    TLNumbers.hpp \
    crypto-aes.hpp \
    crypto-rsa.hpp \
    CTelegramConnection.hpp \
    RpcProcessingContext.hpp \
    TelegramNamespace.hpp \
    TelegramNamespace_p.hpp \
    telegramqt_global.h \
    TLValues.hpp

contains(options, developer-build) {
    SOURCES += TLTypesDebug.cpp TLRpcDebug.cpp
    HEADERS += TLTypesDebug.hpp TLRpcDebug.hpp
    DEFINES += DEVELOPER_BUILD
    DEFINES += QT_DEPRECATED_WARNINGS
}

OTHER_FILES += CMakeLists.txt

# Installation
public_headers.files = $$PUBLIC_HEADERS
public_headers.path = $$INSTALL_INCLUDE_DIR/TelegramQt$${QT_MAJOR_VERSION}/TelegramQt

target.path = $$INSTALL_LIB_DIR
INSTALLS += public_headers target

# pkg-config support
CONFIG += create_pc create_prl no_install_prl

QMAKE_PKGCONFIG_NAME = TelegramQt
QMAKE_PKGCONFIG_FILE = TelegramQt$${QT_MAJOR_VERSION}
QMAKE_PKGCONFIG_DESCRIPTION = Qt-based library for Telegram network
QMAKE_PKGCONFIG_PREFIX = $$INSTALL_PREFIX
QMAKE_PKGCONFIG_LIBDIR = $$INSTALL_LIB_DIR
QMAKE_PKGCONFIG_INCDIR = $$INSTALL_INCLUDE_DIR/TelegramQt$${QT_MAJOR_VERSION}
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
QMAKE_PKGCONFIG_REQUIRES = openssl zlib
unix:QMAKE_CLEAN += -r pkgconfig lib$${TARGET}.prl
