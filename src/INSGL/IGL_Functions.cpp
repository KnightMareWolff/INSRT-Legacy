#include "IGL_Functions.h"

//Valor estatico para verificar se o contexto já foi criado
bool CIGLFunctions::bIGLContextoInicializado = false;

CIGLFunctions::CIGLFunctions()
{
}


bool CIGLFunctions::iglEnableStates()
{
    return true;
}

bool CIGLFunctions::iglDisableStates()
{
    return true;
}

bool CIGLFunctions::iglActiveTexture(unsigned int estado)
{
    Q_UNUSED(estado);
    return true;
}


bool CIGLFunctions::iglEnable(unsigned int estado)
{
    Q_UNUSED(estado);
    return true;
}

bool CIGLFunctions::iglDisable(unsigned int estado)
{
    Q_UNUSED(estado);
    return true;
}

bool CIGLFunctions::iglDeleteTextures(int vlr, GLuint *Id)
{
    Q_UNUSED(vlr);
    Q_UNUSED(Id);
    return true;
}

bool CIGLFunctions::iglDeleteBuffers(int vlr, GLuint *Id)
{
    Q_UNUSED(vlr);
    Q_UNUSED(Id);
    return true;
}

bool CIGLFunctions::iglRenderBuffers(int            vlr           ,
                                     long           QtdVertices   ,
                                     long           QtdIndices    ,
                                     GLuint         ProgramId,
                                     GLuint        *Id            ,
                                     bool           FeedBack      ,
                                     FeedBackData  *FeedbackBuffer)
{
    Q_UNUSED(vlr);
    Q_UNUSED(QtdVertices);
    Q_UNUSED(QtdIndices);
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(FeedBack);
    Q_UNUSED(FeedbackBuffer);
    return true;
}


bool CIGLFunctions::iglSetaMaterial(GLuint ProgramId,
                                    CIMTVetor4 CorDifusa        ,
                                    CIMTVetor4 CorAmbiente      ,
                                    CIMTVetor4 CorEmissiva      ,
                                    CIMTVetor4 CorSpecular      ,
                                    CIMTVetor4 CorAlpha         ,
                                    bool       bRejeitaAlphabits,
                                    float      opacidade        ,
                                    float      brilho           ,
                                    float      reflexao         ,
                                    float      IndiceRefracao   )
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorEmissiva);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(CorAlpha);
    Q_UNUSED(bRejeitaAlphabits);
    Q_UNUSED(opacidade);
    Q_UNUSED(brilho);
    Q_UNUSED(reflexao);
    Q_UNUSED(IndiceRefracao);
    return true;
}

bool CIGLFunctions::iglSetaLuzPonto       (GLuint ProgramId,
                                           unsigned int Id ,
                                                CIMTVetor4   pos,
                                                CIMTVetor4   dir,
                                                CIMTVetor4   CorDifusa,
                                                CIMTVetor4   CorAmbiente,
                                                CIMTVetor4   CorSpecular,
                                                float        Expoente   ,
                                                float        CutOff     ,
                                                float        AtenuacaoConstante,
                                                float        AtenuacaoLinear   ,
                                                float        AtenuacaoQuadratica)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(pos);
    Q_UNUSED(dir);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(Expoente);
    Q_UNUSED(CutOff);
    Q_UNUSED(AtenuacaoConstante);
    Q_UNUSED(AtenuacaoLinear);
    Q_UNUSED(AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctions::iglSetaLuzDirecional  (GLuint ProgramId, unsigned int Id,
                                                CIMTVetor4 pos ,
                                                CIMTVetor4 dir,
                                                CIMTVetor4 CorDifusa,
                                                CIMTVetor4 CorAmbiente,
                                                CIMTVetor4 CorSpecular,
                                                float Expoente,
                                                float CutOff,
                                                float AtenuacaoConstante,
                                                float AtenuacaoLinear,
                                                float AtenuacaoQuadratica)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(pos);
    Q_UNUSED(dir);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(Expoente);
    Q_UNUSED(CutOff);
    Q_UNUSED(AtenuacaoConstante);
    Q_UNUSED(AtenuacaoLinear);
    Q_UNUSED(AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctions::iglSetaLuzSpot        (GLuint ProgramId, unsigned int Id,
                                                CIMTVetor4  pos,
                                                CIMTVetor4 dir,
                                                CIMTVetor4 CorDifusa,
                                                CIMTVetor4 CorAmbiente,
                                                CIMTVetor4 CorSpecular,
                                                float Expoente,
                                                float CutOff,
                                                float AtenuacaoConstante,
                                                float AtenuacaoLinear,
                                                float AtenuacaoQuadratica)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(pos);
    Q_UNUSED(dir);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(Expoente);
    Q_UNUSED(CutOff);
    Q_UNUSED(AtenuacaoConstante);
    Q_UNUSED(AtenuacaoLinear);
    Q_UNUSED(AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctions::iglSetaVisPerspectiva(GLuint  ProgramId ,
                                          float ValorProx   ,
                                          float ValorDist   ,
                                          int   ValorAltura ,
                                          int   ValorLargura,
                                          float FOV         )
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(ValorProx);
    Q_UNUSED(ValorDist);
    Q_UNUSED(ValorAltura);
    Q_UNUSED(ValorLargura);
    Q_UNUSED(FOV);
    return true;
}

bool CIGLFunctions::iglSetaVisOrtogonal(GLuint ProgramId,
                                        float  ValorProx,
                                        float  ValorDist,
                                        int    ValorAltura,
                                        int    ValorLargura)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(ValorProx);
    Q_UNUSED(ValorDist);
    Q_UNUSED(ValorAltura);
    Q_UNUSED(ValorLargura);
    return true;
}

bool CIGLFunctions::iglSetaLookAt(GLuint ProgramId, CIMTVetor Pos, CIMTVetor View, CIMTVetor Up)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Pos);
    Q_UNUSED(View);
    Q_UNUSED(Up);
    return true;
}

