/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Cubo 3D utilizando a GUI do Qt
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO02_H
#define CISMEXEMPLO02_H

#include "ISM_Cenario.h"

class CISMExemplo02 : public CISMCenario
{
private:
    CI3DCamera         *pCam                 ;//Camera principal de visualização
    CI3DCubo           *pCubo                ;//Cubo a ser desenhado
    bool                japosicionou         ;//Flag informando se ja posicionou a camera

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo02(QOpenGLContext   *pI3DContext);
     CISMExemplo02(QGLContext       *pI3DContext);
    ~CISMExemplo02(                             );

     /*******************************************/
     /*Metodos Polimorficos herdados do Cenario */
     /*******************************************/
     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
     /*******************************************/
     /*Metodos Especificos do Exemplo           */
     /*******************************************/
     bool RodarCubo(CIMTVetor EixoRotacao);
};


#endif // CISMEXEMPLO02_H
