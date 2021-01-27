/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Utilização de Operações Booleanas(CSG)
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO07_H
#define CISMEXEMPLO07_H

#include "ISM_Cenario.h"

class CISMExemplo07 : public CISMCenario
{
private:
    CI3DCamera            *pCam          ;//Camera principal de visualização
    CI3DLuz               *pLuzAmbiente  ;//Luz Ambiente
    CI3DCubo              *pSky          ;//SkyBox
    CI3DCubo              *pCubo01       ;//Seleção 01
    CI3DCubo              *pCubo02       ;//Seleção 02
    CI3DCubo              *pCubo03       ;//Seleção 03
    CI3DProcessadorCSG    *pProcessador  ;//Processador CSG
    bool                   japosicionou  ;//Flag informando se ja posicionou a camera
    bool                   csgok         ;//Flag informando CSG realizado

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo07(QOpenGLContext   *pI3DContext);
     CISMExemplo07(QGLContext       *pI3DContext);
    ~CISMExemplo07(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool Seleciona      (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};

#endif // CISMEXEMPLO07_H
