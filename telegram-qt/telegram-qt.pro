
QT = core

TEMPLATE = lib
TARGET   = TelegramQt
CONFIG  += dll

SOURCES = CTelegramCore.cpp \
    CTelegramStream.cpp \
    Utils.cpp
HEADERS = CTelegramCore.hpp \
    CTelegramStream.hpp \
    Utils.hpp
HEADERS += TLValues.h

LIBS += -lssl
