/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMA_GlobalDef.h"
#include "IMA_Textura.h"
#include "IMA_TextureManager.h"
#include "INSMA.h"


CIMATextura::CIMATextura()
{
   I3D_Altura=I3D_Largura=0;
   I3D_IdT = -1;

   //Será substituido por define especifico de canal de textura
   I3D_Layers[0]=0;
   I3D_Layers[1]=1;
   I3D_Layers[2]=2;
   I3D_Layers[3]=3;

   IMA_Video       = NULL;
   IMA_TextureMode = IGL_TEXTURE_LINEAR;
}

CIMATextura::~CIMATextura()
{
    //Como agora as texturas estão indexadas atraves de alocação de base unica a destruição da textura
    //Na placa de vídeo será realizada pelo Pool de texturas.
    //execGL(IGL_PF_DELTEXTURE,1,&IdT);
}

void CIMATextura::RemoveTextura()
{
    execGL(IGL_SH_DELTEXTURE,1,&I3D_IdT);

    I3D_Altura=I3D_Largura=0;

    I3D_IdT = -1;

    if(IMA_Video)IMA_Video=NULL;
}

void CIMATextura::CriaTextura(QString pIMA_NomeTextura, int pIMA_TextureMode)
{

    IMA_TextureMode = pIMA_TextureMode;

    //Para Estados que não precisam de programid envia 0
    execGL(IGL_SH_ENABLE,0,GL_TEXTURE_2D);

    I3D_NomeTextura   = pIMA_NomeTextura;

    I3D_Imagem = imread(I3D_NomeTextura.toStdString(),CV_LOAD_IMAGE_COLOR);

    //flip(I3D_Imagem,I3D_Imagem,0);
    //cvtColor(I3D_Imagem,I3D_Imagem,CV_8UC3);

    I3D_Altura    = I3D_Imagem.rows;
    I3D_Largura   = I3D_Imagem.cols;
    I3D_Formato   = GL_RGB;

    execGL(IGL_TEXTURE_CREATE,I3D_IdT,I3D_Imagem.ptr(),I3D_Altura,I3D_Largura,I3D_Formato,1);
}

void CIMATextura::CriaCubeMap(QString      pIMA_NomeRight                         ,
                              QString      pIMA_NomeLeft                          ,
                              QString      pIMA_NomeTop                           ,
                              QString      pIMA_NomeBottom                        ,
                              QString      pIMA_NomeBack                          ,
                              QString      pIMA_NomeFront)
{

    IMA_TextureMode = IGL_TEXTURE_CUBEMAP;

    //Envia zero para estado que nao precisa de program ID
    execGL(IGL_SH_ENABLE,0,GL_TEXTURE_CUBE_MAP);

    //NOME PARA IDENTIFICAÇÃO DO CUBEMAP(Atenção leva em conta so o primeiro!)
    I3D_NomeTextura   = pIMA_NomeRight;

    I3D_ImagemRight  = imread(pIMA_NomeRight.toStdString() ,CV_LOAD_IMAGE_COLOR);
    I3D_ImagemLeft   = imread(pIMA_NomeLeft.toStdString()  ,CV_LOAD_IMAGE_COLOR);
    I3D_ImagemTop    = imread(pIMA_NomeTop.toStdString()   ,CV_LOAD_IMAGE_COLOR);
    I3D_ImagemBottom = imread(pIMA_NomeBottom.toStdString(),CV_LOAD_IMAGE_COLOR);
    I3D_ImagemBack   = imread(pIMA_NomeBack.toStdString()  ,CV_LOAD_IMAGE_COLOR);
    I3D_ImagemFront  = imread(pIMA_NomeFront.toStdString() ,CV_LOAD_IMAGE_COLOR);

    //flip(I3D_Imagem,I3D_Imagem,0);
    //cvtColor(I3D_Imagem,I3D_Imagem,CV_8UC3);

    I3D_Altura    = I3D_ImagemRight.rows;
    I3D_Largura   = I3D_ImagemRight.cols;
    I3D_Formato   = GL_RGB;

    execGL(IGL_TEXTURE_CREATE,I3D_IdT               ,
                              I3D_ImagemRight.ptr() ,
                              I3D_ImagemLeft.ptr()  ,
                              I3D_ImagemTop.ptr()   ,
                              I3D_ImagemBottom.ptr(),
                              I3D_ImagemBack.ptr()  ,
                              I3D_ImagemFront.ptr() ,
                              I3D_Altura            ,
                              I3D_Largura           ,
                              I3D_Formato           ,
                              1                     );
}

void CIMATextura::AddLayer(int pI3D_IdLayer, int pI3D_CanalLayer)
{
    I3D_Layers[pI3D_CanalLayer] = pI3D_IdLayer;
}

