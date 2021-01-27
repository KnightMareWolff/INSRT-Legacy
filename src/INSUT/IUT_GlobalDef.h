/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IUT_GLOBALDEF_H
#define IUT_GLOBALDEF_H

#include <QtGui>
#include <list>
using namespace std;

#include "../INSMT/INSMT.h"
#include <../assimp/include/assimp/Importer.hpp>      // C++ importer interface
#include <../assimp/include/assimp/scene.h>           // Output data structure
#include <../assimp/include/assimp/postprocess.h>     // Post processing flags

//Defines globais de Utilitários

#define IUT_TRIGGER_PL_INPUT  0
#define IUT_TRIGGER_PL_UPDATE 1
#define IUT_TRIGGER_PL_INICIO 2
#define IUT_TRIGGER_PL_RENDER 3
#define IUT_TRIGGER_PL_CREATE 4
#define IUT_TRIGGER_PL_VOID   5

#define IUT_TRIGGER_TP_INT     0 //Tipo de Parametro int
#define IUT_TRIGGER_TP_QSTRING 1 //Tipo de Parametro QString
#define IUT_TRIGGER_TP_FLOAT   2 //Tipo de Parametro float
#define IUT_TRIGGER_TP_LONG    3 //Tipo de Parametro long
#define IUT_TRIGGER_TP_CHARP   4 //Tipo de Parametro char *
#define IUT_TRIGGER_TP_DOUBLE  5 //Tipo de Parametro double
#define IUT_TRIGGER_TP_SSTRING 6 //Tipo de Parametro std::string
#define IUT_TRIGGER_TP_VECTOR  7 //Tipo de Parametro CIMTVetor

#define IUT_TRIGGER_ST_ATIVO   0 //Estado de processamento Ativo
#define IUT_TRIGGER_ST_INATIVO 1 //Estado de processamento Inativo
#define IUT_TRIGGER_ST_EXEC    2 //Estado de processamento Executando
#define IUT_TRIGGER_ST_NULO    3 //Estado de processamento Nao foi executado ainda
#define IUT_TRIGGER_ST_RAIZ    4 //Estado de processamento Indicando raiz de fila

#define IUT_NODE_LINK_SIMPLES  0 //No com encadeamento Simples
#define IUT_NODE_LINK_DUPLO    1 //No duplamente encadeado
#define IUT_NODE_LINK_PRTY     2 //No duplamente encadeado COM PRIORIDADE



#endif // IUT_GLOBALDEF_H
