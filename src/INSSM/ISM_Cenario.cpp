/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "ISM_Cenario.h"

extern bool            bRodando;
extern bool             PipeUpd;

lua_State*   CISMCenario::S = NULL;

CISMCenario::CISMCenario(QOpenGLContext *pI3DContext)
{
    pINS3DPlatInterface            = new INS3D(pI3DContext);//Interface Inicialização 3D
    ISM_CenarioInicializado        = false;
    ISM_ThreadLuaInicializada      = false;
    ISM_ThreadPipelineInicializada = false;
}

CISMCenario::CISMCenario(QGLContext *pI3DContext)
{
    pINS3DPlatInterface            = new INS3D(pI3DContext);//Interface Inicialização 3D
    ISM_CenarioInicializado        = false;
    ISM_ThreadLuaInicializada      = false;
    ISM_ThreadPipelineInicializada = false;
}

CISMCenario::~CISMCenario()
{

}

bool CISMCenario::Render()
{
   return true;
}

bool CISMCenario::Render(float pTimeElapsed)
{
    Q_UNUSED(pTimeElapsed);
    return true;
}

bool CISMCenario::Inicializa()
{
    //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );//Fundo Preto
    return true;
}


bool CISMCenario::Resize(int w, int h)
{
    Q_UNUSED(w);
    Q_UNUSED(h);
    return true;
}

bool CISMCenario::MapeiaMouse(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return true;
}

bool CISMCenario::Seleciona(int x, int y)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    return true;
}

bool CISMCenario::MoverCamera(int pAction)
{
    Q_UNUSED(pAction);
    return true;
}

bool CISMCenario::InputKey(int pKey)
{
    Q_UNUSED(pKey);
    return true;
}

int CISMCenario::AddTrigger(int      pTipoTrigger   ,
                            QString  pNomeTrigger   ,
                            QString  pFuncao)
{
   Q_UNUSED(pTipoTrigger);
   Q_UNUSED(pNomeTrigger);
   Q_UNUSED(pFuncao);
   return true;
}

bool CISMCenario::AddParametroTrigger(int      pTipoTrigger            ,
                                      int      pIdTrigger              ,
                                      CIUTParametroTrigger  pParametro )
{
   Q_UNUSED(pTipoTrigger);
   Q_UNUSED(pIdTrigger);
   Q_UNUSED(pParametro);
   return true;
}

bool CISMCenario::AddParametroTrigger(int      pTipoTrigger            ,
                                      QString  pNomeTrigger            ,
                                      CIUTParametroTrigger  pParametro)
{
   Q_UNUSED(pTipoTrigger);
   Q_UNUSED(pNomeTrigger);
   Q_UNUSED(pParametro);
   return true;
}

bool CISMCenario::EnableOGLStates()
{
    pINS3DPlatInterface->EnableStates();
    return true;
}

bool CISMCenario::DisableOGLStates()
{
    pINS3DPlatInterface->DisableStates();
    return true;
}

bool CISMCenario::CriaFenceSync(GLsync &pISM_GLSync)
{
    pINS3DPlatInterface->CriaFenceSync(pISM_GLSync);
    return true;
}

bool CISMCenario::WaitFenceSync(GLsync pISM_GLSync)
{
    pINS3DPlatInterface->WaitFenceSync(pISM_GLSync);
    return true;
}

bool CISMCenario::UpdateHardwareDC()
{
   pINS3DPlatInterface->UpdateHardDC();
   return true;
}

bool CISMCenario::EnableOGLCW()
{
    pINS3DPlatInterface->Enable(INSSH::pISHProgramManager->ProgramId("CoreRender"),IGL_WINMODE_CW);
    return true;
}

bool CISMCenario::EnableOGLCCW()
{
    pINS3DPlatInterface->Enable(INSSH::pISHProgramManager->ProgramId("CoreRender"),IGL_WINMODE_CCW);
    return true;
}

bool CISMCenario::ReadPixels(int x,int y, GLchar *res)
{
    pINS3DPlatInterface->ReadPixels(x,y,res);
    return true;
}

bool CISMCenario::CenarioInicializado()
{
    return ISM_CenarioInicializado;
}

bool CISMCenario::ThreadLuaInicializada()
{
    return ISM_ThreadLuaInicializada;
}

bool CISMCenario::ThreadPipeInicializada()
{
    return ISM_ThreadPipelineInicializada;
}

bool CISMCenario::SistemaLivre()
{
    if(ISM_CenarioInicializado && ISM_ThreadLuaInicializada) return true;
    return false;
}

bool CISMCenario::InterrompeExecucao()
{
    ISM_CenarioInicializado   = false;
    ISM_ThreadLuaInicializada = false;
    return false;
}

bool CISMCenario::LiberaCenario()
{
    ISM_CenarioInicializado = true;
    return true;
}

bool CISMCenario::LiberaLua()
{
    ISM_ThreadLuaInicializada = true;
    return true;
}

bool CISMCenario::CriaThreadLua(lua_State*  L)
{
    if(ISM_ThreadLuaInicializada)
    {
       S = lua_newthread(L);
       lua_xmove(L,S,1);
       ISM_ThreadPipelineInicializada=true;
    }
    return true;
}

lua_State* CISMCenario::PegaThreadLua()
{
    if(ISM_ThreadLuaInicializada)
    {
       return S;
    }
    return NULL;
}
