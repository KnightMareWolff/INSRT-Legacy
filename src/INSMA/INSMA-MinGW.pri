#-------------------------------------------------
#
# Project created by QtCreator 2016-01-03T19:48:20
#
#-------------------------------------------------

QT       += core opengl multimedia

TARGET = INSMA
TEMPLATE = lib
CONFIG += staticlib

SOURCES += INSMA.cpp \
    IMA_Material.cpp \
    IMA_TextureManager.cpp \
    IMA_Textura.cpp \
    IMA_MaterialManager.cpp \
    IMA_Cor.cpp \
    IMA_ColorMap.cpp \
    IMA_DepthMap.cpp

HEADERS += INSMA.h \
    IMA_GlobalDef.h \
    IMA_Material.h \
    IMA_TextureManager.h \
    IMA_Textura.h \
    IMA_MaterialManager.h \
    IMA_Cor.h \
    IMA_ColorMap.h \
    IMA_DepthMap.h
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

#OpenCV
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../libs/opencv/MinGW/release/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../libs/opencv/MinGW/debug/ -lopencv_world320d

INCLUDEPATH += $$PWD/../../libs/opencv/MinGW/include/320
DEPENDPATH += $$PWD/../../libs/opencv/MinGW/include/320

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/release/opencv_world320.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/debug/opencv_world320d.lib
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/release/opencv_world320.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../libs/opencv/MinGW/debug/opencv_world320d.lib
