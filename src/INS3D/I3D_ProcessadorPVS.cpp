#include "I3D_ProcessadorPVS.h"

CPVSPortal::CPVSPortal()
{
    Status              = PS_NOTPROCESSED;
    Plane               = -1;
    NeighbourLeaf       = -1;
    PossibleVisCount    = 0;
    PossibleVis         = NULL;
    ActualVis           = NULL;
    Points              = NULL;
    OwnsPoints          = false;
}

CPVSPortal::~CPVSPortal()
{
    if (ActualVis && PossibleVis != ActualVis) delete []ActualVis;
    if (PossibleVis) delete []PossibleVis;
    if (Points && OwnsPoints ) delete Points;

    PossibleVis = NULL;
    ActualVis   = NULL;
    Points      = NULL;
}

CPortalPoints::CPortalPoints()
{
    OwnsVertices = false;
    OwnerPortal  = NULL;
}

CPortalPoints::CPortalPoints( const CI3DPoligono * pPolygon, bool Duplicate )
{
    OwnsVertices = false;
    OwnerPortal  = NULL;
    if (!pPolygon) return;

    if ( Duplicate )
    {
        AdicionaVertices( pPolygon->I3D_QtdVertices , IGL_RENDER_TRIANGLES);
        memcpy( Vertices, pPolygon->Vertices, I3D_QtdVertices * sizeof(CI3DVertice) );

        OwnsVertices = true;
    }
    else
    {
        Vertices         = pPolygon->Vertices;
        I3D_QtdVertices  = pPolygon->I3D_QtdVertices;
        OwnsVertices     = false;

    }
}

CPortalPoints::~CPortalPoints()
{
    if (OwnsVertices) LimpaVertices();

    Vertices        = NULL;
    Indices         = NULL;
    I3D_QtdVertices = 0;
}

CPortalPoints * CPortalPoints::Clip( const CIMTPlano& Plane, bool KeepOnPlane )
{
    CPortalPoints * NewPoints = NULL;

    // Classifica os pontos
    CLASSIFICACAO Location = Plane.ClassificaPoligono( Vertices,I3D_QtdVertices,sizeof(CI3DVertice));

    // Processa a localização
    switch ( Location )
    {
            case FRENTE:
                // Tudo está na frente apenas retorna ele mesmo(this)
                NewPoints = this;
                break;

            case ATRAS:
                // Nada na Frente
                NewPoints = NULL;
                break;

            case COPLANAR:
                // Preciso manter coplanares?
                if ( KeepOnPlane ) NewPoints = this;
                break;

            case CRUZANDO:

                // Aloca novos pontos
                NewPoints = new CPortalPoints;
                //if (!NewPoints) throw std::bad_alloc();

                // Clipping dos novos pontos pelo Plano associado.
                Divide( Plane, NewPoints, NULL );

                break;

    }
    return NewPoints;
}

bool CPortalPoints::Divide( const CIMTPlano& Plane, CPortalPoints * FrontSplit, CPortalPoints * BackSplit)
{
    CI3DPoligono::Divide(Plane, FrontSplit, BackSplit );

    if (FrontSplit){ FrontSplit->OwnsVertices = true; }
    if (BackSplit ){ BackSplit ->OwnsVertices = true; }

    return true;
}

CI3DProcessadorPVS::CI3DProcessadorPVS()
{
    m_PVSBytesPerSet    = 0;
    m_pTree             = NULL ;
    CompilacaoTotal     = false;
}

CI3DProcessadorPVS::~CI3DProcessadorPVS()
{
    ULONG i;

    for ( i = 0; i < GetPVSPortalCount(); i++ ) if ( GetPVSPortal(i) ) delete GetPVSPortal(i);

    m_vpPVSPortals.clear();

}

