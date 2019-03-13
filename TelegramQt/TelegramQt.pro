
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

isEmpty(BUILD_VERSION) {
    BUILD_VERSION = "unknown"
}
VERSION_FILE_CONTENT = $$cat("Version.cpp.in", blob)
VERSION_FILE = "$$OUT_PWD/Version.cpp"
VERSION_FILE_CONTENT = $$replace(VERSION_FILE_CONTENT, "@TELEGRAM_QT_VERSION@", "$$VERSION")
VERSION_FILE_CONTENT = $$replace(VERSION_FILE_CONTENT, "@BUILD_VERSION@", "$$BUILD_VERSION")
write_file("$$VERSION_FILE", VERSION_FILE_CONTENT)

SOURCES += $$VERSION_FILE


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
    ApiUtils.cpp \
    DcConfiguration.cpp \
    DialogList.cpp \
    DhLayer.cpp \
    Client.cpp \
    ClientApi.cpp \
    ClientBackend.cpp \
    ClientConnection.cpp \
    ClientDhLayer.cpp \
    ClientSettings.cpp \
    ClientRpcLayer.cpp \
    ClientRpcLayerExtension.cpp \
    ConnectionApi.cpp \
    ContactList.cpp \
    ContactsApi.cpp \
    DataStorage.cpp \
    IgnoredMessageNotification.cpp \
    RpcError.cpp \
    RpcLayer.cpp \
    RsaKey.cpp \
    Connection.cpp \
    ConnectionError.cpp \
    CRawStream.cpp \
    CTelegramStream.cpp \
    CTelegramStreamExtraOperators.cpp \
    Debug.cpp \
    Utils.cpp \
    FileRequestDescriptor.cpp \
    CTelegramTransport.cpp \
    CTcpTransport.cpp \
    CClientTcpTransport.cpp \
    TelegramNamespace.cpp \
    LegacySecretReader.cpp \
    MessagingApi.cpp \
    PendingOperation.cpp \
    PendingRpcOperation.cpp \
    PendingRpcResult.cpp \
    RandomGenerator.cpp \
    SendPackageHelper.cpp \
    SslBigNumber.cpp \
    TLValues.cpp \
    UpdatesLayer.cpp

PUBLIC_HEADERS += \
    telegramqt_global.h \
    CAppInformation.hpp \
    ClientApi.hpp \
    ConnectionApi.hpp \
    ContactList.hpp \
    ContactsApi.hpp \
    Debug.hpp \
    DialogList.hpp \
    MessagingApi.hpp \
    ReadyObject.hpp \
    RsaKey.hpp \
    TelegramNamespace.hpp \
    TelegramQt/CAppInformation \
    TelegramQt/CTelegramCore \
    TelegramQt/AccountStorage \
    TelegramQt/Client \
    TelegramQt/TelegramNamespace

HEADERS += \
    CAppInformation.hpp \
    AbridgedLength.hpp \
    AccountStorage.hpp \
    ApiUtils.hpp \
    DcConfiguration.hpp \
    Debug.hpp \
    Debug_p.hpp \
    DialogList.hpp \
    DhLayer.hpp \
    Client.hpp \
    Client_p.hpp \
    ClientApi.hpp \
    ClientApi_p.hpp \
    ClientBackend.hpp \
    ClientConnection.hpp \
    ClientDhLayer.hpp \
    ClientSettings.hpp \
    ClientRpcLayer.hpp \
    ClientRpcLayerExtension.hpp \
    ClientRpcLayerExtension_p.hpp \
    ConnectionApi.hpp \
    ConnectionApi_p.hpp \
    ContactList.hpp \
    ContactsApi.hpp \
    ContactsApi_p.hpp \
    DataStorage.hpp \
    DataStorage_p.hpp \
    IgnoredMessageNotification.hpp \
    MessagingApi.hpp \
    MessagingApi_p.hpp \
    ReadyObject.hpp \
    RpcError.hpp \
    RpcLayer.hpp \
    Connection.hpp \
    ConnectionError.hpp \
    CTelegramStream.hpp \
    CTelegramStreamExtraOperators.hpp \
    CTelegramStream_p.hpp \
    CRawStream.hpp \
    UniqueLazyPointer.hpp \
    Utils.hpp \
    FileRequestDescriptor.hpp \
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
    PendingOperation_p.hpp \
    PendingRpcOperation.hpp \
    PendingRpcResult.hpp \
    RandomGenerator.hpp \
    SendPackageHelper.hpp \
    SslBigNumber.hpp \
    TelegramNamespace.hpp \
    TelegramNamespace_p.hpp \
    telegramqt_global.h \
    TLValues.hpp \
    UpdatesLayer.hpp

include(RpcLayers/layers.pri)
include(Crypto/crypto.pri)
include(Operations/operations.pri)

SOURCES += \
    MTProto/MessageHeader.cpp

HEADERS += \
    MTProto/MessageHeader.hpp \
    MTProto/Stream.hpp

SOURCES += TLTypesDebug.cpp
HEADERS += TLTypesDebug.hpp

contains(options, developer-build) {
    SOURCES += TLRpcDebug.cpp
    HEADERS += TLRpcDebug.hpp
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
QMAKE_PKGCONFIG_REQUIRES = openssl zlib
unix:QMAKE_CLEAN += -r pkgconfig lib$${TARGET}.prl
