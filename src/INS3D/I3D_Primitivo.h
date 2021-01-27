/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef I3D_PRIMITIVO_H
#define I3D_PRIMITIVO_H

#include "I3D_Mesh.h"

class CI3DPrimitivo : public INSGL
{
public:
    /*********************************/
    /*Atributos Publicos Vetoriais   */
    /*********************************/
    CIMTVetor           I3D_View     ;//View
    CIMTVetor           I3D_Up       ;//Up Vector
    CIMTVetor           I3D_Pos      ;//Posição
    CIMTVetor           I3D_RefPos   ;//Projeção necessaria para translate
    CIMTVetor           I3D_Rot      ;//Quantidade em Rad, da rotacao a ser aplicada
    CIMTVetor           I3D_RefRot   ;//Ponto de Controle para rotação
    CIMTVetor           I3D_Scl      ;//Escala a ser aplicada
    CIMTVetor           I3D_RefScl   ;//Ponto de Controle para escala
    CIMTVetor           I3D_Dim      ;//Dimensões(x=largura,y=altura,z=profundidade)
    /*********************************/
    /*Atributos Publicos Matriciais  */
    /*********************************/
    CIMTMatriz          I3D_MtxTransf;//Matriz Model View
    CIMTMatriz          I3D_MtxLocal ;//Matriz Transformação Local
    /*********************************/
    /*Atributos Publicos Booleanos   */
    /*********************************/
    bool                I3D_Pickable   ;//Sinaliza que o Primitivo pode ser selecionado
    bool                I3D_Selecionado;//Informa se o primitivo está selecionado ou não.
    /*********************************/
    /*Atributos Publicos Inteiros    */
    /*********************************/
    int                 I3D_TpPrimitivo ;//Tipo de Primitivo
    int                 I3D_IdPrimitivo ;//Id de atribuição temporario para picking
    int                 I3D_Shader      ;//Shader associado ao primitivo
    /*********************************/
    /*Mesh combinado com o primitivo */
    /*********************************/
    CI3DMesh           *I3D_Mesh;

    CI3DPrimitivo(                  );
    CI3DPrimitivo(CIMTVetor pI3D_Pos);
   ~CI3DPrimitivo(                  );

    /*****************************************************/
    /*Métodos Virtuais para o Polimorfismo de primitivos */
    /*****************************************************/
    virtual void Render          (int pRenderMode , int pPolygonMode , int pShadingMode);
    virtual void Update          (                                                     );
    virtual void Build           (                                                     );
    virtual bool Collision       (CI3DPrimitivo *pI3D_Primitivo, float pI3D_TimeElapsed);
    /*************************************************/
    /*Metodos publicos para operações com primitivos */
    /*************************************************/
     void Translate       (CIMTVetor  pTransf,bool Incremento                         );
     void Rotate          (bool pControlPoint,CIMTVetor  pTransf,CIMTVetor  pControl  );
     void Scale           (bool pControlPoint,CIMTVetor  pTransf,CIMTVetor  pControl  );
     void SetaSelecao     (bool    pFlagSelecionavel                                  );
     void SetaIdSelecao   (int     pIdSelecao                                         );
     void SetaSelecionado (bool    pFlagSelecionado                                   );
};

#endif // I3D_PRIMITIVO_H
