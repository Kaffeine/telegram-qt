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
