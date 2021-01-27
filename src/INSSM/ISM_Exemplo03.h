/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Utilização de Iluminação e Materiais
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO03_H
#define CISMEXEMPLO03_H

#include "ISM_Cenario.h"

class CISMExemplo03 : public CISMCenario
{
private:
    CI3DCamera         *pCam          ;//Camera principal de visualização
    CI3DLuz            *pLuzAmbiente  ;//Luz Ambiente
    CI3DCubo           *pSky          ;//SkyBox
    CI3DModelo         *pModelo       ;//Modelo Ogro
    CI3DEsfera         *pEsfera01     ;//Esfera a ser desenhado
    CI3DEsfera         *pEsfera02     ;//Esfera a ser desenhado
    CI3DCubo           *pCubo01       ;//Esfera a ser desenhado
    CI3DCubo           *pCubo02       ;//Esfera a ser desenhado

    float               direction;
    bool                colidiu;

    bool                japosicionou  ;//Flag informando se ja posicionou a camera

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo03(QOpenGLContext   *pI3DContext);
     CISMExemplo03(QGLContext       *pI3DContext);
    ~CISMExemplo03(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};

#endif // CISMEXEMPLO03_H
