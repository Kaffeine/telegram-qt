include(options.pri)
message("QMake build is deprecated. Use CMake instead.")

# The macro is taken from QtCreator
defineTest(minQtVersion) {
    maj = $$1
    min = $$2
    patch = $$3
    isEqual(QT_MAJOR_VERSION, $$maj) {
        isEqual(QT_MINOR_VERSION, $$min) {
            isEqual(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
            greaterThan(QT_PATCH_VERSION, $$patch) {
                return(true)
            }
        }
        greaterThan(QT_MINOR_VERSION, $$min) {
            return(true)
        }
    }
    greaterThan(QT_MAJOR_VERSION, $$maj) {
        return(true)
    }
    return(false)
}

!minQtVersion(5, 5, 0) {
    message("Cannot build TelegramQt with Qt version $${QT_VERSION}.")
    error("Use at least Qt 5.5.0.")
}

TEMPLATE = subdirs
SUBDIRS = TelegramQt

isEmpty(BUILD_ONLY_LIBRARY) {
    BUILD_ONLY_LIBRARY = "false"
}
isEmpty(BUILD_WIDGETS_CLIENT) {
    equals(BUILD_ONLY_LIBRARY, "true") {
        BUILD_WIDGETS_CLIENT = "false"
    } else {
        BUILD_WIDGETS_CLIENT = "true"
    }
}
isEmpty(BUILD_QML_CLIENT) {
    BUILD_QML_CLIENT = "false"
}

isEmpty(BUILD_QML_IMPORT) {
    BUILD_QML_IMPORT = "true"
}

equals(BUILD_QML_IMPORT, "true") {
    SUBDIRS += imports/TelegramQtQml
}

equals(BUILD_QCH, "true") {
    include(doc/doc.pri)
}

equals(BUILD_WIDGETS_CLIENT, "true") {
    SUBDIRS += clients/widgets
    CONFIG += ordered
}

equals(BUILD_QML_IMPORT, "true") {
    SUBDIRS += clients/qml-client
    CONFIG += ordered
}

contains(options, developer-build) {
    SUBDIRS += tests
    SUBDIRS += TelegramQt/tests
    minQtVersion(5, 6, 0) {
        SUBDIRS += generator
        SUBDIRS += generator/tests
    } else {
        message("Use Qt 5.6.0 or higher to build GeneratorNG")
    }
}


contains(options, server) {
    SUBDIRS += server
}

OTHER_FILES += CMakeLists.txt
OTHER_FILES += README.md
OTHER_FILES += .travis.yml
OTHER_FILES += rpm/telegram-qt.spec
