/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/


#ifndef IMT_PLANO_H
#define IMT_PLANO_H

#include "IMT_Vetor.h"

//em caso de problemas incluir typedef...
enum CLASSIFICACAO
{
       FRENTE      = 1 ,
       ATRAS       = 2 ,
       COPLANAR    = 3 ,
       CRUZANDO    = 4
};

/************************************************************/
/************************************************************/
class CIMTPlano
{
public:
    //------------------------------------------------------------
    //------------------------------------------------------------
     CIMTPlano(                                             );
     CIMTPlano( const CIMTVetor& vecNormal, float fDistance );
     CIMTPlano( const CIMTVetor& vecNormal, const CIMTVetor& vecPointOnPlane );

    //------------------------------------------------------------
    //------------------------------------------------------------
    CLASSIFICACAO  ClassificaPoligono( const CIMTVetor pVertices[] ,
                                       unsigned long VertexCount   ,
                                       unsigned long VertexStride  ) const;

    CLASSIFICACAO  ClassificaPonto   ( const CIMTVetor& vecPoint   ,
                                             float *    Dist =    0) const;

    CLASSIFICACAO  ClassificaLinha   ( const CIMTVetor& Point1     ,
                                       const CIMTVetor& Point2     ) const;

    CLASSIFICACAO  ClassificaEsfera  ( const CIMTVetor& i3dPosicao ,
                                       float i3dRaio               ,
                                       float *i3dDistancia         ) const;

    CIMTVetor      PegaPtoNoPlano    (                             ) const;

    bool           CruzamentoRaio    ( const CIMTVetor& RayStart    ,
                                       const CIMTVetor& RayEnd      ,
                                             CIMTVetor& Intersection,
                                       float *    pPercentage =    0) const;

    bool           CruzamentoRaio    ( const CIMTVetor& RayStart    ,
                                       const CIMTVetor& RayDir      ,
                                       float *          Intervalo   ) const;

    bool           MesmoLado         ( const CIMTVetor& vecNormal ) const;

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTVetor       IMT_NormalPlano;
    float           IMT_DistanciaPlano;
};

#endif // IMT_PLANO_H
