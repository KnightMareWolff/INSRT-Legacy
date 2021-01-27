/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_CAMERA_H
#define I3D_CAMERA_H

#include "I3D_GlobalDef.h"

/************************************************************/
/*Nome da Classe      : CI3DCamera
/*
/*Objetivo            : Responsável pelos eventos de Câmera
/*                      Tem a responsabilidade de armazenar
/*                      e manipular a câmera utilizada para
/*                      a visualização da cena.
/************************************************************/
class CI3DCamera : public INSGL
{
public:

    CI3DCamera();

    float     I3D_Velocidade     ;// Velocidade da camera
    float     I3D_Intervalo      ;// Intervalo dos Frames

    CIMTVetor    I3D_CameraPos         ;// Posicao da camera
    CIMTVetor    I3D_CameraView        ;// Visão da Câmera
    CIMTVetor    I3D_CameraUp          ;// Direcao Superior
    CIMTVetor    I3D_CameraStrafe      ;// Strafe

    float     i3dFramesPorSegundo    ;
    float     i3dUltimoTempo		 ;
    float     i3dTempoFrame          ;
    clock_t   t                      ;

    int       AtTela;
    int       LgTela;

    void Inicializa            (                           );

    void SetaCamera            (float i3dPosicaoX          ,
                                float i3dPosicaoY          ,
                                float i3dPosicaoZ          ,
                                float i3dViewX             ,
                                float i3dViewY             ,
                                float i3dViewZ             ,
                                float i3dUpX               ,
                                float i3dUpY               ,
                                float i3dUpZ               );
    void PegaDirecao           (float &i3dPosicaoX         ,
                                float &i3dPosicaoY         ,
                                float &i3dPosicaoZ         );

    CIMTVetor PegaDirecao      (                           );

    void MoverCamera           (float i3dDirecao           );

    void AtualizaCamera        (float xDir                 ,
                                float yDir                 ,
                                float zDir                 ,
                                float dir                  );
    void Rodar                 (float i3dAnguloDirecao     ,
                                float i3dPosicaoX          ,
                                float i3dPosicaoY          ,
                                float i3dPosicaoZ          );

    void  MapeiaMouse           (float x,float y            );
    void  CalculaStrafe         (                           );
    void  CameraStrafe          (float        i3dDirecao    );
    void  PosicionaCamera       (                           );
    void  PosicionaCamera       (float &pI3D_CurrentTime    ,
                                 float &pI3D_TimeLapsed     );
    void  CalculaTempo          (                           );
    void  ResetaCamera          (                           );
    void  CalculaPerspectiva    (float i3dProx,float i3dDist,int i3dProjection);
};



#endif // CCAMERA_H
