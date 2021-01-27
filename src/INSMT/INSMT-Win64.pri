#-------------------------------------------------
#
# Project created by QtCreator 2014-07-21T01:10:13
#
#-------------------------------------------------
QT       += gui

TARGET = INSMT
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSMT.cpp \
    IMT_Borda.cpp \
    IMT_Matriz.cpp \
    IMT_Plano.cpp \
    IMT_Quaternion.cpp \
    IMT_Vetor.cpp

HEADERS += INSMT.h \
    IMT_Borda.h \
    IMT_Matriz.h \
    IMT_Plano.h \
    IMT_Quaternion.h \
    IMT_Vetor.h \
    IMT_GlobalDef.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
