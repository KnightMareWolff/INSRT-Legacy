/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IUT_NODE_H
#define IUT_NODE_H

#include "IUT_GlobalDef.h"

class CIUTNode
{
public:
    CIUTNode(                   );
    CIUTNode(CIUTNode* pIUT_Node);

public:
    unsigned int  IUT_TpNode    ;
    CIUTNode     *IUT_Proximo   ;
    CIUTNode     *IUT_Anterior  ;
    int           IUT_Prioridade;
    QString       IUT_Nome      ;
};

#endif // IUT_NODE_H
