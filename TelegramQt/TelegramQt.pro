
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

SOURCES += \
    CAppInformation.cpp \
    AbridgedLength.cpp \
    AccountStorage.cpp \
    DcConfiguration.cpp \
    DhLayer.cpp \
    Client.cpp \
    ClientBackend.cpp \
    ClientConnection.cpp \
    ClientDhLayer.cpp \
    ClientSettings.cpp \
    ClientRpcLayer.cpp \
    ClientRpcLayerExtension.cpp \
    DataStorage.cpp \
    RpcError.cpp \
    RpcLayer.cpp \
    Connection.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    CTelegramStreamExtraOperators.cpp \
    Debug.cpp \
    Utils.cpp \
    FileRequestDescriptor.cpp \
    TelegramUtils.cpp \
    CTelegramTransport.cpp \
    CTcpTransport.cpp \
    CClientTcpTransport.cpp \
    TelegramNamespace.cpp \
    LegacySecretReader.cpp \
    PendingOperation.cpp \
    PendingRpcOperation.cpp \
    RandomGenerator.cpp \
    RpcProcessingContext.cpp \
    SendPackageHelper.cpp \
    TLValues.cpp

PUBLIC_HEADERS += \
    telegramqt_global.h \
    CAppInformation.hpp \
    Debug.hpp \
    TelegramNamespace.hpp \
    CTelegramCore.hpp \
    TelegramQt/CAppInformation \
    TelegramQt/CTelegramCore \
    TelegramQt/AccountStorage \
    TelegramQt/Client \
    TelegramQt/TelegramNamespace

HEADERS += \
    CAppInformation.hpp \
    AbridgedLength.hpp \
    AccountStorage.hpp \
    DcConfiguration.hpp \
    Debug.hpp \
    Debug_p.hpp \
    DhLayer.hpp \
    Client.hpp \
    Client_p.hpp \
    ClientBackend.hpp \
    ClientConnection.hpp \
    ClientDhLayer.hpp \
    ClientSettings.hpp \
    ClientRpcLayer.hpp \
    ClientRpcLayerExtension.hpp \
    DataStorage.hpp \
    DataStorage_p.hpp \
    RpcError.hpp \
    RpcLayer.hpp \
    Connection.hpp \
    CTelegramStream.hpp \
    CTelegramStreamExtraOperators.hpp \
    CTelegramStream_p.hpp \
    CRawStream.hpp \
    Utils.hpp \
    FileRequestDescriptor.hpp \
    TelegramUtils.hpp \
    CTelegramTransport.hpp \
    CTcpTransport.hpp \
    CClientTcpTransport.hpp \
    TLFunctions.hpp \
    TLTypes.hpp \
    TLNumbers.hpp \
    crypto-aes.hpp \
    crypto-rsa.hpp \
    LegacySecretReader.hpp \
    PendingOperation.hpp \
    PendingRpcOperation.hpp \
    RandomGenerator.hpp \
    RpcProcessingContext.hpp \
    SendPackageHelper.hpp \
    TelegramNamespace.hpp \
    TelegramNamespace_p.hpp \
    telegramqt_global.h \
    TLValues.hpp

include(RpcLayers/layers.pri)
include(Crypto/crypto.pri)
include(Operations/operations.pri)

SOURCES += TLTypesDebug.cpp
HEADERS += TLTypesDebug.hpp

contains(options, developer-build) {
    SOURCES += TLRpcDebug.cpp
    HEADERS += TLRpcDebug.hpp
    DEFINES += DEVELOPER_BUILD
    DEFINES += QT_DEPRECATED_WARNINGS
}

OTHER_FILES += CMakeLists.txt

OTHER_FILES += \
    CTelegramCore.cpp \
    CTelegramCore.hpp \
    CTelegramConnection.cpp \
    CTelegramConnection.hpp \
    CTelegramDispatcher.cpp \
    CTelegramDispatcher.hpp \
    CTelegramModule.cpp \
    CTelegramModule.hpp \
    CTelegramAuthModule.cpp \
    CTelegramAuthModule.hpp \
    CTelegramMediaModule.cpp \
    CTelegramMediaModule.hpp \
    CTelegramTransportModule.cpp \
    CTelegramTransportModule.hpp

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
