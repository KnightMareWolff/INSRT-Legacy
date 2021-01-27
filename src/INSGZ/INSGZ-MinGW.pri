#-------------------------------------------------
#
# Project created by QtCreator 2014-09-07T23:08:18
#
#-------------------------------------------------

QT       += opengl multimedia

TARGET = INSGZ
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSGZ.cpp \
    IGZ_AnimadorFisico.cpp \
    IGZ_Construtor3D.cpp \
    IGZ_Animador3D.cpp \
    IGZ_Transportador.cpp \
    IGZ_Sonorizador.cpp \
    IGZ_Otimizador.cpp \
    IGZ_Compilador.cpp

HEADERS += INSGZ.h \
    IGZ_GlobalDef.h \
    IGZ_AnimadorFisico.h \
    IGZ_Construtor3D.h \
    IGZ_Animador3D.h \
    IGZ_Transportador.h \
    IGZ_Compilador.h \
    IGZ_Otimizador.h \
    IGZ_Sonorizador.h
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
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSUT/libINSUT.a

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
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencv/MinGW/release/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencv/MinGW/debug/ -lopencv_world320d

INCLUDEPATH += $$PWD/../../libs/opencv/MinGW/include/320
DEPENDPATH += $$PWD/../../libs/opencv/MinGW/include/320

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/release/opencv_world320.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/debug/opencv_world320d.lib
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/release/opencv_world320.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/debug/opencv_world320d.lib

#OpenCL
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencl/Win64/release/ -lOpenCL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencl/Win64/debug/ -lOpenCL
else:unix: LIBS += -L$$PWD/../../libs/opencl/Win64/ -lOpenCL

INCLUDEPATH += $$PWD/../../libs/opencl/Win64/include
DEPENDPATH += $$PWD/../../libs/opencl/Win64/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencl/Win64/release/libOpenCL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencl/Win64/debug/libOpenCL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencl/Win64/release/OpenCL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencl/Win64/debug/OpenCL.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../libs/opencl/Win64/libOpenCL.a

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
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/vulkan/MinGW/release/ -lvulkan-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/vulkan/MinGW/debug/ -lvulkan-1
else:unix: LIBS += -L$$PWD/../../libs/vulkan/MinGW/ -lvulkan-1

INCLUDEPATH += $$PWD/../../libs/vulkan/MinGW/include
DEPENDPATH += $$PWD/../../libs/vulkan/MinGW/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/MinGW/release/vulkan-1.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/MinGW/debug/vulkan-1.lib
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/MinGW/release/vulkan-1.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/vulkan/MinGW/debug/vulkan-1.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../libs/vulkan/MinGW/libvulkan-1.a
