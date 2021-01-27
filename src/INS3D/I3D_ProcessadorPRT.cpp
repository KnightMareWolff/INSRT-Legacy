#include "I3D_ProcessadorPRT.h"


//-----------------------------------------------------------------------------
// Name : CKbcProPRT () (Constructor)
// Desc : CKbcProPRT Class Constructor
//-----------------------------------------------------------------------------
CI3DProcessadorPRT::CI3DProcessadorPRT()
{
    CompilacaoTotal=true;
}

//-----------------------------------------------------------------------------
// Name : ~CKbcProPRT () (Destructor)
// Desc : CKbcProPRT Class Destructor
//-----------------------------------------------------------------------------
CI3DProcessadorPRT::~CI3DProcessadorPRT()
{
    // Clean up after ourselves
}

//-----------------------------------------------------------------------------
// Name : Processa ()
// Desc : Compiles a set of portals by essentially sending a large polygon
//        per node through the tree clipping them down until they reach empty
//        space. If they are valid portals, they are added to the master array.
//-----------------------------------------------------------------------------
bool CI3DProcessadorPRT::Processa( CI3DArvoreBsp * pTree )
{
    CIMTBorda    PortalBounds;
    CI3DPortal * InitialPortal = NULL;
    CI3DNoBsp  * CurrentNode   = NULL;
    CI3DNoBsp  * RootNode      = NULL;
    CIMTPlano  * NodePlane     = NULL;
    CI3DPortal * PortalList    = NULL;

    // Store tree for compilation
    PRTBSP = pTree;

    try
    {
        // Store required values ready for use.
        RootNode = PRTBSP->PegaNo(0);

        // Create a portal for each node
        for (unsigned long i = 0; i < pTree->PegaQtdNos(); i++)
        {
            // Store required values ready for use.
            CurrentNode = PRTBSP->PegaNo(i);
            NodePlane   = PRTBSP->PegaPlano(CurrentNode->Plano);

            // Allocate a new initial portal for clipping
            InitialPortal = CI3DArvoreBsp::AlocaPortalBsp();
            /*
            if(InitialPortal==NULL)
            {
                throw false;
            }
            */


            // Should we build a full portal or not
            if (CompilacaoTotal)
            {
                PortalBounds = RootNode->I3D_Borda;
            }
            else
            {
                PortalBounds = CurrentNode->I3D_Borda;
            }


            InitialPortal->GeraPoligono( *NodePlane, PortalBounds );
            // Generate the portal polygon for the current node

            /*
            if(!(InitialPortal->GeraPoligono( *NodePlane, PortalBounds )))
            {
                throw false;
            }
            */

            InitialPortal->NoGerador = i;

            // Clip the portal and obtain a list of all fragments
            PortalList = ClipPortal(0, InitialPortal );

            // Clear the initial portal value, we no longer own this
            InitialPortal = NULL;

            // Add any valid fragments to the final portal list
            if (PortalList)
            {
                AdicionaPortais( PortalList );
                /*
                if(!(AdicionaPortais( PortalList )))
                {
                    throw false;
                }
                */
            } // End If PortalList

        } // Next Node

    } // End Try

    catch (...)
    {
        return false;
    }

    return true;
}

