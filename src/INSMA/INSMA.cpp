/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "INSMA.h"

CIMAMaterialManager*  INSMA::pINSMAMaterialManager = NULL;
CIMATextureManager*   INSMA::pINSMATextureManager  = NULL;

INSMA::INSMA()
{

}

bool INSMA::Inicializa()
{
    pINSMAMaterialManager = new CIMAMaterialManager();
    pINSMATextureManager  = new CIMATextureManager();
    return true;
}
