project(cli-client)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(app_SOURCES
    main.cpp
)

find_package(Qt5 5.9 COMPONENTS Core REQUIRED)

add_executable(cli-client-qt${QT_VERSION_MAJOR} ${app_SOURCES})

target_link_libraries(cli-client-qt${QT_VERSION_MAJOR} LINK_PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    TelegramQt${QT_VERSION_MAJOR}::Core
)

install(
    TARGETS cli-client-qt${QT_VERSION_MAJOR}
    DESTINATION ${CMAKE_INSTALL_BINDIR}
    COMPONENT Runtime
)
