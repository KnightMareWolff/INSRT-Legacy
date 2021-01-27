#include "I3D_ProcessadorRON.h"
#include "I3D_Portal.h"
#include "I3D_ProcessadorPRT.h"

//-----------------------------------------------------------------------------
// Nome : CI3DProcessadorHSR () (Constructor)
// Desc : Construtor da Classe CI3DProcessadorHSR
//-----------------------------------------------------------------------------
CI3DProcessadorRON::CI3DProcessadorRON()
{
    mPrimitivoResultante = NULL;
}

//-----------------------------------------------------------------------------
// Nome : ~CI3DProcessadorHSR () (Destrutor)
// Desc :  Destrutor da Classe CI3DProcessadorHSR
//-----------------------------------------------------------------------------
CI3DProcessadorRON::~CI3DProcessadorRON()
{
    Finaliza();
}

//-----------------------------------------------------------------------------
// Nome : Finaliza ()
// Desc : Limpa o processador para mais um processamento Batch.
//-----------------------------------------------------------------------------
void CI3DProcessadorRON::Finaliza()
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
bool CI3DProcessadorRON::AddPrimitivo( CI3DModelo * pPrimitivo )
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
bool CI3DProcessadorRON::Processa()
{
    ULONG               i, j;
    CI3DArvoreBsp       Tree;
    CI3DProcessadorPRT  ProcessPRT;

    bool       *LeavesVisited = NULL;


    try
    {

        Tree.I3D_TpArvore=0;
        Tree.I3D_RemoveFolhasIlegais=true;
        Tree.I3D_HeuristicaDivisao =3.0f;
        Tree.I3D_AcumuladorDivisores = 60;

        // Add all faces to the tree ready for compilation
        for ( i = 0; i < mListaPrimitivos.size(); i++ )
        {
            CI3DModelo * pModelo = mListaPrimitivos[i];
            if(!Tree.AdicionaFaces( pModelo->I3D_Mesh->Faces, pModelo->I3D_Mesh->I3D_QtdFaces, true ))
            {
                throw false;
            }
        }

        // Compile the BSP Tree
        Tree.CompilaArvore();

        // Compile the portals
        if(!ProcessPRT.Processa(&Tree ))
        {
            throw false;
        }

        // Find the initial beginning leaf
        long LeafStart = -1;

        LeafStart = Tree.ProcuraFolha( CIMTVetor( 3.0e+38f, 3.0e+38f, 3.0e+38f ) );

        // Return, but we will continue regardless.
        if ( LeafStart < 0 ) return false;

        // Allocate a set of tracking values
        LeavesVisited = new bool[Tree.PegaQtdFolhas()];
        if (!LeavesVisited) throw std::bad_alloc();

        // Set all leaves to unvisited initially
        ZeroMemory( LeavesVisited, Tree.PegaQtdFolhas() * sizeof(bool) );

        // Flood through the leaves
        PercorrePortais( &Tree, LeavesVisited, LeafStart );

        // Determine which polys should be discarded
        for ( i = 0; i < Tree.PegaQtdFolhas(); i++ )
        {
            // Skip if required
            //if ( LeavesVisited[ i ] != m_OptionSet.RemoveWet ) continue;
            if ( LeavesVisited[ i ] != false ) continue;//Prestar atencao!!!
            // Retrieve leaf for easy access
            CI3DFolhaBsp * pLeaf = Tree.PegaFolha(i);

            // Loop through and flag all polys as deleted
            for ( j = 0; j < pLeaf->I3D_FaceCount; j++ )
            {
                Tree.PegaFace( pLeaf->I3D_FaceIndices[j] )->Deleted = true;
            } // Next Face

        } // Next Leaf

        // Release used memory
        if ( LeavesVisited ) delete []LeavesVisited;

        // Count the number of un-deleted faces
        ULONG FaceCount = 0;
        for ( i = 0; i < Tree.PegaQtdFaces(); i++ )
        {
            CI3DFaceBsp * pFace = Tree.PegaFace( i );
            if (!pFace) continue;

            // Is this face active ?
            if ( !pFace->Deleted ) FaceCount++;

        } // Next Face

        if ( FaceCount > 0 )
        {
            // Allocate our result mesh
            mPrimitivoResultante = new CI3DModelo;
            if (!mPrimitivoResultante) throw std::bad_alloc();

            // Append all of the faces from our tree
            if ( !mPrimitivoResultante->I3D_Mesh->ConstroiBSP( &Tree, true ) ) throw false;

        } // End if Faces Exist
        else
        {
            //m_pLogger->ProgressFailure( LOG_ESR );
            //m_pLogger->LogWrite( LOG_ESR, LOGF_WARNING, false, _T("\r\n\r\nProcess resulted in all faces being removed!\r\n" ) );
            return false;

        } // End if no Faces Exist

        // *************************
        // *   Stats Recording     *
        // *************************

        // *************************
        // *     End of Stats      *
        // *************************

    } // End Try Block

    catch ( HRESULT& e )
    {
        // Clean up and return (failure)
        //m_pLogger->ProgressFailure( LOG_ESR );
        if ( mPrimitivoResultante ) delete mPrimitivoResultante;
        Finaliza();
        return e;

    } // End Catch Block

    catch ( ... )
    {
        // Clean up and return (failure)
        //m_pLogger->ProgressFailure( LOG_ESR );
        if ( mPrimitivoResultante ) delete mPrimitivoResultante;
        Finaliza();
        return false;

    } // End Catch Block

    // Success!
    //if ( m_pLogger ) m_pLogger->ProgressSuccess( LOG_ESR );
    return true;

}

//-----------------------------------------------------------------------------
// Nome : GetResultMesh ()
// Desc : Retrieves the resulting mesh build during the HSR process.
//-----------------------------------------------------------------------------
CI3DModelo* CI3DProcessadorRON::PegaPrimitivoResultante() const
{
    return mPrimitivoResultante;
}

//-----------------------------------------------------------------------------
// Nome : LeafPortalFlood () (Private, Recursive)
// Desc : Floods through the portals in the specified leaf.
//-----------------------------------------------------------------------------
void CI3DProcessadorRON::PercorrePortais(CI3DArvoreBsp *pTree, bool pVisited[], ULONG Leaf)
{
    // Valida Parâmetros
    if ( !pTree || !pVisited || Leaf >= pTree->PegaQtdFolhas() ) return;

    //Marca a Folha como visitada
    pVisited[ Leaf ] = true;

    //Recupera a folha para facil acesso
    CI3DFolhaBsp * pLeaf = pTree->PegaFolha( Leaf );

    //Percorre Todos os Portais da Folha
    for ( ULONG i = 0; i < pLeaf->PortalCount; i++ )
    {
        CI3DPortal * pPortal = pTree->PegaPortal( pLeaf->PortalIndices[ i ] );

        // Retrieve the correct leaf index
        ULONG LeafIndex = pPortal->FolhaProprietaria[ FRONT_OWNER ];
        if ( LeafIndex == Leaf ) LeafIndex = pPortal->FolhaProprietaria[ BACK_OWNER ];

        // Iterate into this leaf if not already visited
        if ( !pVisited[ LeafIndex ] ) PercorrePortais( pTree, pVisited, LeafIndex );

    } // Next Portal
}

