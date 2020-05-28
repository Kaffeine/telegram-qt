cmake_minimum_required(VERSION 3.6...3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(TelegramQt
    VERSION 0.2.0
    LANGUAGES CXX
)

set(TELEGRAM_QT_ABI "${TelegramQt_VERSION_MAJOR}.${TelegramQt_VERSION_MINOR}")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules")

include(GNUInstallDirs)
include(FeatureSummary)

# Local includes
include(CompilerSettings)
include(ProjectOption)

project_option(BUILD_CLIENT "Build a client app" FALSE)
project_option(BUILD_DOCUMENTATION "Enable generation of Qt Help (qch) file" FALSE)
project_option(BUILD_GENERATOR "Build protocol code generator (useful for developers)" FALSE)
project_option(BUILD_QML_IMPORT "Enable compilation of qml import plugin" TRUE)
project_option(BUILD_SERVER "Build server" FALSE)
project_option(ENABLE_SERVER_PLUGINS "Enable server plugins (enable build and embed)" TRUE)
project_option(BUILD_SHARED_LIBS "Compile libraries as shared" TRUE)
project_option(BUILD_TESTS "Enable compilation of automated tests" FALSE)

project_option(DEVELOPER_BUILD "Enable extra debug codepaths, like asserts and extra output" FALSE)
project_option(EXPORT_INTERNAL_API "Export internal and unstable API" FALSE)

if(NOT ${CMAKE_VERSION} VERSION_LESS 3.9)
    project_option(ENABLE_IPO "Enable interprocedural optimizations" FALSE)
endif()

if(TELEGRAMQT_ENABLE_IPO)
    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_supported OUTPUT ipo_output)
    if(NOT ipo_supported)
        message(SEND_ERROR "Unable to enable IPO: ${ipo_output}")
    endif()
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CCache)

    set(OVERRIDE_CXX_STANDARD 11 CACHE STRING "Compile with custom C++ standard version")
    set(CMAKE_CXX_STANDARD ${OVERRIDE_CXX_STANDARD})
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)

    if(TELEGRAMQT_ENABLE_IPO)
        set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    endif()
endif()

set(CMAKE_AUTOMOC TRUE)

if(TELEGRAMQT_DEVELOPER_BUILD)
    set(TELEGRAMQT_EXPORT_INTERNAL_API TRUE)
endif()

set(QT_VERSION_MAJOR "5")
set(QT_COMPONENTS Core Network)

set(INSTALL_QML_IMPORT_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt${QT_VERSION_MAJOR}/qml"
    CACHE PATH "Custom QML import installation directory")

set(INSTALL_PLUGINS_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt${QT_VERSION_MAJOR}/plugins/TelegramQt"
    CACHE PATH "Custom plugins installation directory")

if(TELEGRAMQT_BUILD_TESTS)
    list(APPEND QT_COMPONENTS Test)
endif()

if(TELEGRAMQT_BUILD_QML_IMPORT)
    list(APPEND QT_COMPONENTS Qml)
endif()

# For XMPP server
list(APPEND QT_COMPONENTS Xml)

if(TELEGRAMQT_BUILD_SERVER)
    if(NOT TELEGRAMQT_EXPORT_INTERNAL_API)
        message(SEND_ERROR "Unable to build the server because the internal API export disabled")
    endif()
    # QtGui is used by the server to resize images
    list(APPEND QT_COMPONENTS Gui)
    if(TELEGRAMQT_DEVELOPER_BUILD)
        # In Developer mode the server shows auth code via Notification DBus iface
        list(APPEND QT_COMPONENTS DBus)
    endif()
endif()

set(QT_MINUMUM_VERSION 5.5.0)

find_package(Qt5 ${QT_MINUMUM_VERSION} REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

if (NOT BUILD_VERSION)
    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/.git")
        execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
            OUTPUT_VARIABLE BUILD_VERSION
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
    else()
        set(BUILD_VERSION "unknown")
    endif()
endif()

# Add the source subdirectories
add_subdirectory(TelegramQt)

if(TELEGRAMQT_BUILD_QML_IMPORT)
    add_subdirectory(imports/TelegramQt)
    set(QML_IMPORT_PATH
            ${CMAKE_CURRENT_SOURCE_DIR}/imports
            ${CMAKE_CURRENT_BINARY_DIR}/imports
        CACHE
        STRING "QML Import path for IDE code model"
        FORCE
    )
endif()

if(TELEGRAMQT_BUILD_CLIENT)
    add_subdirectory(clients)
endif()

if(TELEGRAMQT_BUILD_TESTS)
    if(NOT TELEGRAMQT_EXPORT_INTERNAL_API)
        message(SEND_ERROR "Unable to the tests because the internal API export disabled")
    endif()
    enable_testing()
    add_subdirectory(TelegramQt/tests)
    add_subdirectory(tests/data)
    if(TELEGRAMQT_BUILD_SERVER)
        # All top-level tests are "client-server"
        add_subdirectory(tests)
    else()
        message(STATUS "Some tests are disabled because the server is not a part of the build")
    endif()
endif()

if(TELEGRAMQT_BUILD_SERVER)
    add_subdirectory(server)
endif()

if(TELEGRAMQT_BUILD_GENERATOR)
    if(Qt5_VERSION VERSION_LESS "5.6.0")
        message(WARNING "Use Qt 5.6.0 or higher to build GeneratorNG")
    else()
        add_subdirectory(generator)
    endif()
endif()

if(TELEGRAMQT_BUILD_DOCUMENTATION)
    add_subdirectory(doc)
endif()

message(STATUS "${PROJECT_NAME} configuration:")
message(STATUS "  Export internal API: ${TELEGRAMQT_EXPORT_INTERNAL_API}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Qt: ${Qt5_VERSION} at ${_qt5Core_install_prefix}")

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
