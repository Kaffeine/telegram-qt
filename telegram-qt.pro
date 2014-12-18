
TEMPLATE = subdirs
SUBDIRS = telegram-qt tests testApp telegram-qt/generator
CONFIG += ordered

greaterThan(QT_MAJOR_VERSION, 4) {
    SUBDIRS += telegram-qt/generator-ng
}
