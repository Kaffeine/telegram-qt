
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/qxmpp)
    add_subdirectory(qxmpp)
else()
    find_package(QXmpp 1.0 QUIET CONFIG)
endif()

if(TARGET QXmpp::QXmpp)
    set(xmpp_SOURCES
        XmppFederation.cpp
        XmppFederation.hpp
        XmppGroupChat.cpp
        XmppGroupChat.hpp
        XmppPlugin.cpp
        XmppServerExtension.cpp
        XmppServerExtension.hpp
        XmppUser.cpp
        XmppUser.hpp
    )

    add_library(XmppFederalizationPlugin STATIC
        ${xmpp_SOURCES}
    )
    target_link_libraries(XmppFederalizationPlugin PUBLIC
        Qt5::Core
        Qt5::Network
        QXmpp::QXmpp
        TelegramQt${QT_VERSION_MAJOR}::Server
    )

    process_plugin(XmppFederalizationPlugin)
endif()
