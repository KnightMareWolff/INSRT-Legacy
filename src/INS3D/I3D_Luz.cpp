/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_GlobalDef.h"
#include "I3D_Luz.h"


/************************************************************/
/************************************************************/
CI3DLuz::CI3DLuz( )
{
    tipo = LIGHTTYPE_POINT;
    canal= IGL_LIGHT_CHANNEL_01;

    pos  = CIMTVetor4(0.0f, 0.0f,  0.0f ,1.0f);
    dir  = CIMTVetor4(0.0f, 0.0f, -1.0f ,1.0f);

    I3D_CorAmbiente = CIMACor(0.4f, 0.4f, 0.4f, 1.0f);
    I3D_CorDifusa   = CIMACor(0.0f, 0.0f, 0.0f, 1.0f);
    I3D_CorSpecular = CIMACor(0.0f, 0.0f, 0.0f, 1.0f);

    AtenuacaoConstante   = 0.5f;
    AtenuacaoLinear      = 0.001f;
    AtenuacaoQuadratica  = 0.0001f;

    Expoente = 0.5f;
    CutOff   = 180.0f;
}

/************************************************************/
/************************************************************/
CIMACor CI3DLuz::PegaCorDifusa()
{
    return I3D_CorDifusa ;
}
/************************************************************/
/************************************************************/
CIMACor CI3DLuz::PegaCorAmbiente()
{
    return I3D_CorAmbiente ;
}

/************************************************************/
/************************************************************/
CIMACor CI3DLuz::PegaCorSpecular()
{
    return I3D_CorSpecular ;
}

/************************************************************/
/************************************************************/
float CI3DLuz::PegaAttConstante()
{
    return AtenuacaoConstante;
}

/************************************************************/
/************************************************************/
float CI3DLuz::PegaAttLinear()
{
    return AtenuacaoLinear;
}

/************************************************************/
/************************************************************/
float CI3DLuz::PegaAttQuadratica()
{
    return AtenuacaoQuadratica;
}

/************************************************************/
/************************************************************/
CIMTVetor CI3DLuz::PegaDir()
{
    return CIMTVetor(dir.x,dir.y,dir.z);
}

/************************************************************/
/************************************************************/
CIMTVetor CI3DLuz::PegaPos()
{
    return CIMTVetor(pos.x,pos.y,pos.z);
}

/************************************************************/
/************************************************************/
void    CI3DLuz::SetaCorDifusa   (CIMACor i3dCorDifusa  )
{
   I3D_CorDifusa = i3dCorDifusa;
}
/************************************************************/
/************************************************************/
void    CI3DLuz::SetaCorAmbiente (CIMACor i3dCorAmbiente)
{
    I3D_CorAmbiente =  i3dCorAmbiente ;
}

/************************************************************/
/************************************************************/
void CI3DLuz::SetaCorSpecular (CIMACor i3dCorSpecular)
{
    I3D_CorSpecular  = i3dCorSpecular ;
}

/************************************************************/
/************************************************************/
void CI3DLuz::SetaPos(CIMTVetor m_pos)
{
    pos  = CIMTVetor4(m_pos.x,m_pos.y,m_pos.z , 1.0f);
}

/************************************************************/
/************************************************************/
void CI3DLuz::SetaDir(CIMTVetor m_dir)
{
    m_dir.Normalizar();

    dir  = CIMTVetor4(m_dir.x,m_dir.y,m_dir.z , 1.0f);
}

void CI3DLuz::ConfiguraSpot(float Exp, float Cut)
{
    Expoente = Exp;
    CutOff   = Cut;
}

void CI3DLuz::SetaAtenuacao(float Constant, float Linear, float Quadratic)
{
    AtenuacaoConstante   = Constant;
    AtenuacaoLinear      = Linear;
    AtenuacaoQuadratica  = Quadratic;
}

void CI3DLuz::Prepara(int pI3D_ProgramId, int Indice)
{
    /******************************************************************/
    /*No caso de shaders não há diferença nenhuma entre atualiza e    */
    /*prepara, porem mantive apenas para fins de compatibilidade      */
    /*PODE SER ELIMINADO NO FUTURO!                                   */
    /******************************************************************/
    switch(tipo)
    {
       case LIGHTTYPE_POINT:      {PreparaLuzPonto      (pI3D_ProgramId,Indice);}break;
       case LIGHTTYPE_SPOT:       {PreparaLuzSpot       (pI3D_ProgramId,Indice);}break;
       case LIGHTTYPE_DIRECTIONAL:{PreparaLuzDirectional(pI3D_ProgramId,Indice);}break;
       default:{}break;
     }
}

