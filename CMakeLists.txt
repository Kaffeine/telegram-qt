project(TelegramQt)

cmake_minimum_required(VERSION 2.8)

set(TELEGRAM_QT_VERSION_MAJOR 0)
set(TELEGRAM_QT_VERSION_MINOR 1)
set(TELEGRAM_QT_VERSION_PATCH 0)

set(TELEGRAM_QT_VERSION "${TELEGRAM_QT_VERSION_MAJOR}.${TELEGRAM_QT_VERSION_MINOR}.${TELEGRAM_QT_VERSION_PATCH}")
set(TELEGRAM_QT_ABI "${TELEGRAM_QT_VERSION_MAJOR}.${TELEGRAM_QT_VERSION_MINOR}")

# Add an option for building tests
option(ENABLE_TESTS "Enable compilation of automated tests" FALSE)
# Add an option for building tests
option(ENABLE_TESTAPP "Enable compilation of testing application" FALSE)
# Add an option for building tests
option(STATIC_BUILD "Compile static library instead of shared" FALSE)
# Add an option for dev build
option(DEVELOPER_BUILD "Enable extra debug codepaths, like asserts and extra output" FALSE)

if (USE_QT4)
    set(QT_VERSION_MAJOR "4")

    if(ENABLE_TESTAPP)
        find_package(Qt4 4.8.0 REQUIRED QtCore QtNetwork QtGui)
    else()
        find_package(Qt4 4.8.0 REQUIRED QtCore QtNetwork)
    endif()
else()
    set(QT_VERSION_MAJOR "5")

    if(ENABLE_TESTAPP)
        find_package(Qt5 REQUIRED COMPONENTS Core Network Gui Widgets)
    else()
        find_package(Qt5 REQUIRED COMPONENTS Core Network)
    endif()
endif()

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

include(GNUInstallDirs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Add the source subdirectories
add_subdirectory(TelegramQt)

#if(ENABLE_TESTS)
#    add_subdirectory(tests)
#endif()

if(ENABLE_TESTAPP)
    add_subdirectory(testApp)
endif()