bool CIGLFunctions::iglSetaUniformInt(GLuint ProgramId, const GLchar *nome, int vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetaUniformFloat(GLuint ProgramId, const GLchar *nome, float vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetaUniformVec3(GLuint ProgramId, const GLchar *nome, CIMTVetor vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetaUniformVec4(GLuint ProgramId, const GLchar *nome, CIMTVetor4 vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetaUniformMatrix(GLuint ProgramId, CIMTMatriz mtx)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(mtx);
    return true;
}

bool CIGLFunctions::iglCalculaPVMMatrix(CIMTMatriz mtx,CIMTMatriz &resmtx)
{
    Q_UNUSED(mtx);
    Q_UNUSED(resmtx);
    return true;
}

bool CIGLFunctions::iglPegaPVMMatrix(CIMTMatriz &resmtx)
{
    Q_UNUSED(resmtx);
    return true;
}

bool CIGLFunctions::iglInitBuffers( IGLVertexBuffer   *IGL_VertexBuffer  ,
                                    GLuint            *IGL_VertexIndices ,
                                    long               IGL_QtdVertices   ,
                                    long               IGL_QtdIndices    ,
                                    GLuint             IGL_VboIds[]      )
{
    Q_UNUSED(IGL_VertexBuffer);
    Q_UNUSED(IGL_VertexIndices);
    Q_UNUSED(IGL_QtdVertices);
    Q_UNUSED(IGL_QtdIndices);
    Q_UNUSED(IGL_VboIds);
    return true;
}

bool CIGLFunctions::iglFinish()
{
   return true;
}

bool CIGLFunctions::iglFenceSync(GLsync &pIGL_Sync)
{

   Q_UNUSED(pIGL_Sync);
   return true;
}

bool CIGLFunctions::iglWaitSync(GLsync pIGL_Sync)
{
   Q_UNUSED(pIGL_Sync);
   return true;
}

bool CIGLFunctions::iglColormaterial(GLuint ProgramId, bool bHabilita)
{
    return true;
}

bool CIGLFunctions::iglMaterialMode(GLuint ProgramId, int iMode)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(iMode);
    return true;
}



bool CIGLFunctions::iglReadPixels(int x,int y,GLchar *res)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(res);
    return true;
}

bool CIGLFunctions::iglFrontFace(int iMode)
{
    Q_UNUSED(iMode);
    return true;
}

int CIGLFunctions::iglGetVersion()
{
    return 99;
}

bool CIGLFunctions::iglCreateTexture(GLuint        &IGL_TextureId     ,
                                     GLubyte       *IGL_TextureData   ,
                                     GLuint         IGL_TextureWidth  ,
                                     GLuint         IGL_TextureHeight ,
                                     GLuint         IGL_TextureFormat,
                                     GLuint         IGL_TextureMipmaps)
{
    Q_UNUSED(IGL_TextureId);
    Q_UNUSED(IGL_TextureData);
    Q_UNUSED(IGL_TextureWidth);
    Q_UNUSED(IGL_TextureHeight);
    Q_UNUSED(IGL_TextureFormat);
    Q_UNUSED(IGL_TextureMipmaps);
    return true;
}

bool CIGLFunctions::iglCreateCubeMap      (GLuint        &IGL_TextureId     ,
                                           GLubyte       *IGL_TextureRight  ,
                                           GLubyte       *IGL_TextureLeft   ,
                                           GLubyte       *IGL_TextureTop    ,
                                           GLubyte       *IGL_TextureBottom ,
                                           GLubyte       *IGL_TextureBack   ,
                                           GLubyte       *IGL_TextureFront  ,
                                           GLuint         IGL_TextureWidth  ,
                                           GLuint         IGL_TextureHeight ,
                                           GLuint         IGL_TextureFormat ,
                                           GLuint         IGL_TextureMipmaps)
{
    Q_UNUSED(IGL_TextureId);
    Q_UNUSED(IGL_TextureRight);
    Q_UNUSED(IGL_TextureLeft);
    Q_UNUSED(IGL_TextureTop);
    Q_UNUSED(IGL_TextureBottom);
    Q_UNUSED(IGL_TextureBack);
    Q_UNUSED(IGL_TextureFront);
    Q_UNUSED(IGL_TextureWidth);
    Q_UNUSED(IGL_TextureHeight);
    Q_UNUSED(IGL_TextureFormat);
    Q_UNUSED(IGL_TextureMipmaps);
    return true;
}

bool CIGLFunctions::iglPreparaTextura(GLuint     IGL_TextureId     ,
                                      GLuint     IGL_TextureMode   ,
                                      GLboolean  IGL_TextureUpdate ,
                                      GLubyte   *IGL_TextureData   ,
                                      GLuint     IGL_TextureWidth  ,
                                      GLuint     IGL_TextureHeight,
                                      GLuint     IGL_TextureFormat)
{
    Q_UNUSED(IGL_TextureId);
    Q_UNUSED(IGL_TextureMode);
    Q_UNUSED(IGL_TextureUpdate);
    Q_UNUSED(IGL_TextureData);
    Q_UNUSED(IGL_TextureWidth);
    Q_UNUSED(IGL_TextureHeight);
    Q_UNUSED(IGL_TextureFormat);
    return true;
}

bool CIGLFunctions::iglTransformFeedback(GLuint IGL_ProgramId)
{
    Q_UNUSED(IGL_ProgramId);
    return true;
}

bool CIGLFunctions::iglTransformBuffer(GLuint           IGL_ProgramId,
                                       GLuint           IGL_VboId    ,
                                       GLuint           IGL_QtdVertices,
                                       CIMTMatriz       IGL_TransfMtx,
                                       IGLVertexBuffer *IGL_VertexData)
{
    Q_UNUSED(IGL_ProgramId);
    Q_UNUSED(IGL_VboId);
    Q_UNUSED(IGL_QtdVertices);
    Q_UNUSED(IGL_TransfMtx);
    Q_UNUSED(IGL_VertexData);
    return true;
}

IGLVertexBuffer *CIGLFunctions::iglMapBuffer(GLuint           IGL_ProgramId,
                                             GLuint           IGL_VboId    )
{
    Q_UNUSED(IGL_ProgramId);
    Q_UNUSED(IGL_VboId);
    //Q_UNUSED(IGL_VertexData);
    return NULL;
}

bool CIGLFunctions::iglUnMapBuffer(GLuint           IGL_ProgramId,
                                   GLuint           IGL_VboId    ,
                                   IGLVertexBuffer *IGL_VertexData)
{
    Q_UNUSED(IGL_ProgramId);
    Q_UNUSED(IGL_VboId);
    Q_UNUSED(IGL_VertexData);
    return true;
}

QString CIGLFunctions::iglGetString(GLuint           IGL_StringId)
{
    Q_UNUSED(IGL_StringId);
    return QString("Default String");
}

