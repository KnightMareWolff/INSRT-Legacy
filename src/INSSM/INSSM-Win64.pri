#-------------------------------------------------
#
# Project created by QtCreator 2014-09-14T13:28:03
#
#-------------------------------------------------

QT       += opengl multimedia

TARGET = INSSM
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSSM.cpp \
    ISM_Cenario.cpp \
    ISM_Exemplo01.cpp \
    ISM_DemoProject.cpp \
    ISM_Exemplo02.cpp \
    ISM_Exemplo03.cpp \
    ISM_Exemplo04.cpp \
    ISM_Exemplo05.cpp \
    ISM_Exemplo06.cpp \
    ISM_Exemplo07.cpp \
    ISM_EditorProject.cpp \
    ISM_Exemplo08.cpp \
    ISM_Exemplo09.cpp \
    ISM_Exemplo10.cpp \
    ISM_Exemplo11.cpp

HEADERS += INSSM.h \
    ISM_Cenario.h \
    ISM_GlobalDef.h \
    ISM_Exemplo01.h \
    ISM_DemoProject.h \
    ISM_Exemplo02.h \
    ISM_Exemplo03.h \
    ISM_Exemplo04.h \
    ISM_Exemplo05.h \
    ISM_Exemplo06.h \
    ISM_Exemplo07.h \
    ISM_EditorProject.h \
    ISM_Exemplo08.h \
    ISM_Exemplo09.h \
    ISM_Exemplo10.h \
    ISM_Exemplo11.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

#INS3D
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INS3D/release/ -lINS3D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INS3D/debug/ -lINS3D
else:unix: LIBS += -L$$OUT_PWD/../INS3D/ -lINS3D

INCLUDEPATH += $$PWD/../INS3D
DEPENDPATH += $$PWD/../INS3D

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INS3D/release/libINS3D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INS3D/debug/libINS3D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INS3D/release/INS3D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INS3D/debug/INS3D.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INS3D/libINS3D.a

#INSGZ
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSGZ/release/ -lINSGZ
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSGZ/debug/ -lINSGZ
else:unix: LIBS += -L$$OUT_PWD/../INSGZ/ -lINSGZ

INCLUDEPATH += $$PWD/../INSGZ
DEPENDPATH += $$PWD/../INSGZ

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGZ/release/libINSGZ.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGZ/debug/libINSGZ.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGZ/release/INSGZ.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGZ/debug/INSGZ.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSGZ/libINSGZ.a

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
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSSM/libINSUT.a

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

#LUA522
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../extools/lua522/release/ -llua522
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../extools/lua522/debug/ -llua522
else:unix: LIBS += -L$$OUT_PWD/../../extools/lua522/ -llua522

INCLUDEPATH += $$PWD/../../extools/lua522
DEPENDPATH += $$PWD/../../extools/lua522

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua522/release/liblua522.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua522/debug/liblua522.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua522/release/lua522.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua522/debug/lua522.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua522/liblua522.a

#LUA531
#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../extools/lua531/release/ -llua531
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../extools/lua531/debug/ -llua531
#else:unix: LIBS += -L$$OUT_PWD/../../extools/lua531/ -llua531
#
#INCLUDEPATH += $$PWD/../../extools/lua531
#DEPENDPATH += $$PWD/../../extools/lua531
#
#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua531/release/liblua531.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua531/debug/liblua531.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua531/release/lua531.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua531/debug/lua531.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../extools/lua531/liblua531.a

#TOLUA
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../extools/tolua/release/ -ltolua
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../extools/tolua/debug/ -ltolua
else:unix: LIBS += -L$$OUT_PWD/../../extools/tolua/ -ltolua

INCLUDEPATH += $$PWD/../../extools/tolua
DEPENDPATH += $$PWD/../../extools/tolua

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/tolua/release/libtolua.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/tolua/debug/libtolua.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/tolua/release/tolua.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../extools/tolua/debug/tolua.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../extools/tolua/libtolua.a

#INSGO
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSGO/release/ -lINSGO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSGO/debug/ -lINSGO
else:unix: LIBS += -L$$OUT_PWD/../INSGO/ -lINSGO

INCLUDEPATH += $$PWD/../INSGO
DEPENDPATH += $$PWD/../INSGO

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGO/release/libINSGO.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGO/debug/libINSGO.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGO/release/INSGO.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSGO/debug/INSGO.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSGO/libINSGO.a

#INSMA
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSMA/release/ -lINSMA
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSMA/debug/ -lINSMA
else:unix: LIBS += -L$$OUT_PWD/../INSMA/ -lINSMA

INCLUDEPATH += $$PWD/../INSMA
DEPENDPATH += $$PWD/../INSMA

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMA/release/libINSMA.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMA/debug/libINSMA.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMA/release/INSMA.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMA/debug/INSMA.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSMA/libINSMA.a

#OpenCV
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencv/Win64/release/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencv/Win64/debug/ -lopencv_world320d

INCLUDEPATH += $$PWD/../../libs/opencv/Win64/include/320
DEPENDPATH += $$PWD/../../libs/opencv/Win64/include/320

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/Win64/release/libopencv_world320.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/Win64/debug/libopencv_world320d.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/Win64/release/opencv_world320.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/Win64/debug/opencv_world320d.lib


#INSMD
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSMD/release/ -lINSMD
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSMD/debug/ -lINSMD
else:unix: LIBS += -L$$OUT_PWD/../INSMD/ -lINSMD

INCLUDEPATH += $$PWD/../INSMD
DEPENDPATH += $$PWD/../INSMD

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMD/release/libINSMD.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMD/debug/libINSMD.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMD/release/INSMD.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSMD/debug/INSMD.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSMD/libINSMD.a

#INSSH
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSSH/release/ -lINSSH
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSSH/debug/ -lINSSH
else:unix: LIBS += -L$$OUT_PWD/../INSSH/ -lINSSH

INCLUDEPATH += $$PWD/../INSSH
DEPENDPATH += $$PWD/../INSSH

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSH/release/libINSSH.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSH/debug/libINSSH.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSH/release/INSSH.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSH/debug/INSSH.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSSH/libINSSH.a

#OpenCL
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencl/Win64/release/ -lOpenCL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencl/Win64/debug/ -lOpenCL
else:unix: LIBS += -L$$PWD/../../libs/opencl/Win64/ -lOpenCL

INCLUDEPATH += $$PWD/../../libs/opencl/Win64/include
DEPENDPATH += $$PWD/../../libs/opencl/Win64/include

#INSVK
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSVK/release/ -lINSVK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSVK/debug/ -lINSVK
else:unix: LIBS += -L$$OUT_PWD/../INSVK/ -lINSVK

INCLUDEPATH += $$PWD/../INSVK
DEPENDPATH += $$PWD/../INSVK

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSVK/release/libINSVK.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSVK/debug/libINSVK.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSVK/release/INSVK.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSVK/debug/INSVK.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSVK/libINSVK.a

#VULKAN
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/vulkan/Win64/release/ -lvulkan-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/vulkan/Win64/debug/ -lvulkan-1
else:unix: LIBS += -L$$PWD/../../libs/vulkan/Win64/ -lvulkan-1

INCLUDEPATH += $$PWD/../../libs/vulkan/Win64/include
DEPENDPATH += $$PWD/../../libs/vulkan/Win64/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/Win64/release/libvulkan-1.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/Win64/debug/libvulkan-1.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/Win64/release/vulkan-1.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/Win64/debug/vulkan-1.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../libs/vulkan/Win64/libvulkan-1.a
