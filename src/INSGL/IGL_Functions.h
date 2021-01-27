#ifndef IGL_FUNCTIONS_H
#define IGL_FUNCTIONS_H

#include "IGL_GlobalDef.h"

class CIGLFunctions
{
public:
    CIGLFunctions();

    virtual bool iglEnableStates       ();
    virtual bool iglDisableStates      ();
    virtual bool iglFinish             ();
    virtual bool iglFenceSync          (GLsync &pIGL_Sync);
    virtual bool iglWaitSync           (GLsync  pIGL_Sync);
    virtual bool iglActiveTexture      (unsigned int estado);
    virtual bool iglEnable             (unsigned int estado);
    virtual bool iglDisable            (unsigned int estado);
    virtual bool iglDeleteTextures     (int vlr, GLuint *Id);
    virtual bool iglDeleteBuffers      (int vlr, GLuint *Id);

    virtual bool iglRenderBuffers      (int           vlr,
                                        long          QtdVertices,
                                        long          QtdIndices,
                                        GLuint        ProgramId ,
                                        GLuint       *Id,
                                        bool          FeedBack,
                                        FeedBackData *FeedbackBuffer);

    virtual bool iglSetaMaterial       (GLuint ProgramId,
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

    virtual bool iglSetaLuzPonto       (GLuint ProgramId,
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

    virtual bool iglSetaLuzDirecional  (GLuint ProgramId,
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

    virtual bool iglSetaLuzSpot        (GLuint ProgramId,
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

    virtual bool iglSetaVisPerspectiva (GLuint  ProgramId ,
                                        float ValorProx,
                                        float ValorDist,
                                        int   ValorAltura,
                                        int   ValorLargura,
                                        float FOV);
    virtual bool iglSetaVisOrtogonal   (GLuint  ProgramId ,
                                        float ValorProx,
                                        float ValorDist,
                                        int   ValorAltura,
                                        int   ValorLargura);

    virtual bool iglSetaLookAt         (GLuint  ProgramId ,CIMTVetor Pos,CIMTVetor View,CIMTVetor Up);

    virtual bool iglSetaUniformInt     (GLuint  ProgramId ,const GLchar *nome,int        vlr);
    virtual bool iglSetaUniformFloat   (GLuint  ProgramId ,const GLchar *nome,float      vlr);
    virtual bool iglSetaUniformVec3    (GLuint  ProgramId ,const GLchar *nome,CIMTVetor  vlr);
    virtual bool iglSetaUniformVec4    (GLuint  ProgramId ,const GLchar *nome,CIMTVetor4 vlr);
    virtual bool iglSetaUniformMatrix  (GLuint  ProgramId ,CIMTMatriz mtx);

    virtual bool iglCalculaPVMMatrix   (CIMTMatriz mtx,CIMTMatriz &resmtx);
    virtual bool iglPegaPVMMatrix      (CIMTMatriz &resmtx               );

    virtual bool iglInitBuffers        (IGLVertexBuffer   *IGL_VertexBuffer   ,
                                        GLuint            *IGL_VertexIndices  ,
                                        long               IGL_QtdVertices    ,
                                        long               IGL_QtdIndices     ,
                                        GLuint             IGL_VboIds[3]      );

    virtual bool iglColormaterial      (GLuint ProgramId, bool bHabilita);
    virtual bool iglMaterialMode       (GLuint ProgramId, int  iMode    );
    virtual bool iglReadPixels         (int x,int y,  GLchar *res    );
    virtual bool iglFrontFace          (int           iMode          );
    virtual int  iglGetVersion         (                             );

    virtual bool iglCreateTexture      (GLuint        &IGL_TextureId     ,
                                        GLubyte       *IGL_TextureData   ,
                                        GLuint         IGL_TextureWidth  ,
                                        GLuint         IGL_TextureHeight ,
                                        GLuint         IGL_TextureFormat ,
                                        GLuint         IGL_TextureMipmaps);
    virtual bool iglCreateCubeMap      (GLuint        &IGL_TextureId     ,
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

    virtual bool iglPreparaTextura     (GLuint         IGL_TextureId     ,
                                        GLuint         IGL_TextureMode   ,
                                        GLboolean      IGL_TextureUpdate ,
                                        GLubyte       *IGL_TextureData   ,
                                        GLuint         IGL_TextureWidth  ,
                                        GLuint         IGL_TextureHeight ,
                                        GLuint         IGL_TextureFormat);

    virtual bool iglTransformFeedback  (GLuint         IGL_ProgramId);

    virtual bool iglTransformBuffer    (GLuint           IGL_ProgramId  ,
                                        GLuint           IGL_VboId      ,
                                        GLuint           IGL_QtdVertices,
                                        CIMTMatriz       IGL_TransfMtx  ,
                                        IGLVertexBuffer *IGL_VertexData);

    virtual IGLVertexBuffer * iglMapBuffer          (GLuint           IGL_ProgramId  ,
                                                     GLuint           IGL_VboId     );
    virtual bool iglUnMapBuffer        (GLuint           IGL_ProgramId  ,
                                        GLuint           IGL_VboId      ,
                                        IGLVertexBuffer *IGL_VertexData);
    virtual QString iglGetString       (GLuint           IGL_StringId   );

protected:

    int  iIGLVersion       ,
         iIGLMinorVersion  ,
         iIGLMajorVersion  ,
         iIGLPlataforma    ;

    static bool bIGLContextoInicializado;

    CIMTMatriz mIGLViewMatrix;
    CIMTMatriz mIGLProjectionMatrix;
    CIMTMatriz mIGLPVMMatrix;
};

#endif // IGL_FUNCTIONS_H
