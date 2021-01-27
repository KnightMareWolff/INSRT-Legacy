/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_Trigger.h"

CIUTTrigger::CIUTTrigger()
{
    IUT_TipoTrigger   = IUT_TRIGGER_PL_VOID ;
    IUT_NomeTrigger   = "Trigger Vazia"     ;
    IUT_FuncaoTrigger = "Funcao Vazia"      ;
    IUT_EstadoTrigger = IUT_TRIGGER_ST_NULO ;
}

CIUTTrigger::CIUTTrigger(int pTipo,QString pNome,QString pFuncao)
{
   IUT_TipoTrigger   = pTipo  ;
   IUT_NomeTrigger   = pNome  ;
   IUT_FuncaoTrigger = pFuncao;
   IUT_EstadoTrigger = IUT_TRIGGER_ST_NULO ;
}

CIUTTrigger::~CIUTTrigger()
{

}

void CIUTTrigger::Ativar()
{
    IUT_EstadoTrigger = IUT_TRIGGER_ST_ATIVO;
}

void CIUTTrigger::Desativar()
{
    IUT_EstadoTrigger = IUT_TRIGGER_ST_INATIVO;
}

void CIUTTrigger::Executando()
{
    IUT_EstadoTrigger = IUT_TRIGGER_ST_EXEC;
}

