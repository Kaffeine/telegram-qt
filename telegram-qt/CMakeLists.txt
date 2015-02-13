
set(telegram_qt_SOURCES
    TelegramNamespace.cpp
    CAppInformation.cpp
    CTelegramCore.cpp
    CTelegramDispatcher.cpp
    CTelegramConnection.cpp
    CTelegramTransport.hpp
    CTelegramStream.cpp
    CTcpTransport.cpp
    CRawStream.cpp
    Utils.cpp
)

set(telegram_qt_HEADERS
    telegramqt_export.h
    TelegramNamespace.hpp
    CTelegramCore.hpp
    CTelegramDispatcher.hpp
    CTelegramConnection.hpp
    TLTypes.hpp
    CAppInformation.hpp
    crypto-rsa.hpp
    crypto-aes.hpp
)

set(telegram_qt_public_HEADERS
    telegramqt_export.h
    CAppInformation.hpp
    TelegramNamespace.hpp
    CTelegramCore.hpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${OPENSSL_INCLUDE_DIR}
    ${ZLIB_INCLUDE_DIR}
)

add_definitions(-DTELEGRAMQT_LIBRARY)

#add_library(telegram-qt${QT_VERSION_MAJOR} SHARED ${telegram_qt_SOURCES})
add_library(telegram-qt${QT_VERSION_MAJOR} STATIC ${telegram_qt_SOURCES})

set_target_properties(telegram-qt${QT_VERSION_MAJOR} PROPERTIES AUTOMOC TRUE)

if(USE_QT4)
    target_link_libraries(telegram-qt${QT_VERSION_MAJOR}
        ${QT_QTCORE_LIBRARY}
        ${QT_QTNETWORK_LIBRARY}
    )
    target_include_directories(telegram-qt${QT_VERSION_MAJOR} PRIVATE
        ${QT_INCLUDES}
    )
else()
    target_link_libraries(telegram-qt${QT_VERSION_MAJOR}
        Qt5::Core
        Qt5::Network
    )
    target_include_directories(telegram-qt${QT_VERSION_MAJOR} PRIVATE
        ${QT5_INCLUDES}
    )
endif()

target_link_libraries(telegram-qt${QT_VERSION_MAJOR}
    ${OPENSSL_LIBRARIES}
    ${ZLIB_LIBRARIES}
)

set(TELEGRAM_QT_INCLUDE_DIR ${CMAKE_INSTALL_INCLUDEDIR}/telegram-qt${QT_VERSION_MAJOR})
set(TELEGRAM_QT_LIB_DIR ${CMAKE_INSTALL_LIBDIR})

install(
    TARGETS telegram-qt${QT_VERSION_MAJOR}
#    LIBRARY DESTINATION ${TELEGRAM_QT_LIB_DIR}
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

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}ConfigVersion.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/TelegramQt${QT_VERSION_MAJOR}Config.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/TelegramQt${QT_VERSION_MAJOR}
    COMPONENT Devel
)
