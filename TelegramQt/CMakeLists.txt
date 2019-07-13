
add_library(TelegramQt${QT_VERSION_MAJOR})

target_compile_definitions(TelegramQt${QT_VERSION_MAJOR} PRIVATE TELEGRAMQT_LIBRARY)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    AbridgedLength.cpp
    AbridgedLength.hpp
    AccountApi.cpp
    AccountApi.hpp
    AccountApi_p.hpp
    AccountStorage.cpp
    AccountStorage.hpp
    ApiUtils.cpp
    ApiUtils.hpp
    CAppInformation.cpp
    CAppInformation.hpp
    CClientTcpTransport.cpp
    CClientTcpTransport.hpp
    CRawStream.cpp
    CRawStream.hpp
    CTcpTransport.cpp
    CTcpTransport.hpp
    CTelegramTransport.cpp
    CTelegramTransport.hpp
    Client.cpp
    Client.hpp
    ClientApi.cpp
    ClientApi.hpp
    ClientApi_p.hpp
    ClientBackend.cpp
    ClientBackend.hpp
    ClientConnection.cpp
    ClientConnection.hpp
    ClientDhLayer.cpp
    ClientDhLayer.hpp
    ClientRpcLayer.cpp
    ClientRpcLayer.hpp
    ClientRpcLayerExtension.cpp
    ClientRpcLayerExtension.hpp
    ClientSettings.cpp
    ClientSettings.hpp
    Client_p.hpp
    Connection.cpp
    Connection.hpp
    ConnectionApi.cpp
    ConnectionApi.hpp
    ConnectionApi_p.hpp
    ConnectionError.cpp
    ConnectionError.hpp
    ContactList.cpp
    ContactList.hpp
    ContactsApi.cpp
    ContactsApi.hpp
    ContactsApi_p.hpp
    Crypto/Aes.cpp
    Crypto/Aes.hpp
    Crypto/AesCtr.cpp
    Crypto/AesCtr.hpp
    DataStorage.cpp
    DataStorage.hpp
    DataStorage_p.hpp
    DataStorage_p.hpp
    DcConfiguration.cpp
    Debug.cpp
    Debug.hpp
    Debug_p.hpp
    DhLayer.cpp
    DhLayer.hpp
    DialogList.cpp
    DialogList.hpp
    FileRequestDescriptor.cpp
    FileRequestDescriptor.hpp
    IgnoredMessageNotification.cpp
    IgnoredMessageNotification.hpp
    LegacySecretReader.cpp
    LegacySecretReader.hpp
    MessagingApi.cpp
    MessagingApi.hpp
    MessagingApi_p.hpp
    PendingOperation.cpp
    PendingOperation.hpp
    PendingOperation_p.hpp
    PendingRpcOperation.cpp
    PendingRpcOperation.hpp
    PendingRpcResult.cpp
    PendingRpcResult.hpp
    RandomGenerator.cpp
    RandomGenerator.hpp
    ReadyObject.hpp
    RpcError.cpp
    RpcError.hpp
    RpcLayer.cpp
    RpcLayer.hpp
    RsaKey.cpp
    RsaKey.hpp
    SendPackageHelper.cpp
    SendPackageHelper.hpp
    SslBigNumber.cpp
    SslBigNumber.hpp
    TelegramNamespace.cpp
    TelegramNamespace.hpp
    TelegramNamespace_p.hpp
    UniqueLazyPointer.hpp
    UpdatesLayer.cpp
    UpdatesLayer.hpp
    Utils.cpp
    Utils.hpp
    telegramqt_global.h
)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    RpcLayers/ClientRpcAccountLayer.cpp
    RpcLayers/ClientRpcAccountLayer.hpp
    RpcLayers/ClientRpcAuthLayer.cpp
    RpcLayers/ClientRpcAuthLayer.hpp
    RpcLayers/ClientRpcBotsLayer.cpp
    RpcLayers/ClientRpcBotsLayer.hpp
    RpcLayers/ClientRpcChannelsLayer.cpp
    RpcLayers/ClientRpcChannelsLayer.hpp
    RpcLayers/ClientRpcContactsLayer.cpp
    RpcLayers/ClientRpcContactsLayer.hpp
    RpcLayers/ClientRpcHelpLayer.cpp
    RpcLayers/ClientRpcHelpLayer.hpp
    RpcLayers/ClientRpcLangpackLayer.cpp
    RpcLayers/ClientRpcLangpackLayer.hpp
    RpcLayers/ClientRpcMessagesLayer.cpp
    RpcLayers/ClientRpcMessagesLayer.hpp
    RpcLayers/ClientRpcPaymentsLayer.cpp
    RpcLayers/ClientRpcPaymentsLayer.hpp
    RpcLayers/ClientRpcPhoneLayer.cpp
    RpcLayers/ClientRpcPhoneLayer.hpp
    RpcLayers/ClientRpcPhotosLayer.cpp
    RpcLayers/ClientRpcPhotosLayer.hpp
    RpcLayers/ClientRpcStickersLayer.cpp
    RpcLayers/ClientRpcStickersLayer.hpp
    RpcLayers/ClientRpcUpdatesLayer.cpp
    RpcLayers/ClientRpcUpdatesLayer.hpp
    RpcLayers/ClientRpcUploadLayer.cpp
    RpcLayers/ClientRpcUploadLayer.hpp
    RpcLayers/ClientRpcUsersLayer.cpp
    RpcLayers/ClientRpcUsersLayer.hpp
)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    MTProto/TLNumbers.hpp
    MTProto/TLTypes.hpp
    MTProto/TLValues.cpp
    MTProto/TLValues.hpp
    MTProto/MessageHeader.cpp
    MTProto/MessageHeader.hpp
    MTProto/Stream.cpp # 1.0 Mb
    MTProto/Stream.hpp
    MTProto/StreamExtraOperators.cpp # 0.2 Mb
    MTProto/StreamExtraOperators.hpp
    MTProto/Stream_p.hpp
)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    Operations/ClientAuthOperation.cpp
    Operations/ClientAuthOperation.hpp
    Operations/ClientAuthOperation_p.hpp
    Operations/ClientHelpOperation.cpp
    Operations/ClientHelpOperation.hpp
    Operations/ClientPingOperation.cpp
    Operations/ClientPingOperation.hpp
    Operations/ConnectionOperation.cpp
    Operations/ConnectionOperation.hpp
    Operations/PendingContactsOperation.cpp
    Operations/PendingContactsOperation.hpp
    Operations/PendingContactsOperation_p.hpp
    Operations/PendingMessages.cpp
    Operations/PendingMessages.hpp
    Operations/PendingMessages_p.hpp
)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    RpcLayers/ClientRpcAccountLayer.cpp
    RpcLayers/ClientRpcAccountLayer.hpp
    RpcLayers/ClientRpcAuthLayer.cpp
    RpcLayers/ClientRpcAuthLayer.hpp
    RpcLayers/ClientRpcBotsLayer.cpp
    RpcLayers/ClientRpcBotsLayer.hpp
    RpcLayers/ClientRpcChannelsLayer.cpp
    RpcLayers/ClientRpcChannelsLayer.hpp
    RpcLayers/ClientRpcContactsLayer.cpp
    RpcLayers/ClientRpcContactsLayer.hpp
    RpcLayers/ClientRpcHelpLayer.cpp
    RpcLayers/ClientRpcHelpLayer.hpp
    RpcLayers/ClientRpcLangpackLayer.cpp
    RpcLayers/ClientRpcLangpackLayer.hpp
    RpcLayers/ClientRpcMessagesLayer.cpp
    RpcLayers/ClientRpcMessagesLayer.hpp
    RpcLayers/ClientRpcPaymentsLayer.cpp
    RpcLayers/ClientRpcPaymentsLayer.hpp
    RpcLayers/ClientRpcPhoneLayer.cpp
    RpcLayers/ClientRpcPhoneLayer.hpp
    RpcLayers/ClientRpcPhotosLayer.cpp
    RpcLayers/ClientRpcPhotosLayer.hpp
    RpcLayers/ClientRpcStickersLayer.cpp
    RpcLayers/ClientRpcStickersLayer.hpp
    RpcLayers/ClientRpcUpdatesLayer.cpp
    RpcLayers/ClientRpcUpdatesLayer.hpp
    RpcLayers/ClientRpcUploadLayer.cpp
    RpcLayers/ClientRpcUploadLayer.hpp
    RpcLayers/ClientRpcUsersLayer.cpp
    RpcLayers/ClientRpcUsersLayer.hpp
)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    MTProto/MessageHeader.cpp
    MTProto/MessageHeader.hpp
    MTProto/Stream.hpp
)

