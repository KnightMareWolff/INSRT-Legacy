/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_Lista.h"

CIUTLista::CIUTLista(QString pIUT_NomeLista)
{
    IUT_Tamanho = 0;
    IUT_Inicio  = new CIUTNode();
    IUT_Fim     = new CIUTNode();

    //Estabelece os Nós Iniciais da Lista.
    IUT_Inicio->IUT_Proximo  = IUT_Fim;
    IUT_Inicio->IUT_Anterior = NULL;
    IUT_Fim   ->IUT_Anterior = IUT_Inicio;
    IUT_Fim   ->IUT_Proximo  = NULL;

    IUT_Nome = pIUT_NomeLista;
}

CIUTLista::~CIUTLista()
{
    Limpa();
    delete IUT_Inicio;
    delete IUT_Fim;
}

void          CIUTLista::Limpa    (                    )
{
    int Index = 0;
    while(!Vazio())
    {
        Remove(Index);
        Index++;
    }
}
bool          CIUTLista::Vazio    (                    )
{
    return IUT_Tamanho == 0;
}
void          CIUTLista::Add      (CIUTNode* pIUT_Node )
{
    CIUTNode *novo = pIUT_Node;

    /****************************************************/
    /*O no é inserido no final da lista                 */
    /****************************************************/
    CIUTNode *temp = IUT_Inicio;
    while(temp != IUT_Fim)
    {
        temp = temp->IUT_Proximo;
    }

    /****************************************/
    /*Insere o no na posicao anterior       */
    /****************************************/
    novo->IUT_Anterior              = temp->IUT_Anterior;
    novo->IUT_Proximo               = temp;
    temp->IUT_Anterior              = novo;
    novo->IUT_Anterior->IUT_Proximo = novo;

    IUT_Tamanho++;
}
void          CIUTLista::Remove   (CIUTNode* pIUT_Node )
{
    CIUTNode *temp  = NULL;
    int       index = 0   ;

    if(IUT_Tamanho > 0)
    {
        temp = IUT_Inicio;

        while(temp != IUT_Fim)
        {
            temp = temp->IUT_Proximo;

            if(temp == pIUT_Node)
            {
                /****************************************/
                /*Insere o no na posicao anterior       */
                /****************************************/
                temp->IUT_Proximo->IUT_Anterior = temp->IUT_Anterior;
                temp->IUT_Anterior              = temp->IUT_Proximo;

                delete temp;

                IUT_Tamanho--;
            }

            index++;
        }
    }
}
void          CIUTLista::Remove   (unsigned int pIUT_Id)
{
    CIUTNode *temp  = NULL;
    int       index = 0   ;

    if(IUT_Tamanho > 0)
    {
        temp = IUT_Inicio;

        while(temp != IUT_Fim)
        {
            temp = temp->IUT_Proximo;

            if(index == pIUT_Id)
            {
                /****************************************/
                /*Insere o no na posicao anterior       */
                /****************************************/
                temp->IUT_Proximo->IUT_Anterior = temp->IUT_Anterior;
                temp->IUT_Anterior              = temp->IUT_Proximo;

                delete temp;

                IUT_Tamanho--;
            }

            index++;
        }
    }
}
CIUTNode*     CIUTLista::Busca    (unsigned int pIUT_Id)
{
    CIUTNode *temp;

    if(pIUT_Id > IUT_Tamanho)return NULL;

    temp = IUT_Inicio->IUT_Proximo;

    int posicao = 0;

    while(posicao<IUT_Tamanho)
    {
        if(posicao == pIUT_Id)
        {
            return temp;
        }
        temp = temp->IUT_Proximo;
        posicao++;
    }

    return  NULL;
}
unsigned int  CIUTLista::Tam      (                    )
{
   return IUT_Tamanho;
}
