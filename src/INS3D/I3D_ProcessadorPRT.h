/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CI3DPROCESSADORPRT_H
#define CI3DPROCESSADORPRT_H

#include "I3D_GlobalDef.h"
#include "I3D_ArvoreBsp.h"
#include "I3D_Portal.h"

class CI3DProcessadorPRT
{
public:

    bool CompilacaoTotal;
    //-------------------------------------------------------------------------
    // Constructors & Destructors for This Class.
    //-------------------------------------------------------------------------
             CI3DProcessadorPRT();
    virtual ~CI3DProcessadorPRT();

    //-------------------------------------------------------------------------
    // Public Functions for This Class.
    //-------------------------------------------------------------------------
    bool         Processa( CI3DArvoreBsp * pTree );

private:
    //-------------------------------------------------------------------------
    // Private Functions for This Class.
    //-------------------------------------------------------------------------
    bool            VerificaPortalDuplicado( CI3DPortal * CheckPortal, unsigned long& Index );
    CI3DPortal     *ClipPortal             ( unsigned long Node, CI3DPortal * pPortal );
    bool            ProcuraFolha           ( unsigned long Leaf, unsigned long Node );
    unsigned long   ClassificaFolha        ( unsigned long Leaf, unsigned long Node );
    void            RemovePortalLista      ( CI3DPortal * RemovePortal );
    bool            AdicionaPortais        ( CI3DPortal * PortalList );

    CI3DArvoreBsp  *PRTBSP;            //Arvore usada para compilar o set de Portais.
};

#endif // CI3DPROCESSADORPRT_H
