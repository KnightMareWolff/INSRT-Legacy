/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_MODELO_H
#define I3D_MODELO_H

#include "I3D_Primitivo.h"

class CI3DModelo : public CI3DPrimitivo , public INSMA
{
public:

    QString mNomeModelo;

    CI3DModelo(                                                                         );
    CI3DModelo(QString   pI3D_NomeArquivo,QString pI3D_NomeModelo,bool pI3D_MakeLeftHand);
   ~CI3DModelo(                                                                         );

private:

    CIUTCarregadorArquivos *importador;
};

#endif // I3D_MODELO_H
