#-------------------------------------------------
#
# Project created by QtCreator 2014-07-20T23:25:30
#
#-------------------------------------------------

QT       -= gui

TARGET = tolua
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    tolua_event.c \
    tolua_is.c \
    tolua_map.c \
    tolua_push.c \
    tolua_to.c

HEADERS += tolua.h \
    tolua_event.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lua522/release/ -llua522
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lua522/debug/ -llua522
else:unix: LIBS += -L$$OUT_PWD/../lua522/ -llua522

INCLUDEPATH += $$PWD/../lua522
DEPENDPATH += $$PWD/../lua522

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lua522/release/liblua522.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lua522/debug/liblua522.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lua522/release/lua522.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../lua522/debug/lua522.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../lua522/liblua522.a

