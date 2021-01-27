HEADERS += \
    INS_GlobalDef.h \
    INS_Launcher.h \
    INS_LauncherPages.h

SOURCES += \
    INS.cpp \
    INS_Launcher.cpp \
    INS_LauncherPages.cpp

QT+= core opengl concurrent widgets quickwidgets quick network multimedia

#!android:DESTDIR = PWD/../../bin

############################################################################
#BIBLIOTECAS INTERNAS A INS(NAO PRECISA SER MAPEADA APENAS RECOMPILADA)    #
############################################################################
#INSSL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSSL/release/ -lINSSL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSSL/debug/ -lINSSL
else:unix: LIBS += -L$$OUT_PWD/../src/INSSL/ -lINSSL

INCLUDEPATH += $$PWD/../src/INSSL
DEPENDPATH += $$PWD/../src/INSSL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSL/release/libINSSL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSL/debug/libINSSL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSL/release/INSSL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSL/debug/INSSL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSSL/libINSSL.a

#INSSM
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSSM/release/ -lINSSM
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSSM/debug/ -lINSSM
else:unix: LIBS += -L$$OUT_PWD/../src/INSSM/ -lINSSM

INCLUDEPATH += $$PWD/../src/INSSM
DEPENDPATH += $$PWD/../src/INSSM

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSM/release/libINSSM.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSM/debug/libINSSM.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSM/release/INSSM.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSM/debug/INSSM.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSSM/libINSSM.a

#INSPL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSPL/release/ -lINSPL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSPL/debug/ -lINSPL
else:unix: LIBS += -L$$OUT_PWD/../src/INSPL/ -lINSPL

INCLUDEPATH += $$PWD/../src/INSPL
DEPENDPATH += $$PWD/../src/INSPL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSPL/release/libINSPL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSPL/debug/libINSPL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSPL/release/INSPL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSPL/debug/INSPL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSPL/libINSPL.a

#INS3D
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INS3D/release/ -lINS3D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INS3D/debug/ -lINS3D
else:unix: LIBS += -L$$OUT_PWD/../src/INS3D/ -lINS3D

INCLUDEPATH += $$PWD/../src/INS3D
DEPENDPATH += $$PWD/../src/INS3D

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/release/libINS3D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/debug/libINS3D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/release/INS3D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/debug/INS3D.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/libINS3D.a

#INSGZ
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSGZ/release/ -lINSGZ
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSGZ/debug/ -lINSGZ
else:unix: LIBS += -L$$OUT_PWD/../src/INSGZ/ -lINSGZ

INCLUDEPATH += $$PWD/../src/INSGZ
DEPENDPATH += $$PWD/../src/INSGZ

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGZ/release/libINSGZ.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGZ/debug/libINSGZ.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGZ/release/INSGZ.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGZ/debug/INSGZ.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSGZ/libINSGZ.a

#INSMT
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSMT/release/ -lINSMT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSMT/debug/ -lINSMT
else:unix: LIBS += -L$$OUT_PWD/../src/INSMT/ -lINSMT

INCLUDEPATH += $$PWD/../src/INSMT
DEPENDPATH += $$PWD/../src/INSMT

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/release/libINSMT.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/debug/libINSMT.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/release/INSMT.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/debug/INSMT.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/libINSMT.a

#INSGL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSGL/release/ -lINSGL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSGL/debug/ -lINSGL
else:unix: LIBS += -L$$OUT_PWD/../src/INSGL/ -lINSGL

INCLUDEPATH += $$PWD/../src/INSGL
DEPENDPATH += $$PWD/../src/INSGL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/release/libINSGL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/debug/libINSGL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/release/INSGL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/debug/INSGL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/libINSGL.a

#INSVK
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSVK/release/ -lINSVK
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSVK/debug/ -lINSVK
else:unix: LIBS += -L$$OUT_PWD/../src/INSVK/ -lINSVK

INCLUDEPATH += $$PWD/../src/INSVK
DEPENDPATH += $$PWD/../src/INSVK

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSVK/release/libINSVK.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSVK/debug/libINSVK.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSVK/release/INSVK.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSVK/debug/INSVK.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSVK/libINSVK.a

#VULKAN
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/vulkan/MinGW/release/ -lvulkan-1
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/vulkan/MinGW/debug/ -lvulkan-1
else:unix: LIBS += -L$$PWD/../libs/vulkan/MinGW/ -lvulkan-1

