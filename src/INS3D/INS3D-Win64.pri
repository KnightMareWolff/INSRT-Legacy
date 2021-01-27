#-------------------------------------------------
#
# Project created by QtCreator 2014-04-18T18:43:03
#
#-------------------------------------------------

QT       += gui opengl openglextensions multimedia

TARGET = INS3D
TEMPLATE = lib
CONFIG += staticlib


SOURCES += INS3D.cpp \
    I3D_Camera.cpp \
    I3D_Cilindro.cpp \
    I3D_Cubo.cpp \
    I3D_Esfera.cpp \
    I3D_Face.cpp \
    I3D_Luz.cpp \
    I3D_Mesh.cpp \
    I3D_Modelo.cpp \
    I3D_Painel.cpp \
    I3D_Poligono.cpp \
    I3D_Primitivo.cpp \
    I3D_Vertice.cpp \
    I3D_Texto.cpp \
    I3D_PainelHeightMap.cpp \
    I3D_Fonte.cpp \
    I3D_ModeloHierarquico.cpp \
    I3D_ArvoreBsp.cpp \
    I3D_FaceBsp.cpp \
    I3D_FolhaBsp.cpp \
    I3D_NoBsp.cpp \
    I3D_ModeloLowPoly.cpp \
    I3D_ProcessadorHSR.cpp \
    I3D_ProcessadorCSG.cpp \
    I3D_ProcessadorRON.cpp \
    I3D_Portal.cpp \
    I3D_ProcessadorPRT.cpp \
    I3D_ProcessadorPVS.cpp \
    I3D_LightMap.cpp

HEADERS += INS3D.h \
    I3D_Camera.h \
    I3D_Cilindro.h \
    I3D_Cubo.h \
    I3D_Esfera.h \
    I3D_Face.h \
    I3D_GlobalDef.h \
    I3D_Luz.h \
    I3D_Mesh.h \
    I3D_Modelo.h \
    I3D_Painel.h \
    I3D_Poligono.h \
    I3D_Primitivo.h \
    I3D_Vertice.h \
    I3D_Texto.h \
    I3D_PainelHeightMap.h \
    I3D_Fonte.h \
    I3D_ModeloHierarquico.h \
    I3D_ArvoreBsp.h \
    I3D_FaceBsp.h \
    I3D_FolhaBsp.h \
    I3D_NoBsp.h \
    I3D_ModeloLowPoly.h \
    I3D_ProcessadorHSR.h \
    I3D_ProcessadorCSG.h \
    I3D_ProcessadorRON.h \
    I3D_Portal.h \
    I3D_ProcessadorPRT.h \
    I3D_ProcessadorPVS.h \
    I3D_LightMap.h
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


#INSCL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../INSCL/release/ -lINSCL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../INSCL/debug/ -lINSCL
else:unix: LIBS += -L$$OUT_PWD/../INSCL/ -lINSCL

INCLUDEPATH += $$PWD/../INSCL
DEPENDPATH += $$PWD/../INSCL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCL/release/libINSCL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCL/debug/libINSCL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCL/release/INSCL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../INSCL/debug/INSCL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSCL/libINSCL.a

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
