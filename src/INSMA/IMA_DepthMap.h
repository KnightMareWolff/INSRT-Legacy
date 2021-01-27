/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_DEPTHMAP_H
#define IMA_DEPTHMAP_H

#include "IMA_GlobalDef.h"

class CIMADepthMap
{
public:
    CIMADepthMap(                                                             );
    CIMADepthMap(int     pIMA_Tam        , int pIMA_TamQuad, float pIMA_Escala);
    CIMADepthMap(QString pIMA_NomeArquivo, int pIMA_TamQuad, float pIMA_Escala);
   ~CIMADepthMap(                                                             );

    int       PegaTam        (                                                       );
    int       PegaQuad       (                                                       );
    float     PegaEscala     (                                                       );
    float    *PegaAlturas    (                                                       );
    float     PegaAltura     (float pIMA_X   ,  float pIMA_Z                         );
    float     PegaAlturaPixel(float pIMA_X   ,  float pIMA_Z                         );
    void      PegaNormal     (float pIMA_X   ,  float pIMA_Z , CIMTVetor &pIMA_Normal);
    void      PegaNormalPixel(float pIMA_X   ,  float pIMA_Z , CIMTVetor &pIMA_Normal);
    void      GeraFractal    (float pIMA_Roughness                                   );




private:
    int           IMA_TamMapa;
    int           IMA_TamQuad;
    float         IMA_Escala ;
    vector<float> IMA_Alturas;
    Mat           I3D_Imagem ;

    void         FiltroBlur   (float pIMA_Passos);
    unsigned int PegaIndice   (int x   ,   int z);
    void         FiltroSmooth (                 );
};

#endif // CIMADEPTHMAP_H
