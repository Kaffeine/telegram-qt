#find_package(Qt5 5.6.0 REQUIRED COMPONENTS Core Help)
find_package(Doxygen REQUIRED)

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(ECMAddQch)

# Documentation

ecm_add_qch(
    TelegramQt_QCH
    NAME TelegramQt
    VERSION ${PROJECT_VERSION}
    ORG_DOMAIN org.telegramqt
    SOURCE_DIRS
        ../TelegramQt ../TelegramQt/doc
    LINK_QCHS
        Qt5Core_QCH
    TAGFILE_INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/tags
    QCH_INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/qch
    COMPONENT Devel
)
