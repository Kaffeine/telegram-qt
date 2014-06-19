project(TelegramQt)

cmake_minimum_required(VERSION 2.8)

set(TELEGRAM_QT_VERSION_MAJOR 0)
set(TELEGRAM_QT_VERSION_MINOR 0)
set(TELEGRAM_QT_VERSION_PATCH 1)

set(TELEGRAM_QT_VERSION "${SIMPLECM_VERSION_MAJOR}.${SIMPLECM_VERSION_MINOR}.${SIMPLECM_VERSION_PATCH}")

# Required dependencies
# Find qt4 version >= 4.6 or qt5 >= 5.0.0
set(QT4_MIN_VERSION "4.6.0")
set(QT4_MAX_VERSION "5.0.0")
set(QT5_MIN_VERSION "5.0.0")
set(QT5_MAX_VERSION "6.0.0")
find_package(Qt REQUIRED)

IF(QT_VERSION_MAJOR MATCHES 5)
    # It is QtCore for Qt4 but Qt5Core for Qt5 in pkg-config
    SET(QT_VERSION_PC 5)
ENDIF(QT_VERSION_MAJOR MATCHES 5)

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
