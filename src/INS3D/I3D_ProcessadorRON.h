/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_PROCESSADORRON_H
#define I3D_PROCESSADORRON_H

#include "I3D_GlobalDef.h"
#include "I3D_Modelo.h"

//-----------------------------------------------------------------------------
// Definições Diversas Locais
//-----------------------------------------------------------------------------
#define BLOCO_MEMORIA_RON  100

//-----------------------------------------------------------------------------
// Typedefs Utilizados apenas para simplificar a utilização de STL.
//-----------------------------------------------------------------------------
typedef std::vector<CI3DModelo *>     VetorMesh;

class CI3DProcessadorRON
{
public:
    //-------------------------------------------------------------------------
    // Construtores e Destrutores da Classe
    //-------------------------------------------------------------------------
             CI3DProcessadorRON();
    virtual ~CI3DProcessadorRON();

    //-------------------------------------------------------------------------
    // Métodos Públicos da Classe
    //-------------------------------------------------------------------------
    bool            AddPrimitivo           (CI3DModelo *pPrimitivo      );
    CI3DModelo*     PegaPrimitivoResultante(                            ) const;
    bool            Processa               (                            );
    void            Finaliza               (                            );

private:
    //-------------------------------------------------------------------------
    // Metodos Privados da Classe
    //-------------------------------------------------------------------------
    void            PercorrePortais( CI3DArvoreBsp* pTree, bool pVisited[], ULONG Leaf );

    //-------------------------------------------------------------------------
    // Atributos Privados da Classe
    //-------------------------------------------------------------------------
    VetorMesh       mListaPrimitivos;     //Lista de Primitivos para Processamento HSR.
    CI3DModelo*     mPrimitivoResultante; //Primitivo Unico como resultado de Processamento.
};

#endif // CI3DPROCESSADORRON_H
