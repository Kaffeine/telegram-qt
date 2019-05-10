QT = core network qml

TEMPLATE = lib
TARGET   = TelegramQt$${QT_MAJOR_VERSION}QmlPlugin
VERSION = 0.2.0

include(../../options.pri)

CONFIG += c++11

DEFINES += TELEGRAMQT_QML_LIBRARY

SOURCES = plugin.cpp
OTHER_FILES += CMakeLists.txt

INCLUDEPATH += ../../TelegramQt
SOURCES += \
    DeclarativeAuthOperation.cpp \
    DeclarativeChatInfo.cpp \
    DeclarativeClient.cpp \
    DeclarativeClientOperator.cpp \
    DeclarativeMessageSender.cpp \
    DeclarativeOperation.cpp \
    DeclarativeRsaKey.cpp \
    DeclarativeSettings.cpp \
    DeclarativeUserInfo.cpp \

HEADERS += \
    DeclarativeAuthOperation.hpp \
    DeclarativeChatInfo.hpp \
    DeclarativeClient.hpp \
    DeclarativeClientOperator.hpp \
    DeclarativeMessageSender.hpp \
    DeclarativeOperation.hpp \
    DeclarativeRsaKey.hpp \
    DeclarativeSettings.hpp \
    DeclarativeUserInfo.hpp \

target.path += $$INSTALL_QML_IMPORT_DIR/TelegramQt
INSTALLS += target

LIBS += -lssl -lcrypto -lz
LIBS += -L$$OUT_PWD/../../TelegramQt
LIBS += -lTelegramQt$${QT_MAJOR_VERSION}

qmlIndexFiles.files += qmldir plugins.qmltypes
qmlIndexFiles.path += $$target.path
INSTALLS += qmlIndexFiles
