
include(options.pri)

TEMPLATE = subdirs
SUBDIRS = telegram-qt
SUBDIRS += testApp
SUBDIRS += cmdApp
CONFIG += ordered

contains(options, developer-build) {
    SUBDIRS += telegram-qt/tests
    SUBDIRS += telegram-qt/generator
    greaterThan(QT_MAJOR_VERSION, 4) {
        SUBDIRS += telegram-qt/generator-ng
    }
}
