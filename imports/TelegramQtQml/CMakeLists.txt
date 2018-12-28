project(TelegramQtQml)

find_package(Qt5 COMPONENTS Core Qml REQUIRED)

add_definitions(-DTELEGRAMQT_QML_LIBRARY)

add_definitions(-DQT_DEPRECATED_WARNINGS)
add_definitions(-DQT_NO_CAST_FROM_ASCII)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC TRUE)

if (NOT INSTALL_QML_IMPORT_DIR)
    set(INSTALL_QML_IMPORT_DIR ${CMAKE_INSTALL_LIBDIR}/qt5/qml)
endif()

add_library(TelegramQt${QT_VERSION_MAJOR}Qml SHARED
    DeclarativeClient.cpp
    DeclarativeClientOperator.cpp
    DeclarativeOperation.cpp
    DeclarativeAuthOperation.cpp
    DeclarativeSettings.cpp
)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}Qml
    Qt5::Core
    Qt5::Qml
)

target_include_directories(TelegramQt${QT_VERSION_MAJOR}Qml PRIVATE
    ${QT5_INCLUDES}
)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}Qml
    ${OPENSSL_LIBRARIES}
    ${ZLIB_LIBRARIES}
    TelegramQt${QT_VERSION_MAJOR}
)

# Set the correct version number
set_target_properties(
    TelegramQt${QT_VERSION_MAJOR}Qml PROPERTIES
    SOVERSION ${TELEGRAM_QT_ABI}
    VERSION ${TELEGRAM_QT_VERSION}
)
install(
    TARGETS TelegramQt${QT_VERSION_MAJOR}Qml
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Library
)

add_library(TelegramQt${QT_VERSION_MAJOR}QmlPlugin SHARED plugin.cpp)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}QmlPlugin LINK_PUBLIC
    TelegramQt${QT_VERSION_MAJOR}
    TelegramQt${QT_VERSION_MAJOR}Qml
)

install(
    TARGETS TelegramQt${QT_VERSION_MAJOR}QmlPlugin
    LIBRARY DESTINATION ${INSTALL_QML_IMPORT_DIR}/TelegramQt
    COMPONENT Library
)

install(
    FILES qmldir plugins.qmltypes
    DESTINATION ${INSTALL_QML_IMPORT_DIR}/TelegramQt
)
