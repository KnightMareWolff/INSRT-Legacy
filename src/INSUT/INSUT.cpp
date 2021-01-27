/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "INSUT.h"


INSUT::INSUT()
{
    pINSUTPath = new CIUTGerenciadorPath;
}

void INSUT::SetaAppPaths(QString pPathApp, QString pPathWorld)
{
    pINSUTPath->SetaAppPaths(pPathApp,pPathWorld);
}
