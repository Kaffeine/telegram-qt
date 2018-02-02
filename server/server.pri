
SOURCES += $$PWD/ServerDhLayer.cpp
SOURCES += $$PWD/ServerRpcLayer.cpp
SOURCES += $$PWD/ServerRpcOperation.cpp
SOURCES += $$PWD/RpcOperationFactory.cpp
SOURCES += $$PWD/TelegramServer.cpp
SOURCES += $$PWD/TelegramServerClient.cpp
SOURCES += $$PWD/TelegramServerUser.cpp
SOURCES += $$PWD/CServerTcpTransport.cpp
SOURCES += $$PWD/FunctionStreamOperators.cpp

HEADERS += $$PWD/ServerDhLayer.hpp
HEADERS += $$PWD/ServerRpcLayer.hpp
HEADERS += $$PWD/ServerRpcOperation.hpp
HEADERS += $$PWD/RpcOperationFactory.hpp
HEADERS += $$PWD/TelegramServer.hpp
HEADERS += $$PWD/TelegramServerClient.hpp
HEADERS += $$PWD/TelegramServerUser.hpp
HEADERS += $$PWD/CServerTcpTransport.hpp
HEADERS += $$PWD/FunctionStreamOperators.hpp

include(RpcOperations/operations.pri)
