
set(server_lib_SOURCES
    LocalCluster.cpp
    ServerDhLayer.cpp
    ServerRpcLayer.cpp
    ServerRpcOperation.cpp
    RpcOperationFactory.cpp
    TelegramServer.cpp
    TelegramServerClient.cpp
    TelegramServerUser.cpp
    CServerTcpTransport.cpp
    RemoteServerConnection.cpp
    FunctionStreamOperators.cpp
)

set(server_lib_META_HEADERS
    LocalCluster.hpp
    ServerDhLayer.hpp
    ServerRpcLayer.hpp
    ServerRpcOperation.hpp
    RpcOperationFactory.hpp
    TelegramServer.hpp
    TelegramServerClient.hpp
    TelegramServerUser.hpp
    CServerTcpTransport.hpp
    RemoteServerConnection.hpp
)

FILE(GLOB RPC_SOURCES RpcOperations/*.cpp)
FILE(GLOB RPC_HEADERS RpcOperations/*.hpp)

list(APPEND server_lib_SOURCES ${RPC_SOURCES})
list(APPEND server_lib_META_HEADERS ${RPC_HEADERS})

set(server_lib_HEADERS
    ${server_lib_META_HEADERS}
    FunctionStreamOperators.hpp
    ServerApi.hpp
    Session.hpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
)

if (DEVELOPER_BUILD)
    add_definitions(-DDEVELOPER_BUILD)
    add_definitions(-DQT_DEPRECATED_WARNINGS)
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

QT5_WRAP_CPP(server_lib_MOC_SOURECES ${server_lib_META_HEADERS})

add_library(TelegramServerQt${QT_VERSION_MAJOR} STATIC ${server_lib_SOURCES} ${server_lib_MOC_SOURECES})

target_include_directories(TelegramServerQt${QT_VERSION_MAJOR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TelegramServerQt${QT_VERSION_MAJOR} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/RpcOperations)

target_link_libraries(TelegramServerQt${QT_VERSION_MAJOR} LINK_PUBLIC
    Qt5::Core
    Qt5::Network
)

target_include_directories(TelegramServerQt${QT_VERSION_MAJOR} PRIVATE
    ${QT5_INCLUDES}
)

set(TELEGRAM_QT_INCLUDE_DIR ${CMAKE_INSTALL_FULL_INCLUDEDIR}/TelegramQt${QT_VERSION_MAJOR})
set(TELEGRAM_QT_LIB_DIR ${CMAKE_INSTALL_FULL_LIBDIR})

target_link_libraries(TelegramServerQt${QT_VERSION_MAJOR} LINK_PUBLIC
    TelegramQt${QT_VERSION_MAJOR}
)

set(server_SOURCES
    main.cpp
)

add_executable(TelegramServer ${server_SOURCES})
target_link_libraries(TelegramServer LINK_PUBLIC
    TelegramServerQt${QT_VERSION_MAJOR}
)