//-----------------------------------------------------------------------------
// Name : ClipPortal () (Recursive) (Private)
// Desc : This recursive function repeatedly clips the current portal to the
//        tree until it ends up in a leaf at which point it is returned.
//-----------------------------------------------------------------------------
CI3DPortal * CI3DProcessadorPRT::ClipPortal( unsigned long Node, CI3DPortal * pPortal )
{
    // 52 Bytes including Parameter list (based on __thiscall declaration)
    CI3DPortal   * PortalList     = NULL, *FrontPortalList = NULL;
    CI3DPortal   * BackPortalList = NULL, *Iterator        = NULL;
    CI3DPortal   * FrontSplit     = NULL, *BackSplit       = NULL;
    CI3DNoBsp    * CurrentNode    = NULL;
    CIMTPlano    * CurrentPlane   = NULL;
    unsigned long  OwnerPos, LeafIndex;

    // Store node for quick access
    CurrentNode  = PRTBSP->PegaNo( Node );
    CurrentPlane = PRTBSP->PegaPlano(CurrentNode->Plano);

    // Classify the portal against this nodes plane
    switch (CurrentPlane->ClassificaPoligono(pPortal->Vertices, pPortal->I3D_QtdVertices,sizeof(CI3DVertice)))
    {

        case COPLANAR:

            // The Portal has to be sent down Both sides of the tree and tracked. Send it down
            // front first but DO NOT delete any bits that end up in solid space, just ignore them.
            if (CurrentNode->I3D_Frente < 0 )
            {
                 // The Front is a Leaf
                LeafIndex   = abs(CurrentNode->I3D_Frente + 1);
                OwnerPos    = ClassificaFolha( LeafIndex, pPortal->NoGerador );
                if ( OwnerPos != NO_OWNER)
                {
                    pPortal->FolhaProprietaria[OwnerPos] = LeafIndex;
                    pPortal->NumeroFolhas++;
                    pPortal->Proximo = NULL;
                    pPortal->Anterior = NULL;
                    FrontPortalList	= pPortal;
                }
                else
                {
                    delete pPortal;
                    return NULL;
                } // End If

            }
            else
            {
                // Send the Portal Down the Front List and get returned a list of PortalFragments
                // that survived the Front Tree
                FrontPortalList = ClipPortal(CurrentNode->I3D_Frente, pPortal);

            } // End If

            // Then send each fragment down the back tree.
            if (FrontPortalList == NULL) return NULL;
            if (CurrentNode->I3D_Atras < 0  ) return FrontPortalList;

            // Loop through each front list fragment and send it down the back branch
            while (FrontPortalList != NULL)
            {
                CI3DPortal * Proximo = FrontPortalList->Proximo;
                BackPortalList	        = NULL;
                BackPortalList	        = ClipPortal(CurrentNode->I3D_Atras, FrontPortalList);
                // Now set to the end of the returned back fragment list to get the last fragment
                if (BackPortalList != NULL)
                {
                    Iterator = BackPortalList;
                    while ( Iterator->Proximo != NULL) Iterator = Iterator->Proximo;
                    // Attach the last fragment to the first fragment from a previos loop.
                    Iterator->Proximo  = PortalList;
                    if (PortalList != NULL)  PortalList->Anterior = Iterator;
                    // Portal List now points at the current complete list of fragment collected from each loop
                    PortalList = BackPortalList;

                } // End if BackPortalList is not empty

                FrontPortalList = Proximo;
            } // End While

            // Return the full list
            return PortalList;

        case FRENTE:

            // Either send it down the front tree or add it to the portal
            // list because it has come out in Empty Space
            if (CurrentNode->I3D_Frente < 0 )
            {
                // The Front Node is a Empty Leaf so Add the fragment to the Portal List
                LeafIndex   = abs(CurrentNode->I3D_Frente + 1);
                OwnerPos    = ClassificaFolha( LeafIndex, pPortal->NoGerador );

                if ( OwnerPos != NO_OWNER)
                {
                    pPortal->FolhaProprietaria[OwnerPos] = LeafIndex;
                    pPortal->NumeroFolhas++;
                    pPortal->Proximo	= NULL;
                    pPortal->Anterior	= NULL;
                    return pPortal;
                }
                else
                {
                    delete pPortal;
                    return NULL;
                } // End If

            }
            else
            {
                // If Not a leaf in front
                PortalList = ClipPortal(CurrentNode->I3D_Frente, pPortal);
                return PortalList;
            } // End If

            break;

        case ATRAS:

            // either send it down the back tree or Delete it if no back tree exists
            // because it means it has come out in solid space
            if (CurrentNode->I3D_Atras < 0 )
            {
                delete pPortal;
                return NULL;
            }
            else
            {
                PortalList = ClipPortal(CurrentNode->I3D_Atras, pPortal);
                return PortalList;
            } // End If

            break;

        case CRUZANDO:

            // Allocate new front fragment
            FrontSplit = CI3DArvoreBsp::AlocaPortalBsp();
            // Allocate new back fragment
            BackSplit  = CI3DArvoreBsp::AlocaPortalBsp();

            // Portal fragment is spanning the plane, so it must be split
            pPortal->Divide(*CurrentPlane, FrontSplit, BackSplit);

            delete pPortal;
            pPortal = NULL;

            // There is another Front NODE ?
            if (CurrentNode->I3D_Frente < 0 )
            {
                // Its about to get pushed into a Leaf
                LeafIndex   = abs(CurrentNode->I3D_Frente + 1);
                OwnerPos    = ClassificaFolha(LeafIndex, FrontSplit->NoGerador );
                if ( OwnerPos != NO_OWNER)
                {
                    FrontSplit->FolhaProprietaria[OwnerPos] = LeafIndex;
                    FrontSplit->NumeroFolhas++;
                    FrontSplit->Anterior = NULL;
                    FrontSplit->Proximo = NULL;
                    FrontPortalList        = FrontSplit;
                }
                else
                {
                    delete FrontSplit;
                } // End If
            }
            else
            {
                FrontPortalList = ClipPortal(CurrentNode->I3D_Frente, FrontSplit);
            } // End If

            // The backsplit is in solid space
            if (CurrentNode->I3D_Atras < 0 )
            {
                // We ended up in solid space
                delete BackSplit;
                BackSplit = NULL;
            }
            else
            {
                BackPortalList = ClipPortal(CurrentNode->I3D_Atras, BackSplit);
            } // End If

            // Find the End of the list and attach it to Front Back List
            if (FrontPortalList != NULL)
            {
                // there is something in the front list
                Iterator = FrontPortalList;
                while (Iterator->Proximo != NULL) Iterator = Iterator->Proximo;

                if (BackPortalList != NULL)
                {
                    Iterator->Proximo	   = BackPortalList;
                    BackPortalList->Anterior = Iterator;
                } // End If

                return FrontPortalList;
            }
            else
            {
                //There is nothing in the front list
                if (BackPortalList != NULL) return BackPortalList;
                return NULL;
            } // End if

            // if we got here, we are fresh out of portal fragments
            // so simply return NULL.
            return NULL;

    } // End switch

    return NULL;
}

