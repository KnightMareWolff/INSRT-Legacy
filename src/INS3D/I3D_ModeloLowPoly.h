/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CI3DMODELOLOWPOLY_H
#define CI3DMODELOLOWPOLY_H

#include "I3D_Primitivo.h"
#include "I3D_ArvoreBsp.h"
#include "I3D_ModeloHierarquico.h"
#include "I3D_ProcessadorHSR.h"

class CI3DModeloLowPoly : public CI3DPrimitivo , public INSMA
{
public:
    CI3DModeloLowPoly(                                    );
    CI3DModeloLowPoly(QString   pNomeArquivo              );
    CI3DModeloLowPoly(CIMTVetor pPos                      );
    CI3DModeloLowPoly(CIMTVetor pPos,QString mNomeMaterial);

    bool AddGeometria(CI3DModeloHierarquico  pModelo       );
    bool AddBorda    (bool  bTrue                          );
    void Compila     (                                     );
    void CalculaBorda(                                     );

    void Render      (CIMTVetor pPos         ,
                      int       pRenderMode  ,
                      int       pPolygonMode ,
                      int       pMaterialMode,
                      int       pShadingMode ,
                      int       pGeometryMode);//operação de Renderização

private:
    CI3DArvoreBsp       *  mBsp                ;
    CI3DProcessadorHSR  *  mHSR                ;
    vector<int>            mMateriaisLowPoly   ;
    vector<CI3DModelo   *> mGeometriaLowPoly   ;
    CI3DPrimitivo       *  mPrimitivoResultante;
};

#endif // CI3DMODELOLOWPOLY_H
