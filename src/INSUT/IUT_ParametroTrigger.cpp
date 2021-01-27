/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_ParametroTrigger.h"

CIUTParametroTrigger::CIUTParametroTrigger()
{

}

CIUTParametroTrigger::CIUTParametroTrigger(int pTipoParametro, int pDado)
{
   IUT_TipoParametro = pTipoParametro;
   IUT_DadoInt       = pDado;
}

CIUTParametroTrigger::CIUTParametroTrigger(int pTipoParametro, CIMTVetor pDado)
{
   IUT_TipoParametro = pTipoParametro;
   IUT_DadoVetor     = pDado;
}