bool CI3DProcessadorPVS::Process( CI3DArvoreBsp * pTree )
{
    bool hRet=true;

    // verifica arvore valida
    //if (!pTree) return false;
    if ( pTree->PegaQtdPortais() == 0 ) return false;

    m_pTree = pTree;

    // Calcula o numero de bytes de alocação para cada folha
    // 8 Folhas por byte não comprimido
    m_PVSBytesPerSet = (pTree->PegaQtdFolhas() + 7) / 8;

    // 32 bit align the bytes per set to allow for our early out long conversion
    m_PVSBytesPerSet = (m_PVSBytesPerSet * 3 + 3) & 0xFFFFFFFC;

    // Retrieve all of our one way portals
    GeneratePVSPortals();

    // Calculate initial portal visibility
    InitialPortalVis();

    // Perform actual full PVS calculation
    hRet = CalcPortalVis();

    // Export the visibility set to the final BSP Tree master array
    ExportPVS( pTree );

    return hRet;
}

bool CI3DProcessadorPVS::GeneratePVSPortals( )
{
    ULONG i, p, PortalCount = m_pTree->PegaQtdPortais();

    try
    {
        m_vpPVSPortals.resize( PortalCount * 2 );
        for ( i = 0; i < PortalCount * 2; i++ )
        {
            m_vpPVSPortals[i] = new CPVSPortal;
            //if (!m_vpPVSPortals[i]) throw std::bad_alloc();

        }
    }

    catch (...){ return false; }

    for ( i = 0, p = 0; i < PortalCount; i++, p+=2 )
    {
        CI3DPortal * pBSPPortal = m_pTree->PegaPortal(i);

        CPortalPoints *pp = AllocPortalPoints( pBSPPortal, false );

        m_vpPVSPortals[p    ]->Points        = pp;
        m_vpPVSPortals[p    ]->Side          = FRONT_OWNER;
        m_vpPVSPortals[p    ]->Status        = PS_NOTPROCESSED;
        m_vpPVSPortals[p    ]->Plane         = m_pTree->PegaNo( pBSPPortal->NoGerador )->Plano;
        m_vpPVSPortals[p    ]->NeighbourLeaf = pBSPPortal->FolhaProprietaria[ FRONT_OWNER ];
        m_vpPVSPortals[p    ]->OwnsPoints    = true;

        pp->OwnerPortal = m_vpPVSPortals[p];

        m_vpPVSPortals[p + 1]->Points        = pp;
        m_vpPVSPortals[p + 1]->Side          = BACK_OWNER;
        m_vpPVSPortals[p + 1]->Status        = PS_NOTPROCESSED;
        m_vpPVSPortals[p + 1]->Plane         = m_pTree->PegaNo( pBSPPortal->NoGerador )->Plano;
        m_vpPVSPortals[p + 1]->NeighbourLeaf = pBSPPortal->FolhaProprietaria[ BACK_OWNER ];
        m_vpPVSPortals[p + 1]->OwnsPoints    = false;

    }

    return true;
}

bool CI3DProcessadorPVS::InitialPortalVis()
{
    CPortalPoints  *pp;
    ULONG           p1, p2, i;
    CIMTPlano       Plane1, Plane2;
    UCHAR          *PortalVis = NULL;
    CPVSPortal     *pPortal1, *pPortal2;

    try
    {
        PortalVis = new UCHAR[ GetPVSPortalCount() ];
        //if ( !(PortalVis = new UCHAR[ GetPVSPortalCount() ])) throw std::bad_alloc();

        for ( p1 = 0; p1 < GetPVSPortalCount(); p1++)
        {
            pPortal1 = GetPVSPortal( p1 );

            GetPortalPlane( pPortal1, Plane1 );

            pPortal1->PossibleVis = new UCHAR[m_PVSBytesPerSet];
            //if (!(pPortal1->PossibleVis = new UCHAR[m_PVSBytesPerSet])) throw std::bad_alloc();

            ZeroMemory( pPortal1->PossibleVis, m_PVSBytesPerSet );
            ZeroMemory( PortalVis, GetPVSPortalCount() );

            for ( p2 = 0; p2 < GetPVSPortalCount(); p2++)
            {
                if (p2 == p1) continue;

                pPortal2 = GetPVSPortal( p2 );

                GetPortalPlane( pPortal2, Plane2 );

                pp = pPortal2->Points;
                for ( i = 0; i < pp->I3D_QtdVertices; i++)
                {
                    if ( Plane1.ClassificaPonto( pp->Vertices[i] ) == FRENTE ) break;
                }

                if ( i == pp->I3D_QtdVertices ) continue;

                pp = pPortal1->Points;
                for ( i = 0; i < pp->I3D_QtdVertices; i++)
                {
                    if ( Plane2.ClassificaPonto( pp->Vertices[i] ) == ATRAS ) break;
                }

                if ( i == pp->I3D_QtdVertices ) continue;

                PortalVis[p2] = 1;
            }

            pPortal1->PossibleVisCount = 0;
            PortalFlood( pPortal1, PortalVis, pPortal1->NeighbourLeaf );
        }
    }

    catch ( std::bad_alloc )
    {
        if (PortalVis) delete []PortalVis;
        return false;
    }

    if (PortalVis) delete []PortalVis;

    return true;
}


