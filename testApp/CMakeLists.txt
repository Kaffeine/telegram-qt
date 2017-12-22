project(testApp)

set(testApp_SOURCES
    main.cpp
    MainWindow.cpp
    CFileManager.cpp
    CPeerModel.cpp
    CContactModel.cpp
    CContactsFilterModel.cpp
    CMessageModel.cpp
    CChatInfoModel.cpp
    CDialogModel.cpp
)

set(testApp_HEADERS
    MainWindow.hpp
    CFileManager.hpp
    CPeerModel.hpp
    CContactModel.hpp
    CContactsFilterModel.hpp
    CMessageModel.hpp
    CChatInfoModel.hpp
    CDialogModel.hpp
)

set(testApp_FORMS
    MainWindow.ui
)

set(testApp_RESOURCES
    resources.qrc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

if (USE_QT4)
    QT4_WRAP_UI(testApp_FORMS_HEADERS ${testApp_FORMS})
    QT4_ADD_RESOURCES(testApp_RESOURCES_RCC ${testApp_RESOURCES})
else()
    QT5_WRAP_UI(testApp_FORMS_HEADERS ${testApp_FORMS})
    QT5_ADD_RESOURCES(testApp_RESOURCES_RCC ${testApp_RESOURCES})
endif()

add_executable(testApp-qt${QT_VERSION_MAJOR} ${testApp_SOURCES} ${testApp_FORMS_HEADERS} ${testApp_RESOURCES_RCC})

set_target_properties(testApp-qt${QT_VERSION_MAJOR} PROPERTIES AUTOMOC TRUE)

if (USE_QT4)
    target_include_directories(testApp-qt${QT_VERSION_MAJOR} PRIVATE
        ${QT_INCLUDES}
    )
    target_link_libraries(testApp-qt${QT_VERSION_MAJOR} LINK_PRIVATE
        ${QT_QTCORE_LIBRARY}
        ${QT_QTGUI_LIBRARY}
        ${QT_QTNETWORK_LIBRARY}
    )
else()
    target_include_directories(testApp-qt${QT_VERSION_MAJOR} PRIVATE
        ${QT5_INCLUDES}
    )

    target_link_libraries(testApp-qt${QT_VERSION_MAJOR} LINK_PUBLIC
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Network
    )
endif()

target_link_libraries(testApp-qt${QT_VERSION_MAJOR} LINK_PUBLIC
    TelegramQt${QT_VERSION_MAJOR}
)
