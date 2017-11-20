include(options.pri)

message("It is highly recommended to use CMake instead of QMake for packaging!")

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

TEMPLATE = subdirs
SUBDIRS = TelegramQt

greaterThan(QT_MAJOR_VERSION, 4) {
    isEmpty(BUILD_ONLY_LIBRARY) {
        BUILD_ONLY_LIBRARY = "false"
    }
    isEmpty(BUILD_QML_IMPORT) {
        BUILD_QML_IMPORT = "true"
    }
} else {
    isEmpty(BUILD_ONLY_LIBRARY) {
        BUILD_ONLY_LIBRARY = "false"
    }
    isEmpty(BUILD_QML_IMPORT) {
        BUILD_QML_IMPORT = "false"
    }
}

equals(BUILD_QML_IMPORT, "true") {
    SUBDIRS += imports/TelegramQtQml
}

!equals(BUILD_ONLY_LIBRARY, "true") {
    SUBDIRS += testApp
    CONFIG += ordered

    contains(options, developer-build) {
        SUBDIRS += TelegramQt/tests
        SUBDIRS += TelegramQt/generator
        minQtVersion(5, 6, 0) {
            SUBDIRS += TelegramQt/generator-ng
            SUBDIRS += TelegramQt/generator-ng/tests
        } else {
            message("Use Qt 5.6.0 or higher to build GeneratorNG")
        }
    }
}

OTHER_FILES += CMakeLists.txt
OTHER_FILES += README.md
OTHER_FILES += rpm/telegram-qt$${QT_MAJOR_VERSION}.spec
