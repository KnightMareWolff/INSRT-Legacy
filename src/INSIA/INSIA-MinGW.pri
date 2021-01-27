#-------------------------------------------------
#
# Project created by QtCreator 2014-04-18T21:39:06
#
#-------------------------------------------------

QT       -= gui

TARGET = INSIA
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSIA.cpp \
    IIA_Estrela.cpp \
    IIA_Mapa.cpp

HEADERS += INSIA.h \
    IIA_Estrela.h \
    IIA_Mapa.h \
    IIA_GlobalDef.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

