/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_PORTAL_H
#define I3D_PORTAL_H

#include "I3D_GlobalDef.h"
#include "I3D_Poligono.h"

/************************************************************/
/*Nome da Classe      : CKbcPortal
/*
/*Descricao           :
/*
/************************************************************/
class CI3DPortal : public CI3DPoligono
{
public:

    /*------------------------------------------------------------*/
    /* Contrutores e Destrutores                                  */
    /*------------------------------------------------------------*/
    CI3DPortal( );

    /*------------------------------------------------------------*/
    /* Variaveis Públicas                                         */
    /*------------------------------------------------------------*/
    CI3DPortal     *Proximo ;               // Proximo  da Lista
    CI3DPortal     *Anterior;               // Anterior da Lista
    unsigned char   NumeroFolhas;           // Numero de folhas no portal
    unsigned long   NoGerador;              // No Gerador
    unsigned long   FolhaProprietaria[2];   // Folha Proprietaria

    /*------------------------------------------------------------*/
    /* Metodos da Classe                                          */
    /*------------------------------------------------------------*/

    virtual bool Divide( const CIMTPlano& Plano     ,
                         CI3DPortal * DivisorFrente ,
                         CI3DPortal * DivisorAtras  ); //Divide o portal em dois fragmentos

};

#endif // CI3DPORTAL_H
