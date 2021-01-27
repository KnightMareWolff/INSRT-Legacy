/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "I3D_ProcessadorCSG.h"

//-----------------------------------------------------------------------------
// Nome : CI3DProcessadorHSR () (Constructor)
// Desc : Construtor da Classe CI3DProcessadorHSR
//-----------------------------------------------------------------------------
CI3DProcessadorCSG::CI3DProcessadorCSG()
{

}

//-----------------------------------------------------------------------------
// Nome : ~CI3DProcessadorHSR () (Destrutor)
// Desc :  Destrutor da Classe CI3DProcessadorHSR
//-----------------------------------------------------------------------------
CI3DProcessadorCSG::~CI3DProcessadorCSG()
{

}

//-----------------------------------------------------------------------------
// Nome : ProcessaUniao ()
// Desc : Processa a União entre dois Primitivos
//-----------------------------------------------------------------------------
CI3DPrimitivo* CI3DProcessadorCSG::ProcessaUniao(CI3DPrimitivo* pPrimA,CI3DPrimitivo* pPrimB)
{
    CI3DArvoreBsp * BSPrimA       = NULL;
    CI3DArvoreBsp * BSPrimB       = NULL;
    CI3DPrimitivo * NovoPrimitivo = NULL;
    CIMTBorda       BordaA ,
                    BordaB ;

    BSPrimA = new CI3DArvoreBsp();
    BSPrimB = new CI3DArvoreBsp();

    //seta parametros de compilação
    BSPrimA->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
    BSPrimA->I3D_RemoveFolhasIlegais = true;
    BSPrimA->I3D_HeuristicaDivisao   = 3.0f;
    BSPrimA->I3D_AcumuladorDivisores = 60;
    //seta parametros de compilação
    BSPrimB->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
    BSPrimB->I3D_RemoveFolhasIlegais = true;
    BSPrimB->I3D_HeuristicaDivisao   = 3.0f;
    BSPrimB->I3D_AcumuladorDivisores = 60;

    //Compilação BSP somente esta aceitando LeftHand Meshs
    if(pPrimA->I3D_Mesh->ConstructionMode != IGL_POLYMODE_LEFT ||
       pPrimB->I3D_Mesh->ConstructionMode != IGL_POLYMODE_LEFT ) return NULL;

    //Como Poligonos Clowise geram Normais voltadas para dentro não representam
    //um solido, invertemos as normais do modelo.
    if(pPrimA->I3D_Mesh->WindingMode == IGL_WINMODE_CW){pPrimA->I3D_Mesh->InverteNormais();}
    if(pPrimB->I3D_Mesh->WindingMode == IGL_WINMODE_CW){pPrimB->I3D_Mesh->InverteNormais();}

    //Adiciona faces no primitivo prontas para serem compiladas
    BSPrimA->AdicionaFaces(pPrimA->I3D_Mesh->Faces, pPrimA->I3D_Mesh->I3D_QtdFaces, true );
    BSPrimB->AdicionaFaces(pPrimB->I3D_Mesh->Faces, pPrimB->I3D_Mesh->I3D_QtdFaces, true );

    //Compila a árvore
    BSPrimA->CompilaArvore();
    BSPrimB->CompilaArvore();

    //Se Eles Não se Intersectam Retorna Nulo
    BordaA = BSPrimA->PegaBorda();
    BordaB = BSPrimB->PegaBorda();

    if (BSPrimA->PegaQtdFaces() == 0) return NULL;
    if (BSPrimB->PegaQtdFaces() == 0) return NULL;
    if ( !BordaA.CruzamentoBorda( BordaB, CIMTVetor( 0.1f, 0.1f, 0.1f ) ) ) return NULL;
    if ( !BSPrimA->CruzamentoArvore( BSPrimB ) ) return NULL;

    //Realiza o Clipping entre A e B e Vice-Versa
    BSPrimA->ClipTree( BSPrimB, false  , true   );
    BSPrimB->ClipTree( BSPrimA, false  , false  );

    //Repara Divisões Desnecessárias
    BSPrimA->ReparaDivisao();
    BSPrimB->ReparaDivisao();

    //Aloca e Constroi o Novo primitivo baseado no processamento resultante.
    NovoPrimitivo = new CI3DPrimitivo();

    NovoPrimitivo->I3D_Mesh->ConstroiBSP(BSPrimA,false);
    NovoPrimitivo->I3D_Mesh->ConstroiBSP(BSPrimB,false);

    NovoPrimitivo->I3D_Mesh->I3D_Material = pPrimA->I3D_Mesh->I3D_Material;
    NovoPrimitivo->I3D_Mesh->SetaShader(pPrimA->I3D_Mesh->I3D_MeshProgramId);
    NovoPrimitivo->I3D_Mesh->ConstroiBuffersSH();

    //limpa as arvores alocadas
    delete BSPrimA;
    delete BSPrimB;

    //devolve o resultado
    return NovoPrimitivo;
}

