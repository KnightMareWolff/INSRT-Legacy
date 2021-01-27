#ifndef IGL_FUNCTIONSPCV45_H
#define IGL_FUNCTIONSPCV45_H

#include "IGL_Functions.h"

#ifdef Q_OS_WIN
#include <QOpenGLFunctions_4_5_Core>

class CIGLFunctionsPCv45 : public CIGLFunctions
{
public:
    CIGLFunctionsPCv45(QOpenGLContext *pContext,int iVersao,int iMajor,int iMinor);

    bool iglEnableStates       ();
    bool iglDisableStates      ();
    bool iglFinish             ();
    bool iglFenceSync          (GLsync &pIGL_Sync);
    bool iglWaitSync           (GLsync  pIGL_Sync);
    bool iglActiveTexture      (unsigned int estado);
    bool iglEnable             (unsigned int estado);
    bool iglDisable            (unsigned int estado);
    bool iglDeleteTextures     (int vlr, GLuint *Id);
    bool iglDeleteBuffers      (int vlr, GLuint *Id);

    bool iglRenderBuffers      (int vlr,
                                long QtdVertices,
                                long QtdIndices,
                                GLuint  ProgramId     ,
                                GLuint *Id,
                                bool FeedBack,
                                FeedBackData *FeedbackBuffer);


    bool iglSetaMaterial       (GLuint     ProgramId        ,
                                CIMTVetor4 CorDifusa        ,
                                CIMTVetor4 CorAmbiente      ,
                                CIMTVetor4 CorEmissiva      ,
                                CIMTVetor4 CorSpecular      ,
                                CIMTVetor4 CorAlpha         ,
                                bool       bRejeitaAlphabits,
                                float      opacidade        ,
                                float      brilho           ,
                                float      reflexao         ,
                                float      IndiceRefracao);

    bool iglSetaLuzPonto       (GLuint        ProgramId,
                                unsigned int  Id ,
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

    bool iglSetaLuzDirecional  (GLuint ProgramId,
                                unsigned int  Id ,
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

    bool iglSetaLuzSpot        (GLuint ProgramId,
                                unsigned int  Id ,
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

    bool iglSetaVisPerspectiva (GLuint ProgramId,
                                float ValorProx,
                                float ValorDist,
                                int   ValorAltura,
                                int   ValorLargura,
                                float FOV);

    bool iglSetaVisOrtogonal   (GLuint ProgramId,
                                float ValorProx,
                                float ValorDist,
                                int   ValorAltura,
                                int   ValorLargura);

    bool iglSetaLookAt         (GLuint ProgramId, CIMTVetor Pos, CIMTVetor View, CIMTVetor Up);

    bool iglSetaUniformInt     (GLuint ProgramId,const GLchar *nome,int        vlr);
    bool iglSetaUniformFloat   (GLuint ProgramId,const GLchar *nome,float      vlr);
    bool iglSetaUniformVec3    (GLuint ProgramId,const GLchar *nome,CIMTVetor  vlr);
    bool iglSetaUniformVec4    (GLuint ProgramId,const GLchar *nome,CIMTVetor4 vlr);
    bool iglSetaUniformMatrix  (GLuint ProgramId,CIMTMatriz mtx);

    bool iglCalculaPVMMatrix   (CIMTMatriz mtx,CIMTMatriz &resmtx);
    bool iglPegaPVMMatrix      (CIMTMatriz &resmtx               );

    bool iglInitBuffers        (IGLVertexBuffer   *IGL_VertexBuffer   ,
                                GLuint            *IGL_VertexIndices  ,
                                long               IGL_QtdVertices    ,
                                long               IGL_QtdIndices     ,
                                GLuint             IGL_VboIds[3]      );

    bool iglColormaterial      (GLuint ProgramId, bool  bHabilita      );
    bool iglMaterialMode       (GLuint ProgramId,int    iMode          );
    bool iglReadPixels         (int x,int y, GLchar    *res  );
    bool iglFrontFace          (int           iMode          );
    int  iglGetVersion         (                             );

    bool iglCreateTexture      (GLuint        &IGL_TextureId     ,
                                GLubyte       *IGL_TextureData   ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat ,
                                GLuint         IGL_TextureMipmaps);

    bool iglPreparaTextura     (GLuint         IGL_TextureId     ,
                                GLuint         IGL_TextureMode   ,
                                GLboolean      IGL_TextureUpdate ,
                                GLubyte       *IGL_TextureData   ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat);

    bool iglCreateCubeMap      (GLuint        &IGL_TextureId     ,
                                GLubyte       *IGL_TextureRight  ,
                                GLubyte       *IGL_TextureLeft   ,
                                GLubyte       *IGL_TextureTop    ,
                                GLubyte       *IGL_TextureBottom ,
                                GLubyte       *IGL_TextureBack   ,
                                GLubyte       *IGL_TextureFront  ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat ,
                                GLuint         IGL_TextureMipmaps);

    bool iglTransformFeedback  (GLuint IGL_ProgramId);

    bool iglTransformBuffer    (GLuint           IGL_ProgramId  ,
                                GLuint           IGL_VboId      ,
                                GLuint           IGL_QtdVertices,
                                CIMTMatriz       IGL_TransfMtx  ,
                                IGLVertexBuffer *IGL_VertexData);

    IGLVertexBuffer * iglMapBuffer          (GLuint           IGL_ProgramId  ,
                                             GLuint           IGL_VboId      );

    bool iglUnMapBuffer        (GLuint           IGL_ProgramId  ,
                                GLuint           IGL_VboId      ,
                                IGLVertexBuffer *IGL_VertexData);

    QString iglGetString       (GLuint           IGL_StringId  );

private:
    QOpenGLFunctions_4_5_Core  *pGL;

    void BindBuffers(GLuint ProgramId, GLuint *Id);

    void TransfFeedback(long           QtdVertices    ,
                        long           QtdIndices     ,
                        FeedBackData  *FeedbackBuffer );

    void RenderBuffers(int TpPoligono, long QtdIndices);
};
#endif
#endif // CIGLFUNCTIONSPCV45_H
