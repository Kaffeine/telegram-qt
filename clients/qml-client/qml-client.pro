TEMPLATE = app

QT += qml quick quickcontrols2
#QT += widgets
CONFIG += c++11
CONFIG += plugin

TARGET = qml-client

SOURCES += main.cpp
SOURCES += src/ImageProvider.cpp
SOURCES += src/ImageProvider.hpp
SOURCES += src/ImageResponse.cpp
SOURCES += src/ImageResponse.hpp

SOURCES += models/DialogsModel.cpp models/MessagesModel.cpp
HEADERS += models/DialogsModel.hpp models/MessagesModel.hpp

RESOURCES += qml.qrc

LIBS += -lssl -lcrypto -lz
LIBS += -L$$OUT_PWD/../../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}
LIBS += -L$$OUT_PWD/../../imports/TelegramQtQml
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}QmlPlugin

INCLUDEPATH += $$PWD/../../TelegramQt
INCLUDEPATH += $$PWD/../../imports/TelegramQtQml

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
!isEmpty(target.path): INSTALLS += target
