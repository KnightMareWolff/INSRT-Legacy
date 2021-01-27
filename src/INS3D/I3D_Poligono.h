/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_POLIGONO_H
#define I3D_POLIGONO_H

#include "I3D_GlobalDef.h"
#include "I3D_Vertice.h"

/************************************************************/
/************************************************************/
class CI3DPoligono : public INSGL
{


public:

   /*********************************/
   /*Atributos para Shaders         */
   /*********************************/
   IGLVertexBuffer   *I3D_VertexBuffer   ;
   GLuint            *I3D_VertexIndices  ;
   GLuint            *I3D_IndicesSkin    ;
   GLuint             I3D_VboIds[3]      ;
   FeedBackData      *I3D_FeedbackBuffer ;


   /*****************************************/
   /*Atributos para a edição de Polígonos   */
   /*****************************************/
   CI3DVertice  	 *Vertices    ;
   int               *Indices     ;


   /*********************************************/
   /*Atributos Comuns entre PF e Shaders        */
   /*********************************************/
   GLuint            I3D_QtdVertices  ;
   GLuint            I3D_QtdIndices   ;
   CIMTBorda         I3D_BordaPoligono;

   //Em algumas situações especificas precisamos do sentido no poligono(BSP e Planos)
   int               PolyWindingMode  ;

public:

   /**************/
   /*Contrutores */
   /**************/
    CI3DPoligono(                               );
    CI3DPoligono(const CI3DPoligono &i3dPoligono);
   ~CI3DPoligono(                               );

   /********************************/
   /*Inclusao de Vertices e Indices*/
   /********************************/
   int          AdicionaVertices(long i3dQtdVert,int pRenderType);
   int          AdicionaIndices (long i3dQtdInd                 );
   long         InsereVertice   (unsigned long nVertexPos                );

   /****************************/
   /*Renderizacao              */
   /****************************/
   void         Renderiza        (int iProgramId,
                                  int iRenderMode,
                                  int iPolygonMode,
                                  int iShadingMode ,
                                  int iGeometryMode);
   /****************************/
   /*Metodos Utilitarios       */
   /****************************/
   void         LimpaVertices      (                                        );
   CIMTVetor    CalculaNormal      (bool      bUpdate                       );
   bool         CalculaNormalSmooth(CIMTVetor centro                        );
   CIMTVetor    InverteNormal      (bool      bUpdate                       );
   bool         InvertePoligono    (                                        );
   bool         CalculaTangentes   (                                        );
   void         Triangulariza      (                                        );
   void         Quadrangulariza    (                                        );
   void         HabilitaVertices   (                                        );
   bool         EstaContido        (CIMTVetor     i3dVetor                  );
   bool         Existe             (CI3DVertice   i3dVertice                );
   bool         Degenerado         (                                        ) const;
   bool         Convexo            (                                        );
   bool         Divide             (const CIMTPlano& imtPlano               ,
                                    CI3DPoligono *i3dPoligonoFrente         ,
                                    CI3DPoligono *i3dPoligonoAtras          );
   bool         GeraPoligono       ( const CIMTPlano& Plano                 ,
                                     const CIMTBorda& Borda                 );
   /**********************************************/
   /*Metodos Utilitarios especificos para Shaders*/
   /**********************************************/
   void         PreencheBuffers    (                                        );
};

#endif // I3D_POLIGONO_H
