/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef INSSL_H
#define INSSL_H

#include "ISL_GlobalDef.h"

class INSSL
{

public:
    INSSL(                                  );
    INSSL(int ModoCarregamento,int IdProjeto);
   ~INSSL(                                  );

    void MostraTela(int ModoCarregamento);

private:
    /***************************************************************/
    /*Contextos globais de Inicialização de plataformas/Componentes*/
    /***************************************************************/
    INSSM          *pINSSMPlatInterface;//Interface Inicialização Gerenciamento Cenario
    INSPL          *pINSPLPlatInterface;//Interface Inicialização Camada de Apresentação
    INSCR          *pINSCRPlatInterface;//Interface Inicialização Camada de Scripts


    QOpenGLContext         *mContextGL    ;//Contexto OpenGL Utilizado na renderização(dependente de plataforma)
    QSurfaceFormat         *mFormatoGL    ;//Formato do Contexto OpenGL
    CIPLRuntimeWindow      *mRuntimeWindow;
    CIPLEditorMainWindow   *mEditorWindow;
    CIPLQQuickView         *mTelaPrincipalQuickMode;

    void CarregaModoEditor (             );
    void CarregaModoRuntime(int IdProjeto);
    void CarregaModoQuick  (             );
};

#endif // INSSL_H