//-----------------------------------------------------------------------------
// Name : AdicionaPortais () (Private)
// Desc : Iterators through all the fragments passed. If the fragments are
//        valid portals, then they are added to the final portal list.
//-----------------------------------------------------------------------------
bool CI3DProcessadorPRT::AdicionaPortais( CI3DPortal * PortalList )
{
    unsigned long PortalIndex = 0;
    CI3DPortal    * Iterator, *Next;
    CI3DFolhaBsp  * Leaf = NULL;


    // Validate
    if (!PortalList) return false;


    // Iterate through the list, obtaining valid portals
    Iterator = PortalList;
    while ( Iterator != NULL )
    {
        if (Iterator->NumeroFolhas != 2)
        {
            // Invalid portal... delete it
            Next     = Iterator->Proximo;
            RemovePortalLista(Iterator);
            Iterator = Next;
        }
        else
        {
            // Check to see if this is an un-needed duplicate portal
            if ( VerificaPortalDuplicado( Iterator, PortalIndex ) )
            {
                // Invalid portal... delete it
                Next      = Iterator->Proximo;
                RemovePortalLista(Iterator);
                Iterator  = Next;
            }
            else
            {
                // Valid portal so add it
                if ( PortalIndex == PRTBSP->PegaQtdPortais() )
                {
                    for ( int i = 0; i < 2; i++ )
                    {
                        Leaf = PRTBSP->PegaFolha( Iterator->FolhaProprietaria[i] );
                        Leaf->AdicionaPortal( PRTBSP->PegaQtdPortais() );
                    } // Next Leaf

                    // We are adding a new portal
                    PRTBSP->IncrementaPortais();

                } // End if Portal Index == NumberOfPortals

                // Set the portal
                PRTBSP->SetaPortal( PortalIndex, Iterator );

                // Move onto next portal
                Iterator = Iterator->Proximo;

            } // End if Check Duplicate Portals
        } // End if Number of leaves != 2
    } // End While

    return true;
}

//-----------------------------------------------------------------------------
// Name : RemovePortalLista () (Private)
// Desc : Removes a portal from the linked list of portals. This is used to
//        remove a portal fragment from the fragment array when it fails the
//        test of either not being in two leafs or the portal already in the
//        array is larger.
//-----------------------------------------------------------------------------
void CI3DProcessadorPRT::RemovePortalLista( CI3DPortal * RemovePortal )
{
    CI3DPortal * Portal = RemovePortal;
    CI3DPortal * Anterior,* Proximo;

    // If there is a previous portal
    if (RemovePortal->Anterior != NULL)
    {
        // Unlink and update next
        Anterior = RemovePortal->Anterior;
        if (RemovePortal->Proximo != NULL)
        {
            Anterior->Proximo = RemovePortal->Proximo;
        } // End If Has Next
        else
        {
            Anterior->Proximo = NULL;
        } // End If No Next

    } // End If No Prev

    if (RemovePortal->Proximo != NULL)
    {
        // Unlink and update previous
        Proximo = RemovePortal->Proximo;
        if (RemovePortal->Anterior != NULL)
        {
            Proximo->Anterior = RemovePortal->Anterior;
        } // End if Has Prev
        else
        {
            Proximo->Anterior = NULL;
        } // End if No Prev

    } // End if No Next

    // Delete the portal
    delete Portal;
}

