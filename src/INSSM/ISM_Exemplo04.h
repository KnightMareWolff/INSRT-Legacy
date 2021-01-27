/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Carregamento de Modelos
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO04_H
#define CISMEXEMPLO04_H

#include "ISM_Cenario.h"

class CISMExemplo04 : public CISMCenario
{
private:
    CI3DCamera          *pCam          ;//Camera principal de visualização
    CI3DLuz             *pLuzAmbiente  ;//Luz Ambiente
    CI3DCubo            *pSky          ;//SkyBox
    CI3DModelo          *pModelo       ;//Modelo Ogro
    bool                japosicionou  ;//Flag informando se ja posicionou a camera
    int                 IdMatSky      ;//Id do Material SkyBox

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo04(QOpenGLContext   *pI3DContext);
     CISMExemplo04(QGLContext       *pI3DContext);
    ~CISMExemplo04(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};


#endif // CISMEXEMPLO04_H
