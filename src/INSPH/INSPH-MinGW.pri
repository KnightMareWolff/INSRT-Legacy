#-------------------------------------------------
#
# Project created by QtCreator 2015-11-27T21:37:16
#
#-------------------------------------------------

QT       -= gui

TARGET = INSPH
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSPH.cpp \
    IPH_Ode.cpp \
    IPH_OdeSolver.cpp \
    IPH_SpringOde.cpp

HEADERS += INSPH.h \
    IPH_GlobalDef.h \
    IPH_Ode.h \
    IPH_OdeSolver.h \
    IPH_SpringOde.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

