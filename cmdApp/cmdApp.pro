QT       += core network
TEMPLATE = app

CONFIG += console

INCLUDEPATH += $$PWD/../telegram-qt

!win32 {
	LIBS += -lssl -lcrypto -lz	
}
LIBS += -lTelegramQt
LIBS += -L$$OUT_PWD/../telegram-qt

QMAKE_CXXFLAGS = -std=c++11

TARGET = cmdApp

SOURCES += main.cpp