INCLUDEPATH += $$PWD/../libs/vulkan/MinGW/include
DEPENDPATH += $$PWD/../libs/vulkan/MinGW/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/vulkan/MinGW/release/vulkan-1.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/vulkan/MinGW/debug/vulkan-1.lib
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/vulkan/MinGW/release/vulkan-1.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/vulkan/MinGW/debug/vulkan-1.lib
else:unix: PRE_TARGETDEPS += $$PWD/../libs/vulkan/MinGW/libvulkan-1.a

#INS3D
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INS3D/release/ -lINS3D
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INS3D/debug/ -lINS3D
else:unix: LIBS += -L$$OUT_PWD/../src/INS3D/ -lINS3D

INCLUDEPATH += $$PWD/../src/INS3D
DEPENDPATH += $$PWD/../src/INS3D

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/release/libINS3D.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/debug/libINS3D.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/release/INS3D.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/debug/INS3D.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INS3D/libINS3D.a

#INSGL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSGL/release/ -lINSGL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSGL/debug/ -lINSGL
else:unix: LIBS += -L$$OUT_PWD/../src/INSGL/ -lINSGL

INCLUDEPATH += $$PWD/../src/INSGL
DEPENDPATH += $$PWD/../src/INSGL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/release/libINSGL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/debug/libINSGL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/release/INSGL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/debug/INSGL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSGL/libINSGL.a

#INSMT
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSMT/release/ -lINSMT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSMT/debug/ -lINSMT
else:unix: LIBS += -L$$OUT_PWD/../src/INSMT/ -lINSMT

INCLUDEPATH += $$PWD/../src/INSMT
DEPENDPATH += $$PWD/../src/INSMT

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/release/libINSMT.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/debug/libINSMT.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/release/INSMT.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/debug/INSMT.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSMT/libINSMT.a

#INSSH
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSSH/release/ -lINSSH
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSSH/debug/ -lINSSH
else:unix: LIBS += -L$$OUT_PWD/../src/INSSH/ -lINSSH

INCLUDEPATH += $$PWD/../src/INSSH
DEPENDPATH += $$PWD/../src/INSSH

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSH/release/libINSSH.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSH/debug/libINSSH.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSH/release/INSSH.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSSH/debug/INSSH.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSSH/libINSSH.a

#ZLIB
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extools/zlib/release/ -lzlib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extools/zlib/debug/ -lzlib
else:unix: LIBS += -L$$OUT_PWD/../extools/zlib/ -lzlib

INCLUDEPATH += $$PWD/../extools/zlib
DEPENDPATH += $$PWD/../extools/zlib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/zlib/release/libzlib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/zlib/debug/libzlib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/zlib/release/zlib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/zlib/debug/zlib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../extools/zlib/libzlib.a

#assimp
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extools/assimp/release/ -lassimp
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extools/assimp/debug/ -lassimp
else:unix: LIBS += -L$$OUT_PWD/../extools/assimp/ -lassimp

INCLUDEPATH += $$PWD/../extools/assimp
DEPENDPATH += $$PWD/../extools/assimp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/assimp/release/libassimp.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/assimp/debug/libassimp.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/assimp/release/assimp.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/assimp/debug/assimp.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../extools/assimp/libassimp.a

#INSUT
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSUT/release/ -lINSUT
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSUT/debug/ -lINSUT
else:unix: LIBS += -L$$OUT_PWD/../src/INSUT/ -lINSUT

INCLUDEPATH += $$PWD/../src/INSUT
DEPENDPATH += $$PWD/../src/INSUT

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSUT/release/libINSUT.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSUT/debug/libINSUT.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSUT/release/INSUT.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSUT/debug/INSUT.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSSH/libINSUT.a

#LUA522 - Atenção!!! path diferente dos componentes!!!
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extools/lua522/release/ -llua522
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extools/lua522/debug/ -llua522
else:unix: LIBS += -L$$OUT_PWD/../extools/lua522/ -llua522

INCLUDEPATH += $$PWD/../extools/lua522
DEPENDPATH += $$PWD/../extools/lua522

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua522/release/liblua522.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua522/debug/liblua522.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua522/release/lua522.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua522/debug/lua522.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../extools/lua522/liblua522.a


