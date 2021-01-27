#-------------------------------------------------
#
# Project created by QtCreator 2016-04-07T19:58:36
#
#-------------------------------------------------

QT       -= gui

TARGET = INSCG
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSCG.cpp \
    ICG_ProcessadorPLY.cpp \
    ICG_ProcessadorMSH.cpp \
    ICG_ProcessadorCSG.cpp \
    ICG_ProcessadorBSP.cpp \
    ICG_ProcessadorPRT.cpp \
    ICG_ProcessadorHSR.cpp \
    ICG_ProcessadorPVS.cpp \
    ICG_ProcessadorRON.cpp

HEADERS += INSCG.h \
    ICG_GlobalDef.h \
    ICG_ProcessadorPLY.h \
    ICG_ProcessadorMSH.h \
    ICG_ProcessadorCSG.h \
    ICG_ProcessadorBSP.h \
    ICG_ProcessadorPRT.h \
    ICG_ProcessadorHSR.h \
    ICG_ProcessadorPVS.h \
    ICG_ProcessadorRON.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

#INSMT
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSMT/release/ -lINSMT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSMT/debug/ -lINSMT
else:unix: LIBS += -L$$OUT_PWD/../INSMT/ -lINSMT

INCLUDEPATH += $$PWD/../INSMT
DEPENDPATH += $$PWD/../INSMT

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMT/release/libINSMT.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMT/debug/libINSMT.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMT/release/INSMT.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMT/debug/INSMT.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSMT/libINSMT.a
