/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMA_GlobalDef.h"
#include "IMA_Material.h"
#include "IMA_TextureManager.h"
#include "INSMA.h"

/************************************************************/
/************************************************************/
CIMAMaterial::CIMAMaterial( )
{
    IMA_Opacy        = 1.0f ;
    IMA_Shininess    = 5.0f ;
    IMA_Reflection   = 0.1f;
    IMA_Refraction   = 0.94f;
    IMA_PixelReject  = false;

    IMA_NomeMaterial = QString("Material Default");

    IMA_MaterialMode = IGL_MATERIAL_COLOR;

    //Laranjado Porreta!!!!
    //CorAmbiente  = CIMACor(0.9f  , 0.5f  , 0.3f  , 1.0f);
    //CorDifusa    = CIMACor(0.9f  , 0.5f  , 0.3f  , 1.0f);
    //CorSpecular  = CIMACor(0.8f  , 0.8f  , 0.8f  , 1.0f);
    //CorEmissiva  = CIMACor(0.0f  , 0.0f  , 1.0f  , 1.0f);
    //AlphaColor   = CIMACor(0.0f  , 0.0f  , 0.0f  , 1.0f);

    //Luz Branca
    IMA_CorAmbiente  = CIMACor(0.0f  , 0.0f  , 0.0f  , 1.0f);
    IMA_CorDifusa    = CIMACor(0.3f  , 0.3f  , 0.3f  , 1.0f);
    IMA_CorSpecular  = CIMACor(0.5f  , 0.5f  , 0.5f  , 1.0f);
    IMA_CorEmissiva  = CIMACor(0.0f  , 0.0f  , 1.0f  , 1.0f);
    IMA_AlphaColor   = CIMACor(0.0f  , 0.0f  , 0.0f  , 1.0f);

}

CIMAMaterial::CIMAMaterial( const CIMAMaterial & material )
{
    IMA_Shininess    = material.IMA_Shininess;
    IMA_CorAmbiente  = material.IMA_CorAmbiente;
    IMA_CorDifusa    = material.IMA_CorDifusa;
    IMA_CorEmissiva  = material.IMA_CorEmissiva;
    IMA_CorSpecular  = material.IMA_CorSpecular;
    IMA_AlphaColor   = material.IMA_AlphaColor;
    IMA_NomeMaterial = material.IMA_NomeMaterial;
    IMA_Opacy        = material.IMA_Opacy;
    IMA_Reflection   = material.IMA_Reflection;
    IMA_Refraction   = material.IMA_Refraction;
    IMA_PixelReject  = material.IMA_PixelReject;

}

/************************************************************/
/************************************************************/
QString  CIMAMaterial::PegaNomeMaterial()
{

    return IMA_NomeMaterial ;

}

/************************************************************/
/************************************************************/
CIMACor CIMAMaterial::PegaCorDifusa()
{

    return IMA_CorDifusa ;

}
/************************************************************/
/************************************************************/
CIMACor CIMAMaterial::PegaCorAmbiente()
{

    return IMA_CorAmbiente ;

}
/************************************************************/
/************************************************************/
CIMACor CIMAMaterial::PegaCorEmissiva()
{

    return IMA_CorEmissiva ;

}
/************************************************************/
/************************************************************/
CIMACor CIMAMaterial::PegaCorSpecular()
{
    return IMA_CorSpecular ;
}

/************************************************************/
/************************************************************/
CIMACor CIMAMaterial::PegaCorAlpha()
{
    return IMA_AlphaColor;
}
/************************************************************/
/************************************************************/
void    CIMAMaterial::SetaNomeMaterial(QString pi3dNomeMaterial)
{

   IMA_NomeMaterial = pi3dNomeMaterial;

}

int CIMAMaterial::AddVetorTextura(QString pI3D_NomeTextura,int pIMA_TextureMode)
{
    int Indice = INSMA::pINSMATextureManager->AddTextura(pI3D_NomeTextura,pIMA_TextureMode);

    IMA_Texturas.push_back(Indice);

    return Indice;
}

