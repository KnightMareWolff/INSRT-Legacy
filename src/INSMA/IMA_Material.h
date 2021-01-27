/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_MATERIAL_H
#define IMA_MATERIAL_H

#include "IMA_GlobalDef.h"
#include "IMA_Textura.h"
#include "IMA_Cor.h"

/************************************************************/
/************************************************************/
class CIMAMaterial : public INSGL
{

private:

    QString      IMA_NomeMaterial ;
    CIMACor      IMA_CorDifusa    ;
    CIMACor      IMA_CorAmbiente  ;
    CIMACor      IMA_CorEmissiva  ;
    CIMACor      IMA_CorSpecular  ;
    CIMACor      IMA_AlphaColor   ;
    bool         IMA_PixelReject  ;//Remove pixel de mesma cor setada
    float        IMA_Opacy        ;
    float        IMA_Shininess    ;
    float        IMA_Reflection   ;//Fator de Reflexão do Material
    float        IMA_Refraction   ;//Indice de Refração aplicado no Material
    int          IMA_MaterialMode ;//Modo de Preparo do Material

    vector<int>  IMA_Texturas;

public:

    CIMAMaterial (                              );
    CIMAMaterial ( const CIMAMaterial & material);

    QString PegaNomeMaterial(                                                                           );
    CIMACor PegaCorDifusa   (                                                                           );
    CIMACor PegaCorAmbiente (                                                                           );
    CIMACor PegaCorEmissiva (                                                                           );
    CIMACor PegaCorSpecular (                                                                           );
    CIMACor PegaCorAlpha    (                                                                           );
    float   PegaPotencia    (                                                                           );
    float   PegaOpacidade   (                                                                           );
    int     PegaQtdTexturas (                                                                           );
    void    SetaCorDifusa   (CIMACor    i3dCorDifusa                                                    );
    void    SetaCorAmbiente (CIMACor    i3dCorAmbiente                                                  );
    void    SetaCorEmissiva (CIMACor    i3dCorEmissiva                                                  );
    void    SetaCorSpecular (CIMACor    i3dCorSpecular                                                  );
    void    SetaPotencia    (float      i3dPotencia                                                     );
    void    SetaOpacidade   (float      opac                                                            );
    void    SetaReflexao    (float      i3dReflexao                                                     );
    void    SetaNomeMaterial(QString    pi3dNomeMaterial                                                );
    void    SetaRejeicaoCor (bool       bRejeita         , CIMACor CorAlpha                             );
    void    SetaMaterialMode(int        pIMA_MaterialMode                                               );
    int     AddVetorTextura (QString    pI3D_NomeTextura , int pIMA_TextureMode                         );

    int     AddCubeMap      (QString    pI3D_NomeTexturaRight                                           ,
                             QString    pI3D_NomeTexturaLeft                                            ,
                             QString    pI3D_NomeTexturaTop                                             ,
                             QString    pI3D_NomeTexturaBottom                                          ,
                             QString    pI3D_NomeTexturaBack                                            ,
                             QString    pI3D_NomeTexturaFront                                           );

    void    AddLayerTextura (QString    pI3D_NomeTextura , QString pI3D_NomeLayer ,int pI3D_CanalTextura);
    void    AddLayerTextura (int        pI3D_IdTextura   , QString pI3D_NomeLayer ,int pI3D_CanalTextura);
    void    Prepara         (int        pIMA_ProgramId                                                  );
    void    Prepara         (int        pIMA_ProgramId   ,int      pIMA_IdTextura                       );
    void    RenderToTexture (CIMDVideo *pIMA_Video                                                      );

    CIMAMaterial &operator=(const CIMAMaterial& opr);

};

#endif // I3D_MATERIAL_H
