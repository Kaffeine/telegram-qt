
set(server_lib_SOURCES
    AuthService.cpp
    AuthService.hpp
    AuthorizationProvider.hpp
    CServerTcpTransport.cpp
    CServerTcpTransport.hpp
    DefaultAuthorizationProvider.cpp
    DefaultAuthorizationProvider.hpp
    FunctionStreamOperators.cpp
    FunctionStreamOperators.hpp
    GroupChat.cpp
    GroupChat.hpp
    IMediaService.hpp
    LocalCluster.cpp
    LocalCluster.hpp
    LocalServerApi.hpp
    MediaService.cpp
    MediaService.hpp
    MessageService.cpp
    MessageService.hpp
    PendingVariant.cpp
    PendingVariant.hpp
    RemoteClientConnection.cpp
    RemoteClientConnection.hpp
    RemoteClientConnectionHelper.cpp
    RemoteClientConnectionHelper.hpp
    RemoteServerConnection.cpp
    RemoteServerConnection.hpp
    RpcOperationFactory.cpp
    RpcOperationFactory.hpp
    RpcOperationFactory_p.hpp
    RpcProcessingContext.cpp
    RpcProcessingContext.hpp
    ServerApi.hpp
    ServerDhLayer.cpp
    ServerDhLayer.hpp
    ServerMessageData.cpp
    ServerMessageData.hpp
    ServerNamespace.cpp
    ServerNamespace.hpp
    ServerRpcLayer.cpp
    ServerRpcLayer.hpp
    ServerRpcOperation.cpp
    ServerRpcOperation.hpp
    ServerRpcOperation_p.hpp
    ServerUtils.cpp
    ServerUtils.hpp
    Session.cpp
    Session.hpp
    TelegramServer.cpp
    TelegramServer.hpp
    TelegramServerConfig.cpp
    TelegramServerConfig.hpp
    TelegramServerUser.cpp
    TelegramServerUser.hpp
)

FILE(GLOB RPC_SOURCES RpcOperations/*.cpp)
FILE(GLOB RPC_HEADERS RpcOperations/*.hpp)

list(APPEND server_lib_SOURCES ${RPC_SOURCES} ${RPC_HEADERS})

set(server_json_SOURCES
    DataImporter.cpp
    DataImporter.hpp
    JsonDataImporter.cpp
    JsonDataImporter.hpp
    JsonUtils_p.hpp
    ServerImportApi.cpp
    ServerImportApi.hpp
    ServerTelegramJson.cpp
    ServerTelegramJson.hpp
)

add_library(TelegramQt${QT_VERSION_MAJOR}Server STATIC)
add_library(TelegramQt${QT_VERSION_MAJOR}::Server ALIAS TelegramQt${QT_VERSION_MAJOR}Server)

target_compile_definitions(TelegramQt${QT_VERSION_MAJOR}Server PRIVATE
    QT_NO_CAST_TO_ASCII
    QT_NO_URL_CAST_FROM_STRING
    QT_NO_CAST_FROM_BYTEARRAY
    QT_RESTRICTED_CAST_FROM_ASCII
    QT_USE_FAST_OPERATOR_PLUS
    QT_USE_QSTRINGBUILDER
    QT_STRICT_ITERATORS
)

find_package(Qt5 5.5 COMPONENTS Core Gui Network REQUIRED)

target_sources(TelegramQt${QT_VERSION_MAJOR}Server PRIVATE
    ${server_lib_SOURCES}
    ${server_json_SOURCES}
)

target_include_directories(TelegramQt${QT_VERSION_MAJOR}Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TelegramQt${QT_VERSION_MAJOR}Server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RpcOperations)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}Server PUBLIC
    Qt5::Core
    Qt5::Network
    Qt5::Gui
    TelegramQt${QT_VERSION_MAJOR}::Core
)

if(TELEGRAMQT_DEVELOPER_BUILD)
    target_compile_definitions(TelegramQt${QT_VERSION_MAJOR}Server PRIVATE
        DEVELOPER_BUILD
        QT_DEPRECATED_WARNINGS
        USE_DBUS_NOTIFIER
    )
    target_link_libraries(TelegramQt${QT_VERSION_MAJOR}Server PUBLIC
        Qt5::DBus
    )
endif()

add_executable(TelegramServer main.cpp)
target_link_libraries(TelegramServer PUBLIC
    TelegramQt${QT_VERSION_MAJOR}::Server
)

install(
    TARGETS TelegramServer
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
)
