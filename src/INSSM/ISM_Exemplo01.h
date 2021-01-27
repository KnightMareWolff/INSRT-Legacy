/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de um Cubo 3D
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO01_H
#define CISMEXEMPLO01_H

#include "ISM_Cenario.h"

/*******************************************************************/
/*Exemplo 02 - Cubo 3D                                             */
/*Neste Exemplo veremos como carregar um Cubo em 3D e posicionarmos*/
/*a camera corretamente em frente a este cubo.                     */
/*******************************************************************/
class CISMExemplo01 : public CISMCenario
{
private:
    CI3DCamera         *pCam                 ;//Camera principal de visualização
    CI3DCubo           *pCubo                ;//Cubo a ser desenhado
    bool                japosicionou         ;//Flag informando se ja posicionou a camera

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo01(QOpenGLContext   *pI3DContext);
     CISMExemplo01(QGLContext       *pI3DContext);
    ~CISMExemplo01(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};

#endif // CISMEXEMPLO01_H
