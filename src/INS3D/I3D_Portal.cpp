#include "I3D_Portal.h"

/************************************************************/
/*Nome do Método      : CKbcPortal()
/*
/*Objetivo            : Construtor Padrão da classe CKbcPortal
/************************************************************/
CI3DPortal::CI3DPortal()
{
    //Inicializa os Itens Especificos do Portal
    FolhaProprietaria[0]    = NO_OWNER;
    FolhaProprietaria[1]    = NO_OWNER;
    NumeroFolhas            =  0;
    NoGerador               = -1;
    Proximo                 = NULL;
    Anterior                = NULL;
}

/************************************************************/
/*Nome do Método      : ~CI3DPortal()
/*
/*Objetivo            : Divide o Portal em dois segmentos
/************************************************************/
bool CI3DPortal::Divide( const CIMTPlano& Plano, CI3DPortal * DivisorFrente, CI3DPortal * DivisorAtras)
{
    //Chama Implementação Base da Divisão
    CI3DPoligono::Divide( Plano, DivisorFrente, DivisorAtras);

    //Copia Valores remanescentes
    if (DivisorFrente)
    {
        DivisorFrente->NumeroFolhas         = NumeroFolhas;
        DivisorFrente->NoGerador            = NoGerador;
        DivisorFrente->FolhaProprietaria[0] = FolhaProprietaria[0];
        DivisorFrente->FolhaProprietaria[1] = FolhaProprietaria[1];
    }

    if (DivisorAtras)
    {
        DivisorAtras->NumeroFolhas          = NumeroFolhas;
        DivisorAtras->NoGerador             = NoGerador;
        DivisorAtras->FolhaProprietaria[0]  = FolhaProprietaria[0];
        DivisorAtras->FolhaProprietaria[1]  = FolhaProprietaria[1];
    }

    return true;
}



