
TEMPLATE = subdirs
SUBDIRS = telegram-qt
SUBDIRS += telegram-qt/tests testApp
SUBDIRS += telegram-qt/generator
CONFIG += ordered

greaterThan(QT_MAJOR_VERSION, 4) {
    SUBDIRS += telegram-qt/generator-ng
}