int CIMAMaterial::AddCubeMap(QString pI3D_NomeTexturaRight,
                             QString pI3D_NomeTexturaLeft,
                             QString pI3D_NomeTexturaTop,
                             QString pI3D_NomeTexturaBottom,
                             QString pI3D_NomeTexturaBack,
                             QString pI3D_NomeTexturaFront)
{
    int Indice = INSMA::pINSMATextureManager->AddCubeMap(pI3D_NomeTexturaRight,
                                                         pI3D_NomeTexturaLeft,
                                                         pI3D_NomeTexturaTop,
                                                         pI3D_NomeTexturaBottom,
                                                         pI3D_NomeTexturaBack,
                                                         pI3D_NomeTexturaFront);

    if(IMA_Texturas.size()==0)
    {
        IMA_Texturas.push_back(Indice);
        INSMA::pINSMATextureManager->AddLayerTextura(Indice,Indice,IMA_LAYER_CHN_CBMAP);
    }
    else
    {
        INSMA::pINSMATextureManager->AddLayerTextura(IMA_Texturas[0],Indice,IMA_LAYER_CHN_CBMAP);
    }

    return Indice;
}

void CIMAMaterial::AddLayerTextura(QString pI3D_NomeTextura, QString pI3D_NomeLayer, int pI3D_CanalTextura)
{
   INSMA::pINSMATextureManager->AddLayerTextura(pI3D_NomeTextura,pI3D_NomeLayer,pI3D_CanalTextura);
}

void CIMAMaterial::AddLayerTextura(int pI3D_IdTextura, QString pI3D_NomeLayer, int pI3D_CanalTextura)
{
   INSMA::pINSMATextureManager->AddLayerTextura(pI3D_IdTextura,pI3D_NomeLayer,pI3D_CanalTextura);
}
/************************************************************/
/************************************************************/
void    CIMAMaterial::SetaCorDifusa   (CIMACor i3dCorDifusa  )
{

   IMA_CorDifusa = i3dCorDifusa;

}

/************************************************************/
/************************************************************/
void    CIMAMaterial::SetaCorAmbiente (CIMACor i3dCorAmbiente)
{

    IMA_CorAmbiente =  i3dCorAmbiente ;

}

/************************************************************/
/************************************************************/
void    CIMAMaterial::SetaCorEmissiva (CIMACor i3dCorEmissiva)
{

    IMA_CorEmissiva = i3dCorEmissiva ;


}
/************************************************************/
/************************************************************/
void CIMAMaterial::SetaCorSpecular (CIMACor i3dCorSpecular)
{
    IMA_CorSpecular  = i3dCorSpecular ;
}

/************************************************************/
/************************************************************/
void CIMAMaterial::SetaOpacidade(float opac)
{
    IMA_Opacy=opac;
}

void CIMAMaterial::SetaPotencia(float i3dPotencia)
{
    IMA_Shininess=i3dPotencia;
}

void CIMAMaterial::SetaRejeicaoCor(bool bRejeita,CIMACor CorAlpha)
{
    IMA_PixelReject = bRejeita;

    //caso seja para rejeitar altera para a cor enviada
    //caso contrario permanece o que estava.
    if(bRejeita)
    {
       IMA_AlphaColor = CIMACor(CorAlpha.PegaCorR(),
                                CorAlpha.PegaCorG(),
                                CorAlpha.PegaCorB(),
                                CorAlpha.PegaCorA());
    }
}

void CIMAMaterial::SetaMaterialMode(int pIMA_MaterialMode)
{
    IMA_MaterialMode = pIMA_MaterialMode;
}


void CIMAMaterial::SetaReflexao(float i3dReflexao)
{
    IMA_Reflection=i3dReflexao;
}


/************************************************************/
/************************************************************/
float CIMAMaterial::PegaOpacidade()
{
    return IMA_Opacy;
}

/************************************************************/
/************************************************************/
int CIMAMaterial::PegaQtdTexturas()
{
    return (int)IMA_Texturas.size();
}
/**************************************/
/*operador de atribuicao              */
/**************************************/
CIMAMaterial &CIMAMaterial::operator=(const CIMAMaterial& opr)
{
    IMA_Shininess    = opr.IMA_Shininess;
    IMA_CorAmbiente  = opr.IMA_CorAmbiente;
    IMA_CorDifusa    = opr.IMA_CorDifusa;
    IMA_CorEmissiva  = opr.IMA_CorEmissiva;
    IMA_CorSpecular  = opr.IMA_CorSpecular;
    IMA_AlphaColor   = opr.IMA_AlphaColor;
    IMA_NomeMaterial = opr.IMA_NomeMaterial;
    IMA_PixelReject  = opr.IMA_PixelReject;
    IMA_Opacy        = opr.IMA_Opacy;
    IMA_Reflection   = opr.IMA_Reflection;
    IMA_Refraction   = opr.IMA_Refraction;

    return (*this);
}

