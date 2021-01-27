/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_ARVOREBSP_H
#define I3D_ARVOREBSP_H

#include "I3D_GlobalDef.h"
#include "I3D_NoBsp.h"
#include "I3D_FaceBsp.h"
#include "I3D_FolhaBsp.h"
#include "I3D_Portal.h"

//-----------------------------------------------------------------------------
// Vetores Utilizados para gerenciamento dos funcionamento do particionamento
//-----------------------------------------------------------------------------
typedef std::vector<CI3DNoBsp*   > VetorNos;
typedef std::vector<CIMTPlano*   > VetorPlanos;
typedef std::vector<CI3DFolhaBsp*> VetorFolhas;
typedef std::vector<CI3DFaceBsp* > VetorFaceBsp;
typedef std::vector<CI3DPortal*  > VetorPortaisBsp;

class CI3DArvoreBsp
{
public:

    unsigned long   I3D_TpArvore           ;// Tipo de Arvore para compilacao
    float           I3D_HeuristicaDivisao  ;// Balanceamento entre divisoes vs Importancia
    unsigned long   I3D_AcumuladorDivisores;// Numero de Divisores para acumulo
    bool            I3D_RemoveFolhasIlegais;// Remove Folhas Ilegais
    bool            I3D_AddPoligonosBorda  ;// Adiciona Faces de Uma Bbox
    VetorFaceBsp    I3D_VetorFacesRemovidas;// Vetor das Faces Removidas
    UCHAR          *I3D_PVSData            ;// Bloco de dados de Visão(Possibility Visibility Settings)
    unsigned long   I3D_PVSDataSize        ;// Tamanho de dados alocados no PVS
    bool            I3D_PVSCompressed      ;// Informa se o PVS é compactado ou não
    //-------------------------------------------------------------------------
    // Construtores & Destrutores desta Classe.
    //-------------------------------------------------------------------------
             CI3DArvoreBsp();
            ~CI3DArvoreBsp();


    unsigned long   PegaQtdNos    ( ) const { return (unsigned long)I3D_VetorNos    .size(); }
    unsigned long   PegaQtdFolhas ( ) const { return (unsigned long)I3D_VetorFolhas .size(); }
    unsigned long   PegaQtdPlanos ( ) const { return (unsigned long)I3D_VetorPlanos .size(); }
    unsigned long   PegaQtdFaces  ( ) const { return (unsigned long)I3D_VetorFaces  .size(); }
    unsigned long   PegaQtdPortais( ) const { return (unsigned long)I3D_VetorPortais.size(); }

    CI3DNoBsp      *PegaNo    ( unsigned long Index ) const { return (Index < I3D_VetorNos    .size()) ? I3D_VetorNos    [Index] : NULL; }
    CIMTPlano      *PegaPlano ( unsigned long Index ) const { return (Index < I3D_VetorPlanos .size()) ? I3D_VetorPlanos [Index] : NULL; }
    CI3DFolhaBsp   *PegaFolha ( unsigned long Index ) const { return (Index < I3D_VetorFolhas .size()) ? I3D_VetorFolhas [Index] : NULL; }
    CI3DFaceBsp    *PegaFace  ( unsigned long Index ) const { return (Index < I3D_VetorFaces  .size()) ? I3D_VetorFaces  [Index] : NULL; }
    CI3DPortal     *PegaPortal( unsigned long Index ) const { return (Index < I3D_VetorPortais.size()) ? I3D_VetorPortais[Index] : NULL; }