void CI3DProcessadorPVS::PortalFlood( CPVSPortal * SourcePortal, unsigned char PortalVis[], unsigned long Leaf )
{
    CI3DFolhaBsp * pLeaf = m_pTree->PegaFolha( Leaf );

    if ( GetPVSBit( SourcePortal->PossibleVis, Leaf ) ) return;

    SetPVSBit( SourcePortal->PossibleVis, Leaf );

    SourcePortal->PossibleVisCount++;

    for ( ULONG i = 0; i < pLeaf->PortalCount; i++)
    {
        ULONG PortalIndex = pLeaf->PortalIndices[ i ] * 2;

        if ( GetPVSPortal( PortalIndex )->NeighbourLeaf == Leaf ) PortalIndex++;

        if ( !PortalVis[ PortalIndex ] ) continue;

        PortalFlood( SourcePortal, PortalVis, GetPVSPortal( PortalIndex )->NeighbourLeaf );

    }
}

bool CI3DProcessadorPVS::CalcPortalVis()
{
    ULONG   i;
    PVSDATA l_PVSData;

    if ( !CompilacaoTotal )
    {
        for ( i = 0; i < GetPVSPortalCount(); i++ )
        {
            CPVSPortal * pPortal = GetPVSPortal( i );
            pPortal->ActualVis = pPortal->PossibleVis;

        }

        return true;
    }

    try
    {
        ZeroMemory( &l_PVSData, sizeof(PVSDATA) );

        for ( i = 0; i != -1; i = GetNextPortal() )
        {
            CPVSPortal * pPortal = GetPVSPortal( i );

            l_PVSData.SourcePoints    = pPortal->Points;
            l_PVSData.VisBits         = pPortal->PossibleVis;
            GetPortalPlane( pPortal, l_PVSData.TargetPlane );

            pPortal->ActualVis = new UCHAR[ m_PVSBytesPerSet ];
            //if (!pPortal->ActualVis) throw std::bad_alloc(); // VC++ Compat

            ZeroMemory( pPortal->ActualVis, m_PVSBytesPerSet );

            RecursePVS( pPortal->NeighbourLeaf, pPortal, l_PVSData );

            pPortal->Status = PS_PROCESSED;
        }
    }

    catch (...){ return false; }

    return true;
}

ULONG CI3DProcessadorPVS::GetNextPortal( )
{
    CPVSPortal * pPortal;
    long PortalIndex = -1, Min = 999999;

    for ( ulong i = 0; i < GetPVSPortalCount(); i++ )
    {
        pPortal = GetPVSPortal(i);

        if ( pPortal->PossibleVisCount < Min && pPortal->Status == PS_NOTPROCESSED)
        {
            Min = pPortal->PossibleVisCount;
            PortalIndex = i;
        }
    }

    if ( PortalIndex > -1) GetPVSPortal( PortalIndex )->Status = PS_PROCESSING;

    return PortalIndex;
}

