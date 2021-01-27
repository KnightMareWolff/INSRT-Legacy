#-------------------------------------------------
#
# Project created by QtCreator 2014-12-07T21:56:06
#
#-------------------------------------------------

QT       += core gui opengl multimedia

TARGET = INSGL
TEMPLATE = lib
CONFIG += staticlib
#--------------------------------------------------------------------------#
#A maneira mais limpa de se garantir a limpeza de um codigo multiplataforma#
#É remover os objetos de Outras plataformas.                               #
#Por mais que estejamos fazendo isto via defines nas classes para garantir #
#em alguns compiladores funciona e em outros não, onde estamos realizando  #
#este tipo de tratamento apenas para a inicialização correta dos mesmos    #
#Obs:                                                                      #
#Tentamos configurar variaveis condicionais porem o Qt nao esta trabalhando#
#bem com a identificacao das plataformas host e target onde duplica a iden #
#tificacao da mesma , bem como para inclusao de arquivos nao funciona...   #
#aparentemente as clausulas SOURCES e HEADERS sao consideradas globais...  #
#--------------------------------------------------------------------------#
#Arquivos Windows                                                          #
#--------------------------------------------------------------------------#
SOURCES += INSGL.cpp \
    IGL_Functions.cpp \
    IGL_FunctionsPCv40.cpp \
    IGL_FunctionsPCv41.cpp \
    IGL_FunctionsPCv42.cpp \
    IGL_FunctionsPCv43.cpp \
    IGL_FunctionsPCv44.cpp \
    IGL_FunctionsPCv45.cpp

HEADERS += INSGL.h \
    IGL_Functions.h \
    IGL_GlobalDef.h \
    IGL_FunctionsPCv40.h \
    IGL_FunctionsPCv41.h \
    IGL_FunctionsPCv42.h \
    IGL_FunctionsPCv43.h \
    IGL_FunctionsPCv44.h \
    IGL_FunctionsPCv45.h
#--------------------------------------------------------------------------#
#Seta Arquivos de target para unix                                         #
#--------------------------------------------------------------------------#
unix {
    target.path = /usr/lib
    INSTALLS += target
}
#--------------------------------------------------------------------------#
#Arquivos Linkagem de Bibliotecas                                          #
#--------------------------------------------------------------------------#
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