#LUA531 - Atenção!!! path diferente dos componentes!!!
#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extools/lua531/release/ -llua531
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extools/lua531/debug/ -llua531
#else:unix: LIBS += -L$$OUT_PWD/../extools/lua531/ -llua531
#
#INCLUDEPATH += $$PWD/../extools/lua531
#DEPENDPATH += $$PWD/../extools/lua531
#
#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua531/release/liblua531.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua531/debug/liblua531.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua531/release/lua531.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/lua531/debug/lua531.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../extools/lua531/liblua531.a

#TOLUA
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../extools/tolua/release/ -ltolua
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../extools/tolua/debug/ -ltolua
else:unix: LIBS += -L$$OUT_PWD/../extools/tolua/ -ltolua

INCLUDEPATH += $$PWD/../extools/tolua
DEPENDPATH += $$PWD/../extools/tolua

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/tolua/release/libtolua.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/tolua/debug/libtolua.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/tolua/release/tolua.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../extools/tolua/debug/tolua.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../extools/tolua/libtolua.a

#INSCR
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSCR/release/ -lINSCR
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSCR/debug/ -lINSCR
else:unix: LIBS += -L$$OUT_PWD/../src/INSCR/ -lINSCR

INCLUDEPATH += $$PWD/../src/INSCR
DEPENDPATH += $$PWD/../src/INSCR

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCR/release/libINSCR.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCR/debug/libINSCR.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCR/release/INSCR.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCR/debug/INSCR.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSCR/libINSCR.a

#INSGO
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSGO/release/ -lINSGO
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSGO/debug/ -lINSGO
else:unix: LIBS += -L$$OUT_PWD/../src/INSGO/ -lINSGO

INCLUDEPATH += $$PWD/../src/INSGO
DEPENDPATH += $$PWD/../src/INSGO

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGO/release/libINSGO.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGO/debug/libINSGO.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGO/release/INSGO.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSGO/debug/INSGO.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSGO/libINSGO.a

#INSMA
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSMA/release/ -lINSMA
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSMA/debug/ -lINSMA
else:unix: LIBS += -L$$OUT_PWD/../src/INSMA/ -lINSMA

INCLUDEPATH += $$PWD/../src/INSMA
DEPENDPATH += $$PWD/../src/INSMA

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMA/release/libINSMA.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMA/debug/libINSMA.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMA/release/INSMA.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMA/debug/INSMA.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSMA/libINSMA.a

#INSCL
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSCL/release/ -lINSCL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSCL/debug/ -lINSCL
else:unix: LIBS += -L$$OUT_PWD/../src/INSCL/ -lINSCL

INCLUDEPATH += $$PWD/../src/INSCL
DEPENDPATH += $$PWD/../src/INSCL

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCL/release/libINSCL.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCL/debug/libINSCL.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCL/release/INSCL.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSCL/debug/INSCL.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSCL/libINSCL.a

#OpenCL
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/opencl/Win64/release/ -lOpenCL
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/opencl/Win64/debug/ -lOpenCL
else:unix: LIBS += -L$$PWD/../libs/opencl/Win64/ -lOpenCL

INCLUDEPATH += $$PWD/../libs/opencl/Win64/include
DEPENDPATH += $$PWD/../libs/opencl/Win64/include

#OpenCV
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../libs/opencv/MinGW/release/ -lopencv_world320
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../libs/opencv/MinGW/debug/ -lopencv_world320d

INCLUDEPATH += $$PWD/../libs/opencv/MinGW/include/320
DEPENDPATH += $$PWD/../libs/opencv/MinGW/include/320

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/opencv/MinGW/release/opencv_world320.lib
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/opencv/MinGW/debug/opencv_world320d.lib
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../libs/opencv/MinGW/release/opencv_world320.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../libs/opencv/MinGW/debug/opencv_world320d.lib

#INSMD
win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../src/INSMD/release/ -lINSMD
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../src/INSMD/debug/ -lINSMD
else:unix: LIBS += -L$$OUT_PWD/../src/INSMD/ -lINSMD

INCLUDEPATH += $$PWD/../src/INSMD
DEPENDPATH += $$PWD/../src/INSMD

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMD/release/libINSMD.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMD/debug/libINSMD.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMD/release/INSMD.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../src/INSMD/debug/INSMD.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../src/INSMD/libINSMD.a

#Libs do windows adicionais
LIBS += -luser32 -lgdi32 -lopengl32

#NO CASO DE DISPOSITIVOS PORTATEIS ESTA USANDO RESOURCE MANAGER DO QT
#!win32:RESOURCES += \world.qrc
