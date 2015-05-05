QT       += core network
TEMPLATE = app

CONFIG += console

INCLUDEPATH += $$PWD/../telegram-qt

!win32 {
	LIBS += -lssl -lcrypto -lz	
}
LIBS += -lTelegramQt
LIBS += -L$$OUT_PWD/../telegram-qt

TARGET = cmdApp

SOURCES += main.cpp