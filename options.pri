#options = developer-build
#options += static-lib

# Installation directories
isEmpty(INSTALL_PREFIX) {
    unix {
        INSTALL_PREFIX = /usr/local
    } else {
        INSTALL_PREFIX = $$[QT_INSTALL_PREFIX]
    }
}

isEmpty(INSTALL_LIBDIR) {
    INSTALL_LIBDIR = $$INSTALL_PREFIX/lib
}

isEmpty(INSTALL_INCLUDE_DIR) {
    INSTALL_INCLUDE_DIR = $$INSTALL_PREFIX/include
}
