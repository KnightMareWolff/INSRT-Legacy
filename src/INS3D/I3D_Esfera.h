/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_ESFERA_H
#define I3D_ESFERA_H

#include "I3D_Primitivo.h"

class CI3DEsfera : public CI3DPrimitivo
{
public:
    CI3DEsfera();
    CI3DEsfera(CIMTVetor pPos);

private:
    void Build();
    void BuildTextureCoord();
};

#endif // I3D_ESFERA_H
