/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_GlobalDef.h"
#include "I3D_Vertice.h"


/************************************************************/
/*Nome do Procedimento: ~CI3DVertice()
/*
/*Objetivo            : Destrutor Padrão da classe
/*                      CI3DVertice
/*                      Destroi o vertice
/************************************************************/
CI3DVertice::~CI3DVertice()
{

}


/************************************************************/
/*Nome do Procedimento: CI3DVertice()
/*
/*Objetivo            : Construtor Padrão da classe
/*                      CI3DVertice
/*                      Constroi um vertice pronto para uso
/*                      porém neutro.(todos vlrs = 0.0f)
/************************************************************/
CI3DVertice::CI3DVertice()
{
    x=y=z=0.0f;

    I3D_CoordTexturaU=0.0f;
    I3D_CoordTexturaV=0.0f;
    I3D_CoordLtmTextU=0.0f;
    I3D_CoordLtmTextV=0.0f;
    I3D_CoordDetTextU=0.0f;
    I3D_CoordDetTextV=0.0f;

    I3D_PlanarNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_SmoothNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_Tangente     = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_BiTangente   = CIMTVetor( 0.0f, 0.0f, 0.0f );

    Status=0;
}

/************************************************************/
/*Nome do Procedimento: CI3DVertice()
/*
/*Objetivo            : Construtor Alternativo da classe
/*                      CI3DVertice
/*                      Constroi um vertice a partir de uma
/*                      coordenada.
/************************************************************/
CI3DVertice::CI3DVertice( float i3dCoordX  ,
                          float i3dCoordY  ,
                          float i3dCoordZ  )
{

   x=i3dCoordX;
   y=i3dCoordY;
   z=i3dCoordZ;

   I3D_CoordTexturaU=0.0f;
   I3D_CoordTexturaV=0.0f;
   I3D_CoordLtmTextU=0.0f;
   I3D_CoordLtmTextV=0.0f;

   I3D_PlanarNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
   I3D_SmoothNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
   I3D_Tangente     = CIMTVetor( 0.0f, 0.0f, 0.0f );
   I3D_BiTangente   = CIMTVetor( 0.0f, 0.0f, 0.0f );

   Status = 0;

}

/************************************************************/
/*Nome do Procedimento: CI3DVertice()
/*
/*Objetivo            : Construtor Alternativo da classe
/*                      CI3DVertice
/*                      Constroi um vertice a partir de um
/*                      vetor contendo as coordenadas.
/************************************************************/
CI3DVertice::CI3DVertice(CIMTVetor& i3dVetor )
{
    x=i3dVetor.x;
    y=i3dVetor.y;
    z=i3dVetor.z;

    I3D_CoordTexturaU=0.0f;
    I3D_CoordTexturaV=0.0f;
    I3D_CoordLtmTextU=0.0f;
    I3D_CoordLtmTextV=0.0f;

    I3D_PlanarNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_SmoothNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_Tangente     = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_BiTangente   = CIMTVetor( 0.0f, 0.0f, 0.0f );

    Status = 0;
}

/************************************************************/
/*Nome do Procedimento: CI3DVertice()
/*
/*Objetivo            : Construtor Alternativo da classe
/*                      CI3DVertice
/*                      Constroi um vertice a partir de um
/*                      vetor contendo as coordenadas.
/************************************************************/

CI3DVertice::CI3DVertice(const CI3DVertice &i3dVertice )
{

    I3D_CoordTexturaU=i3dVertice.I3D_CoordTexturaU;
    I3D_CoordTexturaV=i3dVertice.I3D_CoordTexturaV;
    I3D_CoordLtmTextU=i3dVertice.I3D_CoordLtmTextU;
    I3D_CoordLtmTextV=i3dVertice.I3D_CoordLtmTextV;
    I3D_PlanarNormal =i3dVertice.I3D_PlanarNormal ;
    I3D_SmoothNormal =i3dVertice.I3D_SmoothNormal ;
    I3D_Tangente     =i3dVertice.I3D_Tangente     ;
    I3D_BiTangente   =i3dVertice.I3D_BiTangente   ;
    x=i3dVertice.x;
    y=i3dVertice.y;
    z=i3dVertice.z;

    Status = i3dVertice.Status ;

}

/************************************************************/
/*Nome do Procedimento: CI3DVertice()
/*
/*Objetivo            : Construtor Alternativo da classe
/*                      CI3DVertice
/*                      Constroi um vertice a partir de todas
/*                      as coordenadas.
/*                      Útil TAMBÉM para clonarmos vertices com
/*                      suas respectivas coordenadas de textura.
/************************************************************/
CI3DVertice::CI3DVertice(float i3dCoordX     ,
                         float i3dCoordY     ,
                         float i3dCoordZ     ,
                         float i3dTexCoordU  ,
                         float i3dTexCoordV  )

{

    x=i3dCoordX;
    y=i3dCoordY;
    z=i3dCoordZ;

    I3D_CoordTexturaU=i3dTexCoordU;
    I3D_CoordTexturaV=i3dTexCoordV;
    I3D_CoordLtmTextU=0.0f;
    I3D_CoordLtmTextV=0.0f;

    I3D_PlanarNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_SmoothNormal = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_Tangente     = CIMTVetor( 0.0f, 0.0f, 0.0f );
    I3D_BiTangente   = CIMTVetor( 0.0f, 0.0f, 0.0f );

    Status = 0;

}


/************************************************************/
/*Nome do Procedimento: Igual()
/*
/*Objetivo            : Retorna se e igual ou nao.
/************************************************************/
bool CI3DVertice::Igual(CI3DVertice i3dVertice)
{
    return *this==i3dVertice;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CI3DVertice& CI3DVertice::operator=  ( const CI3DVertice& vertice )
{
    x                 = vertice.x                ;
    y                 = vertice.y                ;
    z                 = vertice.z                ;
    I3D_CoordTexturaU = vertice.I3D_CoordTexturaU;
    I3D_CoordTexturaV = vertice.I3D_CoordTexturaV;
    I3D_CoordLtmTextU = vertice.I3D_CoordLtmTextU;
    I3D_CoordLtmTextV = vertice.I3D_CoordLtmTextV;
    I3D_PlanarNormal  = vertice.I3D_PlanarNormal ;
    I3D_SmoothNormal  = vertice.I3D_SmoothNormal ;
    I3D_Tangente      = vertice.I3D_Tangente     ;
    I3D_BiTangente    = vertice.I3D_BiTangente   ;
    Status            = vertice.Status           ;
    return *this;
}