    void            SetaNo    ( unsigned long Index, CI3DNoBsp   * pNo    ){ if (Index < I3D_VetorNos   .size ()) I3D_VetorNos    [Index] = pNo    ; }
    void            SetaPlano ( unsigned long Index, CIMTPlano   * pPlano ){ if (Index < I3D_VetorPlanos.size ()) I3D_VetorPlanos [Index] = pPlano ; }
    void            SetaFolha ( unsigned long Index, CI3DFolhaBsp* pFolha ){ if (Index < I3D_VetorFolhas.size ()) I3D_VetorFolhas [Index] = pFolha ; }
    void            SetaFace  ( unsigned long Index, CI3DFaceBsp * pFace  ){ if (Index < I3D_VetorFaces .size ()) I3D_VetorFaces  [Index] = pFace  ; }
    void            SetaPortal( unsigned long Index, CI3DPortal  * pPortal){ if (Index < I3D_VetorPortais.size()) I3D_VetorPortais[Index] = pPortal; }

    bool            SetaPVS( UCHAR m_PVSData[], unsigned long PVSSize, bool pPVSCompressed );

    bool            IncrementaFaces  ();
    bool            IncrementaNos    ();
    bool            IncrementaFolhas ();
    bool            IncrementaPlanos ();
    bool            IncrementaPortais();

    bool            ClipTree( CI3DArvoreBsp * pTree                  ,
                              bool            ClipSolid              ,
                              bool            RemoveCoPlanar         ,
                              unsigned long   CurrentNode  = 0       ,
                              CI3DFaceBsp *   pFaceList    = NULL   );

    void            ReparaDivisao();
    void            InicializaPVS();
    void            CalculaBorda ();

    long            ProcuraFolha( const CIMTVetor& pPosicao ) const;

    bool            CruzamentoArvore( const CI3DArvoreBsp * pTree ) const;
    bool            CruzamentoFace  ( const CI3DFace * pFace, unsigned long Node = 0 ) const;
    bool            CruzamentoEsfera( const CIMTVetor& SphereCenter,
                                            float      SphereRadius,
                                            unsigned long      Node = 0    ) const;

    void             CompilaArvore          (                                         );

    bool             AdicionaFaces          ( CI3DFace **    ppFaces                  ,
                                              unsigned long  pQtdFaces        = 1     ,
                                              bool           pSalvaOrigem     = false);

    bool             AdicionaBordasPoligonos(bool pSalvaOrigem);

    void             LimpaArvore( );
    void             Inverte    ( );

    const CIMTBorda& PegaBorda( ) const { return I3D_BordaTotal; }
    //-------------------------------------------------------------------------
    // Metodos Staticos Publicos.
    //-------------------------------------------------------------------------
    static CI3DFaceBsp   *AlocaFaceBsp  ( const CI3DFace * I3D_Replica = NULL );
    static CI3DPortal    *AlocaPortalBsp(                                     );


private:
    void            ConstroiVetorPlanos(                              );
    void            Constroi           ( unsigned long No             ,
                                         CI3DFaceBsp * pListaFaces    );

    void            ProcessaFacesFolha ( CI3DFolhaBsp * pFolha        ,
                                         CI3DFaceBsp  * pListaFaces   );

    CI3DFaceBsp    *CriterioSelecao    ( CI3DFaceBsp *  pListaFaces   ,
                                         float          pHeuristica   ,
                                         unsigned long  pAcumuladorDiv);

    unsigned long   ContaDivisores     ( CI3DFaceBsp * pListaFaces ) const;
    void            LimpaListaFaces    ( CI3DFaceBsp * pListaFaces );
    void            Lixeira            ( CI3DFaceBsp * pListaFaces );

    //-------------------------------------------------------------------------
    // Atributos Privados
    //-------------------------------------------------------------------------
    CI3DFaceBsp    *I3D_ListaFaces    ;
    unsigned long   I3D_NumFacesAtivas;
    VetorNos        I3D_VetorNos      ;
    VetorPlanos     I3D_VetorPlanos   ;
    VetorFolhas     I3D_VetorFolhas   ;
    VetorFaceBsp    I3D_VetorFaces    ;
    VetorPortaisBsp I3D_VetorPortais  ;
    VetorFaceBsp    I3D_VetorLixo     ;
    CIMTBorda       I3D_BordaTotal    ;

};

#endif // I3D_ARVOREBSP_H
