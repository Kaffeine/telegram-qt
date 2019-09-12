project(TelegramQtQml)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC TRUE)

add_library(TelegramQt${QT_VERSION_MAJOR}Qml
    DeclarativeAuthOperation.cpp
    DeclarativeAuthOperation.hpp
    DeclarativeClient.cpp
    DeclarativeClient.hpp
    DeclarativeClientOperator.cpp
    DeclarativeClientOperator.hpp
    DeclarativeMessageSender.cpp
    DeclarativeMessageSender.hpp
    DeclarativeOperation.cpp
    DeclarativeOperation.hpp
    DeclarativePeerInfo.cpp
    DeclarativePeerInfo.hpp
    DeclarativeRsaKey.cpp
    DeclarativeRsaKey.hpp
    DeclarativeSettings.cpp
    DeclarativeSettings.hpp
)
add_library(TelegramQt${QT_VERSION_MAJOR}::Qml ALIAS TelegramQt${QT_VERSION_MAJOR}Qml)

target_compile_definitions(TelegramQt${QT_VERSION_MAJOR}Qml PRIVATE
    TELEGRAMQT_QML_LIBRARY
)

target_compile_definitions(TelegramQt${QT_VERSION_MAJOR}Qml PRIVATE
    QT_NO_CAST_TO_ASCII
    QT_NO_CAST_FROM_ASCII
    QT_NO_URL_CAST_FROM_STRING
    QT_NO_CAST_FROM_BYTEARRAY
    QT_USE_FAST_OPERATOR_PLUS
    QT_USE_QSTRINGBUILDER
    QT_STRICT_ITERATORS
)

target_link_libraries(TelegramQt${QT_VERSION_MAJOR}Qml PUBLIC
    Qt5::Core
    Qt5::Qml
    TelegramQt${QT_VERSION_MAJOR}::Core
)

target_include_directories(TelegramQt${QT_VERSION_MAJOR}Qml
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    PRIVATE
        ${QT5_INCLUDES}
)

set_target_properties(
    TelegramQt${QT_VERSION_MAJOR}Qml
    PROPERTIES
        SOVERSION ${TELEGRAM_QT_ABI}
        VERSION ${TelegramQt_VERSION}
        EXPORT_NAME Qml
)

install(
    TARGETS TelegramQt${QT_VERSION_MAJOR}Qml
    EXPORT TelegramQt${QT_VERSION_MAJOR}Qml-export
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Library
)

install(
    EXPORT TelegramQt${QT_VERSION_MAJOR}Qml-export
    FILE TelegramQt${QT_VERSION_MAJOR}QmlTargets.cmake
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/TelegramQt${QT_VERSION_MAJOR}"
    NAMESPACE TelegramQt${QT_VERSION_MAJOR}::
    COMPONENT Devel
)

add_library(TelegramQmlPlugin SHARED plugin.cpp)

target_link_libraries(TelegramQmlPlugin
    Qt5::Core
    Qt5::Qml
    TelegramQt${QT_VERSION_MAJOR}::Qml
)

install(
    TARGETS TelegramQmlPlugin
    DESTINATION ${INSTALL_QML_IMPORT_DIR}/TelegramQt
)

install(
    FILES qmldir plugins.qmltypes
    DESTINATION ${INSTALL_QML_IMPORT_DIR}/TelegramQt
)

if(DEVELOPER_BUILD)
    message(STATUS "Hint: To update plugins.qmltypes run the following command:\n"
        "    LD_LIBRARY_PATH=${CMAKE_INSTALL_FULL_LIBDIR} "
        "${_qt5Core_install_prefix}/bin/qmlplugindump "
        "-noinstantiate -nonrelocatable -v TelegramQt 0.2 "
        "${CMAKE_INSTALL_FULL_LIBDIR}/qt5/qml "
        "> ${CMAKE_CURRENT_SOURCE_DIR}/plugins.qmltypes"
        "\n"
        ""
        )
endif()
