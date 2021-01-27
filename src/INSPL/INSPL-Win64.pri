#-------------------------------------------------
#
# Project created by QtCreator 2014-10-19T19:37:01
#
#-------------------------------------------------

QT       += gui widgets opengl multimedia quickwidgets quick

TARGET = INSPL
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSPL.cpp \
    IPL_QQuickWidGet.cpp \
    IPL_QQuickView.cpp \
    IPL_EditorMainWindow.cpp \
    IPL_EditorWindow.cpp \
    IPL_RuntimeWindow.cpp \
    IPL_EditorGLWidget.cpp \
    IPL_EditorTabWidget.cpp \
    IPL_EditorTabPageObjetos.cpp \
    IPL_EditorTabPageAmbiente.cpp \
    IPL_EditorTabPageOtimizacao.cpp \
    IPL_EditorMaterialPreview.cpp \
    IPL_EditorTabPageMateriais.cpp

HEADERS += INSPL.h \
    IPL_GlobalDef.h \
    IPL_QQuickWidGet.h \
    IPL_QQuickView.h \
    IPL_EditorMainWindow.h \
    IPL_EditorWindow.h \
    IPL_RuntimeWindow.h \
    IPL_EditorGLWidget.h \
    IPL_EditorTabWidget.h \
    IPL_EditorTabPageObjetos.h \
    IPL_EditorTabPageAmbiente.h \
    IPL_EditorTabPageOtimizacao.h \
    IPL_EditorMaterialPreview.h \
    IPL_EditorTabPageMateriais.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

#INSSM
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSSM/release/ -lINSSM
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSSM/debug/ -lINSSM
else:unix: LIBS += -L$$OUT_PWD/../INSSM/ -lINSSM

INCLUDEPATH += $$PWD/../INSSM
DEPENDPATH += $$PWD/../INSSM

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSM/release/libINSSM.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSM/debug/libINSSM.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSM/release/INSSM.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSSM/debug/INSSM.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSSM/libINSSM.a

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

#INSCR
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSCR/release/ -lINSCR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSCR/debug/ -lINSCR
else:unix: LIBS += -L$$OUT_PWD/../INSCR/ -lINSCR

INCLUDEPATH += $$PWD/../INSCR
DEPENDPATH += $$PWD/../INSCR

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCR/release/libINSCR.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCR/debug/libINSCR.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCR/release/INSCR.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCR/debug/INSCR.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSPL/libINSCR.a

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
