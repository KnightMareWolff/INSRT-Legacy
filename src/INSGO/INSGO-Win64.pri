#-------------------------------------------------
#
# Project created by QtCreator 2014-09-14T13:26:16
#
#-------------------------------------------------

QT       += opengl multimedia

TARGET = INSGO
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSGO.cpp \
    IGO_Brush.cpp \
    IGO_Ator.cpp \
    IGO_Nivel.cpp \
    IGO_Mundo.cpp

HEADERS += INSGO.h \
    IGO_Brush.h \
    IGO_Ator.h \
    IGO_Nivel.h \
    IGO_Mundo.h \
    IGO_GlobalDef.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

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
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../INSSM/libINSUT.a

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
