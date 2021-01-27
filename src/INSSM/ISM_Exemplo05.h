/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Utilização de Arquiteturas Low Poly 3D
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMEXEMPLO05_H
#define CISMEXEMPLO05_H

#include "ISM_Cenario.h"

class CISMExemplo05 : public CISMCenario
{
private:
    CI3DCamera            *pCam          ;//Camera principal de visualização
    CI3DLuz               *pLuzAmbiente  ;//Luz Ambiente
    CI3DCubo              *pSky          ;//SkyBox
    CI3DModeloLowPoly     *pArquitetura  ;//Arquitetura Low Poly
    CI3DModeloHierarquico *pModelo       ;//Arquitetura Low Poly
    bool                  japosicionou   ;//Flag informando se ja posicionou a camera
    int                    IdMatSky      ;//Id do Material SkyBox

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMExemplo05(QOpenGLContext   *pI3DContext);
     CISMExemplo05(QGLContext       *pI3DContext);
    ~CISMExemplo05(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};

#endif // CISMEXEMPLO05_H
