#-------------------------------------------------
#
# Project created by QtCreator 2014-07-20T23:40:34
#
#-------------------------------------------------

QT       += gui multimedia

TARGET = INSMD
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSMD.cpp \
    IMD_Som.cpp \
    IMD_Video.cpp \
    IMD_Sistema.cpp \
    IMD_AudioDevice.cpp \
    IMD_VideoDevice.cpp \
    IMD_CanalVirtual.cpp

HEADERS += INSMD.h \
    IMD_Som.h \
    IMD_GlobalDef.h \
    IMD_Video.h \
    IMD_Sistema.h \
    IMD_AudioDevice.h \
    IMD_VideoDevice.h \
    IMD_CanalVirtual.h
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

#OpenCV
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencv/MinGW/release/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencv/MinGW/debug/ -lopencv_world320d

INCLUDEPATH += $$PWD/../../libs/opencv/MinGW/include/320
DEPENDPATH += $$PWD/../../libs/opencv/MinGW/include/320

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/release/opencv_world320.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/debug/opencv_world320d.lib
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/release/opencv_world320.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/debug/opencv_world320d.lib
