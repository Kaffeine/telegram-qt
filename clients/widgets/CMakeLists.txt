project(testApp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(testApp_SOURCES
    main.cpp
    MainWindow.cpp
#    CFileManager.cpp
    CPeerModel.cpp
    CContactModel.cpp
    CContactsFilterModel.cpp
    CMessageModel.cpp
#    CChatInfoModel.cpp
    CDialogModel.cpp
)

set(testApp_HEADERS
    MainWindow.hpp
#    CFileManager.hpp
    CPeerModel.hpp
    CContactModel.hpp
    CContactsFilterModel.hpp
    CMessageModel.hpp
#    CChatInfoModel.hpp
    CDialogModel.hpp
)

set(testApp_FORMS
    MainWindow.ui
)

set(testApp_RESOURCES
    resources.qrc
)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(Qt5 5.9 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(testApp-qt${QT_VERSION_MAJOR} ${testApp_SOURCES} ${testApp_FORMS} ${testApp_RESOURCES})

target_include_directories(testApp-qt${QT_VERSION_MAJOR} PRIVATE
    ${QT5_INCLUDES}
)

target_link_libraries(testApp-qt${QT_VERSION_MAJOR} LINK_PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Network
)

target_link_libraries(testApp-qt${QT_VERSION_MAJOR} LINK_PUBLIC
    TelegramQt${QT_VERSION_MAJOR}
)
