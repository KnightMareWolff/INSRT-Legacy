/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef IGZ_CONSTRUTOR3D_H
#define IGZ_CONSTRUTOR3D_H

#include "IGZ_GlobalDef.h"
#include "IUT_Lista.h"

class CIGZConstrutor3D: public INSMA
{
public:
    CIGZConstrutor3D();

    void       Render    (                  );
    void       Constroi  (CIMTVetor pCentro );
    void       Animar    (                  );
    CIMTVetor  PegaCentro(                  );
    CIMTVetor  PegaPosTrr(int x,int y       );

    bool       AddTerreno    ();
    bool       AddSky        ();
    bool       AddFonte      ();
    bool       AddTexto      ();
    bool       AddCubo       ();
    bool       AddCuboLowPoly();

private:

   CI3DPainelHeightMap     *pTerreno;
   CI3DCubo                *pSky;
   CI3DFonte               *pFonte;
   CI3DTexto               *pTexto;
   CI3DCubo                *pCubo;
};

#endif // IGZ_CONSTRUTOR_H






