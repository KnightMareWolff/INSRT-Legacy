/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Projeto de Demonstração Geral
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef CISMDEMOPROJECT_H
#define CISMDEMOPROJECT_H

#include "ISM_Cenario.h"

class CISMDemoProject : public CISMCenario
{
private:
    CI3DCamera         *pCam           ;
    CI3DLuz            *pLuzAmbiente   ;
    CI3DCubo           *pCubo          ;
    CIGOMundo          *pMundo;
    CIGOAtor           *pAtor;
    CIGOBrush          *pBrush;

    bool  texturainicializada  ;
    bool  japosicionou         ;
    bool  bObjetosInicializados;
    bool  bFxTocou;
    bool  luainicializado;

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMDemoProject(QOpenGLContext   *pI3DContext);
     CISMDemoProject(QGLContext       *pI3DContext );
    ~CISMDemoProject();

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};

#endif // CISMDEMOPROJECT_H
