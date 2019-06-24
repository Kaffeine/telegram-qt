
set(telegram_qt_SOURCES
    AbridgedLength.cpp
    AccountApi.cpp
    AccountStorage.cpp
    ApiUtils.cpp
    CAppInformation.cpp
    CClientTcpTransport.cpp
    CRawStream.cpp
    CTcpTransport.cpp
    CTelegramStream.cpp
    CTelegramStreamExtraOperators.cpp
    CTelegramTransport.cpp
    Client.cpp
    ClientApi.cpp
    ClientBackend.cpp
    ClientConnection.cpp
    ClientDhLayer.cpp
    ClientRpcLayer.cpp
    ClientRpcLayerExtension.cpp
    ClientSettings.cpp
    Connection.cpp
    ConnectionApi.cpp
    ConnectionError.cpp
    ContactList.cpp
    ContactsApi.cpp
    DataStorage.cpp
    DcConfiguration.cpp
    Debug.cpp
    DhLayer.cpp
    DialogList.cpp
    FileRequestDescriptor.cpp
    IgnoredMessageNotification.cpp
    LegacySecretReader.cpp
    MessagingApi.cpp
    PendingOperation.cpp
    PendingRpcOperation.cpp
    PendingRpcResult.cpp
    RandomGenerator.cpp
    RpcError.cpp
    RpcLayer.cpp
    RsaKey.cpp
    RsaKey.hpp
    SendPackageHelper.cpp
    SslBigNumber.cpp
    SslBigNumber.hpp
    TLValues.cpp
    TelegramNamespace.cpp
    UpdatesLayer.cpp
    Utils.cpp
)

set(telegram_qt_META_HEADERS
    AbridgedLength.hpp
    AccountApi.hpp
    AccountApi_p.hpp
    AccountStorage.hpp
    CAppInformation.hpp
    CClientTcpTransport.hpp
    CTcpTransport.hpp
    CTelegramTransport.hpp
    Client.hpp
    ClientApi.hpp
    ClientApi_p.hpp
    ClientBackend.hpp
    ClientConnection.hpp
    ClientDhLayer.hpp
    ClientRpcLayer.hpp
    ClientRpcLayerExtension.hpp
    ClientSettings.hpp
    Client_p.hpp
    Connection.hpp
    ConnectionApi.hpp
    ConnectionApi_p.hpp
    ContactList.hpp
    ContactsApi.hpp
    ContactsApi_p.hpp
    DataStorage.hpp
    DataStorage_p.hpp
    DhLayer.hpp
    DialogList.hpp
    LegacySecretReader.hpp
    MessagingApi.hpp
    MessagingApi_p.hpp
    PendingOperation.hpp
    PendingRpcOperation.hpp
    PendingRpcResult.hpp
    RpcError.hpp
    RpcLayer.hpp
    SendPackageHelper.hpp
    TLValues.hpp
    TelegramNamespace.hpp
    UpdatesLayer.hpp
)