bool CI3DProcessadorPVS::RecursePVS( ULONG Leaf, CPVSPortal * SourcePortal, PVSDATA & PrevData )
{
    ULONG           i,j;
    bool            More;
    ULONG          *Test, *Possible, *Vis;

    PVSDATA         Data;
    CPVSPortal     *GeneratorPortal;
    CIMTPlano       ReverseGenPlane, SourcePlane;
    CPortalPoints  *SourcePoints, *GeneratorPoints, *NewPoints;

    int TestesClip=2;

    CI3DFolhaBsp * pLeaf = m_pTree->PegaFolha( Leaf );

    SetPVSBit( SourcePortal->ActualVis, Leaf );

    Data.VisBits = new UCHAR[ m_PVSBytesPerSet ];
    //if (!Data.VisBits) return false; // VC++ Compat

    Possible    = (ULONG*)Data.VisBits;
    Vis         = (ULONG*)SourcePortal->ActualVis;
    GetPortalPlane( SourcePortal, SourcePlane );

    for ( i = 0; i < pLeaf->PortalCount; i++ )
    {
        ULONG PortalIndex = pLeaf->PortalIndices[ i ] * 2;
        if ( GetPVSPortal( PortalIndex )->NeighbourLeaf == Leaf ) PortalIndex++;

        GeneratorPortal = GetPVSPortal( PortalIndex );

        if ( !GetPVSBit( PrevData.VisBits, GeneratorPortal->NeighbourLeaf ) ) continue;

        if ( GeneratorPortal->Status == PS_PROCESSED )
            Test = (ULONG*)GeneratorPortal->ActualVis;
        else
            Test = (ULONG*)GeneratorPortal->PossibleVis;

        More = false;

        for ( j = 0; j < m_PVSBytesPerSet / sizeof(ULONG); j++ )
        {
            Possible[j] = ((ULONG*)PrevData.VisBits)[j] & Test[j];
            if ( Possible[j] & ~Vis[j] ) More = true;
        }

        if ( !More ) continue;

        GetPortalPlane( GeneratorPortal, Data.TargetPlane );

        ReverseGenPlane.IMT_NormalPlano    = -Data.TargetPlane.IMT_NormalPlano;
        ReverseGenPlane.IMT_DistanciaPlano = -Data.TargetPlane.IMT_DistanciaPlano;

        if ( ReverseGenPlane.IMT_NormalPlano.Compara(PrevData.TargetPlane.IMT_NormalPlano, 0.001f ) ) continue;

        GeneratorPoints = GeneratorPortal->Points->Clip( SourcePlane, false );
        if ( GeneratorPoints != GeneratorPortal->Points )
        {
            FreePortalPoints( GeneratorPortal->Points );
        }
        if (!GeneratorPoints) continue;

        if ( !PrevData.TargetPoints )
        {
            Data.SourcePoints = PrevData.SourcePoints;
            Data.TargetPoints = GeneratorPoints;
            RecursePVS( GeneratorPortal->NeighbourLeaf, SourcePortal, Data );
            FreePortalPoints( GeneratorPoints );
            continue;
        }

        NewPoints = GeneratorPoints->Clip( PrevData.TargetPlane, false );
        if ( NewPoints != GeneratorPoints )
        {
            FreePortalPoints( GeneratorPoints );
        }
        GeneratorPoints = NewPoints;
        if (!GeneratorPoints) continue;

        SourcePoints = new CPortalPoints( PrevData.SourcePoints, true );

        NewPoints = SourcePoints->Clip( ReverseGenPlane, false );
        if ( NewPoints != SourcePoints )
        {
            FreePortalPoints( SourcePoints );
        }
        SourcePoints = NewPoints;

        if ( !SourcePoints )
        {
            FreePortalPoints(  GeneratorPoints );
            continue;
        }

        if ( TestesClip > 0 )
        {
            GeneratorPoints = ClipToAntiPenumbra( SourcePoints, PrevData.TargetPoints, GeneratorPoints, false );
            if (!GeneratorPoints)
            {
                FreePortalPoints( SourcePoints );
                continue;
            }
        }

        if ( TestesClip > 1 )
        {
            GeneratorPoints = ClipToAntiPenumbra( PrevData.TargetPoints, SourcePoints, GeneratorPoints, true );
            if (!GeneratorPoints)
            {
                FreePortalPoints( SourcePoints );
                continue;
            }

        }

        if ( TestesClip > 2 )
        {
            SourcePoints = ClipToAntiPenumbra( GeneratorPoints, PrevData.TargetPoints, SourcePoints, false );
            if (!SourcePoints)
            {
                FreePortalPoints( GeneratorPoints );
                continue;
            }

        }

        if ( TestesClip > 3 )
        {
            SourcePoints = ClipToAntiPenumbra( PrevData.TargetPoints, GeneratorPoints, SourcePoints, true );
            if (!SourcePoints)
            {
                FreePortalPoints( GeneratorPoints );
                continue;
            }

        }


        Data.SourcePoints = SourcePoints;
        Data.TargetPoints = GeneratorPoints;

        RecursePVS( GeneratorPortal->NeighbourLeaf, SourcePortal, Data );

        FreePortalPoints( SourcePoints );
        FreePortalPoints( GeneratorPoints );
    }

    if (Data.VisBits) delete []Data.VisBits;

    return true;
}

