QT += core gui network
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4) {
    QT += widgets
} else {
    # Qt4 has no c++11 config option and does not turn on the standard by default
    QMAKE_CXXFLAGS += -std=c++11
}

TEMPLATE = app

INCLUDEPATH += $$PWD/../TelegramQt

LIBS += -lssl -lcrypto -lz
LIBS += -L$$OUT_PWD/../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}

TARGET = testApp
TEMPLATE = app

SOURCES += main.cpp\
    MainWindow.cpp \
    CFileManager.cpp \
    CPeerModel.cpp \
    CContactModel.cpp \
    CContactsFilterModel.cpp \
    CChatInfoModel.cpp \
    CDialogModel.cpp \
    CMessageModel.cpp

HEADERS  += MainWindow.hpp \
    CFileManager.hpp \
    CPeerModel.hpp \
    CContactModel.hpp \
    CContactsFilterModel.hpp \
    CChatInfoModel.hpp \
    CDialogModel.hpp \
    CMessageModel.hpp

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += CMakeLists.txt
