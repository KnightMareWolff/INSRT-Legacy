/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CIUTGERENCIADORPATH_H
#define CIUTGERENCIADORPATH_H

#include "IUT_GlobalDef.h"

class CIUTGerenciadorPath
{
public:
    CIUTGerenciadorPath();

    void SetaAppPaths(QString pPathApp,QString pPathWorld);

    static QString IUT_PathApp;
    static QString IUT_PathWorld;
};

#endif // CIUTGERENCIADORPATH_H
