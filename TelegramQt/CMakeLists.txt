
set(telegram_qt_SOURCES
    TelegramNamespace.cpp
    CAppInformation.cpp
    CTelegramCore.cpp
    CTelegramDispatcher.cpp
    CTelegramModule.cpp
    CTelegramAuthModule.cpp
    CTelegramMediaModule.cpp
    CTelegramConnection.cpp
    RpcProcessingContext.cpp
    CTelegramStream.cpp
    CTcpTransport.cpp
    CRawStream.cpp
    Utils.cpp
    FileRequestDescriptor.cpp
    TelegramUtils.cpp
    TLValues.cpp
)

set(telegram_qt_META_HEADERS
    TelegramNamespace.hpp
    CAppInformation.hpp
    CTelegramCore.hpp
    CTelegramDispatcher.hpp
    CTelegramModule.hpp
    CTelegramAuthModule.hpp
    CTelegramMediaModule.hpp
    CTelegramConnection.hpp
    CTelegramTransport.hpp
    CTcpTransport.hpp
    TLValues.hpp
)

set(telegram_qt_HEADERS
    ${telegram_qt_META_HEADERS}
    telegramqt_global.h
    TelegramNamespace_p.hpp
    CTelegramStream.hpp
    RpcProcessingContext.hpp
    CRawStream.hpp
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
    Debug.hpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
)

if (DEVELOPER_BUILD)
    list(APPEND telegram_qt_SOURCES TLTypesDebug.cpp TLRpcDebug.cpp)
    list(APPEND telegram_qt_HEADERS TLTypesDebug.hpp TLRpcDebug.hpp)
    add_definitions(-DDEVELOPER_BUILD)
endif()

add_definitions(-DTELEGRAMQT_LIBRARY)
add_definitions(-DQT_DEPRECATED_WARNINGS)
add_definitions(-DQT_NO_CAST_FROM_ASCII)

QT5_WRAP_CPP(telegram_qt_MOC_SOURECES ${telegram_qt_META_HEADERS})

if (STATIC_BUILD)
    add_library(TelegramQt${QT_VERSION_MAJOR} STATIC ${telegram_qt_SOURCES} ${telegram_qt_MOC_SOURECES})
else()
    add_library(TelegramQt${QT_VERSION_MAJOR} SHARED ${telegram_qt_SOURCES} ${telegram_qt_MOC_SOURECES})
endif()

target_include_directories(TelegramQt${QT_VERSION_MAJOR} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

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

set(TELEGRAM_QT_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/TelegramQt${QT_VERSION_MAJOR})
set(TELEGRAM_QT_LIB_DIR ${CMAKE_INSTALL_LIBDIR})

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
