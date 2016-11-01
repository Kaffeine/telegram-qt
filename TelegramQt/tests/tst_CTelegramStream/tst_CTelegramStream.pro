include(../tests.pri)

TARGET = tst_telegramsteam
SOURCES = tst_CTelegramStream.cpp \
    ../../CTelegramStream.cpp \
    ../../CRawStream.cpp

HEADERS = \
    ../../CTelegramStream.hpp \
    ../../CRawStream.hpp