FILE(GLOB RPC_SOURCES RpcLayers/*.cpp)
FILE(GLOB RPC_HEADERS RpcLayers/*.hpp)

FILE(GLOB MTPROTO_SOURCES MTProto/*.cpp)
FILE(GLOB MTPROTO_HEADERS MTProto/*.hpp)

list(APPEND telegram_qt_SOURCES ${RPC_SOURCES} ${MTPROTO_SOURCES})
list(APPEND telegram_qt_META_HEADERS ${RPC_HEADERS} ${MTPROTO_HEADERS})

FILE(GLOB CLIENT_OPERATIONS_SOURCES Operations/*.cpp)
FILE(GLOB CLIENT_OPERATIONS_HEADERS Operations/*.hpp)

list(APPEND telegram_qt_SOURCES ${CLIENT_OPERATIONS_SOURCES})
list(APPEND telegram_qt_META_HEADERS ${CLIENT_OPERATIONS_HEADERS})

set(telegram_qt_HEADERS
    ${telegram_qt_META_HEADERS}
    ApiUtils.hpp
    CRawStream.hpp
    CTelegramStream.hpp
    CTelegramStreamExtraOperators.hpp
    CTelegramStream_p.hpp
    ConnectionError.hpp
    DataStorage_p.hpp
    Debug.hpp
    Debug_p.hpp
    FileRequestDescriptor.hpp
    IgnoredMessageNotification.hpp
    PendingOperation_p.hpp
    RandomGenerator.hpp
    ReadyObject.hpp
    TLNumbers.hpp
    TLTypes.hpp
    TelegramNamespace_p.hpp
    UniqueLazyPointer.hpp
    Utils.hpp
    crypto-rsa.hpp
    telegramqt_global.h
)

set(telegram_qt_public_HEADERS
    AccountApi.hpp
    AccountStorage.hpp
    CAppInformation.hpp
    Client.hpp
    ClientApi.hpp
    ClientSettings.hpp
    ConnectionApi.hpp
    ConnectionError.hpp
    ContactList.hpp
    ContactsApi.hpp
    DataStorage.hpp
    DcConfiguration.hpp
    Debug.hpp
    DialogList.hpp
    MessagingApi.hpp
    Operations/ClientAuthOperation.hpp
    Operations/PendingContactsOperation.hpp
    Operations/PendingMessages.hpp
    PendingOperation.hpp
    ReadyObject.hpp
    RsaKey.hpp
    TelegramNamespace.hpp
    telegramqt_global.h
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
)

list(APPEND telegram_qt_SOURCES TLTypesDebug.cpp)
list(APPEND telegram_qt_HEADERS TLTypesDebug.hpp)

list(APPEND telegram_qt_SOURCES
    Crypto/Aes.cpp
    Crypto/AesCtr.cpp
)

list(APPEND telegram_qt_HEADERS
    Crypto/Aes.hpp
    Crypto/AesCtr.hpp
)

if (DEVELOPER_BUILD)
    list(APPEND telegram_qt_SOURCES TLRpcDebug.cpp)
    list(APPEND telegram_qt_HEADERS TLRpcDebug.hpp)
    add_definitions(-DDEVELOPER_BUILD)
    add_definitions(-DQT_DEPRECATED_WARNINGS)
endif()

if (NOT BUILD_VERSION)
    set(BUILD_VERSION "unknown")
endif()

configure_file(Version.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/Version.cpp" @ONLY)
list(APPEND telegram_qt_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/Version.cpp")

add_definitions(-DTELEGRAMQT_LIBRARY)

add_definitions(
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_USE_FAST_OPERATOR_PLUS
    -DQT_USE_QSTRINGBUILDER
    -DQT_STRICT_ITERATORS
)

QT5_WRAP_CPP(telegram_qt_MOC_SOURCES ${telegram_qt_META_HEADERS})

if (STATIC_BUILD)
    add_library(TelegramQt${QT_VERSION_MAJOR} STATIC ${telegram_qt_SOURCES} ${telegram_qt_MOC_SOURCES})
else()
    add_library(TelegramQt${QT_VERSION_MAJOR} SHARED ${telegram_qt_SOURCES} ${telegram_qt_MOC_SOURCES})
endif()

target_include_directories(TelegramQt${QT_VERSION_MAJOR} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Crypto
)
target_include_directories(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/RpcLayers
)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR} PUBLIC
    Qt5::Core
    Qt5::Network
)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    OpenSSL::Crypto
)

set(TELEGRAM_QT_INCLUDE_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/TelegramQt${QT_VERSION_MAJOR})
set(TELEGRAM_QT_LIB_DIR ${CMAKE_INSTALL_FULL_LIBDIR})

# Set the correct version number
set_target_properties(
    TelegramQt${QT_VERSION_MAJOR} PROPERTIES
    SOVERSION ${TELEGRAM_QT_ABI}
    VERSION ${TELEGRAM_QT_VERSION}
)

install(
    TARGETS TelegramQt${QT_VERSION_MAJOR}
    LIBRARY DESTINATION ${TELEGRAM_QT_LIB_DIR}
    ARCHIVE DESTINATION ${TELEGRAM_QT_LIB_DIR}
    COMPONENT Library
)

install(
    DIRECTORY TelegramQt
    DESTINATION ${TELEGRAM_QT_INCLUDE_DIR}
    COMPONENT Devel
)

foreach (public_header ${telegram_qt_public_HEADERS})
    get_filename_component( public_header_dir ${public_header} DIRECTORY )
    install(
        FILES ${public_header}
        DESTINATION ${TELEGRAM_QT_INCLUDE_DIR}/TelegramQt/${public_header_dir}
        COMPONENT Devel
    )
endforeach()


# CMake find package stuff
include(CMakePackageConfigHelpers)

configure_file(TelegramQtConfig.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}Config.cmake" @ONLY)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}ConfigVersion.cmake"
                                    VERSION ${TELEGRAM_QT_VERSION}
                                    COMPATIBILITY ExactVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}ConfigVersion.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}Config.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/TelegramQt${QT_VERSION_MAJOR}"
    COMPONENT Devel
)

# pkg-config files
configure_file(TelegramQt.pc.in "${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}.pc" @ONLY)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}.pc"
    DESTINATION "${TELEGRAM_QT_LIB_DIR}/pkgconfig"
    COMPONENT pkgconfig
)
