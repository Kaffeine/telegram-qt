
set(telegram_qt_SOURCES
    AbridgedLength.cpp
    AccountStorage.cpp
    ApiUtils.cpp
    TelegramNamespace.cpp
    Client.cpp
    ClientApi.cpp
    ClientBackend.cpp
    ClientConnection.cpp
    ClientDhLayer.cpp
    ClientRpcLayer.cpp
    ClientRpcLayerExtension.cpp
    ClientSettings.cpp
    ConnectionApi.cpp
    Connection.cpp
    ConnectionError.cpp
    ContactList.cpp
    ContactsApi.cpp
    CAppInformation.cpp
    CTelegramTransport.cpp
    DataStorage.cpp
    DialogList.cpp
    IgnoredMessageNotification.cpp
    LegacySecretReader.cpp
    MessagingApi.cpp
    RpcError.cpp
    RpcLayer.cpp
    RsaKey.cpp
    RsaKey.hpp
    RandomGenerator.cpp
    SendPackageHelper.cpp
    SslBigNumber.cpp
    SslBigNumber.hpp
    CTelegramStream.cpp
    CTelegramStreamExtraOperators.cpp
    CTcpTransport.cpp
    CClientTcpTransport.cpp
    CRawStream.cpp
    DcConfiguration.cpp
    Debug.cpp
    DhLayer.cpp
    Utils.cpp
    FileRequestDescriptor.cpp
    PendingOperation.cpp
    PendingRpcOperation.cpp
    PendingRpcResult.cpp
    TLValues.cpp
    UpdatesLayer.cpp
)

set(telegram_qt_META_HEADERS
    AbridgedLength.hpp
    AccountStorage.hpp
    Client.hpp
    Client_p.hpp
    ClientApi.hpp
    ClientApi_p.hpp
    ClientBackend.hpp
    ClientConnection.hpp
    ClientDhLayer.hpp
    ClientRpcLayer.hpp
    ClientRpcLayerExtension.hpp
    ClientSettings.hpp
    Connection.hpp
    ConnectionApi.hpp
    ConnectionApi_p.hpp
    ContactList.hpp
    ContactsApi.hpp
    ContactsApi_p.hpp
    DataStorage.hpp
    DataStorage_p.hpp
    DialogList.hpp
    DhLayer.hpp
    LegacySecretReader.hpp
    MessagingApi.hpp
    MessagingApi_p.hpp
    RpcError.hpp
    RpcLayer.hpp
    SendPackageHelper.hpp
    TelegramNamespace.hpp
    PendingOperation.hpp
    PendingRpcOperation.hpp
    PendingRpcResult.hpp
    CAppInformation.hpp
    CTelegramTransport.hpp
    CTcpTransport.hpp
    CClientTcpTransport.hpp
    TLValues.hpp
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
    telegramqt_global.h
    TelegramNamespace_p.hpp
    ConnectionError.hpp
    CTelegramStream.hpp
    CTelegramStream_p.hpp
    CTelegramStreamExtraOperators.hpp
    ReadyObject.hpp
    RandomGenerator.hpp
    CRawStream.hpp
    DataStorage_p.hpp
    Debug.hpp
    Debug_p.hpp
    IgnoredMessageNotification.hpp
    PendingOperation_p.hpp
    UniqueLazyPointer.hpp
    Utils.hpp
    FileRequestDescriptor.hpp
    TLNumbers.hpp
    TLTypes.hpp
    crypto-rsa.hpp
    crypto-aes.hpp
)

set(telegram_qt_public_HEADERS
    telegramqt_global.h
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
    PendingOperation.hpp
    ReadyObject.hpp
    RsaKey.hpp
    TelegramNamespace.hpp
    Operations/ClientAuthOperation.hpp
    Operations/ClientMessagesOperation.hpp
    Operations/PendingContactsOperation.hpp
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
    Crypto/AesCtr.cpp
)

list(APPEND telegram_qt_HEADERS
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

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}
    Qt5::Core
    Qt5::Network
)
target_include_directories(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    ${QT5_INCLUDES}
)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}
    ${OPENSSL_LIBRARIES}
    ${ZLIB_LIBRARIES}
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
