/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_Node.h"

CIUTNode::CIUTNode()
{
    IUT_TpNode     = IUT_NODE_LINK_DUPLO  ;
    IUT_Proximo    = 0;
    IUT_Anterior   = 0;
    IUT_Prioridade = 0;

    switch(IUT_TpNode)
    {
       case IUT_NODE_LINK_SIMPLES:
       {
           IUT_Nome = QString("Node Simples Default");
       }break;
       case IUT_NODE_LINK_DUPLO:
       {
           IUT_Nome = QString("Node Duplo Default");
       }break;
       case IUT_NODE_LINK_PRTY:
       {
           IUT_Nome = QString("Node Duplo PRTY");
       }
       default:{IUT_Nome = QString("Node Duplo Default");}break;
    }
}

CIUTNode::CIUTNode(CIUTNode* pIUT_Node)
{
    IUT_TpNode     = pIUT_Node->IUT_TpNode  ;
    IUT_Proximo    = 0;
    IUT_Anterior   = 0;
    IUT_Prioridade = pIUT_Node->IUT_Prioridade;
    IUT_Nome       = pIUT_Node->IUT_Nome;
}