void CIMAMaterial::Prepara(int pIMA_ProgramId)
{
    if(IMA_MaterialMode == IGL_MATERIAL_REFLEXIVE)SetaReflexao(0.85f);
    if(IMA_MaterialMode == IGL_MATERIAL_REFRATIVE)SetaReflexao(0.1f);

    execGL(IGL_SH_MATERIAL,pIMA_ProgramId,
                           CIMTVetor4(IMA_CorDifusa  .PegaCorRGBA()[0],
                                      IMA_CorDifusa  .PegaCorRGBA()[1],
                                      IMA_CorDifusa  .PegaCorRGBA()[2],
                                      IMA_CorDifusa  .PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_CorAmbiente.PegaCorRGBA()[0],
                                      IMA_CorAmbiente.PegaCorRGBA()[1],
                                      IMA_CorAmbiente.PegaCorRGBA()[2],
                                      IMA_CorAmbiente.PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_CorEmissiva.PegaCorRGBA()[0],
                                      IMA_CorEmissiva.PegaCorRGBA()[1],
                                      IMA_CorEmissiva.PegaCorRGBA()[2],
                                      IMA_CorEmissiva.PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_CorSpecular.PegaCorRGBA()[0],
                                      IMA_CorSpecular.PegaCorRGBA()[1],
                                      IMA_CorSpecular.PegaCorRGBA()[2],
                                      IMA_CorSpecular.PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_AlphaColor .PegaCorRGBA()[0],
                                      IMA_AlphaColor .PegaCorRGBA()[1],
                                      IMA_AlphaColor .PegaCorRGBA()[2],
                                      IMA_AlphaColor .PegaCorRGBA()[3]),
                                      IMA_PixelReject,
                                      IMA_Opacy    ,
                                      IMA_Shininess,
                                      IMA_Reflection     ,
                                      IMA_Refraction);

    switch(IMA_MaterialMode)
    {
       case IGL_MATERIAL_COLOR:
       {
           //habilita para considerar apenas as cores e iluminação.
           execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
       }break;
       case IGL_MATERIAL_TEXTURE:
       {
           if(IMA_Texturas.size()>0)
           {
               //realiza o shift de apenas cores para considerar textura
               execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_TEXTURE);
               //Prepara a textura para a renderização
               INSMA::pINSMATextureManager->Prepara(IMA_Texturas[0],pIMA_ProgramId);
           }
           else
           {
               //habilita para considerar apenas as cores e iluminação.
               //Obs:. Desabilitando Material Texture muda para IGL_MATERIAL_COLOR , portanto
               //Não há diferença entre desativar Material Texture ou Ativar Material Color
               //Podemos ver isto no Material Mixed como exemplo.
               execGL(IGL_SH_DISABLE,pIMA_ProgramId,IGL_MATERIAL_TEXTURE);
           }
       }break;
       case IGL_MATERIAL_MIXED:
       {
           if(IMA_Texturas.size()>0)
           {
               //realiza o shift de apenas cores para considerar textura
               execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_MIXED);
               //Prepara a textura para a renderização
               INSMA::pINSMATextureManager->Prepara(IMA_Texturas[0],pIMA_ProgramId);
           }
           else
           {
               //habilita para considerar apenas as cores e iluminação.
               execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
           }
       }break;
       case IGL_MATERIAL_NORMALMAP:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_NORMALMAP);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[0],pIMA_ProgramId);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
       case IGL_MATERIAL_REFLEXIVE:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_REFLEXIVE);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[0],pIMA_ProgramId);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
       case IGL_MATERIAL_REFRATIVE:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_REFRATIVE);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[0],pIMA_ProgramId);
              //Prepara os Canais de Layers para a renderização
              //int IndiceLayer0 = INSMA::pINSMATextureManager->PegaLayerTextura(IMA_Texturas[0],0);

          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
       case IGL_MATERIAL_CUBEMAP:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_CUBEMAP);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[0],pIMA_ProgramId);
              //Prepara os Canais de Layers para a renderização
              //int IndiceLayer0 = INSMA::pINSMATextureManager->PegaLayerTextura(IMA_Texturas[0],0);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
    }
}

