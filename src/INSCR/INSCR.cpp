#include "INSCR.h"
#include "ObjetosExportados.h"
#include "qtconcurrentrun.h"

using namespace QtConcurrent;


/******************************************************/
/*Objetos para inicialização da thread de Scripts Lua */
/******************************************************/
bool          bInicializado=false;
bool          bRodando     =false;
lua_State*                      L;
QFuture<void>                  f1;
/************************************************************/
/*Lista de Funções cadastradas no sistema para exposição Lua*/
/************************************************************/
vector<INS_FUNC> ListaFuncoes;
/*******************************************************************/
/*A ideia Basica deste controle é criar um Pipeline simples para a */
/*Criação de Modelos Dinamicamente, sem a ocorrência de Crash entre*/
/*A alocação Lua e O nucleo Central 3D                             */
/*******************************************************************/
bool                   PipeUpd        =false;
vector<INS_MODEL_PIPE> ModelPipeline        ;
bool                   LockPipeline   =false;

CISMCenario* INSCR::pICRCenario = NULL;//ponteiro para o cenario

/************************************************************/
/*Nome do Método      : processalua( void )
/*
/*Objetivo            : Executa o processamento da logica do
/*                      script lua inicializado na Thread
/************************************************************/
void processalua( void )
{
    L = luaL_newstate();
    if(L == NULL)
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro ao Criar Interface Scripting.");
    }

    //Inicializa todas as bibliotecas Lua
    luaL_openlibs(L);

    //Faz o Bind dos objetos exportados para o Contexto Lua Criado
    tolua_ObjetosExportados_open(L);

    //Executa o Script Principal

    //PATH PARA DEBBUG VIA COMPILADOR
    luaL_dofile(L, QString(CIUTGerenciadorPath::IUT_PathWorld + "Scripts/Main.lua")
                   .toStdString().c_str());

    //PATH PARA DEBBUG VIA EDITOR
    //luaL_dofile(L, "../../world/Scripts/Main.lua");

    //Fecha o contexto de execução do script
    lua_close (L);
}

INSCR::INSCR()
{
    f1 = QtConcurrent::run(processalua);
}

INSCR::~INSCR()
{

}

void INSCR::AtribuiSM(CISMCenario *pISMCenario)
{
    pICRCenario = pISMCenario;
}

CISMCenario* INSCR::PegaSM()
{
    return pICRCenario;
}
