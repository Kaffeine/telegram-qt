project(TelegramQt)

cmake_minimum_required(VERSION 2.8)

set(TELEGRAM_QT_VERSION_MAJOR 0)
set(TELEGRAM_QT_VERSION_MINOR 0)
set(TELEGRAM_QT_VERSION_PATCH 1)

set(TELEGRAM_QT_VERSION "${TELEGRAM_QT_VERSION_MAJOR}.${TELEGRAM_QT_VERSION_MINOR}.${TELEGRAM_QT_VERSION_PATCH}")

# Required dependencies
# Find qt4 version >= 4.6 or qt5 >= 5.0.0
if (USE_QT4)
    set(QT_VERSION_MAJOR "4")
    find_package(Qt4 4.6.0 REQUIRED QtCore QtNetwork)
else()
    set(QT_VERSION_MAJOR "5")
    find_package(Qt5 REQUIRED COMPONENTS Network)
endif()

include(GNUInstallDirs)
                    
# Add an option for building tests
option(ENABLE_TESTS "Enable compilation of automated tests" TRUE)
# Add an option for building tests
option(ENABLE_TESTAPP "Enable compilation of testing application" TRUE)

# Add the source subdirectories
add_subdirectory(telegram-qt)

#if(ENABLE_TESTS)
#    add_subdirectory(tests)
#endif()

#if(ENABLE_TESTAPP)
#    add_subdirectory(testApp)
#endif()
