/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_PAINELHEIGHTMAP_H
#define I3D_PAINELHEIGHTMAP_H

#include "I3D_Primitivo.h"

class CI3DPainelHeightMap : public CI3DPrimitivo
{
public:
    CI3DPainelHeightMap(                );
    CI3DPainelHeightMap(int pWindingMode);

    bool  AddHeightMap(QString pImgBase                                       );
    bool  AddHeightMap(int     pI3D_TAM, int   pI3D_TamQuad, float pI3D_Escala);
    float PegaAltura  (float   pI3D_X  , float pI3D_Y                         );
private:
    void Build        ();
    void GeraVertices ();
    void GeraIndices  ();
    void GeraColorMap ();

    CIMADepthMap *I3D_HeightMap;
    CIMAColorMap *I3D_ColorMap;
};

#endif // I3D_PAINELHEIGHTMAP_H
