/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CIUTPARAMETROTRIGGER_H
#define CIUTPARAMETROTRIGGER_H

#include "IUT_GlobalDef.h"

class CIUTParametroTrigger
{
public:
    CIUTParametroTrigger();
    CIUTParametroTrigger(int pTipoParametro, int       pDado);
    CIUTParametroTrigger(int pTipoParametro, CIMTVetor pDado);

    int       IUT_TipoParametro;
    int       IUT_DadoInt;
    float     IUT_DadoFloat;
    double    IUT_DadoDouble;
    char*     IUT_DadoChar;
    CIMTVetor IUT_DadoVetor;
};

#endif // CIUTPARAMETROTRIGGER_H