void CIMATextura::Prepara(int pIMA_ProgramId)
{
    unsigned int tOpenGLId,tAltura,tLargura,tFormato;

    //Seta Multitextura como verdadeiro
    execGL(IGL_SH_UNIINT,pIMA_ProgramId,"multitextura",1);

    execGL(IGL_SH_ENABLE       ,pIMA_ProgramId,GL_TEXTURE_2D);
    execGL(IGL_SH_ACTIVETEXTURE,pIMA_ProgramId,GL_TEXTURE0);
    execGL(IGL_SH_UNIINT       ,pIMA_ProgramId,"textura_base",0);

    //Caso seja um Render to Texture prepara a textura atualizando a imagem
    if(IMA_TextureMode==IGL_TEXTURE_RENDER)
    {
        if(IMA_Video->PegaStatus() != IMD_VIDEO_STATUS_FINISH)
        {
           IMA_Video->PegaPropriedades(tAltura  ,
                                       tLargura ,
                                       tFormato );

           execGL(IGL_TEXTURE_PREP,I3D_IdT,IGL_TEXTURE_LINEAR,true ,IMA_Video->PegaFrame(),tAltura,tLargura,tFormato);
        }
        else
        {
           execGL(IGL_TEXTURE_PREP,I3D_IdT,IMA_TextureMode,false,NULL,0,0,I3D_Formato);
        }
    }
    else
    {
        //Prepara a textura normal sem atualizar a imagem
        execGL(IGL_TEXTURE_PREP,I3D_IdT,IMA_TextureMode,false,NULL,0,0,I3D_Formato);
    }

    //processa os Layers da textura
    for(int iLayer=0 ;iLayer < 4; iLayer++)
    {
        switch(iLayer)
        {
           case 0:
           {
               execGL(IGL_SH_ENABLE       ,pIMA_ProgramId,GL_TEXTURE_2D);
               execGL(IGL_SH_ACTIVETEXTURE,pIMA_ProgramId,GL_TEXTURE1);
               execGL(IGL_SH_UNIINT       ,pIMA_ProgramId,"textura_detalhe",1);

               INSMA::pINSMATextureManager->PegaPropriedades(I3D_Layers[iLayer],
                                                             tOpenGLId         ,
                                                             tAltura           ,
                                                             tLargura          ,
                                                             tFormato);

               execGL(IGL_TEXTURE_PREP,tOpenGLId,IMA_TextureMode,false,NULL,0,0,tFormato);

           }break;
           case 1:
           {
               execGL(IGL_SH_ENABLE       ,pIMA_ProgramId,GL_TEXTURE_2D);
               execGL(IGL_SH_ACTIVETEXTURE,pIMA_ProgramId,GL_TEXTURE2);
               execGL(IGL_SH_UNIINT       ,pIMA_ProgramId,"textura_normal_map",2);

               INSMA::pINSMATextureManager->PegaPropriedades(I3D_Layers[iLayer],
                                                             tOpenGLId         ,
                                                             tAltura           ,
                                                             tLargura          ,
                                                             tFormato          );

               execGL(IGL_TEXTURE_PREP,tOpenGLId,IMA_TextureMode,false,NULL,0,0,tFormato);
           }break;
           case 2:
           {
               execGL(IGL_SH_ENABLE       ,pIMA_ProgramId,GL_TEXTURE_CUBE_MAP);
               execGL(IGL_SH_ACTIVETEXTURE,pIMA_ProgramId,GL_TEXTURE3);
               execGL(IGL_SH_UNIINT       ,pIMA_ProgramId,"textura_cube_map",3);

               INSMA::pINSMATextureManager->PegaPropriedades(I3D_Layers[iLayer],
                                                             tOpenGLId         ,
                                                             tAltura           ,
                                                             tLargura          ,
                                                             tFormato          );
               execGL(IGL_TEXTURE_PREP,tOpenGLId,IMA_TextureMode,false,NULL,0,0,tFormato);
           }break;
           case 3:
           {
               //execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE4);
               //execGL(IGL_SH_UNIINT,"textura_cube_map",3);
               //pI3DTextureManager->Bind(I3D_Layers[iLayer]);
               //pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
            }break;
            default:
            {
               qWarning() << "Atenção! Numero de Layers em Textura excedido!.";
            }break;
         }
     }
}


int CIMATextura::PegaLayerTextura(int pIMA_CanalLayer)
{
    return I3D_Layers[pIMA_CanalLayer];
}

void CIMATextura::RenderToTexture(CIMDVideo *pIMA_Video)
{
    IMA_Video      = pIMA_Video;
    IMA_TextureMode= IGL_TEXTURE_RENDER;
}
