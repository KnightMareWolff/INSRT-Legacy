/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_TEXTUREMANAGER_H
#define IMA_TEXTUREMANAGER_H

#include "IMA_Textura.h"

class CIMATextureManager
{
public:
    CIMATextureManager();
   ~CIMATextureManager();

    int  AddTextura      (QString pI3D_NomeTextura,int     pIMA_TextureMode                    );
    int  AddCubeMap      (QString pIMA_NomeRight                                               ,
                          QString pIMA_NomeLeft                                                ,
                          QString pIMA_NomeTop                                                 ,
                          QString pIMA_NomeBottom                                              ,
                          QString pIMA_NomeBack                                                ,
                          QString pIMA_NomeFront                                               );
    int  AddLayerTextura (QString pI3D_NomeTextura,QString pI3D_NomeLayer  ,int pI3D_CanalLayer);
    int  AddLayerTextura (int     pI3D_IdTextura  ,QString pI3D_NomeLayer  ,int pI3D_CanalLayer);
    bool AddLayerTextura (int     pI3D_IdTextura  ,int     pI3D_IdLayer    ,int pI3D_CanalLayer);

    bool ConstroiTexturas(                        );
    bool ConstroiTextura (QString pI3D_NomeTextura);
    bool ConstroiTextura (int     pI3D_IdTextura  );

    bool Prepara         (int     pIMA_IdTextura , int pIMA_ProgramId  );
    int  PegaLayerTextura(int     pIMA_IdTextura , int pIMA_CanalLayer );

    bool PegaPropriedades(         int  pIMA_IdTextura ,
                          unsigned int &pIMA_OpenGLId  ,
                          unsigned int &pIMA_Altura    ,
                          unsigned int &pIMA_Largura   ,
                          unsigned int &pIMA_Formato   );

    unsigned char* PegaDados(int  pIMA_IdTextura);

    bool RenderToTexture (int pIMA_IdTextura,CIMDVideo *pIMA_Video);

private:
    /******************************/
    /*Metodos Privados de Acesso  */
    /******************************/
    bool ChecaDuplicado(QString pI3D_NomeTextura,int &IdExistente);
    bool ChecaExistente(QString pI3D_NomeTextura                 );
    bool ChecaExistente(int     pI3D_Indice                      );
    int  PegaIndice    (QString pI3D_NomeTextura                 );

    /******************************/
    /*Metodos Estaticos de Acesso */
    /******************************/

    /********************************/
    /*Atributos Estaticos de Acesso */
    /********************************/
    int                  I3D_QtdTexturas;
    vector<CIMATextura*> I3D_VetorTexturas;
    QString              I3D_PathTexturas;

};

#endif // CI3DTEXTUREMANAGER_H
