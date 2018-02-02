
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
    AccountStorage.cpp \
    DhLayer.cpp \
    Client.cpp \
    ClientBackend.cpp \
    ClientConnection.cpp \
    ClientDhLayer.cpp \
    ClientSettings.cpp \
    ClientRpcLayer.cpp \
    ClientRpcLayerExtension.cpp \
    ClientRpcAccountLayer.cpp \
    ClientRpcAuthLayer.cpp \
    ClientRpcChannelsLayer.cpp \
    ClientRpcContactsLayer.cpp \
    ClientRpcHelpLayer.cpp \
    ClientRpcMessagesLayer.cpp \
    ClientRpcPhotosLayer.cpp \
    ClientRpcUpdatesLayer.cpp \
    ClientRpcUploadLayer.cpp \
    ClientRpcUsersLayer.cpp \
    RpcError.cpp \
    RpcLayer.cpp \
    Connection.cpp \
    CTelegramDispatcher.cpp \
    CTelegramModule.cpp \
    CTelegramAuthModule.cpp \
    CTelegramMediaModule.cpp \
    CTelegramTransportModule.cpp \
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
    CTelegramConnection.cpp \
    LegacySecretReader.cpp \
    PendingOperation.cpp \
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

HEADERS = CTelegramCore.hpp \
    CAppInformation.hpp \
    AccountStorage.hpp \
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
    ClientRpcAccountLayer.hpp \
    ClientRpcAuthLayer.hpp \
    ClientRpcChannelsLayer.hpp \
    ClientRpcContactsLayer.hpp \
    ClientRpcHelpLayer.hpp \
    ClientRpcMessagesLayer.hpp \
    ClientRpcPhotosLayer.hpp \
    ClientRpcUpdatesLayer.hpp \
    ClientRpcUploadLayer.hpp \
    ClientRpcUsersLayer.hpp \
    RpcError.hpp \
    RpcLayer.hpp \
    Connection.hpp \
    CTelegramDispatcher.hpp \
    CTelegramModule.hpp \
    CTelegramAuthModule.hpp \
    CTelegramMediaModule.hpp \
    CTelegramTransportModule.hpp \
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
    CTelegramConnection.hpp \
    LegacySecretReader.hpp \
    PendingOperation.hpp \
    RpcProcessingContext.hpp \
    SendPackageHelper.hpp \
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
