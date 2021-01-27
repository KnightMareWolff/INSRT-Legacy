/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_GlobalDef.h"
#include "I3D_Textura.h"
#include "I3D_TextureManager.h"

extern CI3DTextureManager * pI3DTextureManager;

CI3DTextura::CI3DTextura()
{
   I3D_Altura=I3D_Largura=0;
   I3D_IdT = -1;

   //Será substituido por define especifico de canal de textura
   I3D_Layers[0]=0;
   I3D_Layers[1]=1;
   I3D_Layers[2]=2;
   I3D_Layers[3]=3;
}

CI3DTextura::~CI3DTextura()
{
    //Como agora as texturas estão indexadas atraves de alocação de base unica a destruição da textura
    //Na placa de vídeo será realizada pelo Pool de texturas.
    //execGL(IGL_PF_DELTEXTURE,1,&IdT);
}

void CI3DTextura::RemoveTextura()
{
    execGL(IGL_PF_DELTEXTURE,1,&I3D_IdT);

    I3D_Altura=I3D_Largura=0;

    I3D_IdT = -1;
}

void CI3DTextura::CriaTextura(QString pI3D_NomeTextura)
{
    execGL(IGL_PF_ENABLE,GL_TEXTURE_2D);

    I3D_NomeTextura   = pI3D_NomeTextura;
    I3D_Imagem        = QImage(I3D_NomeTextura);
    I3D_Textura       = new QOpenGLTexture(I3D_Imagem);
    I3D_Altura        = I3D_Textura->height();
    I3D_Largura       = I3D_Textura->width();
    I3D_Formato       = I3D_Textura->format();
    I3D_IdT           = I3D_Textura->textureId();
}

void CI3DTextura::AddLayer(int pI3D_IdLayer, int pI3D_CanalLayer)
{
    I3D_Layers[pI3D_CanalLayer] = pI3D_IdLayer;
}

void CI3DTextura::Prepara(int pI3D_TextureMode)
{
    if(SuportaShader())
    {
        PreparaTexturaSH(pI3D_TextureMode);
    }
    else
    {
        PreparaTexturaPF(pI3D_TextureMode);
    }
}

void CI3DTextura::SetaWrapMode(int pI3D_TextureMode)
{
    switch(pI3D_TextureMode)
    {
       case IGL_TEXTURE_CLAMP:
       {
           I3D_Textura->setMinificationFilter (QOpenGLTexture::Linear);
           I3D_Textura->setMagnificationFilter(QOpenGLTexture::Linear);
           I3D_Textura->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::ClampToEdge);
           I3D_Textura->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::ClampToEdge);
       }break;
       case IGL_TEXTURE_LINEAR:
       {
           I3D_Textura->setMinificationFilter (QOpenGLTexture::Linear);
           I3D_Textura->setMagnificationFilter(QOpenGLTexture::Linear);
       }break;
       case IGL_TEXTURE_GEN_ST:
       {
           I3D_Textura->setMagnificationFilter(QOpenGLTexture::Linear);
           I3D_Textura->setMinificationFilter (QOpenGLTexture::Linear);
           I3D_Textura->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
           I3D_Textura->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);
           if(!SuportaShader())
           {
              GLfloat s_vector[4] = { 1.0f/(GLfloat)I3D_Altura, 0 , 0               , 0 };
              GLfloat t_vector[4] = { 0              , 0 , 1.0f/(GLfloat)I3D_Largura, 0 };

              execGL(IGL_PF_AUTOTEXTURE,s_vector,t_vector);
           }
       }break;
       default:
       {
          qWarning() << "Atenção! Modo de Preparação de textura inexistente!.";
       }break;
    }
}

void CI3DTextura::PreparaTexturaPF(int pTextMode)
{
    execGL(IGL_PF_ENABLE,GL_TEXTURE_2D);

    if(pTextMode==IGL_TEXTURE_GEN_ST)
    {
        execGL(IGL_PF_ENABLE,IGL_PF_ENABLE_ST);
    }
    else
    {
        execGL(IGL_PF_DISABLE,IGL_PF_DISABLE_ST);
    }
    /*
    if(I3D_Layers.size()==0)
    {
        execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE0);
        I3D_Textura->bind();
        SetaWrapMode(pTextMode);
    }
    else
    {
    */
        execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE0);
        Bind();
        SetaWrapMode(pTextMode);

        for(int iLayer=0 ; iLayer < 4 ; iLayer++)
        {
            switch(iLayer)
            {
               case 0:
               {
                   execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE1);
                   pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                   pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
               }break;
               case 1:
               {
                   execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE2);
                   pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                   pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
               }break;
               case 2:
               {
                   execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE3);
                   pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                   pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
               }break;
               case 3:
               {
                   execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE4);
                   pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                   pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
               }break;
               default:
               {
                  qWarning() << "Atenção! Numero de Layers em Textura excedido!.";
               }break;
            }
        }
    /*
    }
    */
}

void CI3DTextura::PreparaTexturaSH(int pTextMode)
{
    execGL(IGL_PF_ENABLE,GL_TEXTURE_2D);

    /*
    if(mLayers.size()==0)
    {
       //Seta Multitextura como falso
       execGL(IGL_SH_UNIINT,"multitextura",0);
       execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE0);

       Textura->bind();

       execGL(IGL_SH_UNIINT,"textura_base",0);
       SetaWrapMode(pTextMode);
    }
    else
    {
    */
        execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE0);

        Bind();

        //Seta Multitextura como verdadeiro
        execGL(IGL_SH_UNIINT,"multitextura",1);
        execGL(IGL_SH_UNIINT,"textura_base",0);

        SetaWrapMode(pTextMode);

        for(int iLayer=0 ;iLayer < 4; iLayer++)
        {
            switch(iLayer)
            {
               case 0:
               {
                   execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE1);
                   execGL(IGL_SH_UNIINT,"textura_detalhe",1);
                   pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                   pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
               }break;
               case 1:
               {
                  execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE2);
                  execGL(IGL_SH_UNIINT,"textura_normal_map",2);
                  pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                  pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
               }break;
               case 2:
               {
                  execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE3);
                  execGL(IGL_SH_UNIINT,"textura_cube_map",3);
                  pI3DTextureManager->Bind(I3D_Layers[iLayer]);
                  pI3DTextureManager->SetaWrapMode(I3D_Layers[iLayer],pTextMode);
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
    /*
    }
    */
}

void CI3DTextura::Bind()
{
    I3D_Textura->bind();
}