void CIMAMaterial::Prepara(int pIMA_ProgramId, int pIMA_IdTextura)
{
    execGL(IGL_SH_MATERIAL,pIMA_ProgramId,
                           CIMTVetor4(IMA_CorDifusa  .PegaCorRGBA()[0],
                                      IMA_CorDifusa  .PegaCorRGBA()[1],
                                      IMA_CorDifusa  .PegaCorRGBA()[2],
                                      IMA_CorDifusa  .PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_CorAmbiente.PegaCorRGBA()[0],
                                      IMA_CorAmbiente.PegaCorRGBA()[1],
                                      IMA_CorAmbiente.PegaCorRGBA()[2],
                                      IMA_CorAmbiente.PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_CorEmissiva.PegaCorRGBA()[0],
                                      IMA_CorEmissiva.PegaCorRGBA()[1],
                                      IMA_CorEmissiva.PegaCorRGBA()[2],
                                      IMA_CorEmissiva.PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_CorSpecular.PegaCorRGBA()[0],
                                      IMA_CorSpecular.PegaCorRGBA()[1],
                                      IMA_CorSpecular.PegaCorRGBA()[2],
                                      IMA_CorSpecular.PegaCorRGBA()[3]),
                           CIMTVetor4(IMA_AlphaColor .PegaCorRGBA()[0],
                                      IMA_AlphaColor .PegaCorRGBA()[1],
                                      IMA_AlphaColor .PegaCorRGBA()[2],
                                      IMA_AlphaColor .PegaCorRGBA()[3]),
                                      IMA_PixelReject,
                                      IMA_Opacy    ,
                                      IMA_Shininess,
                                      IMA_Reflection     ,
                                      IMA_Refraction);

    switch(IMA_MaterialMode)
    {
       case IGL_MATERIAL_COLOR:
       {
           //habilita para considerar apenas as cores e iluminação.
           execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
       }break;
       case IGL_MATERIAL_TEXTURE:
       {
           if(IMA_Texturas.size()>0)
           {
               //realiza o shift de apenas cores para considerar textura
               execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_TEXTURE);
               //Prepara a textura para a renderização
               INSMA::pINSMATextureManager->Prepara(IMA_Texturas[pIMA_IdTextura],pIMA_ProgramId);
           }
           else
           {
               //habilita para considerar apenas as cores e iluminação.
               execGL(IGL_SH_DISABLE,pIMA_ProgramId,IGL_MATERIAL_TEXTURE);
           }
       }break;
       case IGL_MATERIAL_MIXED:
       {
           if(IMA_Texturas.size()>0)
           {
               //realiza o shift de apenas cores para considerar textura
               execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_MIXED);
               //Prepara a textura para a renderização
               INSMA::pINSMATextureManager->Prepara(IMA_Texturas[pIMA_IdTextura],pIMA_ProgramId);
           }
           else
           {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_DISABLE,pIMA_ProgramId,IGL_MATERIAL_TEXTURE);
           }
       }break;
       case IGL_MATERIAL_NORMALMAP:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_NORMALMAP);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[pIMA_IdTextura],pIMA_ProgramId);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
       case IGL_MATERIAL_REFLEXIVE:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_REFLEXIVE);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[pIMA_IdTextura],pIMA_ProgramId);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
       case IGL_MATERIAL_REFRATIVE:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_REFRATIVE);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[pIMA_IdTextura],pIMA_ProgramId);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
       case IGL_MATERIAL_CUBEMAP:
       {
          if(IMA_Texturas.size()>0)
          {
              //realiza o shift de apenas cores para considerar textura
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_CUBEMAP);
              //Prepara a textura para a renderização
              INSMA::pINSMATextureManager->Prepara(IMA_Texturas[pIMA_IdTextura],pIMA_ProgramId);
          }
          else
          {
              //habilita para considerar apenas as cores e iluminação.
              execGL(IGL_SH_ENABLE,pIMA_ProgramId,IGL_MATERIAL_COLOR);
          }
       }break;
    }
}

void CIMAMaterial::RenderToTexture(CIMDVideo *pIMA_Video)
{
    if(IMA_Texturas.size()>0)
    {
       //Seta o Video para RenderToTexture
       INSMA::pINSMATextureManager->RenderToTexture(IMA_Texturas[0],pIMA_Video);
    }
}
