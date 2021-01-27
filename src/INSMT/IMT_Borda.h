/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IMT_BORDA_H
#define IMT_BORDA_H

#include "IMT_Vetor.h"
#include "IMT_Matriz.h"

#define BORDAS_PLANO_TOPO       0
#define BORDAS_PLANO_ABAIXO     1
#define BORDAS_PLANO_ESQUERDO   2
#define BORDAS_PLANO_DIREITO    3
#define BORDAS_PLANO_FRENTE     4
#define BORDAS_PLANO_ATRAS      5

/************************************************************/
/************************************************************/
class CIMTBorda
{
public:

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTBorda(                         );
    CIMTBorda( const CIMTVetor& vecMin,
               const CIMTVetor& vecMax );
    CIMTBorda( float xIMT_MinVetorBorda,
               float yIMT_MinVetorBorda,
               float zIMT_MinVetorBorda,
               float xIMT_MaxVetorBorda,
               float yIMT_MaxVetorBorda,
               float zIMT_MaxVetorBorda );

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTVetor        IMT_MinVetorBorda;
    CIMTVetor        IMT_MaxVetorBorda;
    float            IMT_Raio;

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTVetor       PegaDimensao     (                       ) const;
    CIMTVetor       PegaCentro       (                       ) const;
    CIMTVetor       Transform        (CIMTMatriz     pIMT_Mtx);
    CIMTPlano       PegaPlano        ( unsigned long Side    ) const;


    CIMTBorda&      CalculaBordaMesh ( const CIMTVetor pVertices[],
                                       unsigned long VertexCount ,
                                       unsigned long VertexStride,
                                       bool bReset = true );

    CIMTBorda&      CalculaBordaPonto( const CIMTVetor pPos,
                                       const float     pDimensao,
                                       bool            bReset = true );

    bool            PontoNaBorda     ( const CIMTVetor& Point           ) const;

    bool            PontoNaBorda     ( const CIMTVetor& Point                  ,
                                       const CIMTVetor& Tolerance       ) const;

    bool            CruzamentoRaio   ( const CIMTVetor& RayStart,
                                       const CIMTVetor& RayDir,
                                       CIMTVetor * pIntersection = NULL ) const;

    bool            CruzamentoRaio   ( const CIMTVetor& RayStart ,
                                       const CIMTVetor& RayDir   ,
                                       const CIMTVetor& Tolerance,
                                       CIMTVetor * pIntersection = NULL ) const;

    bool            CruzamentoBorda  ( const CIMTBorda& Borda           ) const;
    bool            CruzamentoBorda  ( const CIMTBorda& Borda                 ,
                                       const CIMTVetor& Tolerance       ) const;

    bool            CruzamentoEsfera ( const CIMTBorda& Borda           ) const;
    bool            CruzamentoEsfera ( const CIMTBorda& Borda                 ,
                                       float pIMT_TimeElapsed           ) const;

    void            ProvaReal        (                                  )      ;
    void            Limpa            (                                  )      ;

    float           Diff             (float a, float b                  )      ;


    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTBorda&        operator += ( const CIMTVetor& vecShift );
    CIMTBorda&        operator -= ( const CIMTVetor& vecShift );

};
#endif // IMT_BORDA_H
