/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef ISM_CENARIO_H
#define ISM_CENARIO_H

#include "ISM_GlobalDef.h"

class CISMCenario
{
public:
    CISMCenario(QOpenGLContext   *pI3DContext);
    CISMCenario(QGLContext       *pI3DContext);
   ~CISMCenario(                             );

    /*****************************************/
    /*Metodos Virtuais para Polimorfismo     */
    /*****************************************/
    virtual bool Inicializa      (                  );
    virtual bool Render          (                  );
    virtual bool Render          (float pTimeElapsed);
    virtual bool Resize          (int w,int h       );
    virtual bool MapeiaMouse     (int x,int y       );
    virtual bool MoverCamera     (int pAction       );
    virtual bool Seleciona       (int x,int y       );
    virtual bool InputKey        (int pKey          );

    /******************************************************/
    /*Rotinas para controle de Pipeline de processamento  */
    /******************************************************/
    virtual int  AddTrigger         (int      pTipoTrigger   ,
                                     QString  pNomeTrigger   ,
                                     QString  pFuncao        );

    virtual bool AddParametroTrigger(int      pTipoTrigger            ,
                                     int      pIdTrigger              ,
                                     CIUTParametroTrigger  pParametro);

    virtual bool AddParametroTrigger(int      pTipoTrigger            ,
                                     QString  pNomeTrigger            ,
                                     CIUTParametroTrigger  pParametro);
    /*****************************************/
    /*Metodos para acesso publico            */
    /*****************************************/
    bool       EnableOGLStates       (                          );
    bool       DisableOGLStates      (                          );
    bool       UpdateHardwareDC      (                          );
    bool       EnableOGLCW           (                          );
    bool       EnableOGLCCW          (                          );
    bool       CriaFenceSync         (GLsync &pISM_GLSync       );
    bool       WaitFenceSync         (GLsync  pISM_GLSync       );
    bool       ReadPixels            (int x, int y, GLchar  *res);
    bool       CenarioInicializado   (                          );
    bool       ThreadLuaInicializada (                          );
    bool       ThreadPipeInicializada(                          );
    bool       SistemaLivre          (                          );
    bool       InterrompeExecucao    (                          );
    bool       LiberaCenario         (                          );
    bool       LiberaLua             (                          );
    bool       CriaThreadLua         (lua_State*  L             );
    lua_State* PegaThreadLua         (                          );

private:
    INS3D              *pINS3DPlatInterface;//Interface Inicialização 3D

    static lua_State*   S;
    bool                ISM_CenarioInicializado;
    bool                ISM_ThreadLuaInicializada;
    bool                ISM_ThreadPipelineInicializada;

};

#endif // ISM_CENARIO_H
