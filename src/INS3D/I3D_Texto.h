/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_TEXTO_H
#define I3D_TEXTO_H

#include "I3D_Painel.h"
#include "I3D_Fonte.h"

class CI3DTexto: public CI3DPainel
{
public:
    CI3DTexto(CI3DFonte *pFonte,int nLinhas,int nColunas);
    CI3DTexto(CI3DFonte *pFonte,QString pTexto,int iTamChar);

protected:
    void Build              (    );
private:
    vector<int>  iTexto;
    CI3DFonte   *cFonte;

    int iTamCaracter;
    int iQtdCaracter;
    int iQtdLinhas  ;
    int iQtdColunas ;
};

#endif // I3D_TEXTO_H