//-----------------------------------------------------------------------------
// Nome : ProcessaUniao ()
// Desc : Processa a União entre dois Primitivos
//-----------------------------------------------------------------------------
CI3DPrimitivo* CI3DProcessadorCSG::ProcessaIntercec(CI3DPrimitivo* pPrimA,CI3DPrimitivo* pPrimB)
{
    CI3DArvoreBsp * BSPrimA       = NULL;
    CI3DArvoreBsp * BSPrimB       = NULL;
    CI3DPrimitivo * NovoPrimitivo = NULL;
    CIMTBorda       BordaA ,
                    BordaB ;

    BSPrimA = new CI3DArvoreBsp();
    BSPrimB = new CI3DArvoreBsp();

    //seta parametros de compilação
    BSPrimA->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
    BSPrimA->I3D_RemoveFolhasIlegais = true;
    BSPrimA->I3D_HeuristicaDivisao   = 3.0f;
    BSPrimA->I3D_AcumuladorDivisores = 60;
    //seta parametros de compilação
    BSPrimB->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
    BSPrimB->I3D_RemoveFolhasIlegais = true;
    BSPrimB->I3D_HeuristicaDivisao   = 3.0f;
    BSPrimB->I3D_AcumuladorDivisores = 60;

    //Compilação BSP somente esta aceitando LeftHand Meshs
    if(pPrimA->I3D_Mesh->ConstructionMode != IGL_POLYMODE_LEFT ||
       pPrimB->I3D_Mesh->ConstructionMode != IGL_POLYMODE_LEFT ) return NULL;

    //Como Poligonos Clowise geram Normais voltadas para dentro não representam
    //um solido, invertemos as normais do modelo.
    if(pPrimA->I3D_Mesh->WindingMode == IGL_WINMODE_CW){pPrimA->I3D_Mesh->InverteNormais();}
    if(pPrimB->I3D_Mesh->WindingMode == IGL_WINMODE_CW){pPrimB->I3D_Mesh->InverteNormais();}


    //Adiciona faces no primitivo prontas para serem compiladas
    BSPrimA->AdicionaFaces(pPrimA->I3D_Mesh->Faces, pPrimA->I3D_Mesh->I3D_QtdFaces, true );
    BSPrimB->AdicionaFaces(pPrimB->I3D_Mesh->Faces, pPrimB->I3D_Mesh->I3D_QtdFaces, true );

    //Compila a árvore
    BSPrimA->CompilaArvore();
    BSPrimB->CompilaArvore();

    //Se Eles Não se Intersectam Retorna Nulo
    BordaA = BSPrimA->PegaBorda();
    BordaB = BSPrimB->PegaBorda();

    if (BSPrimA->PegaQtdFaces() == 0) return NULL;
    if (BSPrimB->PegaQtdFaces() == 0) return NULL;
    if ( !BordaA.CruzamentoBorda( BordaB, CIMTVetor( 0.1f, 0.1f, 0.1f ) ) ) return NULL;
    if ( !BSPrimA->CruzamentoArvore( BSPrimB ) ) return NULL;

    //Realiza o Clipping entre A e B e Vice-Versa
    BSPrimA->ClipTree( BSPrimB, true  , false );
    BSPrimB->ClipTree( BSPrimA, true  , true  );

    //Repara Divisões Desnecessárias
    BSPrimA->ReparaDivisao();
    BSPrimB->ReparaDivisao();

    //Aloca e Constroi o Novo primitivo baseado no processamento resultante.
    NovoPrimitivo = new CI3DPrimitivo();

    NovoPrimitivo->I3D_Mesh->ConstroiBSP(BSPrimA,false);
    NovoPrimitivo->I3D_Mesh->ConstroiBSP(BSPrimB,false);
    NovoPrimitivo->I3D_Mesh->I3D_Material = pPrimA->I3D_Mesh->I3D_Material;
    NovoPrimitivo->I3D_Mesh->SetaShader(pPrimA->I3D_Mesh->I3D_MeshProgramId);
    NovoPrimitivo->I3D_Mesh->ConstroiBuffersSH();

    //limpa as arvores alocadas
    delete BSPrimA;
    delete BSPrimB;

    //devolve o resultado
    return NovoPrimitivo;
}

