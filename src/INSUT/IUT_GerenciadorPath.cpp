/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_GerenciadorPath.h"

QString CIUTGerenciadorPath::IUT_PathApp  =NULL;
QString CIUTGerenciadorPath::IUT_PathWorld=NULL;

CIUTGerenciadorPath::CIUTGerenciadorPath()
{

}

void CIUTGerenciadorPath::SetaAppPaths(QString pPathApp, QString pPathWorld)
{
    IUT_PathApp   = pPathApp;
    IUT_PathWorld = pPathWorld;
}
