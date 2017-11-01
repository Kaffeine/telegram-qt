project(TelegramQt)

cmake_minimum_required(VERSION 2.8)

set(TELEGRAM_QT_VERSION_MAJOR 0)
set(TELEGRAM_QT_VERSION_MINOR 2)
set(TELEGRAM_QT_VERSION_PATCH 0)

set(TELEGRAM_QT_VERSION "${TELEGRAM_QT_VERSION_MAJOR}.${TELEGRAM_QT_VERSION_MINOR}.${TELEGRAM_QT_VERSION_PATCH}")
set(TELEGRAM_QT_ABI "${TELEGRAM_QT_VERSION_MAJOR}.${TELEGRAM_QT_VERSION_MINOR}")

# Add an option for building tests
option(ENABLE_TESTS "Enable compilation of automated tests" FALSE)
# Add an option for building tests
option(ENABLE_TESTAPP "Enable compilation of testing application" FALSE)
# Add an option for building tests
option(ENABLE_QML_IMPORT "Enable compilation of qml import plugin" TRUE)
# Add an option for building tests
option(STATIC_BUILD "Compile static library instead of shared" FALSE)
# Add an option for building GeneratorNG
option(BUILD_GENERATOR "Build protocol code generator" FALSE)
# Add an option for dev build
option(DEVELOPER_BUILD "Enable extra debug codepaths, like asserts and extra output" FALSE)

set(QT_VERSION_MAJOR "5")
set(QT_COMPONENTS Core Network)

if(ENABLE_TESTAPP)
    list(APPEND QT_COMPONENTS Gui Widgets)
endif()

find_package(Qt5 5.6.0 REQUIRED COMPONENTS ${QT_COMPONENTS})
message("-- Found Qt version: ${Qt5_VERSION}")
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Add the source subdirectories
add_subdirectory(TelegramQt)

if (ENABLE_QML_IMPORT)
    add_subdirectory(imports/TelegramQtQml)
endif()

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(TelegramQt/tests)
endif()

if (BUILD_GENERATOR)
    add_subdirectory(TelegramQt/generator-ng)
endif()

if(ENABLE_TESTAPP)
    add_subdirectory(testApp)
endif()
