/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_CUBO_H
#define I3D_CUBO_H
#include "I3D_Primitivo.h"

class CI3DCubo : public CI3DPrimitivo ,
                 public CIUTNode
{
public:
    explicit CI3DCubo(              );
    explicit CI3DCubo(CIMTVetor pPos);
    explicit CI3DCubo(CIMTVetor pPos,CIMTVetor pDim);
    explicit CI3DCubo(CIMTVetor pPos,CIMTVetor pDim,int pWindingMode);
    explicit CI3DCubo(CIMTVetor pPos,CIMTVetor pDim,int pWindingMode,int pConstructMode);

private:
    void Build();
};

#endif // I3D_CUBO_H
