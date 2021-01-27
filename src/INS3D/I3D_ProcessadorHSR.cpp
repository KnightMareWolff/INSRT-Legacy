/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_ProcessadorHSR.h"

//-----------------------------------------------------------------------------
// Nome : CI3DProcessadorHSR () (Constructor)
// Desc : Construtor da Classe CI3DProcessadorHSR
//-----------------------------------------------------------------------------
CI3DProcessadorHSR::CI3DProcessadorHSR()
{
    mPrimitivoResultante = NULL;
}

//-----------------------------------------------------------------------------
// Nome : ~CI3DProcessadorHSR () (Destrutor)
// Desc :  Destrutor da Classe CI3DProcessadorHSR
//-----------------------------------------------------------------------------
CI3DProcessadorHSR::~CI3DProcessadorHSR()
{
    Finaliza();
}

//-----------------------------------------------------------------------------
// Nome : Finaliza ()
// Desc : Limpa o processador para mais um processamento Batch.
//-----------------------------------------------------------------------------
void CI3DProcessadorHSR::Finaliza()
{
    mListaPrimitivos.clear();
    mPrimitivoResultante = NULL;
}

//-----------------------------------------------------------------------------
// Nome : AddPrimitivo ()
// Desc : Adiciona um Primitivo Pronto para Processamento.
// Nota : Os Primitivos passados Não serão alterados , eles somente são usados
//        para gerar um novo objeto resultante do Processamento.
//-----------------------------------------------------------------------------
bool CI3DProcessadorHSR::AddPrimitivo( CI3DModelo * pPrimitivo )
{
    try
    {
        if (mListaPrimitivos.size() >= (mListaPrimitivos.capacity() - 1))
        {
            mListaPrimitivos.reserve( mListaPrimitivos.size() + BLOCO_MEMORIA );
        }

        mListaPrimitivos.push_back( pPrimitivo );
    }
    catch (...)
    {
        mListaPrimitivos.clear();
        return false;
    }
    return true;
}

//-----------------------------------------------------------------------------
// Nome : Processa ()
// Desc : Processa a Remoção de Todas as Superfícies escondidas
//-----------------------------------------------------------------------------
bool CI3DProcessadorHSR::Processa()
{
    int              i, a, b;
    CI3DArvoreBsp ** BSPTrees  = NULL;
    long             ContPrimitivos = mListaPrimitivos.size();
    CIMTBorda        BordaA, BordaB;


    try
    {
        //Aloca Memoria para a Lista de BSP´s
        BSPTrees = new CI3DArvoreBsp*[ ContPrimitivos ];
        if (!BSPTrees) throw false;

        //Seta todos os Ponteiros como NULL(Verificar retirada devido a Multiplataforma)
        ZeroMemory( BSPTrees, ContPrimitivos * sizeof(CI3DArvoreBsp*));

        //Aloca Primitivo Resultante
        mPrimitivoResultante = new CI3DModelo;
        if (!mPrimitivoResultante) throw false;

        // Constroi uma BSP para cada Primitivo(BSP Sem SPLIT!!!).
        for ( i = 0; i < ContPrimitivos; i++ )
        {
            //Aloca Nova Arvore
            BSPTrees[i] = new CI3DArvoreBsp();
            if (!BSPTrees[i])
            {
                throw false;
            }

            BSPTrees[i]->I3D_TpArvore            = BSP_TYPE_NONSPLIT;
            BSPTrees[i]->I3D_RemoveFolhasIlegais = true;
            BSPTrees[i]->I3D_HeuristicaDivisao   = 3.0f;
            BSPTrees[i]->I3D_AcumuladorDivisores = 60;

            //Adiciona faces no primitivo prontas para serem compiladas
            if (!BSPTrees[i]->AdicionaFaces(mListaPrimitivos[i]->I3D_Mesh->Faces,
                                            mListaPrimitivos[i]->I3D_Mesh->I3D_QtdFaces, true ))
            {
                throw false;
            }

            //Compila a árvore
            BSPTrees[i]->CompilaArvore();

        }

        //Agora realiza as Operações de União(CSG) utilizando Clipping
        for ( a = 0; a < ContPrimitivos; a++ )
        {
             //Pula Arvores Vazias
            if (!BSPTrees[a] || BSPTrees[a]->PegaQtdFaces() == 0) continue;

            //Clipa Contra todos os outros Primitivos
            for ( b = 0; b < ContPrimitivos; b++ )
            {
                // Pula Primitivos Nulos (Ex:. Que já Foram Clipados)
                if (!BSPTrees[b] || BSPTrees[b]->PegaQtdFaces() == 0) continue;

                // Impossível Unir-se a si mesmo...Afff
                if (a == b) continue;

                // Pula se Eles Não se Intersectam (O Teste de Borda Requere Tolerancia pequena...)
                BordaA = BSPTrees[a]->PegaBorda();
                BordaB = BSPTrees[b]->PegaBorda();
                if ( !BordaA.CruzamentoBorda( BordaB, CIMTVetor( 0.1f, 0.1f, 0.1f ) ) ) continue;
                if ( !BSPTrees[a]->CruzamentoArvore( BSPTrees[b] ) ) continue;

                //Realiza o Clipping entre A e B e Vice-Versa
                BSPTrees[a]->ClipTree( BSPTrees[b], false  , false );
                BSPTrees[b]->ClipTree( BSPTrees[a], false  , false );

                //Repara Divisões Desnecessárias
                BSPTrees[a]->ReparaDivisao();
                BSPTrees[b]->ReparaDivisao();

            }

            // Coloca as faces resultantes da arvore A no Primitivo Resultante
            if(!(mPrimitivoResultante->I3D_Mesh->ConstroiBSP( BSPTrees[a], false )))
            {
                throw false;
            }

            // A arvore já foi Clipada por todos...portanto...Já Era!
            delete BSPTrees[a];
            BSPTrees[a] = NULL;
        }

        mPrimitivoResultante->I3D_Mesh->ConstroiBuffersSH();

    }

    catch (...)
    {
        if ( BSPTrees )
        {
            for ( i = 0; i < ContPrimitivos; i++ ) if ( BSPTrees[i] ) delete BSPTrees[i];
            delete []BSPTrees;

        }

        if ( mPrimitivoResultante ) { delete mPrimitivoResultante; mPrimitivoResultante = NULL; }

        return false;

    }

    //Limpa a Sujeira...
    if ( BSPTrees )
    {
        for ( i = 0; i < ContPrimitivos; i++ ) if ( BSPTrees[i] ) delete BSPTrees[i];
        delete []BSPTrees;
    }

    return true;

}

//-----------------------------------------------------------------------------
// Nome : GetResultMesh ()
// Desc : Retrieves the resulting mesh build during the HSR process.
//-----------------------------------------------------------------------------
CI3DModelo* CI3DProcessadorHSR::PegaPrimitivoResultante() const
{
    return mPrimitivoResultante;
}

