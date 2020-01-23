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
include(CCache)

set(OVERRIDE_CXX_STANDARD 11 CACHE STRING "Compile with custom C++ standard version")
set(INSTALL_QML_IMPORT_DIR "${CMAKE_INSTALL_FULL_LIBDIR}/qt5/qml"
    CACHE PATH "Custom QML import installation directory")

set(CMAKE_CXX_STANDARD ${OVERRIDE_CXX_STANDARD})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

set(CMAKE_AUTOMOC TRUE)

option(BUILD_CLIENT "Build a client app" FALSE)
option(BUILD_DOCUMENTATION "Enable generation of Qt Help (qch) file" FALSE)
option(BUILD_GENERATOR "Build protocol code generator (useful for developers)" FALSE)
option(BUILD_QML_IMPORT "Enable compilation of qml import plugin" TRUE)
option(BUILD_SERVER "Build server" FALSE)
option(BUILD_SHARED_LIBS "Compile libraries as shared" TRUE)
option(BUILD_TESTS "Enable compilation of automated tests" FALSE)

option(DEVELOPER_BUILD "Enable extra debug codepaths, like asserts and extra output" FALSE)
option(EXPORT_INTERNAL_API "Export internal and unstable API" FALSE)

if(DEVELOPER_BUILD)
    set(EXPORT_INTERNAL_API TRUE)
endif()

if(EXPORT_INTERNAL_API)
    set(TELEGRAMQT_EXPORT_INTERNAL_API TRUE)
else()
    set(TELEGRAMQT_EXPORT_INTERNAL_API FALSE)
endif()

option(ENABLE_COVERAGE_BUILD "Build the project with code-coverage support" FALSE)
option(ENABLE_COVERAGE_HTML "Generate an HTML report for the code-coverage analysis result" FALSE)

set(QT_VERSION_MAJOR "5")
set(QT_COMPONENTS Core Network)

if(BUILD_TESTS)
    list(APPEND QT_COMPONENTS Test)
endif()

if(BUILD_QML_IMPORT)
    list(APPEND QT_COMPONENTS Qml)
endif()

if(BUILD_SERVER)
    if(NOT EXPORT_INTERNAL_API)
        message(SEND_ERROR "Unable to build the server because the internal API export disabled")
    endif()
    # QtGui is used by the server to resize images
    list(APPEND QT_COMPONENTS Gui)
    if(DEVELOPER_BUILD)
        # In Developer mode the server shows auth code via Notification DBus iface
        list(APPEND QT_COMPONENTS DBus)
    endif()
endif()

set(QT_MINUMUM_VERSION 5.5.0)

find_package(Qt5 ${QT_MINUMUM_VERSION} REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")
endif()

if((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND NOT APPLE) OR
        (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND NOT APPLE) OR
        (CMAKE_CXX_COMPILER_ID STREQUAL "Intel" AND NOT WIN32))
    # Linker warnings should be treated as errors
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--fatal-warnings ${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--fatal-warnings ${CMAKE_MODULE_LINKER_FLAGS}")

    # Do not allow undefined symbols, even in non-symbolic shared libraries
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_MODULE_LINKER_FLAGS}")
endif()

if(ENABLE_COVERAGE_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_SHARED_LINKER_FLAGS="${CMAKE_SHARED_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS="${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

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

if(BUILD_QML_IMPORT)
    add_subdirectory(imports/TelegramQt)
    set(QML_IMPORT_PATH
            ${CMAKE_CURRENT_SOURCE_DIR}/imports
            ${CMAKE_CURRENT_BINARY_DIR}/imports
        CACHE
        STRING "QML Import path for IDE code model"
        FORCE
    )
endif()

if(BUILD_CLIENT)
    add_subdirectory(clients)
endif()

if(BUILD_TESTS)
    if(NOT EXPORT_INTERNAL_API)
        message(SEND_ERROR "Unable to the tests because the internal API export disabled")
    endif()
    enable_testing()
    add_subdirectory(TelegramQt/tests)
    add_subdirectory(tests/data)
    if(BUILD_SERVER)
        # All top-level tests are "client-server"
        add_subdirectory(tests)
    else()
        message(STATUS "Some tests are disabled because the server is not a part of the build")
    endif()
endif()

if(BUILD_SERVER)
    add_subdirectory(server)
endif()

if(BUILD_GENERATOR)
    if(Qt5_VERSION VERSION_LESS "5.6.0")
        message(WARNING "Use Qt 5.6.0 or higher to build GeneratorNG")
    else()
        add_subdirectory(generator)
    endif()
endif()

if(BUILD_DOCUMENTATION)
    add_subdirectory(doc)
endif()

if(ENABLE_COVERAGE_BUILD)
    # Code coverage
    find_program(LCOV_PATH lcov)

    set(coverage_full_info "${CMAKE_BINARY_DIR}/coverage-full.info")
    set(coverage_info "${CMAKE_BINARY_DIR}/coverage.info")

    add_custom_command(OUTPUT ${coverage_info}
        COMMAND ${LCOV_PATH} --directory . --capture --output-file ${coverage_full_info}
        COMMAND ${LCOV_PATH} --remove ${coverage_full_info}
            '*/tests/*'
            '*/server/*'
            '/usr/*'
            '/opt/*'
            '*/moc_*.cpp'
            --output-file ${coverage_info}
        COMMAND ${LCOV_PATH} --list ${coverage_info}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        COMMENT "Resetting code coverage counters to zero.\nProcessing code coverage counters and generating report."
    )
    add_custom_target(coverage DEPENDS ${coverage_info})

    if(ENABLE_COVERAGE_HTML)
        find_program(GENHTML_PATH genhtml)
        add_custom_target(coverage_html
            COMMAND ${GENHTML_PATH} -o coverage_report ${coverage_info}
            DEPENDS coverage
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
            COMMENT "Generate HTML report for the coverage analysis"
        )
    endif()
endif()

message(STATUS "${PROJECT_NAME} configuration:")
message(STATUS "  Export internal API: ${EXPORT_INTERNAL_API}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Qt: ${Qt5_VERSION} at ${_qt5Core_install_prefix}")

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
