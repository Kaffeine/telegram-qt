
include(options.pri)

TEMPLATE = subdirs
SUBDIRS = TelegramQt
SUBDIRS += testApp
CONFIG += ordered

contains(options, developer-build) {
    SUBDIRS += TelegramQt/tests
    SUBDIRS += TelegramQt/generator
    greaterThan(QT_MAJOR_VERSION, 4) {
        SUBDIRS += TelegramQt/generator-ng
    }
}

OTHER_FILES += CMakeLists.txt