target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    Operations/ClientAuthOperation.cpp
    Operations/ClientAuthOperation.hpp
    Operations/ClientAuthOperation_p.hpp
    Operations/ClientHelpOperation.cpp
    Operations/ClientHelpOperation.hpp
    Operations/ClientPingOperation.cpp
    Operations/ClientPingOperation.hpp
    Operations/ConnectionOperation.cpp
    Operations/ConnectionOperation.hpp
    Operations/PendingContactsOperation.cpp
    Operations/PendingContactsOperation.hpp
    Operations/PendingContactsOperation_p.hpp
    Operations/PendingMessages.cpp
    Operations/PendingMessages.hpp
    Operations/PendingMessages_p.hpp
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
)

# TODO: Use TypesDebug only in Developer or Debug build
target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE MTProto/TLTypesDebug.cpp) # 0.5 Mb
target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE MTProto/TLTypesDebug.hpp)

if (DEVELOPER_BUILD)
    target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE MTProto/TLRpcDebug.cpp)
    target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE MTProto/TLRpcDebug.hpp)
    target_compile_definitions(TelegramQt${QT_VERSION_MAJOR} PRIVATE DEVELOPER_BUILD)
    target_compile_definitions(TelegramQt${QT_VERSION_MAJOR} PRIVATE QT_DEPRECATED_WARNINGS)
endif()

if (NOT BUILD_VERSION)
    set(BUILD_VERSION "unknown")
endif()

configure_file(Version.cpp.in "${CMAKE_CURRENT_BINARY_DIR}/Version.cpp" @ONLY)
target_sources(TelegramQt${QT_VERSION_MAJOR} PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/Version.cpp"
)

add_definitions(
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_USE_FAST_OPERATOR_PLUS
    -DQT_USE_QSTRINGBUILDER
    -DQT_STRICT_ITERATORS
)

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
    ZLIB::ZLIB
)

set(TELEGRAM_QT_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/TelegramQt${QT_VERSION_MAJOR})

# Set the correct version number
set_target_properties(
    TelegramQt${QT_VERSION_MAJOR} PROPERTIES
    SOVERSION ${TELEGRAM_QT_ABI}
    VERSION ${TELEGRAM_QT_VERSION}
)

install(
    TARGETS TelegramQt${QT_VERSION_MAJOR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
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
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig"
    COMPONENT pkgconfig
)
