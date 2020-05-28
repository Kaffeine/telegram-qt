add_library(DummyFederationPlugin STATIC DummyFederationPlugin.cpp)

target_link_libraries(DummyFederationPlugin
    Qt5::Core
    TelegramQt${QT_VERSION_MAJOR}::Server
)

process_plugin(DummyFederationPlugin)
