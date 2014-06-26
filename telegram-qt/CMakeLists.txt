
set(telegram_qt_SOURCES
    CAppInformation.cpp
    CTelegramCore.cpp
    CTelegramConnection.cpp
    CTelegramTransport.hpp
    CTelegramStream.cpp
    CTcpTransport.cpp
    CRawStream.cpp
    Utils.cpp
)

set(telegram_qt_HEADERS
    telegramqt_export.h
    SDcInfo.hpp
    CTelegramCore.hpp
    CTelegramConnection.hpp
    TLTypes.hpp
    CAppInformation.hpp
    crypto-rsa.hpp
    crypto-aes.hpp
)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_BINARY_DIR}
                    ${QT_INCLUDES})
                    
add_definitions(-DTELEGRAMQT_LIBRARY)

add_library(telegram-qt${QT_VERSION_MAJOR} STATIC ${telegram_qt_SOURCES})

set_target_properties(telegram-qt${QT_VERSION_MAJOR} PROPERTIES AUTOMOC TRUE)

install(
    TARGETS telegram-qt${QT_VERSION_MAJOR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    COMPONENT Library
)

install(
    DIRECTORY TelegramQt
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/telegram-qt${QT_VERSION_MAJOR}
    COMPONENT Devel
)

install(
    FILES ${telegram_qt_HEADERS}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/telegram-qt${QT_VERSION_MAJOR}/TelegramQt
    COMPONENT Devel
)
