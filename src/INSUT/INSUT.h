/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef INSUT_H
#define INSUT_H

#include "IUT_GlobalDef.h"
#include "IUT_Node.h"
#include "IUT_Lista.h"
#include "IUT_Grafo.h"
#include "IUT_CarregadorArquivos.h"
#include "IUT_GerenciadorPath.h"
#include "IUT_FilaPrioridade.h"
#include "IUT_Trigger.h"

class INSUT
{

public:
    INSUT();

    void SetaAppPaths(QString pPathApp,QString pPathWorld);
    /***************************************************/
    /*Contextos globais de Inicialização de Utilitarios*/
    /***************************************************/
    CIUTGerenciadorPath  *pINSUTPath;//Interface Inicialização Gerenciamneto Cenario
};

#endif // INSUT_H