CPortalPoints * CI3DProcessadorPVS::ClipToAntiPenumbra( CPortalPoints * Source, CPortalPoints * Target, CPortalPoints * Generator, bool ReverseClip )
{
    CIMTPlano       Plane;
    CIMTVetor       v1, v2;
    float           Length;
    ULONG           Counts[3];
    ULONG           i, j, k, l;
    bool            ReverseTest;
    CPortalPoints  *NewPoints;

    for ( i = 0; i < Source->I3D_QtdVertices; i++ )
    {
        l = ( i + 1 ) % Source->I3D_QtdVertices;
        v1 = Source->Vertices[l] - Source->Vertices[i];

        for ( j = 0; j < Target->I3D_QtdVertices; j++ )
        {
            v2 = Target->Vertices[j] - Source->Vertices[i];
            Plane.IMT_NormalPlano = v1.ProdutoVetorial(v2);


            Length = Plane.IMT_NormalPlano.x * Plane.IMT_NormalPlano.x +
                     Plane.IMT_NormalPlano.y * Plane.IMT_NormalPlano.y +
                     Plane.IMT_NormalPlano.z * Plane.IMT_NormalPlano.z;
            if ( Length < 0.1f ) continue;

            Length = 1 / sqrtf( Length );
            Plane.IMT_NormalPlano *= Length;

            Plane.IMT_DistanciaPlano= Target->Vertices[j].ProdutoEscalar(Plane.IMT_NormalPlano);

            ReverseTest = false;
            for ( k = 0; k < Source->I3D_QtdVertices; k++ )
            {
                if ( k == i || k == l ) continue;

                CLASSIFICACAO Location = Plane.ClassificaPonto(Source->Vertices[k]);
                if ( Location == ATRAS )
                {
                    ReverseTest = false;
                    break;

                }
                else if ( Location == FRENTE )
                {
                    ReverseTest = true;
                    break;
                }
            }

            if ( k == Source->I3D_QtdVertices) continue;

            if ( ReverseTest )
            {
                Plane.IMT_NormalPlano    = -Plane.IMT_NormalPlano;
                Plane.IMT_DistanciaPlano = -Plane.IMT_DistanciaPlano;
            }

            ZeroMemory( Counts, 3 * sizeof(ULONG) );
            for ( k = 0; k < Target->I3D_QtdVertices; k++ )
            {
                if ( k == j ) continue;

                CLASSIFICACAO Location = Plane.ClassificaPonto( Target->Vertices[k]);
                if ( Location == ATRAS )
                {
                    break;
                }
                else if ( Location == FRENTE )
                {
                    Counts[0]++;
                }
                else
                {
                    Counts[2]++;
                }
            }

            if ( k != Target->I3D_QtdVertices) continue;

            if ( Counts[0] == 0 ) continue;

            if ( ReverseClip )
            {
                Plane.IMT_NormalPlano    = -Plane.IMT_NormalPlano;
                Plane.IMT_DistanciaPlano = -Plane.IMT_DistanciaPlano;
            }

            NewPoints = Generator->Clip( Plane, false );
            if ( NewPoints != Generator )
            {
                FreePortalPoints( Generator );
            }

            Generator = NewPoints;

            if (!Generator)
            {
                return NULL;
            }
        }
    }

    return Generator;
}