void CI3DLuz::Atualiza(int pI3D_ProgramId, int Indice)
{
    /******************************************************************/
    /*No caso de shaders não há diferença nenhuma entre atualiza e    */
    /*prepara, porem mantive apenas para fins de compatibilidade      */
    /*PODE SER ELIMINADO NO FUTURO!                                   */
    /******************************************************************/
    switch(tipo)
    {
       case LIGHTTYPE_POINT:      {PreparaLuzPonto      (pI3D_ProgramId,Indice);}break;
       case LIGHTTYPE_SPOT:       {PreparaLuzSpot       (pI3D_ProgramId,Indice);}break;
       case LIGHTTYPE_DIRECTIONAL:{PreparaLuzDirectional(pI3D_ProgramId,Indice);}break;
       default:{}break;
    }
}

void CI3DLuz::PreparaLuzPonto(int pI3D_ProgramId, GLenum ThisGLLight)
{
    execGL(IGL_SH_LIGHT_POINT      ,
               pI3D_ProgramId      ,
               ThisGLLight         ,
               pos                 ,
               dir                 ,
               CIMTVetor4(I3D_CorDifusa  .PegaCorRGBA()[0],
                          I3D_CorDifusa  .PegaCorRGBA()[1],
                          I3D_CorDifusa  .PegaCorRGBA()[2],
                          I3D_CorDifusa  .PegaCorRGBA()[3]),
               CIMTVetor4(I3D_CorAmbiente.PegaCorRGBA()[0],
                          I3D_CorAmbiente.PegaCorRGBA()[1],
                          I3D_CorAmbiente.PegaCorRGBA()[2],
                          I3D_CorAmbiente.PegaCorRGBA()[3]),
               CIMTVetor4(I3D_CorSpecular.PegaCorRGBA()[0],
                          I3D_CorSpecular.PegaCorRGBA()[1],
                          I3D_CorSpecular.PegaCorRGBA()[2],
                          I3D_CorSpecular.PegaCorRGBA()[3]),
               Expoente            ,
               CutOff              ,
               AtenuacaoConstante  ,
               AtenuacaoLinear     ,
               AtenuacaoQuadratica);
}

void CI3DLuz::PreparaLuzSpot(int pI3D_ProgramId, GLenum ThisGLLight)
{
    execGL(IGL_SH_LIGHT_SPOT       ,
               pI3D_ProgramId      ,
               ThisGLLight         ,
               pos                 ,
               dir                 ,
               CIMTVetor4(I3D_CorDifusa  .PegaCorRGBA()[0],
                          I3D_CorDifusa  .PegaCorRGBA()[1],
                          I3D_CorDifusa  .PegaCorRGBA()[2],
                          I3D_CorDifusa  .PegaCorRGBA()[3]),
               CIMTVetor4(I3D_CorAmbiente.PegaCorRGBA()[0],
                          I3D_CorAmbiente.PegaCorRGBA()[1],
                          I3D_CorAmbiente.PegaCorRGBA()[2],
                          I3D_CorAmbiente.PegaCorRGBA()[3]),
               CIMTVetor4(I3D_CorSpecular.PegaCorRGBA()[0],
                          I3D_CorSpecular.PegaCorRGBA()[1],
                          I3D_CorSpecular.PegaCorRGBA()[2],
                          I3D_CorSpecular.PegaCorRGBA()[3]),
               Expoente            ,
               CutOff              ,
               AtenuacaoConstante  ,
               AtenuacaoLinear     ,
               AtenuacaoQuadratica);
}

void CI3DLuz::PreparaLuzDirectional(int pI3D_ProgramId, GLenum ThisGLLight)
{
    execGL(IGL_SH_LIGHT_DIRECTIONAL  ,
               pI3D_ProgramId        ,
               ThisGLLight           ,
               pos                   ,
               dir                   ,
               CIMTVetor4(I3D_CorDifusa  .PegaCorRGBA()[0],
                          I3D_CorDifusa  .PegaCorRGBA()[1],
                          I3D_CorDifusa  .PegaCorRGBA()[2],
                          I3D_CorDifusa  .PegaCorRGBA()[3]),
               CIMTVetor4(I3D_CorAmbiente.PegaCorRGBA()[0],
                          I3D_CorAmbiente.PegaCorRGBA()[1],
                          I3D_CorAmbiente.PegaCorRGBA()[2],
                          I3D_CorAmbiente.PegaCorRGBA()[3]),
               CIMTVetor4(I3D_CorSpecular.PegaCorRGBA()[0],
                          I3D_CorSpecular.PegaCorRGBA()[1],
                          I3D_CorSpecular.PegaCorRGBA()[2],
                          I3D_CorSpecular.PegaCorRGBA()[3]),
               Expoente            ,
               CutOff              ,
               AtenuacaoConstante  ,
               AtenuacaoLinear     ,
               AtenuacaoQuadratica);
}
