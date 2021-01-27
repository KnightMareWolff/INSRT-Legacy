/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IUT_LISTA_H
#define IUT_LISTA_H

#include "IUT_GlobalDef.h"
#include "IUT_Node.h"

class CIUTLista
{
public:
     CIUTLista(QString pIUT_NomeLista);
    ~CIUTLista(                      );

    void              Limpa    (                    );
    bool              Vazio    (                    );
    void              Add      (CIUTNode* pIUT_Node );
    void              Remove   (CIUTNode* pIUT_Node );
    void              Remove   (unsigned int pIUT_Id);
    CIUTNode*         Busca    (unsigned int pIUT_Id);
    unsigned int      Tam      (                    );

private:

    unsigned int  IUT_Tamanho  ;
    CIUTNode     *IUT_Inicio   ;
    CIUTNode     *IUT_Fim      ;
    QString       IUT_Nome     ;
};

#endif // IUT_LISTA_H
