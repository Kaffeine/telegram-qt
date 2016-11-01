include(options.pri)

!greaterThan(QT_MAJOR_VERSION, 4) {
    error(This project requires Qt5)
}

TEMPLATE = subdirs
SUBDIRS = TelegramQt
SUBDIRS += testApp
CONFIG += ordered

contains(options, developer-build) {
    SUBDIRS += TelegramQt/tests
    SUBDIRS += TelegramQt/generator
    SUBDIRS += TelegramQt/generator-ng
}

OTHER_FILES += CMakeLists.txt
