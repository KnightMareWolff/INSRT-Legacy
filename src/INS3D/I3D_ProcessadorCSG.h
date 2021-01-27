/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef I3D_PROCESSADORCSG_H
#define I3D_PROCESSADORCSG_H

#include "I3D_GlobalDef.h"
#include "I3D_ArvoreBsp.h"
#include "I3D_Primitivo.h"

class CI3DProcessadorCSG
{
public:
            CI3DProcessadorCSG();
   virtual ~CI3DProcessadorCSG();
   //-------------------------------------------------------------------------
   // Public Functions for This Class.
   //-------------------------------------------------------------------------
   CI3DPrimitivo*  ProcessaUniao   (CI3DPrimitivo* pPrimA,CI3DPrimitivo* pPrimB);
   CI3DPrimitivo*  ProcessaIntercec(CI3DPrimitivo* pPrimA,CI3DPrimitivo* pPrimB);
   CI3DPrimitivo*  ProcessaExtrusao(CI3DPrimitivo* pPrimA,CI3DPrimitivo* pPrimB);
};


#endif // CI3DPROCESSADORCSG_H
