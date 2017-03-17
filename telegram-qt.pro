include(options.pri)

message("It is highly recommended to use CMake instead of QMake for packaging!")

!greaterThan(QT_MAJOR_VERSION, 4) {
    error(This project requires Qt5)
}

TEMPLATE = subdirs
SUBDIRS = TelegramQt

isEmpty(BUILD_ONLY_LIBRARY) {
    BUILD_ONLY_LIBRARY = "false"
}
isEmpty(BUILD_QML_IMPORT) {
    BUILD_QML_IMPORT = "true"
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
        SUBDIRS += TelegramQt/generator-ng
    }
}

OTHER_FILES += CMakeLists.txt
OTHER_FILES += rpm/telegram-qt$${QT_MAJOR_VERSION}.spec
