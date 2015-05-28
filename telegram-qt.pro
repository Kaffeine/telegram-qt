
include(options.pri)

TEMPLATE = subdirs
SUBDIRS = telegram-qt
SUBDIRS += testApp
CONFIG += ordered

contains(options, developer-build) {
    SUBDIRS += telegram-qt/tests
    SUBDIRS += telegram-qt/generator
    greaterThan(QT_MAJOR_VERSION, 4) {
        SUBDIRS += telegram-qt/generator-ng
    }
}

# modern compiler needed by cmdApp.
greaterThan(QT_MAJOR_VERSION, 4) {
    win*-msvc2013|win*-msvc2015 {
        SUBDIRS += cmdApp
    }
    # add gcc/clang... checks
    else {
        SUBDIRS += cmdApp
    }
}
