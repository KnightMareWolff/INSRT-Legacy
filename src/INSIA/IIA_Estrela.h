/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef _IIA_ESTRELA_H_
#define _IIA_ESTRELA_H_

#include "IIA_Mapa.h"

/********************************************************/
/*Classe responsavel pela manutensao de um no utilizado */
/*Na montagem do caminho a ser percorrido               */
/********************************************************/
class CIIANoMapa
{
public:
	
    CIIANoMapa(){ n_custo = PosNoX = PosNoY = 0;n_pai = 0;}

    CIIANoMapa(const int x,
		    const int y, 
            CIIANoMapa  *pai,
			const int custo){ PosNoX = x; PosNoY = y; n_pai = pai; n_custo = custo; }
	
    CIIANoMapa(const CIIANoMapa &copia);
	
    virtual ~CIIANoMapa() { n_pai = 0; }
    
    virtual CIIANoMapa &operator= (const CIIANoMapa &opr);
    virtual bool        operator==(const CIIANoMapa &opr);
    virtual bool        operator< (const CIIANoMapa &opr);
    virtual bool        operator> (const CIIANoMapa &opr);

    void         SetaPai  (CIIANoMapa*  pai     ) { n_pai = pai;}
	virtual void SetaCusto(const int custo   );
	virtual int  PegaCusto(                  ) const;
    bool         igual    (const CIIANoMapa &opr) const {return ((PosNoX==opr.PosNoX)&&
		                                                      (PosNoY==opr.PosNoY)); }

	int      PosNoX,
		     PosNoY;

	int      n_custo;

    CIIANoMapa *n_pai;

};

/********************************************************/
/*Classe responsavel pela manutensao de um no euristico */
/*Utilizado pelo algoritmo AEstrela                     */
/********************************************************/
class CIIANoEstrela : public CIIANoMapa
{
public:
	
    CIIANoEstrela() : CIIANoMapa() { g = f = h = 0; }
    CIIANoEstrela(const CIIANoEstrela &copia);
	
    virtual ~CIIANoEstrela() { n_pai = 0; }

    virtual CIIANoEstrela &operator=(const CIIANoEstrela &opr);
	
	virtual void SetaCusto(const int custo);
	virtual int  PegaCusto(               )const;

	int g;
	int f;
	int h;

};

/**************************************************************/
/*Classe responsavel pela manutencao dos nos que sao incluidos*/
/*e excluidos durante o processamento do algoritmo  AEstrela  */
/*Esta Manutencao se da atraves de prioridade com relacao ao  */
/*Custo estimado de cada No.                                  */
/**************************************************************/
class CIIAFilaPrioridade
{
public:
     CIIAFilaPrioridade();
    ~CIIAFilaPrioridade() { limpa(); delete ini->nofila; delete fim->nofila; delete ini; delete fim; }

	void     limpa    (             );
	bool     vazio    (             ) { return tam == 0; }
    void     entrafila( CIIANoMapa *no );
    CIIANoMapa* saifila  (             );
    void     remove   ( CIIANoMapa *no );
    bool     contem   ( CIIANoMapa *no ) const;

private:
    class CIIANoFila
	{
	public:
        CIIANoFila() { nofila = 0; proximo = anterior = 0; }
        CIIANoFila(CIIANoMapa *no) { nofila = no; proximo = anterior = 0; }

        CIIANoMapa   *nofila;
        CIIANoFila   *proximo;
        CIIANoFila   *anterior;
	};

	unsigned int tam;
    CIIANoFila *ini;
    CIIANoFila *fim;
};

/*************************************/
/*Enumerador de retorno do andamento */
/*do processo de busca               */
/*************************************/
typedef enum ANDAMENTO 
{ 
	PROCURANDO  , 
	ACHOUCAMINHO, 
	IMPOSSIVEL 
}STDANDAMENTO;

/*****************************************************/
/*Classe responsavel pela manutencao do processamento*/
/*Propriamente dito do algoritmo AEstrela            */
/*****************************************************/
class CIIAestrela
{
public:
	
    CIIAMapa *grid;

             CIIAestrela      (                );
             CIIAestrela      (CIIAMapa* m_grid);
    virtual ~CIIAestrela      (                );

    virtual STDANDAMENTO Passo      (                     );
    virtual void         reset      (                     );
    int                  estimativa (CIIANoEstrela *origem);
    CIIANoEstrela*       PegaCaminho(                     ){return NoAtual;}
protected:
	virtual void VisitarNo(int x, int y);
private:
    CIIAFilaPrioridade  lista_aberta ;
    CIIAFilaPrioridade  lista_fechada;
    CIIANoEstrela *     NoInicio     ,
                  *     NoAtual      ,
                  *     NoFim        ;
    CIIANoEstrela **    GridNos      ;
    float               PesoEuristica;
};

#endif