//-----------------------------------------------------------------------------
// Nome : ProcessaUniao ()
// Desc : Processa a União entre dois Primitivos
//-----------------------------------------------------------------------------
CI3DPrimitivo* CI3DProcessadorCSG::ProcessaExtrusao(CI3DPrimitivo* pPrimA,CI3DPrimitivo* pPrimB)
{
    CI3DArvoreBsp * BSPrimA       = NULL;
    CI3DArvoreBsp * BSPrimB       = NULL;
    CI3DArvoreBsp * BSPtemp       = NULL;
    CI3DPrimitivo * NovoPrimitivo = NULL;
    CIMTBorda       BordaA ,
                    BordaB ;

    BSPrimA = new CI3DArvoreBsp();
    BSPrimB = new CI3DArvoreBsp();

    //seta parametros de compilação
    BSPrimA->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
    BSPrimA->I3D_RemoveFolhasIlegais = true;
    BSPrimA->I3D_HeuristicaDivisao   = 3.0f;
    BSPrimA->I3D_AcumuladorDivisores = 60;
    //seta parametros de compilação
    BSPrimB->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
    BSPrimB->I3D_RemoveFolhasIlegais = true;
    BSPrimB->I3D_HeuristicaDivisao   = 3.0f;
    BSPrimB->I3D_AcumuladorDivisores = 60;

    //Compilação BSP somente esta aceitando LeftHand Meshs
    if(pPrimA->I3D_Mesh->ConstructionMode != IGL_POLYMODE_LEFT ||
       pPrimB->I3D_Mesh->ConstructionMode != IGL_POLYMODE_LEFT ) return NULL;

    //Como Poligonos Clowise geram Normais voltadas para dentro não representam
    //um solido, invertemos as normais do modelo.
    if(pPrimA->I3D_Mesh->WindingMode == IGL_WINMODE_CW){pPrimA->I3D_Mesh->InverteNormais();}
    if(pPrimB->I3D_Mesh->WindingMode == IGL_WINMODE_CW){pPrimB->I3D_Mesh->InverteNormais();}

    //Adiciona faces no primitivo prontas para serem compiladas
    BSPrimA->AdicionaFaces(pPrimA->I3D_Mesh->Faces, pPrimA->I3D_Mesh->I3D_QtdFaces, true );
    BSPrimB->AdicionaFaces(pPrimB->I3D_Mesh->Faces, pPrimB->I3D_Mesh->I3D_QtdFaces, true );

    //Compila a árvore
    BSPrimA->CompilaArvore();
    BSPrimB->CompilaArvore();

    //Se Eles Não se Intersectam Retorna Nulo
    BordaA = BSPrimA->PegaBorda();
    BordaB = BSPrimB->PegaBorda();

    if (BSPrimA->PegaQtdFaces() == 0) return NULL;
    if (BSPrimB->PegaQtdFaces() == 0) return NULL;
    if ( !BordaA.CruzamentoBorda( BordaB, CIMTVetor( 0.1f, 0.1f, 0.1f ) ) ) return NULL;
    //if ( !BSPrimA->CruzamentoArvore( BSPrimB ) ) return NULL;

    //Realiza o Clipping entre A e B e Vice-Versa
    BSPrimA->ClipTree( BSPrimB, true  , true   );
    //Inverte direção das faces
    BSPrimA->Inverte();
    //Realiza o Cliping com a arvore invertida
    BSPrimB->ClipTree( BSPrimA, false , false  );

    //Repara Divisões Desnecessárias
    BSPrimA->ReparaDivisao();
    BSPrimB->ReparaDivisao();

    //Aloca e Constroi o Novo primitivo baseado no processamento resultante.
    NovoPrimitivo = new CI3DPrimitivo();

    NovoPrimitivo->I3D_Mesh->ConstroiBSP(BSPrimA,false);
    NovoPrimitivo->I3D_Mesh->ConstroiBSP(BSPrimB,false);
    NovoPrimitivo->I3D_Mesh->I3D_Material = pPrimA->I3D_Mesh->I3D_Material;
    NovoPrimitivo->I3D_Mesh->SetaShader(pPrimA->I3D_Mesh->I3D_MeshProgramId);
    NovoPrimitivo->I3D_Mesh->InverteWindingMode();
    NovoPrimitivo->I3D_Mesh->InverteNormais();
    NovoPrimitivo->I3D_Mesh->ConstroiBuffersSH();

    //limpa as arvores alocadas
    delete BSPrimA;
    delete BSPrimB;

    //devolve o resultado
    return NovoPrimitivo;
}

