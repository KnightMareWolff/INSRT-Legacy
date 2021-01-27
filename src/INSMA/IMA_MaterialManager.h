/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_MATERIALMANAGER_H
#define IMA_MATERIALMANAGER_H

#include "IMA_Material.h"

class CIMAMaterialManager
{
public:
    CIMAMaterialManager();

    int  AddMaterial (QString      pIMA_NomeMaterial     ,
                      int          pIMA_MaterialMode     );
    int  AddMaterial (QString      pIMA_NomeMaterial     ,
                      CIMACor      pIMA_CorDifusa        ,
                      CIMACor      pIMA_CorAmbiente      ,
                      CIMACor      pIMA_CorEmissiva      ,
                      CIMACor      pIMA_CorSpecular      ,
                      float        pIMA_Opacidade        ,
                      float        pIMA_Brilho           ,
                      int          pIMA_MaterialMode     );

    int  AddTextura  (QString  pIMA_NomeMaterial         ,
                      QString  pIMA_NomeTextura          ,
                      int      pIMA_TextureMode          );

    int  AddCubeMap  (QString    pIMA_NomeMaterial       ,
                      QString    pI3D_NomeTexturaRight   ,
                      QString    pI3D_NomeTexturaLeft    ,
                      QString    pI3D_NomeTexturaTop     ,
                      QString    pI3D_NomeTexturaBottom  ,
                      QString    pI3D_NomeTexturaBack    ,
                      QString    pI3D_NomeTexturaFront   );

    int  AddTextura  (int      pIMA_Indice               ,
                      QString  pIMA_NomeTextura          ,
                      int      pIMA_TextureMode          );

    int  AddCubeMap  (int        pIMA_Indice             ,
                      QString    pI3D_NomeTexturaRight   ,
                      QString    pI3D_NomeTexturaLeft    ,
                      QString    pI3D_NomeTexturaTop     ,
                      QString    pI3D_NomeTexturaBottom  ,
                      QString    pI3D_NomeTexturaBack    ,
                      QString    pI3D_NomeTexturaFront   );

    bool AddLayerTex (QString  pI3D_NomeMaterial         ,
                      QString  pI3D_NomeTextura          ,
                      QString  pI3D_NomeLayer            ,
                      int      pI3D_CanalTextura         );

    bool AddLayerTex (int      pI3D_Indice               ,
                      QString  pI3D_NomeTextura          ,
                      QString  pI3D_NomeLayer            ,
                      int      pI3D_CanalTextura         );

    bool AddLayerTex (int      pI3D_Indice               ,
                      int      pI3D_IndiceTextura        ,
                      QString  pI3D_NomeLayer            ,
                      int      pI3D_CanalTextura         );

    bool SetaMaterial(int          pI3D_Indice           ,
                      CIMACor      pI3D_CorDifusa        ,
                      CIMACor      pI3D_CorAmbiente      ,
                      CIMACor      pI3D_CorEmissiva      ,
                      CIMACor      pI3D_CorSpecular      ,
                      float        pI3D_Opacidade        ,
                      float        pI3D_Brilho           );

    bool SetaMaterial(QString      pI3D_NomeMaterial     ,
                      CIMACor      pI3D_CorDifusa        ,
                      CIMACor      pI3D_CorAmbiente      ,
                      CIMACor      pI3D_CorEmissiva      ,
                      CIMACor      pI3D_CorSpecular      ,
                      float        pI3D_Opacidade        ,
                      float        pI3D_Brilho           );

    bool SetaNomeMat (int          pI3D_Indice           ,
                      QString      pI3D_NomeMaterial     );

    bool SetaRejeicaoCor(int       pI3D_Indice           ,
                         bool      pI3D_Rejeita          ,
                         CIMACor   pI3D_CorAlpha         );

    bool Prepara     (int pIMA_ProgramId,QString      pI3D_NomeMaterial );
    bool Prepara     (int pIMA_ProgramId, int         pI3D_Indice       );
    bool Prepara     (int pIMA_ProgramId,QString      pI3D_NomeMaterial , int pI3D_IndiceTextura    );
    bool Prepara     (int pIMA_ProgramId,int          pI3D_Indice       , int pI3D_IndiceTextura    );

    int  PegaQtdTexturas (int          pI3D_Indice      );
    int  PegaQtdTexturas (QString      pI3D_NomeMaterial);
    int  PegaQtdMateriais(                              );

    bool RenderToTexture(QString      pIMA_NomeMaterial  ,
                         CIMDVideo   *pIMA_Video         );

    bool RenderToTexture(int          pIMA_Indice        ,
                         CIMDVideo   *pIMA_Video         );

private:
    /******************************/
    /*Metodos Privados de Acesso  */
    /******************************/
    bool ChecaDuplicado(QString pI3D_NomeMaterial,int &IdExistente);
    bool ChecaExistente(QString pI3D_NomeMaterial                 );
    bool ChecaExistente(int     pI3D_Indice                       );
    int  PegaIndice    (QString pI3D_NomeMaterial                 );

    /********************************/
    /*Atributos Privados de Acesso  */
    /********************************/
    int                   IMA_QtdMateriais;
    vector<CIMAMaterial*> IMA_VetorMateriais;
};

#endif // CIMAMATERIALMANAGER_H