bool CI3DProcessadorPVS::ExportPVS( CI3DArvoreBsp * pTree )
{
    UCHAR * p_PVSData = NULL;
    UCHAR * p_LeafPVS = NULL;
    ULONG   PVSWritePtr = 0, i, p, j;

    try
    {

        // Reserve Enough Space to hold every leafs PVS set (plus some to spare)
        p_PVSData = new UCHAR[(pTree->PegaQtdFolhas() + 5) * m_PVSBytesPerSet];
        //if (!p_PVSData) throw std::bad_alloc();

        // Set all visibility initially to off
        ZeroMemory( p_PVSData, (pTree->PegaQtdFolhas() + 5) * m_PVSBytesPerSet);

        // Allocate enough memory for a single leaf set
        p_LeafPVS = new UCHAR[ m_PVSBytesPerSet ];
        //if (!p_LeafPVS) throw std::bad_alloc();

        // Loop round each leaf and collect the vis info
        // this is all OR'd together and ZRLE compressed
        // Then finally stored in the master array
        for ( i = 0; i < pTree->PegaQtdFolhas(); i++ )
        {
            CI3DFolhaBsp * pLeaf = pTree->PegaFolha(i);

            // Clear Temp PVS Array Buffer
            ZeroMemory( p_LeafPVS, m_PVSBytesPerSet );
            pLeaf->I3D_IndicePVS = PVSWritePtr;

            // Current leaf is always visible
            SetPVSBit( p_LeafPVS, i );

            // Loop through all portals in this leaf
            for ( p = 0; p < pLeaf->PortalCount; p++ )
            {
                // Find correct portal index (the one IN this leaf)
                ULONG PortalIndex = pLeaf->PortalIndices[ p ] * 2;
                if ( GetPVSPortal( PortalIndex )->NeighbourLeaf == i ) PortalIndex++;

                // Or the vis bits together
                for ( j = 0; j < m_PVSBytesPerSet; j++ )
                {
                    p_LeafPVS[j] |= GetPVSPortal( PortalIndex )->ActualVis[j];

                } // Next PVS Byte

            } // Next Portal

            #if ( PVS_COMPRESSDATA )

                // Compress the leaf set here and update our master write pointer
                PVSWritePtr += CompressLeafSet( p_PVSData, p_LeafPVS, PVSWritePtr );

            #else

                // Copy the data into the Master PVS Set
                memcpy( &p_PVSData[ PVSWritePtr ], p_LeafPVS, m_PVSBytesPerSet );
                PVSWritePtr += m_PVSBytesPerSet;

            #endif

        } // Next Leaf

        // Clean up after ourselves
        delete []p_LeafPVS;
        p_LeafPVS = NULL;

        // Pass this data off to the BSP Tree (data, size, compressed)
        pTree->SetaPVS( p_PVSData, PVSWritePtr, PVS_COMPRESSDATA );
        /*
        if(!(pTree->SetPVSData( p_PVSData, PVSWritePtr, PVS_COMPRESSDATA )))
        {
            throw false;
        }
        */

        // Free our PVS buffer
        delete []p_PVSData;

    } // End Try Block

    catch (...)
    {
        // Clean up and return (Failure)
        if ( p_LeafPVS ) delete []p_LeafPVS;
        if ( p_PVSData ) delete []p_PVSData;
        return false;
    } // End Catch Block

    // Success!!
    return true;
}

//-------------------------------------------------------------------------------------
// Name : CompressLeafSet () (Private)
// Desc : ZRLE Compresses the uncompressed vis bit array which was passed in, and
//        compresses and adds it to the master PVS Array, this function returns
//        the size of the compressed set so we can update our write pointer.
//-------------------------------------------------------------------------------------
ULONG CI3DProcessadorPVS::CompressLeafSet ( UCHAR MasterPVS[], const UCHAR VisArray[], ULONG WritePos)
{
    ULONG   RepeatCount;
    UCHAR  *pDest = &MasterPVS[ WritePos ];
    UCHAR  *pDest_p;

    // Set dynamic pointer to start position
    pDest_p = pDest;

    // Loop through and compress the set
    for ( ULONG j = 0; j < m_PVSBytesPerSet; j++ )
    {
        // Store the current 8 leaves
        *pDest_p++ = VisArray[j];

        // Don't compress if all bits are not zero
        if ( VisArray[j] ) continue;

        // Count the number of 0 bytes
        RepeatCount = 1;
        for ( j++; j < m_PVSBytesPerSet; j++ )
        {
            // Keep counting until byte != 0 or we reach our max repeat count
            if ( VisArray[j] || RepeatCount == 255) break; else RepeatCount++;

        } // Next Byte

        // Store our repeat count
        *pDest_p++ = RepeatCount;

        // Step back one byte because the outer loop
        // will increment. We are already at the correct pos.
        j--;

    } // Next Byte

    // Return written size
    return pDest_p - pDest;
}

