/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CIUTFILAPRIORIDADE_H
#define CIUTFILAPRIORIDADE_H

#include "IUT_GlobalDef.h"
#include "IUT_Node.h"

class CIUTFilaPrioridade
{
public:
     CIUTFilaPrioridade();
    ~CIUTFilaPrioridade();

    void              limpa    (                            );
    bool              vazio    (                            );

    void              entrafila(CIUTNode*    pIUT_Node      ,
                                int          pIUT_Prioridade,
                                QString      pIUT_Nome      );

    CIUTNode*         saifila  (                            );
    CIUTNode*         busca    (QString      pIUT_Nome      );
    CIUTNode*         busca    (unsigned int pIUT_Id        );
    unsigned int      Tam      (                            );

private:

    unsigned int IUT_Tamanho;
    CIUTNode    *IUT_Inicio ;
    CIUTNode    *IUT_Fim    ;
    QString      IUT_Nome   ;
};

#endif // CIUTFILAPRIORIDADE_H
