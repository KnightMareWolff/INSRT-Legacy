#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T20:38:26
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = tolua
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    toluabind.c \
    tolua.c

#LUA522-W64
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../libs/lua/Win64/release/ -llua522
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../libs/lua/Win64/debug/ -llua522
else:unix: LIBS += -L$$PWD/../../../../libs/lua/Win64/ -llua522

INCLUDEPATH += $$PWD/../../../../libs/lua/Win64/include
DEPENDPATH += $$PWD/../../../../libs/lua/Win64/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/lua/Win64/release/liblua522.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/lua/Win64/debug/liblua522.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/lua/Win64/release/lua522.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/lua/Win64/debug/lua522.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../libs/lua/Win64/liblua522.a

#TOLUA-W64
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../libs/tolua/Win64/release/ -ltolua
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../libs/tolua/Win64/debug/ -ltolua
else:unix: LIBS += -L$$PWD/../../../../libs/tolua/Win64/ -ltolua

INCLUDEPATH += $$PWD/../../../../libs/tolua/Win64/include
DEPENDPATH += $$PWD/../../../../libs/tolua/Win64/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/tolua/Win64/release/libtolua.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/tolua/Win64/debug/libtolua.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/tolua/Win64/release/tolua.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../libs/tolua/Win64/debug/tolua.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../libs/tolua/Win64/libtolua.a
