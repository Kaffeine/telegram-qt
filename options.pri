options = developer-build
#options += static-lib

# Installation directories
isEmpty(INSTALL_PREFIX) {
    unix {
        INSTALL_PREFIX = /usr/local
    } else {
        INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
    }
}

isEmpty(INSTALL_LIB_DIR) {
    INSTALL_LIB_DIR = $$INSTALL_PREFIX/lib
}

isEmpty(INSTALL_INCLUDE_DIR) {
    INSTALL_INCLUDE_DIR = $$INSTALL_PREFIX/include
}

isEmpty(INSTALL_QML_IMPORT_DIR) {
    INSTALL_QML_IMPORT_DIR = $$[QT_INSTALL_QML]
}
