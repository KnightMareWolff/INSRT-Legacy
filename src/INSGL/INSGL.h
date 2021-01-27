#ifndef INSGL_H
#define INSGL_H

#include "IGL_GlobalDef.h"
#include "IGL_Functions.h"

#ifdef Q_OS_WIN
   #include "IGL_FunctionsPCv40.h"
   #include "IGL_FunctionsPCv41.h"
   #include "IGL_FunctionsPCv42.h"
   #include "IGL_FunctionsPCv43.h"
   #include "IGL_FunctionsPCv44.h"
   #include "IGL_FunctionsPCv45.h"
#endif

#ifdef Q_OS_MAC
   #include "IGL_FunctionsMacOS.h"
#endif

#ifdef Q_OS_ANDROID
   #include "IGL_FunctionsAndroid.h"
#endif

#ifdef Q_OS_IOS
   #include "IGL_FunctionsIOS.h"
#endif


class INSGL
{

public:
    INSGL(                        );
    INSGL(QOpenGLContext *pContext);
    INSGL(QGLContext     *pContext);

    bool execGL   (int iOglFcn);
    bool execGL   (int iOglFcn, GLuint ProgramId, unsigned int  estado        );
    bool execGL   (int iOglFcn, GLuint ProgramId, const GLchar *nome , int vlr);
    bool execGL   (int iOglFcn, GLuint ProgramId, CIMTMatriz       mtx        );
    bool execGL   (int iOglFcn,int vlr          , GLuint *Id    );

    bool execGL   (int iOglFcn, int           vlr           ,
                                long          QtdVertices   ,
                                long          QtdIndices    ,
                                GLuint        ProgramId     ,
                                GLuint       *Id            ,
                                bool          FeedBack      ,
                                FeedBackData *FeedbackBuffer);

    bool execGL   (int iOglFcn, GLuint ProgramId,
                               float ValorProx,
                               float ValorDist,
                               int   ValorAltura,
                               int   ValorLargura,
                               float FOV);

    bool execGL   (int iOglFcn, GLuint ProgramId, CIMTVetor Pos, CIMTVetor View, CIMTVetor Up);

    bool execGL   (int iOglFcn,GLuint          ProgramId        ,
                               CIMTVetor4      CorDifusa        ,
                               CIMTVetor4      CorAmbiente      ,
                               CIMTVetor4      CorEmissiva      ,
                               CIMTVetor4      CorSpecular      ,
                               CIMTVetor4      CorAlpha         ,
                               bool            bAlphaReject     ,
                               float           opacidade        ,
                               float           brilho           ,
                               float           reflexao         ,
                               float           IndiceRefracao);


    bool execGL   (int iOglFcn,GLuint ProgramId                 ,
                               unsigned int  Id                 ,
                               CIMTVetor4    pos                ,
                               CIMTVetor4    dir                ,
                               CIMTVetor4    CorDifusa          ,
                               CIMTVetor4    CorAmbiente        ,
                               CIMTVetor4    CorSpecular        ,
                               float         Expoente           ,
                               float         CutOff             ,
                               float         AtenuacaoConstante ,
                               float         AtenuacaoLinear    ,
                               float         AtenuacaoQuadratica);

    bool execGL   (int iOglFcn, IGLVertexBuffer   *IGL_VertexBuffer   ,
                                GLuint            *IGL_VertexIndices  ,
                                long               IGL_QtdVertices    ,
                                long               IGL_QtdIndices     ,
                                GLuint             IGL_VboIds[2]      );

    bool execGL   (int iOglFcn, int  x, int y ,  GLchar *res);

    bool execGL   (int iOglFcn, GLuint        &IGL_TextureId     ,
                                GLubyte       *IGL_TextureData   ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat ,
                                GLuint         IGL_TextureMipmaps);

    bool execGL   (int iOglFcn, GLuint        &IGL_TextureId     ,
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

    bool execGL   (int iOglFcn, GLuint         IGL_TextureId     ,
                                GLuint         IGL_TextureMode   ,
                                GLboolean      IGL_TextureUpdate ,
                                GLubyte       *IGL_TextureData   ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat );


     bool CalculaPVMMatrix      (CIMTMatriz  pIGLModelMatrix            ,
                                 CIMTMatriz &pIGLPVMMatrix              ,
                                 bool        bReset                     );
     int  PegaVersao            (                                       );
     bool FenceSync             (GLsync &pIGL_Sync                      );
     bool WaitSync              (GLsync  pIGL_Sync                      );
     bool AddTransformFeedback  (GLuint  ProgramId                      );

     bool TransformBuffer       (GLuint             IGL_ProgramId    ,
                                 GLuint             IGL_VboId        ,
                                 GLuint             IGL_QtdVert      ,
                                 CIMTMatriz         IGL_ModelMatrix  ,
                                 IGLVertexBuffer   *IGL_VertexBuffer );

     IGLVertexBuffer *MapBuffer (GLuint             IGL_ProgramId    ,
                                 GLuint             IGL_VboId        );

     bool UnMapBuffer           (GLuint             IGL_ProgramId    ,
                                 GLuint             IGL_VboId        ,
                                 IGLVertexBuffer   *IGL_VertexBuffer );

     QString PegaVendor         (                                    );



private:
    static CIGLFunctions  *pGLExec;
    static QOpenGLContext *pINS3DContext;
    QSurfaceFormat         pINS3DFormat ;

    int CalculaVersao(int iMajor,int iMinor);

};

#endif // INSGL_H
