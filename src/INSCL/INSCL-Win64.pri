#-------------------------------------------------
#
# Project created by QtCreator 2016-04-11T21:21:15
#
#-------------------------------------------------

QT      += core gui opengl openglextensions

TARGET = INSCL
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSCL.cpp \
    ICL_Plataforma.cpp \
    ICL_Device.cpp \
    ICL_Programa.cpp \
    ICL_Kernel.cpp \
    ICL_Sistema.cpp

HEADERS += INSCL.h \
    ICL_GlobalDef.h \
    ICL_Plataforma.h \
    ICL_Device.h \
    ICL_Programa.h \
    ICL_Kernel.h \
    ICL_Sistema.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

#INSGL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSGL/release/ -lINSGL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSGL/debug/ -lINSGL
else:unix: LIBS += -L$$OUT_PWD/../INSGL/ -lINSGL

INCLUDEPATH += $$PWD/../INSGL
DEPENDPATH += $$PWD/../INSGL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGL/release/libINSGL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGL/debug/libINSGL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGL/release/INSGL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGL/debug/INSGL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSGL/libINSGL.a

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

#OpenCL
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencl/Win64/release/ -lOpenCL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencl/Win64/debug/ -lOpenCL
else:unix: LIBS += -L$$PWD/../../libs/opencl/Win64/ -lOpenCL

INCLUDEPATH += $$PWD/../../libs/opencl/Win64/include
DEPENDPATH += $$PWD/../../libs/opencl/Win64/include

#INSUT
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSUT/release/ -lINSUT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSUT/debug/ -lINSUT
else:unix: LIBS += -L$$OUT_PWD/../INSUT/ -lINSUT

INCLUDEPATH += $$PWD/../INSUT
DEPENDPATH += $$PWD/../INSUT

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSUT/release/libINSUT.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSUT/debug/libINSUT.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSUT/release/INSUT.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSUT/debug/INSUT.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSUT/libINSUT.a

#assimp
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../extools/assimp/release/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../extools/assimp/debug/ -lassimp
else:unix: LIBS += -L$$OUT_PWD/../../extools/assimp/ -lassimp

INCLUDEPATH += $$PWD/../../extools/assimp
DEPENDPATH += $$PWD/../../extools/assimp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/assimp/release/libassimp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/assimp/debug/libassimp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/assimp/release/assimp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/assimp/debug/assimp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../extools/assimp/libassimp.a

