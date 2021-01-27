/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CIUTTRIGGER_H
#define CIUTTRIGGER_H

#include "IUT_GlobalDef.h"
#include "IUT_ParametroTrigger.h"
#include "IUT_FilaPrioridade.h"
#include "IUT_Node.h"

class CIUTTrigger : public CIUTNode
{
public:
    CIUTTrigger(                                       );
    CIUTTrigger(int pTipo,QString pNome,QString pFuncao);
   ~CIUTTrigger(                                       );

    int                           IUT_TipoTrigger;
    int                           IUT_EstadoTrigger;
    QString                       IUT_NomeTrigger;
    QString                       IUT_FuncaoTrigger;
    vector<CIUTParametroTrigger>  IUT_ParametrosTrigger;

    void Ativar();
    void Desativar();
    void Executando();
};

#endif // CIUTTRIGGER_H
