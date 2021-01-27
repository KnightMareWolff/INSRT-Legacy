/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CI3DPROCESSADORPVS_H
#define CI3DPROCESSADORPVS_H


#include "I3D_GlobalDef.h"
#include "I3D_ArvoreBsp.h"

//-----------------------------------------------------------------------------
// Declarações de definições Foward
//-----------------------------------------------------------------------------
class CPortalPoints;
class CPVSPortal;

//-----------------------------------------------------------------------------
// Defines Diversos
//-----------------------------------------------------------------------------
#define PVS_ARRAY_THRESHOLD     100

#define PS_NOTPROCESSED			0       // Portal ainda não foi processado
#define PS_PROCESSING			1       // Portal está sendo processado
#define PS_PROCESSED			2       // Portal foi processado

//-----------------------------------------------------------------------------
// Flags de Pre-processamento de compilação
//-----------------------------------------------------------------------------
#define PVS_COMPRESSDATA        1       // 1 = Compressão ZRLE , 0 = Não comprime

//-----------------------------------------------------------------------------
// Typedefs, structuras & enumeradores
//-----------------------------------------------------------------------------
typedef struct _PVSDATA
{
    CPortalPoints   *SourcePoints;   // source portals points Atual
    CPortalPoints   *TargetPoints;   // target portals points Atual
    CIMTPlano        TargetPlane;    // O plano descrito pelo Alvo(target)
    UCHAR           *VisBits;        // Bits de Visão Sendo Calculados
} PVSDATA;


//-----------------------------------------------------------------------------
// Nome : CPortalPoints
// Desc : Pontos usados pelo processo de portal PVS e passado por toda a recursão
//        de maneira independente. Foi derivada da classe poligono para aproveitar
//        os metodos de suporte da classe como divisão e verificações.
//-----------------------------------------------------------------------------
class CPortalPoints : public CI3DPoligono
{
public:
    //-------------------------------------------------------------------------
    // Construtores/Destrutores
    //-------------------------------------------------------------------------
             CPortalPoints( );
             CPortalPoints( const CI3DPoligono * pPolygon, bool Duplicate = false );
    virtual ~CPortalPoints( );

    //-------------------------------------------------------------------------
    // Métodos Publicos
    //-------------------------------------------------------------------------
    CPortalPoints * Clip( const CIMTPlano& Plane, bool KeepOnPlane );

    //-------------------------------------------------------------------------
    // Métodos Virtuais Públicos
    //-------------------------------------------------------------------------
    virtual   bool  Divide( const CIMTPlano& Plane, CPortalPoints * FrontSplit, CPortalPoints * BackSplit);

    //-------------------------------------------------------------------------
    // Atributos Públicos
    //-------------------------------------------------------------------------
    bool                OwnsVertices;           // Temos Pontos armazenados?
    CPVSPortal         *OwnerPortal;            // Ponteiro para o dono dos pontos

};

//-----------------------------------------------------------------------------
// Nome : CPVSPortal
// Desc : Classe Portal usana na compilação PVS
//-----------------------------------------------------------------------------
class CPVSPortal
{
public:
    //-------------------------------------------------------------------------
    // Construtores/Destrutores
    //-------------------------------------------------------------------------
             CPVSPortal( );
    virtual ~CPVSPortal( );

    //-------------------------------------------------------------------------
    // Atributos Públicos
    //-------------------------------------------------------------------------
    UCHAR             Status;               // Status de compilação deste portal
    UCHAR             Side;                 // Direção que este portal aponta
    long              Plane;                // Plano associado a este portal
    long              NeighbourLeaf;        // Folha a qual este portal aponta
    long              PossibleVisCount;     // Tamanho do Buffer de Visão
    UCHAR            *PossibleVis;          // Buffer de "Possível" Visão
    UCHAR            *ActualVis;            // Buffer de Visão "Atual"
    bool              OwnsPoints;           // Possui pontos?
    CPortalPoints    *Points;               // Vertices que montam este portal

};

//-----------------------------------------------------------------------------
// Typedefs para simplificação de stl::
//-----------------------------------------------------------------------------
typedef std::vector<CPVSPortal*> vectorPVSPortal;

//-----------------------------------------------------------------------------
// Name : CI3DProcessadorPVS
// Desc : Processador PVS.
//-----------------------------------------------------------------------------
class CI3DProcessadorPVS
{
public:

    //-------------------------------------------------------------------------
    // Atributos Públicos
    //-------------------------------------------------------------------------
    bool CompilacaoTotal;
    //-------------------------------------------------------------------------
    // Construtores/Destrutores
    //-------------------------------------------------------------------------
             CI3DProcessadorPVS();
    virtual ~CI3DProcessadorPVS();

    //-------------------------------------------------------------------------
    // Métodos Privados
    //-------------------------------------------------------------------------
    bool            Process   ( CI3DArvoreBsp * pTree );

    unsigned long   GetPVSPortalCount( ) const { return (unsigned long)m_vpPVSPortals.size(); }
    CPVSPortal     *GetPVSPortal( unsigned long Index ) const { return (Index < m_vpPVSPortals.size()) ? m_vpPVSPortals[Index] : NULL; }

private:
    //-------------------------------------------------------------------------
    // Métodos Privados
    //-------------------------------------------------------------------------
    bool         GeneratePVSPortals( );
    bool         InitialPortalVis( );
    bool         CalcPortalVis( );
    void         PortalFlood( CPVSPortal * SourcePortal, unsigned char PortalVis[], unsigned long Leaf );
    bool         ExportPVS( CI3DArvoreBsp * pTree );
    void         GetPortalPlane( const CPVSPortal * pPortal, CIMTPlano& Plane );
    ULONG        CompressLeafSet ( UCHAR MasterPVS[], const UCHAR VisArray[], ULONG WritePos);
    ULONG        GetNextPortal();
    bool         RecursePVS( ULONG Leaf, CPVSPortal * SourcePortal, PVSDATA & PrevData );
    CPortalPoints * ClipToAntiPenumbra( CPortalPoints * Source, CPortalPoints * Target, CPortalPoints * Generator, bool ReverseClip );

    //-------------------------------------------------------------------------
    // Métodos Estáticos Privados
    //-------------------------------------------------------------------------
    static CPortalPoints *  AllocPortalPoints( CI3DPoligono * pPolygon, bool Duplicate );
    static bool             GetPVSBit( UCHAR VisArray[], ULONG DestLeaf );
    static void             SetPVSBit( UCHAR VisArray[], ULONG DestLeaf, bool Value = true );
    static void             FreePortalPoints( CPortalPoints * pPoints );

    //-------------------------------------------------------------------------
    // Atributos Privados
    //-------------------------------------------------------------------------
    CI3DArvoreBsp   *m_pTree;           // Arvore usada para compilação PVS.
    ULONG           m_PVSBytesPerSet;   // Numero de Bytes necessario para descrever a visibilidade de uma folha.
    vectorPVSPortal m_vpPVSPortals;     // Vetor de portais

};


#endif // CI3DPROCESSADORPVS_H
