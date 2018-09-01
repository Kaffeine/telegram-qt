
set(telegram_qt_SOURCES
    AbridgedLength.cpp
    AccountStorage.cpp
    TelegramNamespace.cpp
    Client.cpp
    ClientBackend.cpp
    ClientConnection.cpp
    ClientDhLayer.cpp
    ClientRpcLayer.cpp
    ClientRpcLayerExtension.cpp
    ClientSettings.cpp
    Connection.cpp
    CAppInformation.cpp
    CTelegramTransport.cpp
    DataStorage.cpp
    LegacySecretReader.cpp
    RpcError.cpp
    RpcLayer.cpp
    RandomGenerator.cpp
    RpcProcessingContext.cpp
    SendPackageHelper.cpp
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
    TelegramUtils.cpp
    TLValues.cpp
)

set(telegram_qt_META_HEADERS
    AbridgedLength.hpp
    AccountStorage.hpp
    Client.hpp
    Client_p.hpp
    ClientBackend.hpp
    ClientConnection.hpp
    ClientDhLayer.hpp
    ClientRpcLayer.hpp
    ClientRpcLayerExtension.hpp
    ClientSettings.hpp
    Connection.hpp
    DataStorage.hpp
    DhLayer.hpp
    LegacySecretReader.hpp
    RpcError.hpp
    RpcLayer.hpp
    SendPackageHelper.hpp
    TelegramNamespace.hpp
    PendingOperation.hpp
    PendingRpcOperation.hpp
    CAppInformation.hpp
    CTelegramTransport.hpp
    CTcpTransport.hpp
    CClientTcpTransport.hpp
    TLValues.hpp
)

FILE(GLOB RPC_SOURCES RpcLayers/*.cpp)
FILE(GLOB RPC_HEADERS RpcLayers/*.hpp)

list(APPEND telegram_qt_SOURCES ${RPC_SOURCES})
list(APPEND telegram_qt_META_HEADERS ${RPC_HEADERS})

FILE(GLOB CLIENT_OPERATIONS_SOURCES Operations/*.cpp)
FILE(GLOB CLIENT_OPERATIONS_HEADERS Operations/*.hpp)

list(APPEND telegram_qt_SOURCES ${CLIENT_OPERATIONS_SOURCES})
list(APPEND telegram_qt_META_HEADERS ${CLIENT_OPERATIONS_HEADERS})

set(telegram_qt_HEADERS
    ${telegram_qt_META_HEADERS}
    telegramqt_global.h
    TelegramNamespace_p.hpp
    CTelegramStream.hpp
    CTelegramStream_p.hpp
    CTelegramStreamExtraOperators.hpp
    RandomGenerator.hpp
    RpcProcessingContext.hpp
    CRawStream.hpp
    DataStorage_p.hpp
    Debug.hpp
    Debug_p.hpp
    Utils.hpp
    FileRequestDescriptor.hpp
    TelegramUtils.hpp
    TLTypes.hpp
    crypto-rsa.hpp
    crypto-aes.hpp
)

set(telegram_qt_public_HEADERS
    telegramqt_global.h
    CAppInformation.hpp
    TelegramNamespace.hpp
    CTelegramCore.hpp
    DcConfiguration.hpp
    Debug.hpp
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

QT5_WRAP_CPP(telegram_qt_MOC_SOURECES ${telegram_qt_META_HEADERS})

if (STATIC_BUILD)
    add_library(TelegramQt${QT_VERSION_MAJOR} STATIC ${telegram_qt_SOURCES} ${telegram_qt_MOC_SOURECES})
else()
    add_library(TelegramQt${QT_VERSION_MAJOR} SHARED ${telegram_qt_SOURCES} ${telegram_qt_MOC_SOURECES})
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

install(
    FILES ${telegram_qt_public_HEADERS}
    DESTINATION ${TELEGRAM_QT_INCLUDE_DIR}/TelegramQt
    COMPONENT Devel
)

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
