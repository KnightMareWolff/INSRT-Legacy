/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef I3D_NOBSP_H
#define I3D_NOBSP_H


#include "I3D_GlobalDef.h"
#include "I3D_FaceBsp.h"

class CI3DNoBsp
{

public:

  long      Plano      ;
  long      I3D_Frente ;
  long      I3D_Atras  ;
  CIMTBorda I3D_Borda  ;


public:

             CI3DNoBsp( );
            ~CI3DNoBsp( );

  void CalculaBordaNo(CI3DFaceBsp *ListaFaces,bool kbcPermiteAcumulo);

};

#endif // I3D_NOBSP_H
