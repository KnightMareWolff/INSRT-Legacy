/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_FilaPrioridade.h"

/**************************************/
/*Construtor da Fila                  */
/**************************************/
CIUTFilaPrioridade::CIUTFilaPrioridade()
{
    IUT_Tamanho = 0;
    IUT_Inicio  = new CIUTNode();
    IUT_Fim     = new CIUTNode();

    //Estabelece prioridade Minima e Maxima de entrada.
    IUT_Inicio->IUT_Prioridade = 0;
    IUT_Fim   ->IUT_Prioridade = 999;

    IUT_Inicio->IUT_Proximo  = IUT_Fim;
    IUT_Inicio->IUT_Anterior = NULL;
    IUT_Fim   ->IUT_Anterior = IUT_Inicio;
    IUT_Fim   ->IUT_Proximo  = NULL;
}

/**************************************/
/*Destrutor da Fila                   */
/**************************************/
CIUTFilaPrioridade::~CIUTFilaPrioridade()
{
    limpa();
    delete IUT_Inicio;
    delete IUT_Fim;
}

/**************************************/
/*Insere No na Fila                   */
/**************************************/
void CIUTFilaPrioridade::entrafila(CIUTNode* pIUT_Node , int pIUT_Prioridade , QString pIUT_Nome)
{
    CIUTNode *novo = pIUT_Node;

    novo->IUT_Nome = pIUT_Nome;
    /****************************************************/
    /*Os Nos sao inseridos de acordo com sua prioridade */
    /*Neste caso quanto maior for o custo menor sera sua*/
    /*prioridade.                                       */
    /****************************************************/
    CIUTNode *temp = IUT_Inicio;
    while(pIUT_Prioridade > temp->IUT_Prioridade)
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

/**************************************/
/*Retira no da Fila                   */
/**************************************/
CIUTNode* CIUTFilaPrioridade::saifila()
{

    /******************************************/
    /*Sempre sendo removido o primeiro da fila*/
    /******************************************/
    CIUTNode* item = NULL;
    CIUTNode* temp;

    if(IUT_Tamanho > 0)
    {
        IUT_Inicio->IUT_Proximo->IUT_Proximo->IUT_Anterior = IUT_Inicio;
        temp = IUT_Inicio->IUT_Proximo;
        IUT_Inicio->IUT_Proximo = IUT_Inicio->IUT_Proximo->IUT_Proximo;

        item = temp;
        delete temp;
    }

    IUT_Tamanho--;

    return item;
}

/**************************************/
/*Limpa a Fila                        */
/**************************************/
void CIUTFilaPrioridade::limpa()
{
    while(!vazio())
    {
        saifila();
    }
}

/**************************************/
/*Verifica se a lista esta vazia      */
/**************************************/
bool CIUTFilaPrioridade::vazio()
{
    return IUT_Tamanho == 0;
}

/**************************************/
/*Busca pelo Nome                     */
/**************************************/
CIUTNode* CIUTFilaPrioridade::busca(QString nome)
{
    CIUTNode *temp = IUT_Inicio->IUT_Proximo;

    while(temp->IUT_Proximo != NULL)
    {
        if(temp->IUT_Nome == nome)
        {
            return temp;
        }
        temp = temp->IUT_Proximo;
    }

    return NULL;
}

/**************************************/
/*Busca pelo Nome                     */
/**************************************/
CIUTNode* CIUTFilaPrioridade::busca(unsigned int Id)
{
    CIUTNode *temp;

    if(Id > IUT_Tamanho)return NULL;

    temp = IUT_Inicio->IUT_Proximo;

    int posicao = 0;

    while(temp->IUT_Proximo != NULL)
    {
        if(posicao == Id)
        {
            return temp;
        }
        temp = temp->IUT_Proximo;
        posicao++;
    }

    return NULL;
}

/**************************************/
/*Retorna o Tamanho da Fila           */
/**************************************/
unsigned int CIUTFilaPrioridade::Tam()
{
    return IUT_Tamanho;
}