//-----------------------------------------------------------------------------
// Name : VerificaPortalDuplicado () (Private)
// Desc : This is used to check the current portal with the portal already
//        sharing the same leaves in tree. It is only accepted if the Portal is
//        Larger than the one that is ready occupying this place in the Master
//        Portal Array.
// Note : The final array index is returned via the Index reference.
//-----------------------------------------------------------------------------
bool CI3DProcessadorPRT::VerificaPortalDuplicado(CI3DPortal * CheckPortal, unsigned long& Index )
{
    long      CheckPortalLeaf1 = CheckPortal->FolhaProprietaria[0];
    long      CheckPortalLeaf2 = CheckPortal->FolhaProprietaria[1];
    long      PALeaf1 = 0, PALeaf2 = 0;
    CIMTBorda  Bounds1, Bounds2;
    CI3DPortal  *CurrentPortal = NULL;

    // Loop through the portals
    for ( unsigned long i = 0; i < PRTBSP->PegaQtdPortais(); i++)
    {
        CurrentPortal = PRTBSP->PegaPortal(i);
        PALeaf1 = CurrentPortal->FolhaProprietaria[0];
        PALeaf2 = CurrentPortal->FolhaProprietaria[1];

        if ((CheckPortalLeaf1 == PALeaf1 && CheckPortalLeaf2 == PALeaf2) ||
            (CheckPortalLeaf1 == PALeaf2 && CheckPortalLeaf2 == PALeaf1))
        {

            Bounds1.CalculaBordaMesh( CheckPortal->Vertices, CheckPortal->I3D_QtdVertices, sizeof(CI3DVertice) );
            Bounds2.CalculaBordaMesh( CurrentPortal->Vertices, CurrentPortal->I3D_QtdVertices, sizeof(CI3DVertice) );

            // Measure the Length of the vectors to see which is bigger (No need to sqrt)
            float NewSize = Bounds1.PegaDimensao().MeiaMagnitude();
            float OldSize = Bounds2.PegaDimensao().MeiaMagnitude();

            // Check to see if this is larger
            if (NewSize > OldSize)
            {
                delete CurrentPortal;
                Index = i;
                return false;
            }
            else
            {
                // This portal is already in the array
                return true;
            } // End If NewSize is larger

        } // End If

    } // Next Portal

    // This portal was not found in the array
    Index = PRTBSP->PegaQtdPortais();
    return false;
}

//-----------------------------------------------------------------------------
// Name : ProcuraFolha () (Recursive) (Private)
// Desc : Determines if the leaf passed is somewhere below the specified node.
//-----------------------------------------------------------------------------
bool CI3DProcessadorPRT::ProcuraFolha( unsigned long Leaf, unsigned long Node )
{
    CI3DNoBsp * CurrentNode = NULL;


    // Validate Requirements
    //if (!PRTBSP) return false;

    CurrentNode = PRTBSP->PegaNo( Node );

    // Check to see if the front is this leaf
    if ( CurrentNode->I3D_Frente < 0 )
    {
        if ( abs(CurrentNode->I3D_Frente + 1) == Leaf ) return true;
    }
    else
    {
        if (ProcuraFolha( Leaf, CurrentNode->I3D_Frente )) return true;
    } // End If

    // Iterate down the back if it's a node
    if ( CurrentNode->I3D_Atras >= 0 )
    {
        if (ProcuraFolha( Leaf, CurrentNode->I3D_Atras )) return true;
    } // End If

    return false;
}

//-----------------------------------------------------------------------------
// Name : ClassificaFolha () (Private)
// Desc : Classifies a leaf against this node (for ClipPortal). Leaf must be
//        somewhere relative to the node passed.
//-----------------------------------------------------------------------------
unsigned long CI3DProcessadorPRT::ClassificaFolha( unsigned long Leaf, unsigned long Node )
{
    CI3DNoBsp * CurrentNode = NULL;

    /*
    // Validate Requirements
    if (!PRTBSP) throw BCERR_INVALIDPARAMS;
    */
    CurrentNode = PRTBSP->PegaNo( Node );

    // Check to see if the front is this leaf
    if ( CurrentNode->I3D_Frente < 0 )
    {
        if ( abs(CurrentNode->I3D_Frente + 1) == Leaf ) return FRONT_OWNER;
    }
    else
    {
        if (ProcuraFolha( Leaf, CurrentNode->I3D_Frente )) return FRONT_OWNER;
    } // End If

    if ( CurrentNode->I3D_Atras >= 0 )
    {
        if (ProcuraFolha(Leaf, CurrentNode->I3D_Atras )) return BACK_OWNER;
    } // End If

    return NO_OWNER;
}


