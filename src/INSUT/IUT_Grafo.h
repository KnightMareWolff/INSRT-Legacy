/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CIUTGRAFO_H
#define CIUTGRAFO_H

#include "IUT_GlobalDef.h"
#include "IUT_Lista.h"

template<class T>
class CIUTGrafo : public CIUTNode
{
private:
    CIUTLista IUT_Filhos;
    T*        IUT_Dados ;

protected:
    CIUTGrafo *IUT_Pai;


public:
               CIUTGrafo           (QString pIUT_NomeGrafo         );
    virtual   ~CIUTGrafo           (                               ) {}
    void       AddFilho            (CIUTGrafo* pIUT_Grafo          );
    void       RemoveFilho         (CIUTGrafo* pIUT_Grafo          );
    void       AddDados            (T*         pIUT_Dados          );
    CIUTGrafo* PegaPai             (                               );
    T*         PegaDados           (                               );
    CIUTGrafo* PegaFilho           (int     pIUT_IdFilho           );
    int        PegaQtdFilhos       (                               );
};

template<class T>
CIUTGrafo<T>::CIUTGrafo(QString pIUT_NomeGrafo):
    IUT_Pai(NULL),
    IUT_Filhos(pIUT_NomeGrafo)
{

}


template<class T>
void CIUTGrafo<T>::AddFilho(CIUTGrafo* pIUT_Grafo)
{
    IUT_Filhos.Add(pIUT_Grafo);
    pIUT_Grafo->IUT_Pai = this;
}


template<class T>
void CIUTGrafo<T>::RemoveFilho(CIUTGrafo* pIUT_Grafo)
{
    IUT_Filhos.Remove(pIUT_Grafo);
    delete pIUT_Grafo;
}

template<class T>
void CIUTGrafo<T>::AddDados(T* pIUT_Dados)
{
    IUT_Dados = pIUT_Dados;
}

template<class T>
int CIUTGrafo<T>::PegaQtdFilhos()
{
    return IUT_Filhos.Tam();
}

template<class T>
T* CIUTGrafo<T>::PegaDados()
{
    return IUT_Dados;
}

template<class T>
CIUTGrafo<T>* CIUTGrafo<T>::PegaPai()
{
    return IUT_Pai;
}

template<class T>
CIUTGrafo<T>* CIUTGrafo<T>::PegaFilho(int pIUT_IdFilho)
{
    CIUTNode *pNode = IUT_Filhos.Busca(pIUT_IdFilho);

    return (CIUTGrafo<T>*)pNode;
}

#endif // CIUTGRAFO_H
