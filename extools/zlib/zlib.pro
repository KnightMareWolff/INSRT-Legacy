#-------------------------------------------------
#
# Project created by QtCreator 2014-12-20T20:30:21
#
#-------------------------------------------------

QT       += opengl

TARGET = zlib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    adler32.c \
    compress.c \
    crc32.c \
    deflate.c \
    gzclose.c \
    gzlib.c \
    gzread.c \
    gzwrite.c \
    infback.c \
    inffast.c \
    inflate.c \
    inftrees.c \
    trees.c \
    uncompr.c \
    zutil.c

HEADERS += \
    crc32.h \
    deflate.h \
    gzguts.h \
    inffast.h \
    inffixed.h \
    inflate.h \
    inftrees.h \
    trees.h \
    zconf.h \
    zlib.h \
    zutil.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

QMAKE_CXXFLAGS += -Z_PREFIX
