/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_TEXTURA_H
#define IMA_TEXTURA_H

#include "IMA_GlobalDef.h"
#include "IMA_Cor.h"

class CIMATextura : public INSGL
{
public:

    QString                  I3D_NomeTextura  ;//O Nome da textura é o path completo do arquivo.
    unsigned int             I3D_IdT          ;//Id na OpenGL da Textura
    int                      I3D_Altura       ,//Altura da Textura
                             I3D_Largura      ,//Largura da Textura
                             I3D_Formato      ;//Formato da Textura
    int                      I3D_Layers[4]    ;//Vetor de Layers para Multitextura
    Mat                      I3D_Imagem       ;//Imagem carregada OpenCV
    Mat                      I3D_ImagemRight  ;//Imagem Cubemap
    Mat                      I3D_ImagemLeft   ;//Imagem Cubemap
    Mat                      I3D_ImagemTop    ;//Imagem Cubemap
    Mat                      I3D_ImagemBottom ;//Imagem Cubemap
    Mat                      I3D_ImagemBack   ;//Imagem Cubemap
    Mat                      I3D_ImagemFront  ;//Imagem Cubemap
    bool                     I3D_Status       ;//Status de carregamento da textura
    CIMDVideo               *IMA_Video        ;//Ponteiro para Video
    int                      IMA_TextureMode  ;

          CIMATextura();
         ~CIMATextura();
    void RemoveTextura        (                                                    );
    void CriaTextura          (QString      pIMA_NomeTextura , int pIMA_TextureMode);
    void CriaCubeMap          (QString      pIMA_NomeRight                         ,
                               QString      pIMA_NomeLeft                          ,
                               QString      pIMA_NomeTop                           ,
                               QString      pIMA_NomeBottom                        ,
                               QString      pIMA_NomeBack                          ,
                               QString      pIMA_NomeFront                         );
    void AddLayer             (int          pI3D_IdLayer     , int pI3D_CanalLayer );
    void Prepara              (int          pIMA_ProgramId                         );
    int  PegaLayerTextura     (int          pIMA_CanalLayer                        );
    void RenderToTexture      (CIMDVideo   *pIMA_Video                             );
};


#endif // I3D_TEXTURA_H
