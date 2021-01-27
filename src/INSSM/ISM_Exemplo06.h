/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Utilização de Picking
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO06_H
#define CISMEXEMPLO06_H


#include "ISM_Cenario.h"

class CISMExemplo06 : public CISMCenario
{
private:
    CI3DCamera            *pCam          ;//Camera principal de visualização
    CI3DLuz               *pLuzAmbiente  ;//Luz Ambiente
    CI3DCubo              *pSky          ;//SkyBox
    CI3DCubo              *pCubo01       ;//Seleção 01
    CI3DCubo              *pCubo02       ;//Seleção 02
    CI3DCubo              *pCubo03       ;//Seleção 03
    bool                   japosicionou   ;//Flag informando se ja posicionou a camera

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo06(QOpenGLContext   *pI3DContext);
     CISMExemplo06(QGLContext       *pI3DContext);
    ~CISMExemplo06(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool Seleciona      (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};

#endif // CISMEXEMPLO06_H
