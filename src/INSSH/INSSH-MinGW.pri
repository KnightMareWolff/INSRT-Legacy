#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T11:29:20
#
#-------------------------------------------------

QT       += opengl core

TARGET = INSSH
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSSH.cpp \
    ISH_ComputeShader.cpp \
    ISH_FragmentShader.cpp \
    ISH_GeometryShader.cpp \
    ISH_Program.cpp \
    ISH_TessCtrlShader.cpp \
    ISH_TessEvalShader.cpp \
    ISH_VertexShader.cpp \
    ISH_ProgramManager.cpp

HEADERS += INSSH.h \
    ISH_ComputeShader.h \
    ISH_FragmentShader.h \
    ISH_GeometryShader.h \
    ISH_GlobalDef.h \
    ISH_Program.h \
    ISH_TessCtrlShader.h \
    ISH_TessEvalShader.h \
    ISH_VertexShader.h \
    ISH_ProgramManager.h
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

