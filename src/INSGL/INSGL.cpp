#include "INSGL.h"

CIGLFunctions*  INSGL::pGLExec=NULL;
QOpenGLContext* INSGL::pINS3DContext=NULL;

INSGL::INSGL()
{

}

INSGL::INSGL(QOpenGLContext *pContext)
{
    int VF,VMaj,VMin;

    if(pContext->isValid())
    {
       pINS3DContext = pContext;
       pINS3DFormat  = pContext->format();
    }
    else
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Criação Contexto OpenGL");
        qWarning() << "Erro na Criação Contexto OpenGL.";

        exit(1);
    }

    VMaj = pINS3DFormat.majorVersion();
    VMin = pINS3DFormat.minorVersion();

    VF = CalculaVersao(VMaj,VMin);

   #ifdef Q_OS_WIN
   switch(VF)
   {
      case 40:{pGLExec = new CIGLFunctionsPCv40(pINS3DContext,VF,VMaj,VMin);}break;
      case 41:{pGLExec = new CIGLFunctionsPCv41(pINS3DContext,VF,VMaj,VMin);}break;
      case 42:{pGLExec = new CIGLFunctionsPCv42(pINS3DContext,VF,VMaj,VMin);}break;
      case 43:{pGLExec = new CIGLFunctionsPCv43(pINS3DContext,VF,VMaj,VMin);}break;
      case 44:{pGLExec = new CIGLFunctionsPCv44(pINS3DContext,VF,VMaj,VMin);}break;
      case 45:{pGLExec = new CIGLFunctionsPCv45(pINS3DContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsPCv45(pINS3DContext,VF,VMaj,VMin);}break;
   }
   #endif

   #ifdef Q_OS_ANDROID
   switch(VF)
   {
      case 20:{pGLExec = new CIGLFunctionsAndroid(pINS3DContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsAndroid(pINS3DContext,VF,VMaj,VMin);}break;
   }
   #endif

   #ifdef Q_OS_MAC
   switch(VF)
   {
      case 20:{pGLExec = new CIGLFunctionsMacOS(pINS3DContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsMacOS(pINS3DContext,VF,VMaj,VMin);}break;
   }
   #endif

}

INSGL::INSGL(QGLContext *pContext)
{
    int VF,VMaj,VMin;

    if(pContext->isValid())
    {
       pINS3DContext = pContext->contextHandle();
       pINS3DFormat  = pINS3DContext->format();

#ifdef Q_OS_WIN
       pINS3DFormat.setMajorVersion(4);
       pINS3DFormat.setMinorVersion(3);
#endif
#ifdef Q_OS_ANDROID
       pINS3DFormat.setMajorVersion(2);
       pINS3DFormat.setMinorVersion(0);
#endif
    }

    VMaj = pINS3DFormat.majorVersion();
    VMin = pINS3DFormat.minorVersion();

    VF = CalculaVersao(VMaj,VMin);

   #ifdef Q_OS_WIN
   switch(VF)
   {
      case 40:{pGLExec = new CIGLFunctionsPCv40(pINS3DContext,VF,VMaj,VMin);}break;
      case 41:{pGLExec = new CIGLFunctionsPCv41(pINS3DContext,VF,VMaj,VMin);}break;
      case 42:{pGLExec = new CIGLFunctionsPCv42(pINS3DContext,VF,VMaj,VMin);}break;
      case 43:{pGLExec = new CIGLFunctionsPCv43(pINS3DContext,VF,VMaj,VMin);}break;
      case 44:{pGLExec = new CIGLFunctionsPCv44(pINS3DContext,VF,VMaj,VMin);}break;
      case 45:{pGLExec = new CIGLFunctionsPCv45(pINS3DContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsPCv45(pINS3DContext,VF,VMaj,VMin);}break;
   }
   #endif

   #ifdef Q_OS_ANDROID
   switch(VF)
   {
      case 20:{pGLExec = new CIGLFunctionsAndroid(pINS3DContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsAndroid(pINS3DContext,VF,VMaj,VMin);}break;
   }
   #endif

   #ifdef Q_OS_MAC
   switch(VF)
   {
      case 20:{pGLExec = new CIGLFunctionsMacOS(pINS3DContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsMacOS(pINS3DContext,VF,VMaj,VMin);}break;
   }
   #endif

}

int INSGL::CalculaVersao(int iMajor, int iMinor)
{
    switch(iMajor)
    {
        case 1:
        {
            switch(iMinor)
            {
               case 0:{return 10;}break;
               case 1:{return 11;}break;
               case 2:{return 12;}break;
               case 3:{return 13;}break;
               case 4:{return 14;}break;
               case 5:{return 15;}break;
               default:
               {
                QMessageBox::information(0, "Insane RT Framework",
                                            "Erro de identificação da Versão OGL");
                qWarning() << "Erro de identificação da Versão OGL.";

                exit(1);
               }break;
            }
        }break;

        case 2:
        {
           switch(iMinor)
           {
              case 0:{return 20;}break;
              case 1:{return 21;}break;
              default:
              {
               QMessageBox::information(0, "Insane RT Framework",
                                           "Erro de identificação da Versão OGL");
               qWarning() << "Erro de identificação da Versão OGL.";

               exit(1);
              }break;
           }
        }break;

        case 3:
        {
           switch(iMinor)
           {
              case 0:{return 30;}break;
              case 1:{return 31;}break;
              case 2:{return 32;}break;
              case 3:{return 33;}break;
              default:
              {
               QMessageBox::information(0, "Insane RT Framework",
                                           "Erro de identificação da Versão OGL");
               qWarning() << "Erro de identificação da Versão OGL.";

               exit(1);
              }break;
           }
        }break;

        case 4:
        {
           switch(iMinor)
           {
              case 0:{return 40;}break;
              case 1:{return 41;}break;
              case 2:{return 42;}break;
              case 3:{return 43;}break;
              case 4:{return 44;}break;
              case 5:{return 45;}break;
              case 6:{return 46;}break;
              default:
              {
               QMessageBox::information(0, "Insane RT Framework",
                                           "Erro de identificação da Versão OGL");
               qWarning() << "Erro de identificação da Versão OGL.";

               exit(1);
              }break;
           }
        }break;

        default:
        {
           QMessageBox::information(0, "Insane RT Framework",
                                       "Erro de identificação da Versão OGL");
           qWarning() << "Erro de identificação da Versão OGL.";

           exit(1);

        }break;
    }

    return 0;
}

bool INSGL::execGL(int iOglFcn)
{
    switch(iOglFcn)
    {
       case IGL_SH_ENABLESTATES:
       {
          pGLExec->iglEnableStates();
       }break;

       case IGL_SH_DISABLESTATES:
       {
          pGLExec->iglDisableStates();
       }break;

       case IGL_SH_FINISH:
       {
          pGLExec->iglFinish();
       }
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
          return false;
       }
    }
    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint ProgramId,unsigned int estado)
{
    switch(iOglFcn)
    {
       case IGL_SH_ACTIVETEXTURE:
       {
          pGLExec->iglActiveTexture(estado);
       }break;

       case IGL_SH_ENABLE:
       {
          switch(estado)
          {
             case IGL_MATERIAL_COLOR    :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_COLORMATERIAL   );}break;
             case IGL_MATERIAL_TEXTURE  :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_TEXTUREDMATERIAL);}break;
             case IGL_MATERIAL_MIXED    :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_MIXEDMATERIAL   );}break;
             case IGL_MATERIAL_NORMALMAP:{pGLExec->iglMaterialMode(ProgramId,IGL_SH_NMAPMATERIAL    );}break;
             case IGL_MATERIAL_REFLEXIVE:{pGLExec->iglMaterialMode(ProgramId,IGL_SH_REFLMATERIAL    );}break;
             case IGL_MATERIAL_REFRATIVE:{pGLExec->iglMaterialMode(ProgramId,IGL_SH_REFRMATERIAL    );}break;
             case IGL_MATERIAL_CUBEMAP  :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_CUBEMAPMATERIAL );}break;
             case IGL_WINMODE_CW        :{pGLExec->iglFrontFace   (GL_CW                  );}break;
             case IGL_WINMODE_CCW       :{pGLExec->iglFrontFace   (GL_CCW                 );}break;
             default:                    {pGLExec->iglEnable(estado);}break;
          }
       }break;

       case IGL_SH_DISABLE:
       {
          switch(estado)
          {
             case IGL_MATERIAL_COLOR    :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_COLORMATERIAL   );}break;
             case IGL_MATERIAL_TEXTURE  :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_COLORMATERIAL   );}break;
             case IGL_MATERIAL_MIXED    :{pGLExec->iglMaterialMode(ProgramId,IGL_SH_TEXTUREDMATERIAL);}break;
             case IGL_MATERIAL_NORMALMAP:{pGLExec->iglMaterialMode(ProgramId,IGL_SH_MIXEDMATERIAL   );}break;
             case IGL_MATERIAL_REFLEXIVE:{pGLExec->iglMaterialMode(ProgramId,IGL_SH_MIXEDMATERIAL   );}break;
             case IGL_MATERIAL_REFRATIVE:{pGLExec->iglMaterialMode(ProgramId,IGL_SH_MIXEDMATERIAL   );}break;
             case IGL_WINMODE_CW        :{pGLExec->iglFrontFace   (GL_CCW                 );}break;
             case IGL_WINMODE_CCW       :{pGLExec->iglFrontFace   (GL_CW                  );}break;
             default:                    {pGLExec->iglDisable(estado);}break;
          }
       }break;

       default:
       {
          qWarning() << "Função com ESTADO execGL , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL(int iOglFcn, int vlr, GLuint *Id)
{
    switch(iOglFcn)
    {
       case IGL_SH_DELTEXTURE:
       {
          pGLExec->iglDeleteTextures(vlr,Id);
       }break;

       case IGL_SH_DELBUFFERS:
       {
          pGLExec->iglDeleteBuffers(vlr,Id);
       }break;

       default:
       {
          qWarning() << "Função com parametro quantidade e Id execGL , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL   (int            iOglFcn       ,
                      int            vlr           ,
                      long           QtdVertices   ,
                      long           QtdIndices    ,
                      GLuint         ProgramId     ,
                      GLuint        *Id            ,
                      bool           FeedBack      ,
                      FeedBackData  *FeedbackBuffer)
{
    switch(iOglFcn)
    {
       case IGL_SH_RENDERBUFFERS:
       {
          pGLExec->iglRenderBuffers(vlr           ,
                                    QtdVertices   ,
                                    QtdIndices    ,
                                    ProgramId     ,
                                    Id            ,
                                    FeedBack      ,
                                    FeedbackBuffer);
       }break;

       default:
       {
          qWarning() << "Função com parametro quantidade e Id execGL , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL   (int          iOglFcn          ,
                      GLuint       ProgramId        ,
                      CIMTVetor4   CorDifusa        ,
                      CIMTVetor4   CorAmbiente      ,
                      CIMTVetor4   CorEmissiva      ,
                      CIMTVetor4   CorSpecular      ,
                      CIMTVetor4   CorAlpha         ,
                      bool         bAlphaReject     ,
                      float        opacidade        ,
                      float        brilho           ,
                      float        reflexao         ,
                      float        IndiceRefracao   )
{
    switch(iOglFcn)
    {
       case IGL_SH_MATERIAL:
       {
          pGLExec->iglSetaMaterial(ProgramId     ,
                                   CorDifusa     ,
                                   CorAmbiente   ,
                                   CorEmissiva   ,
                                   CorSpecular   ,
                                   CorAlpha      ,
                                   bAlphaReject  ,
                                   opacidade     ,
                                   brilho        ,
                                   reflexao      ,
                                   IndiceRefracao);
       }break;
       default:
       {
          qWarning() << "Função execGL (material) utilizada em versao nao suportada.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL   (int iOglFcn      ,
                      GLuint ProgramId ,
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
                      float         AtenuacaoQuadratica)
{
    switch(iOglFcn)
    {
       case IGL_SH_LIGHT_POINT:
       {
           pGLExec->iglSetaLuzPonto(ProgramId           ,
                                    Id                  ,
                                    pos                 ,
                                    dir                 ,
                                    CorDifusa           ,
                                    CorAmbiente         ,
                                    CorSpecular         ,
                                    Expoente            ,
                                    CutOff              ,
                                    AtenuacaoConstante  ,
                                    AtenuacaoLinear     ,
                                    AtenuacaoQuadratica);
       }break;
       case IGL_SH_LIGHT_DIRECTIONAL:
       {
        pGLExec->iglSetaLuzDirecional(ProgramId           ,
                                      Id                  ,
                                      pos                 ,
                                      dir                 ,
                                      CorDifusa           ,
                                      CorAmbiente         ,
                                      CorSpecular         ,
                                      Expoente            ,
                                      CutOff              ,
                                      AtenuacaoConstante  ,
                                      AtenuacaoLinear     ,
                                      AtenuacaoQuadratica);
       }break;
       case IGL_SH_LIGHT_SPOT:
       {
        pGLExec->iglSetaLuzSpot(ProgramId           ,
                                Id                  ,
                                pos                 ,
                                dir                 ,
                                CorDifusa           ,
                                CorAmbiente         ,
                                CorSpecular         ,
                                Expoente            ,
                                CutOff              ,
                                AtenuacaoConstante  ,
                                AtenuacaoLinear     ,
                                AtenuacaoQuadratica);
       }break;
       default:
       {
          qWarning() << "Função execGL (LUZES PF) Inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint  ProgramId ,float ValorProx,float ValorDist,int ValorAltura,int ValorLargura,float FOV)
{
    switch(iOglFcn)
    {
       case IGL_SH_PERSPECTIVE:
       {
          pGLExec->iglSetaVisPerspectiva(ProgramId    ,
                                         ValorProx    ,
                                         ValorDist    ,
                                         ValorAltura  ,
                                         ValorLargura ,
                                         FOV         );
       }break;

       case IGL_SH_ORTHO:
       {
          pGLExec->iglSetaVisOrtogonal(ProgramId    ,
                                       ValorProx    ,
                                       ValorDist    ,
                                       ValorAltura  ,
                                       ValorLargura );
       }break;

       default:
       {
          qWarning() << "Função execGL (perspectiva) Inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint  ProgramId ,CIMTVetor Pos,CIMTVetor View,CIMTVetor Up)
{
    switch(iOglFcn)
    {
       case IGL_SH_LOOKAT:
       {
          pGLExec->iglSetaLookAt(ProgramId,Pos,View,Up);
       }break;

       default:
       {
          qWarning() << "Função execGL (Lookat) Inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint  ProgramId ,const GLchar *nome,int vlr)
{
    switch(iOglFcn)
    {
       case IGL_SH_UNIINT:
       {
          pGLExec->iglSetaUniformInt(ProgramId,nome,vlr);
       }break;
       default:
       {
          qWarning() << "Função execGL (Nome,Valor) inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL   (int iOglFcn,
                      IGLVertexBuffer *IGL_VertexBuffer   ,
                      GLuint          *IGL_VertexIndices  ,
                      long             IGL_QtdVertices    ,
                      long             IGL_QtdIndices     ,
                      GLuint           IGL_VboIds[3]      )
{
    switch(iOglFcn)
    {
       case IGL_SH_BUFFERINIT:
       {
          pGLExec->iglInitBuffers(IGL_VertexBuffer   ,
                                  IGL_VertexIndices  ,
                                  IGL_QtdVertices    ,
                                  IGL_QtdIndices     ,
                                  IGL_VboIds         );
       }break;

       default:
       {
          qWarning() << "Função com parametro Vertex Buffer , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL(int iOglFcn, GLuint  ProgramId ,CIMTMatriz mtx )
{
    switch(iOglFcn)
    {
       case IGL_SH_MODELMTX:
       {
          pGLExec->iglSetaUniformMatrix(ProgramId,mtx);
       }break;

       default:
       {
          qWarning() << "Função com parametro Matriz , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL(int iOglFcn, int  x,int y ,GLchar *res)
{
    switch(iOglFcn)
    {
       case IGL_FRAMEBUFFER_PIXEL:
       {
          pGLExec->iglReadPixels(x,y,res);
       }break;

       default:
       {
          qWarning() << "Função com parametro IGL_FRAMEBUFFER_PIXEL , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL   (int iOglFcn, GLuint        &IGL_TextureId     ,
                                   GLubyte       *IGL_TextureData   ,
                                   GLuint         IGL_TextureWidth  ,
                                   GLuint         IGL_TextureHeight ,
                                   GLuint         IGL_TextureFormat ,
                                   GLuint         IGL_TextureMipmaps)
{
    switch(iOglFcn)
    {
       case IGL_TEXTURE_CREATE:
       {
          pGLExec->iglCreateTexture(IGL_TextureId     ,
                                    IGL_TextureData   ,
                                    IGL_TextureWidth  ,
                                    IGL_TextureHeight ,
                                    IGL_TextureFormat ,
                                    IGL_TextureMipmaps);
       }break;

       default:
       {
          qWarning() << "Função com parametro IGL_TEXTURE_CREATE , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL   (int iOglFcn, GLuint        &IGL_TextureId     ,
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
    switch(iOglFcn)
    {
       case IGL_TEXTURE_CREATE:
       {
          pGLExec->iglCreateCubeMap(IGL_TextureId     ,
                                    IGL_TextureRight  ,
                                    IGL_TextureLeft   ,
                                    IGL_TextureTop    ,
                                    IGL_TextureBottom ,
                                    IGL_TextureBack   ,
                                    IGL_TextureFront  ,
                                    IGL_TextureWidth  ,
                                    IGL_TextureHeight ,
                                    IGL_TextureFormat ,
                                    IGL_TextureMipmaps);
       }break;

       default:
       {
          qWarning() << "Função com parametro IGL_TEXTURE_CREATE , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::execGL   (int iOglFcn, GLuint         IGL_TextureId     ,
                                   GLuint         IGL_TextureMode   ,
                                   GLboolean      IGL_TextureUpdate ,
                                   GLubyte       *IGL_TextureData   ,
                                   GLuint         IGL_TextureWidth  ,
                                   GLuint         IGL_TextureHeight ,
                                   GLuint         IGL_TextureFormat )
{
    switch(iOglFcn)
    {
       case IGL_TEXTURE_PREP:
       {
          pGLExec->iglPreparaTextura(IGL_TextureId    ,
                                     IGL_TextureMode  ,
                                     IGL_TextureUpdate,
                                     IGL_TextureData  ,
                                     IGL_TextureWidth ,
                                     IGL_TextureHeight,
                                     IGL_TextureFormat);
       }break;

       default:
       {
          qWarning() << "Função com parametro IGL_TEXTURE_PREP , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::CalculaPVMMatrix(CIMTMatriz pIGLModelMatrix, CIMTMatriz &pIGLPVMMatrix, bool bReset)
{
    if(bReset)
    {
        return pGLExec->iglCalculaPVMMatrix(pIGLModelMatrix,pIGLPVMMatrix);
    }
    else
    {
        return pGLExec->iglPegaPVMMatrix(pIGLPVMMatrix);
    }
    return false;//apenas para o compilador não reclamar...
}

int INSGL::PegaVersao()
{
    return pGLExec->iglGetVersion();
}

bool INSGL::FenceSync(GLsync &pIGL_Sync)
{
   return pGLExec->iglFenceSync(pIGL_Sync);
}

bool INSGL::WaitSync(GLsync  pIGL_Sync)
{
   return pGLExec->iglWaitSync(pIGL_Sync);
}

bool INSGL::AddTransformFeedback(GLuint ProgramId)
{
    pGLExec->iglTransformFeedback(ProgramId);
    return true;
}

bool INSGL::TransformBuffer(GLuint           IGL_ProgramId   ,
                            GLuint           IGL_VboId       ,
                            GLuint           IGL_QtdVert     ,
                            CIMTMatriz       IGL_ModelMatrix ,
                            IGLVertexBuffer *IGL_VertexBuffer)
{
    pGLExec->iglTransformBuffer(IGL_ProgramId      ,
                                IGL_VboId          ,
                                IGL_QtdVert        ,
                                IGL_ModelMatrix    ,
                                IGL_VertexBuffer   );
    return true;
}

IGLVertexBuffer * INSGL::MapBuffer(GLuint           IGL_ProgramId   ,
                                   GLuint           IGL_VboId       )
{
    return pGLExec->iglMapBuffer(IGL_ProgramId      ,
                                 IGL_VboId          );
}

bool INSGL::UnMapBuffer(GLuint           IGL_ProgramId   ,
                        GLuint           IGL_VboId       ,
                        IGLVertexBuffer *IGL_VertexBuffer)
{
    pGLExec->iglUnMapBuffer(IGL_ProgramId      ,
                            IGL_VboId          ,
                            IGL_VertexBuffer   );
    return true;
}

QString INSGL::PegaVendor()
{
   return QString(pGLExec->iglGetString(GL_VENDOR));
}
