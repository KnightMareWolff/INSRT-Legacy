#-------------------------------------------------
#
# Project created by QtCreator 2014-10-12T12:02:10
#
#-------------------------------------------------

QT       += core gui opengl multimedia concurrent

TARGET = INSCR
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSCR.cpp \
    ObjetosExportados.cpp \
    SCR_Objetos.cpp

HEADERS += INSCR.h \
    ObjetosExportados.h \
    SCR_Objetos.h \
    SCR_GlobalDef.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

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

#Lua522
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

#Tolua
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
