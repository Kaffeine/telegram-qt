cmake_minimum_required(VERSION 3.1)

project(TelegramQtServer
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(server_lib_SOURCES
    AuthorizationProvider.hpp
    DefaultAuthorizationProvider.cpp
    DefaultAuthorizationProvider.hpp
    LocalCluster.cpp
    LocalCluster.hpp
    ServerApi.hpp
    ServerDhLayer.cpp
    ServerDhLayer.hpp
    ServerRpcLayer.cpp
    ServerRpcLayer.hpp
    ServerRpcOperation.cpp
    ServerRpcOperation.hpp
    ServerRpcOperation_p.hpp
    ServerUtils.cpp
    Session.cpp
    Session.hpp
    Storage.cpp
    Storage.hpp
    RpcOperationFactory.cpp
    RpcOperationFactory.hpp
    RpcOperationFactory_p.hpp
    RpcProcessingContext.cpp
    RpcProcessingContext.hpp
    TelegramServer.cpp
    TelegramServer.hpp
    TelegramServerConfig.cpp
    TelegramServerConfig.hpp
    TelegramServerUser.cpp
    TelegramServerUser.hpp
    CServerTcpTransport.cpp
    CServerTcpTransport.hpp
    RemoteClientConnection.cpp
    RemoteClientConnection.hpp
    RemoteServerConnection.cpp
    RemoteServerConnection.hpp
    FunctionStreamOperators.cpp
    FunctionStreamOperators.hpp
)

FILE(GLOB RPC_SOURCES RpcOperations/*.cpp)
FILE(GLOB RPC_HEADERS RpcOperations/*.hpp)

list(APPEND server_lib_SOURCES ${RPC_SOURCES} ${RPC_HEADERS})

if (DEVELOPER_BUILD)
    add_definitions(-DDEVELOPER_BUILD)
    add_definitions(-DQT_DEPRECATED_WARNINGS)
    add_definitions(-DUSE_DBUS_NOTIFIER)
endif()

add_definitions(
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
    -DQT_NO_URL_CAST_FROM_STRING
    -DQT_NO_CAST_FROM_BYTEARRAY
    -DQT_USE_FAST_OPERATOR_PLUS
    -DQT_USE_QSTRINGBUILDER
    -DQT_STRICT_ITERATORS
)

add_library(TelegramServerQt${QT_VERSION_MAJOR} STATIC
    ${server_lib_SOURCES}
)

target_include_directories(TelegramServerQt${QT_VERSION_MAJOR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TelegramServerQt${QT_VERSION_MAJOR} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RpcOperations)

target_link_libraries(TelegramServerQt${QT_VERSION_MAJOR} PUBLIC
    Qt5::Core
    Qt5::Network
)

if (DEVELOPER_BUILD)
    target_link_libraries(TelegramServerQt${QT_VERSION_MAJOR} PUBLIC
        Qt5::DBus
    )
endif()

target_link_libraries(TelegramServerQt${QT_VERSION_MAJOR} PUBLIC
    TelegramQt${QT_VERSION_MAJOR}
)

set(server_SOURCES
    main.cpp
)

add_executable(TelegramServer ${server_SOURCES})
target_link_libraries(TelegramServer PUBLIC
    TelegramServerQt${QT_VERSION_MAJOR}
)
