/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/


#ifndef I3D_FACE_H
#define I3D_FACE_H

#include "I3D_Poligono.h"

/************************************************************/
/************************************************************/
class CI3DFace : public CI3DPoligono
{

public:

    CIMTVetor       I3D_NormalFace;
    int             I3D_IndiceTextura ;
    int             I3D_IndiceMaterial;
    int             I3D_IndiceMesh    ;
    int             I3D_IndiceLightMap;
    int             I3D_FaceProgramId ;
    CIMTVetor2      I3D_HeightMapXY   ;

    bool            Status            ;

    CIMTBorda       BordaFace         ;

    bool       texturizado  ;//Texturizado?
    bool       lightmap     ;//Contem Lightmap?
    int        textProj     ;//Qual e a projecao?
    CIMTVetor  ScalaTextura ;//Qual e a Scala?
    CIMTVetor  TransTextura ;//Qual e o Offset?
    CIMTVetor  AngulTextura ;//Qual e o Angulo?

public:

    /**********************************/
    /*Construtores                    */
    /**********************************/
     CI3DFace(                        );
     CI3DFace(const CI3DFace &i3dFace );
    ~CI3DFace(                        );

     virtual bool Divide          ( const CIMTPlano& Plano   ,
                                          CI3DFace  *DivisorFrente ,
                                          CI3DFace  *DivisorAtras );

     virtual bool GeraPoligono    ( const CIMTPlano& Plane   ,
                                    const CIMTBorda& Bounds );

    void         Renderiza         (int iRenderMode, int iPolygonMode, int iShadingMode, int iGeometryMode);
    void         SetaVertice       (int index,CI3DVertice vert);
    void         CalculaBordaFace  (                          );
    CIMTPlano    PegaPlano         (                          );
    bool         CruzamentoRaio    (const CIMTVetor& RayStart ,
                                    const CIMTVetor& RayDir   );
    bool         CruzamentoPontos  (const CIMTVetor& RayStart ,
                                    const CIMTVetor& RayEnd   ,
                                          CIMTVetor& ponto    );
    bool         CruzamentoRaio    (const CIMTVetor& RayStart ,
                                    const CIMTVetor& RayDir   ,
                                          CIMTVetor& ponto    );

};


#endif // I3D_FACE_H
