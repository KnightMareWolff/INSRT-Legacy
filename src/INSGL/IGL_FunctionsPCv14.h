#ifndef IGL_FUNCTIONSPCV14_H
#define IGL_FUNCTIONSPCV14_H

#include "IGL_Functions.h"

#ifdef Q_OS_WIN
#include <QOpenGLFunctions_1_4>

class CIGLFunctionsPCv14 : public CIGLFunctions
{
public:
    CIGLFunctionsPCv14(QOpenGLContext *pContext,int iVersao,int iMajor,int iMinor);

    bool iglEnableStates       ();
    bool iglDisableStates      ();
    bool iglEnd                ();
    bool iglSuportaShaders     ();
    bool iglSuportaFeedback    ();
    bool iglCompile            ();
    bool iglAddShader          (QString pi3dNomeShader, int pShaderType);
    bool iglActiveTexture      (unsigned int estado);
    bool iglBegin              (unsigned int estado);
    bool iglEnable             (unsigned int estado);
    bool iglDisable            (unsigned int estado);
    bool iglDeleteTextures     (int vlr, GLuint *Id);
    bool iglDeleteBuffers      (int vlr, GLuint *Id);

    bool iglRenderBuffers      (int vlr,
                                long QtdVertices,
                                long QtdIndices,
                                GLuint *Id,
                                GLuint *FbId,
                                GLuint *QryId,
                                bool FeedBack,
                                FeedBackData *FeedbackBuffer);

    bool iglRenderVertice      (CIMTVetor vertice,
                                CIMTVetor normal ,
                                bool Autotexture ,
                                bool Multitextura,
                                float tu         ,
                                float tv         );

    bool iglAutoTexture        (float S[4],float T[4]);
    bool iglMultiTexture       (float S[4],float T[4]);

    bool iglSetaMaterial       (CIMTVetor4 CorDifusa        ,
                                CIMTVetor4 CorAmbiente      ,
                                CIMTVetor4 CorEmissiva      ,
                                CIMTVetor4 CorSpecular      ,
                                float      opacidade        ,
                                float      brilho           );

    bool iglSetaLuzPonto       (unsigned int  Id ,
                                CIMTVetor4    pos,
                                CIMTVetor4    dir,
                                CIMTVetor4    CorDifusa,
                                CIMTVetor4    CorAmbiente,
                                CIMTVetor4    CorSpecular,
                                float         Expoente,
                                float         CutOff,
                                float         AtenuacaoConstante,
                                float         AtenuacaoLinear,
                                float         AtenuacaoQuadratica);

    bool iglSetaLuzDirecional  (unsigned int  Id ,
                                CIMTVetor4    pos,
                                CIMTVetor4    dir,
                                CIMTVetor4    CorDifusa,
                                CIMTVetor4    CorAmbiente,
                                CIMTVetor4    CorSpecular,
                                float         Expoente,
                                float         CutOff,
                                float         AtenuacaoConstante,
                                float         AtenuacaoLinear,
                                float         AtenuacaoQuadratica);

    bool iglSetaLuzSpot        (unsigned int  Id ,
                                CIMTVetor4    pos,
                                CIMTVetor4    dir,
                                CIMTVetor4    CorDifusa,
                                CIMTVetor4    CorAmbiente,
                                CIMTVetor4    CorSpecular,
                                float         Expoente,
                                float         CutOff,
                                float         AtenuacaoConstante,
                                float         AtenuacaoLinear,
                                float         AtenuacaoQuadratica);

    bool iglSetaVisPerspectiva (float ValorProx,
                                float ValorDist,
                                int   ValorAltura,
                                int   ValorLargura,
                                float FOV);

    bool iglSetaVisOrtogonal   (float ValorProx,
                                float ValorDist,
                                int   ValorAltura,
                                int   ValorLargura);

    bool iglSetaLookAt         (CIMTVetor Pos,CIMTVetor View,CIMTVetor Up);

    bool iglSetaUniformInt     (GLchar *nome,int vlr);

    bool iglSetaUniformMatrix  (CIMTMatriz mtx);
    bool iglCalculaPVMMatrix   (CIMTMatriz mtx,CIMTMatriz &resmtx);
    bool iglPegaPVMMatrix      (CIMTMatriz &resmtx               );

    bool iglInitBuffers        (VertexData   *VertexBuffer   ,
                                GLuint       *VertexIndices  ,
                                long          QtdVertices    ,
                                long          QtdIndices     ,
                                GLuint        vboIds[3]      ,
                                GLuint        qryIds[1]      );

    bool iglPegaIdLuz          (GLenum       &ThisGLLight    ,
                                int           IdLuz          ,
                                bool          bHabilita      );
    bool iglColormaterial      (bool          bHabilita      );
    bool iglTextureST          (bool          bHabilita      );
    bool iglQuads              (                             );
    bool iglPolygons           (                             );

private:
    QOpenGLFunctions_1_4  *pGL;
};

#endif
#endif // IGL_FUNCTIONSPCV14_H