//-------------------------------------------------------------------------------------
// Name : GetPortalPlane()
// Desc : Calculates the correct plane orientation for the specified portal
//-------------------------------------------------------------------------------------
void CI3DProcessadorPVS::GetPortalPlane( const CPVSPortal * pPortal, CIMTPlano& Plane )
{

    // Store plane information
    Plane = *m_pTree->PegaPlano( pPortal->Plane );

    // Swap sides if necessary
    if ( pPortal->Side == BACK_OWNER )
    {
        Plane.IMT_NormalPlano    = -Plane.IMT_NormalPlano;
        Plane.IMT_DistanciaPlano = -Plane.IMT_DistanciaPlano;
    } // End if Swap Sides
}

//-------------------------------------------------------------------------------------
// Name : GetPVSBit() (Static, Private)
// Desc : Pass in a destination leaf and it will return true if it's corresponding
//        uncompressed bit position is set to 1 in the array passed
//-------------------------------------------------------------------------------------
bool CI3DProcessadorPVS::GetPVSBit( UCHAR VisArray[], ULONG DestLeaf )
{
    return (VisArray[ DestLeaf >> 3 ] & (1 << ( DestLeaf & 7))) != 0;
}

//-------------------------------------------------------------------------------------
// Name : SetPVSBit()
// Desc : Pass in a destination leaf and it will set it's corresponding uncompressed
//        bit position to the value specified, in the array passed
//-------------------------------------------------------------------------------------
void CI3DProcessadorPVS::SetPVSBit( UCHAR VisArray[], ULONG DestLeaf, bool Value /* = true */ )
{
    // Set / remove bit depending on the value
    if ( Value == true )
    {
        VisArray[ DestLeaf >> 3 ] |=  (1 << ( DestLeaf & 7 ));
    }
    else
    {
        VisArray[ DestLeaf >> 3 ] &= ~(1 << ( DestLeaf & 7 ));

    } // End if Value
}

//-----------------------------------------------------------------------------
// Name : AllocPortalPoints () (Static, Private)
// Desc : Simply allocate a brand new CPortalPoints object and return it.
// Note : Provided for ease of use, and to provide some level of portability
//        without polluting the main code base.
//-----------------------------------------------------------------------------
CPortalPoints * CI3DProcessadorPVS::AllocPortalPoints( CI3DPoligono * pPolygon, bool Duplicate )
{

    CPortalPoints * NewPoints = NULL;

    try
    {

        // Attempt to allocate a new set of points
        NewPoints = new CPortalPoints( pPolygon, Duplicate );

        //if (!NewPoints) throw std::bad_alloc();

    } // End try block

    catch (HRESULT)
    {
        // Constructor throws HRESULT
        if (NewPoints) delete NewPoints;
        return NULL;

    } // End Catch

    /*
    catch ( std::bad_alloc )
    {
        // Failed to allocate
        return NULL;

    } // End Catch
    */
    // Success!!
    return NewPoints;
}

//-----------------------------------------------------------------------------
// Name : FreePortalPoints() (Static, Private)
// Desc : Releases a set of portal points.
// Note : Only releases if it is not owned by a physical portal.
//-----------------------------------------------------------------------------
void CI3DProcessadorPVS::FreePortalPoints( CPortalPoints * pPoints )
{
    // Validate Parameters
    if (!pPoints) return;

    // We are only allowed to delete NON-Owned point sets
    if ( pPoints->OwnerPortal == NULL ) delete pPoints;

}

