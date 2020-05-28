
# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

# the RPATH to be used when installing
SET(CMAKE_INSTALL_RPATH "")

# don't add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

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

target_link_libraries(TelegramTestServer PUBLIC
    Qt5::Core
    Qt5::Network

    TelegramQt${QT_VERSION_MAJOR}::Server
    TelegramQt${QT_VERSION_MAJOR}::Test
    test_keys_data
)

if(TELEGRAMQT_ENABLE_SERVER_PLUGINS)
    target_link_libraries(TelegramTestServer PUBLIC
        TelegramQt${QT_VERSION_MAJOR}::PluginsLoader
    )
endif()

if(TELEGRAMQT_DEVELOPER_BUILD)
    target_compile_definitions(TelegramTestServer PRIVATE
        DEVELOPER_BUILD
        QT_DEPRECATED_WARNINGS
        USE_DBUS_NOTIFIER
    )

    target_link_libraries(TelegramTestServer PUBLIC
        Qt5::DBus
    )
endif()

install(
    TARGETS TelegramTestServer
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
)
