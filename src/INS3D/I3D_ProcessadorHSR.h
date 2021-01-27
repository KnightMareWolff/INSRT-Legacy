/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef I3D_PROCESSADORHSR_H
#define I3D_PROCESSADORHSR_H

#include "I3D_GlobalDef.h"
#include "I3D_ArvoreBsp.h"
#include "I3D_Modelo.h"

//-----------------------------------------------------------------------------
// Typedefs Utilizados apenas para simplificar a utilização de STL.
//-----------------------------------------------------------------------------
typedef std::vector<CI3DModelo   *>  VetorMesh   ;
typedef std::vector<CI3DArvoreBsp*>  vetorBSPTree;

class CI3DProcessadorHSR
{
public:

            CI3DProcessadorHSR();
   virtual ~CI3DProcessadorHSR();

   //-------------------------------------------------------------------------
   // Métodos Públicos da classe.
   //-------------------------------------------------------------------------
   bool            AddPrimitivo           (CI3DModelo *pPrimitivo      );
   CI3DModelo*     PegaPrimitivoResultante(                            ) const;
   bool            Processa               (                            );
   void            Finaliza               (                            );

private:
   VetorMesh       mListaPrimitivos;     //Lista de Primitivos para Processamento HSR.
   CI3DModelo*     mPrimitivoResultante; //Primitivo Unico como resultado de Processamento.
};

#endif // CI3DPROCESSADORHSR_H
