/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CI3DMODELOHIERARQUICO_H
#define CI3DMODELOHIERARQUICO_H

#include "I3D_GlobalDef.h"
#include "I3D_Primitivo.h"
#include "I3D_Modelo.h"

class CI3DNoModelo
{
public:

    CI3DNoModelo(QString pNome);
   ~CI3DNoModelo(             ){}

    void          AddFilho            (CI3DNoModelo   *no     );
    void          AddModelo           (CI3DPrimitivo  *pModelo);

    void          RemoveFilho         (CI3DNoModelo   *no     );

    CI3DNoModelo*  PegaPai             (                       ) const;
    int            PegaQtdFilhos       (                       ) const;
    int            PegaQtdModelos      (                       ) const;
    QString        PegaNome            (                       ) const;
    CI3DModelo*    PegaModelo          (int pIdModelo          ) ;

    void          Render              (int pRenderMode     ,
                                       int pPolygonMode    ,
                                       int pShadingMode    );//operação de Renderização

    void          Translate           (CIMTVetor  pTransf  );//operação de Translação
    void          Rotate              (CIMTVetor  pTransf  );//operação de Rotação
    void          InvTransf           (                    );//operação de Transformação Inversa

    bool          TemModelo           (                    );//Este nó tem modelo?

private:
    //CI3DPrimitivo      *Modelo;
    vector<CI3DPrimitivo*>Modelo;
    QString               Nome  ;
    list<CI3DNoModelo*>   filho ;
    CI3DNoModelo         *pai;
    CIMTVetor             pos;
    CIMTVetor             rot;
};


class CI3DModeloHierarquico : public CI3DPrimitivo , public INSMA
{
public:
    CI3DModeloHierarquico(                                             );
    CI3DModeloHierarquico(QString   pNomeArquivo,bool pI3D_MakeLeftHand);


    //Rotinas para carregamento do modelo
    bool Carrega  (QString  pNomeArquivo,bool pI3D_MakeLeftHand);
    //Rotinas para Build do modelo
    bool AddModelo(int          pTipo  , CI3DNoModelo *pGrupo);
    bool AddModelo(int          pTipo  , QString       pGrp2 );
    bool AddModelo(QString      pFile  , QString       pGrp2 );
    bool AddModelo(CI3DModelo  *pModelo, QString       pGrp2 );

    bool AddGrupo (QString  pNome, CI3DNoModelo *pGrupo);
    bool AddGrupo (QString  pGrp1, QString       pGrp2 );

    bool Connect  (QString  pGrp1, QString       pGrp2 );
    //Rotinas para acesso a dados do Modelo
    int  PegaQtdGrupos (                 );
    int  PegaQtdModelos(QString  pGrp1   );
    int  PegaQtdModelos(int      pIdGrupo);
    int  PegaQtdModelos(                 );

    CI3DNoModelo* BuscaGrupo       (QString  pNome                 );
    CI3DNoModelo* BuscaGrupo       (int      pIdGrupo              );
    CI3DModelo  * BuscaModelo      (QString  pNome   ,int pIdModelo);
    CI3DModelo  * BuscaModelo      (int      pIdGrupo,int pIdModelo);
    CI3DModelo  * BuscaModeloIndice(int      pIndiceModelo);

    void Render   (int pRenderMode , int pPolygonMode , int pShadingMode);

private:
    CI3DNoModelo           *  hierarquia;
    list<CI3DPrimitivo     *> modelos;
    list<CI3DNoModelo      *> grupos;
    CIUTCarregadorArquivos *  importador;
    void Build();

    void ProcessaFilhoAssimp(aiNode *pFilho);
};

#endif // CI3DMODELOHIERARQUICO_H
