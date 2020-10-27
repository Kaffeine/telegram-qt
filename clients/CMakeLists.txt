if(TELEGRAMQT_BUILD_QML_IMPORT)
    add_subdirectory(qml-client)
endif()

add_subdirectory(cli)

# The widget client is not ported to the new API yet
add_subdirectory(widgets)
