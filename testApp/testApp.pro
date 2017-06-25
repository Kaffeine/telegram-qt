QT += core gui widgets network
CONFIG += c++11

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
    CContactModel.cpp \
    CContactsFilterModel.cpp \
    CChatInfoModel.cpp \
    CMessageModel.cpp

HEADERS  += MainWindow.hpp \
    CFileManager.hpp \
    CContactModel.hpp \
    CContactsFilterModel.hpp \
    CChatInfoModel.hpp \
    CMessageModel.hpp

FORMS    += MainWindow.ui

RESOURCES += \
    resources.qrc

OTHER_FILES += CMakeLists.txt
