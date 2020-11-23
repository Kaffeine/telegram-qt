
set(QT_VERSION_MAJOR "5")
set(QT_COMPONENTS Core Network)

if(TELEGRAMQT_DEVELOPER_BUILD)
    list(APPEND QT_COMPONENTS DBus)
endif()

find_package(Qt5 REQUIRED COMPONENTS ${QT_COMPONENTS})
find_package(ZLIB REQUIRED)

set(server_SOURCES
    main.cpp
)

add_executable(TelegramTestServer ${server_SOURCES})
target_link_libraries(TelegramTestServer
    TelegramQt${QT_VERSION_MAJOR}::Server
    TelegramQt${QT_VERSION_MAJOR}::Test
    test_keys_data
)

if(TELEGRAMQT_DEVELOPER_BUILD)
    target_compile_definitions(TelegramTestServer PRIVATE
        DEVELOPER_BUILD
        QT_DEPRECATED_WARNINGS
    )
endif()

install(
    TARGETS TelegramTestServer
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
)
