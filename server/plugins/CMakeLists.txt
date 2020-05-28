function(process_plugin)
    set(ARG_PLUGIN_NAME ${ARGV0})

    get_target_property(PLUGIN_LIB_TYPE ${ARG_PLUGIN_NAME} TYPE)
    if("${PLUGIN_LIB_TYPE}" STREQUAL "STATIC_LIBRARY")
        message("Register static plugin ${ARG_PLUGIN_NAME}")
        target_compile_definitions(${ARG_PLUGIN_NAME} PRIVATE
            QT_STATICPLUGIN
        )
        set_property(TARGET TelegramQt${QT_VERSION_MAJOR}PluginsLoader
            APPEND
            PROPERTY RegisteredPlugins ${ARG_PLUGIN_NAME}
        )
    else()
        message("Install dynamic plugin ${ARG_PLUGIN_NAME}")
        install(
            TARGETS ${ARG_PLUGIN_NAME}
            DESTINATION ${INSTALL_PLUGINS_DIR}
            COMPONENT Runtime
        )
    endif()
endfunction()

add_subdirectory(dummy-federation)
add_subdirectory(xmpp-federation)
