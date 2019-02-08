cmake_minimum_required(VERSION 3.1)

# Required by cmake >= 3.12 to allow usage of <Package>_ROOT variables
#   for find_package() calls. Useful for Windows
cmake_policy(SET CMP0074 NEW)

project(TelegramQt
    VERSION 0.2.0
    LANGUAGES CXX
)

set(TELEGRAM_QT_VERSION "${PROJECT_VERSION}")
set(TELEGRAM_QT_ABI "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Add an option for building tests
option(ENABLE_TESTS "Enable compilation of automated tests" FALSE)

option(BUILD_CLIENT "Build a client app" FALSE)

option(ENABLE_COVERAGE_BUILD "Build the project with code-coverage support" FALSE)
option(ENABLE_COVERAGE_HTML "Generate an HTML report for the code-coverage analysis result" FALSE)

# Add an option for building tests
option(ENABLE_QML_IMPORT "Enable compilation of qml import plugin" TRUE)
# Add an option for building tests
option(ENABLE_QCH_BUILD "Enable generation of Qt Help (qch) file" FALSE)
# Add an option for building tests
option(STATIC_BUILD "Compile static library instead of shared" FALSE)
# Add an option for building server
option(BUILD_SERVER "Build server" FALSE)
# Add an option for building GeneratorNG
option(BUILD_GENERATOR "Build protocol code generator" FALSE)
# Add an option for dev build
option(DEVELOPER_BUILD "Enable extra debug codepaths, like asserts and extra output" FALSE)

set(QT_VERSION_MAJOR "5")
set(QT_COMPONENTS Core Network)

if (BUILD_SERVER)
    if (DEVELOPER_BUILD)
        list(APPEND QT_COMPONENTS DBus)
    endif()
endif()

if(WIN32)
    include(WindowsInstallDirs)
else()
    include(GNUInstallDirs)
endif()
include(FeatureSummary)

find_package(Qt5 5.5.0 REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

if (NOT WIN32)
    # MSVC Produces >130k warnings with this
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

if (ENABLE_COVERAGE_BUILD)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_SHARED_LINKER_FLAGS="${CMAKE_SHARED_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    SET(CMAKE_EXE_LINKER_FLAGS="${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Add the source subdirectories
add_subdirectory(TelegramQt)

if (ENABLE_QML_IMPORT)
    add_subdirectory(imports/TelegramQtQml)
endif()

if (BUILD_CLIENT)
    add_subdirectory(clients)
endif()

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(TelegramQt/tests)
    add_subdirectory(tests/data)
    if (BUILD_SERVER)
        add_subdirectory(tests)
    endif()
endif()

if (BUILD_SERVER)
    add_subdirectory(server)
endif()

if (BUILD_GENERATOR)
    if (Qt5_VERSION VERSION_LESS "5.6.0")
        message(WARNING "Use Qt 5.6.0 or higher to build GeneratorNG")
    else()
        add_subdirectory(generator)
    endif()
endif()

if (ENABLE_QCH_BUILD)
    add_subdirectory(doc)
endif()

if (ENABLE_COVERAGE_BUILD)
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

    if (ENABLE_COVERAGE_HTML)
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
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  Qt: ${Qt5_VERSION} at ${_qt5Core_install_prefix}")

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
