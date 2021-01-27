/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "IIA_GlobalDef.h"
#include "IIA_Estrela.h"

/**************************************/
/*Construtor de copia                 */
/**************************************/
CIIANoMapa::CIIANoMapa(const CIIANoMapa &copia)
{ 
	PosNoX  = copia.PosNoX; 
	PosNoY  = copia.PosNoY; 
	n_pai   = copia.n_pai; 
	n_custo = copia.n_custo; 
}

/**************************************/
/*Construtor do No                    */
/**************************************/
CIIANoMapa & CIIANoMapa::operator=(const CIIANoMapa &opr)
{ 
	PosNoX = opr.PosNoX; 
	PosNoY = opr.PosNoY; 
	n_pai  = opr.n_pai; 
	n_custo= opr.n_custo; 
	
	return *this; 
}

/**************************************/
/*operador de igualdade               */
/**************************************/
bool CIIANoMapa::operator==(const CIIANoMapa &opr)
{
	return this->igual(opr);
}

/**************************************/
/*operador de comparacao              */
/**************************************/
bool CIIANoMapa::operator<(const CIIANoMapa &opr)
{
	return n_custo < opr.n_custo;
}

/**************************************/
/*operador de comparacao              */
/**************************************/
bool CIIANoMapa::operator>(const CIIANoMapa &opr)
{
	return n_custo > opr.n_custo;
}

/**************************************/
/*Atribui o custo do No               */
/**************************************/
void CIIANoMapa::SetaCusto(const int custo)
{ 
	n_custo = custo; 
}

/**************************************/
/*Pega o Custo do No                  */
/**************************************/
int CIIANoMapa::PegaCusto() const
{ 
	return n_custo; 
}

/**************************************/
/*Construtor do NoEstrela             */
/**************************************/
CIIANoEstrela::CIIANoEstrela(const CIIANoEstrela &copia)
{
	PosNoX  = copia.PosNoX; 
	PosNoY  = copia.PosNoY; 
	n_pai   = copia.n_pai; 
	n_custo = copia.n_custo; 
	g       = copia.g;
	h       = copia.h;
	f       = copia.f;
}

/**************************************/
/*operador de atribuicao              */
/**************************************/
CIIANoEstrela & CIIANoEstrela::operator=(const CIIANoEstrela &opr)
{
	PosNoX  = opr.PosNoX; 
	PosNoY  = opr.PosNoY; 
	n_pai   = opr.n_pai; 
	n_custo = opr.n_custo; 
	g       = opr.g;
	h       = opr.h;
	f       = opr.f;

	return *this;
}

/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
void CIIANoEstrela::SetaCusto(const int custo)
{ 
	f = custo; 
}

/**************************************/
/*Retorna o custo do NoEstrela        */
/**************************************/
int CIIANoEstrela::PegaCusto() const
{ 
	return f; 
}

/**************************************/
/*Construtor da Fila                  */
/**************************************/
CIIAFilaPrioridade::CIIAFilaPrioridade()
{
	tam = 0;
    ini = new CIIANoFila(new CIIANoMapa(-1, -1, NULL,-1));
    fim = new CIIANoFila(new CIIANoMapa(-1, -1, NULL,10000000));
	ini->proximo  = fim;
	ini->anterior = NULL;
	fim->anterior = ini;
	fim->proximo  = NULL;
}

/**************************************/
/*Insere No na Fila                   */
/**************************************/
void CIIAFilaPrioridade::entrafila( CIIANoMapa * no )
{
    CIIANoFila *novo = new CIIANoFila(no);

	/****************************************************/
	/*Os Nos sao inseridos de acordo com sua prioridade */
	/*Neste caso quanto maior for o custo menor sera sua*/
	/*prioridade.                                       */
	/****************************************************/
    CIIANoFila *temp = ini;
	while(no->PegaCusto() > temp->nofila->PegaCusto())
	{
		temp = temp->proximo;
	}

	/****************************************/
	/*Insere o no na posicao anterior       */
	/****************************************/
	novo->anterior          = temp->anterior;
	novo->proximo           = temp;
	temp->anterior          = novo;
	novo->anterior->proximo = novo;

	tam++;
}

/**************************************/
/*Retira no da Fila                   */
/**************************************/
CIIANoMapa* CIIAFilaPrioridade::saifila()
{
	
	/******************************************/
	/*Sempre sendo removido o primeiro da fila*/
	/******************************************/
    CIIANoMapa *item = NULL;
    CIIANoFila *temp;

	if(tam > 0)
	{
		ini->proximo->proximo->anterior = ini;
		temp = ini->proximo;		
		ini->proximo = ini->proximo->proximo;

		item = temp->nofila;
		delete temp;
	}

	tam--;

	return item;
}

/**************************************/
/*Exclui no da Fila                   */
/**************************************/
void CIIAFilaPrioridade::remove(CIIANoMapa* no)
{
	/*************************************/
	/*Exclui invariavelmente sem criterio*/
	/*************************************/
    CIIANoFila *temp = ini;
	while(!no->igual(*(temp->nofila)))
	{
		temp = temp->proximo;
	}

	temp->proximo->anterior = temp->anterior;
	temp->anterior->proximo = temp->proximo;

	tam--;

	delete temp;
}

/**************************************/
/*Verifica se o No existe na Fila     */
/**************************************/
bool CIIAFilaPrioridade::contem(CIIANoMapa* no) const
{
    CIIANoFila *temp = ini;

	while(temp != fim)
	{
		if(temp->nofila->igual(*no))
			return true;
		temp = temp->proximo;
	}
	return false;
}

/**************************************/
/*Limpa a Fila                        */
/**************************************/
void CIIAFilaPrioridade::limpa()
{
	while(!vazio())
	{
		saifila();
	}
}

/**************************************/
/*Construtor do AEstrela              */
/**************************************/
CIIAestrela::CIIAestrela()
{
	NoAtual       = NULL;
	GridNos       = NULL;
	grid          = NULL;
	PesoEuristica = 5000.0f;
}

/**************************************/
/*Construtor do AEstrela              */
/**************************************/
CIIAestrela::CIIAestrela(CIIAMapa *m_grid)
{ 
	NoAtual       = NULL;
	GridNos       = NULL;
	grid          = m_grid;
	PesoEuristica = 5000.0f;
}

/**************************************/
/*Destrutor do AEsrterla              */
/**************************************/
CIIAestrela::~CIIAestrela()
{
	/*****************************/
	/*Limpa a memoria alocada    */
	/*****************************/
	if(GridNos != NULL)
	{
		for(int i = 0; i < grid->PegaTam(); i++)
		{
			delete [] GridNos[i];
		}
		delete [] GridNos;
	}
}

/**************************************/
/*Realiza um Passo da Procura         */
/**************************************/
STDANDAMENTO CIIAestrela::Passo()
{
	int x, y;
	/******************************************/
	/*Verifica se existe alguem a ser visitado*/
	/******************************************/
	if(!lista_aberta.vazio())
	{
		/********************************/
		/*Pega este No para verificacao */
		/********************************/
        NoAtual = (CIIANoEstrela*)lista_aberta.saifila();
		/*********************************/
		/*Se chagamos ao objetivo retorna*/
		/*********************************/
		if(NoAtual->igual(*NoFim))
		{
			return ACHOUCAMINHO;
		}

		/*********************************/
		/*Realiza as inclusoes nas listas*/
		/*aberta e fechada de acordo com */
		/*os nos adjacentes              */
		/*********************************/
		/*********************/
		/*Leste              */
		/*********************/
		x = NoAtual->PosNoX+1;
		y = NoAtual->PosNoY;
		if(NoAtual->PosNoX < (grid->PegaTam() - 1))
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Sudeste            */
		/*********************/
		x = NoAtual->PosNoX+1;
		y = NoAtual->PosNoY+1;
		if(NoAtual->PosNoX < (grid->PegaTam() - 1) && NoAtual->PosNoY < (grid->PegaTam() - 1))
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Sul                */
		/*********************/
		x = NoAtual->PosNoX;
		y = NoAtual->PosNoY+1;
		if(NoAtual->PosNoY < (grid->PegaTam() - 1))
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Sudoeste           */
		/*********************/
		x = NoAtual->PosNoX-1;
		y = NoAtual->PosNoY+1;
		if(NoAtual->PosNoY < (grid->PegaTam() - 1) && NoAtual->PosNoX > 0)
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Oeste              */
		/*********************/
		x = NoAtual->PosNoX-1;
		y = NoAtual->PosNoY;
		if(NoAtual->PosNoX > 0)
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Noroeste           */
		/*********************/
		x = NoAtual->PosNoX-1;
		y = NoAtual->PosNoY-1;
		if(NoAtual->PosNoX > 0 && NoAtual->PosNoY > 0)
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Norte              */
		/*********************/
		x = NoAtual->PosNoX;
		y = NoAtual->PosNoY-1;
		if(NoAtual->PosNoY > 0)
		{
			VisitarNo(x, y);
		}

		/*********************/
		/*Nordeste           */
		/*********************/
		x = NoAtual->PosNoX+1;
		y = NoAtual->PosNoY-1;
		if(NoAtual->PosNoY > 0 && NoAtual->PosNoX < (grid->PegaTam() - 1))
		{
			VisitarNo(x, y);
		}
		
		/*******************************/
		/*Insere na lista fechada o no */
		/*ja visitado                  */
		/*******************************/
		lista_fechada.entrafila(NoAtual);

		/*******************************/
		/*Retorna que esta procurando o*/
		/*Caminho ainda...             */
		/*******************************/
		return PROCURANDO;
	}
	
	/***********************************/
	/*Retorna que e impossivel achar o */
	/*caminho para este objetivo       */
	/***********************************/
	return IMPOSSIVEL;
}

/**************************************/
/*Visita o No Apropriado              */
/**************************************/
void CIIAestrela::VisitarNo(int x, int y)
{
	int novo_g;

	/*************************************/
	/*Se o caminho esta bloqueado retorna*/
	/*************************************/
	if(grid->PegaCusto(x, y) == BLOQUEADO)
		return;

	/******************************************/
	/*Calcula o novo custo                    */
	/******************************************/
	novo_g = NoAtual->g + grid->PegaCusto(x, y);
	
	/*********************************************/
	/*Se ja passamos por este no ou ja temos o   */
	/*No de menor custo nao precisamos prosseguir*/
	/*********************************************/
	if( (lista_aberta .contem(&GridNos[x][y]) || 
		 lista_fechada.contem(&GridNos[x][y]))&& 
		 GridNos[x][y].g <= novo_g) return;
    
    /******************************************************/
	/*Linka este no a seu pai e calcula a estimativa      */
	/******************************************************/
	GridNos[x][y].n_pai = NoAtual;
	GridNos[x][y].g     = novo_g;
	GridNos[x][y].h     = estimativa( &GridNos[x][y] );
	GridNos[x][y].f     = GridNos[x][y].g + GridNos[x][y].h;

	/**********************************************************/
	/*Caso esteja na lista fechada removemos para que possamos*/
	/*visita-lo Novamente.                                    */
	/**********************************************************/
	if(lista_fechada.contem(&GridNos[x][y]))
	{
		lista_fechada.remove(&GridNos[x][y]);
	}

    /**********************************************/
	/*Caso nao esteja na lista aberta o inserimos.*/
	/**********************************************/
	if(!lista_aberta.contem(&GridNos[x][y]))
	{
		lista_aberta.entrafila(&GridNos[x][y]);
	}
	else
	{
		/*****************************************************/
		/*Caso esteja na lista aberta o retiramos e inserimos*/
		/*Novamente para que sua nova posicao seja atualizada*/
		/*Ja que seu custo mudou tambem...                   */
		/*****************************************************/
		lista_aberta.remove(&GridNos[x][y]);
		lista_aberta.entrafila(&GridNos[x][y]);
	}
}

/**************************************/
/*Limpa para nova Busca               */
/**************************************/
void CIIAestrela::reset()
{
	int x, y;
	
	/**************************/
	/*Limpa as listas         */
	/**************************/
	lista_aberta .limpa();
	lista_fechada.limpa();

	/************************************/
	/*Libera memoria previamente alocada*/
	/************************************/
	if(GridNos != NULL)
	{
		for(int i = 0; i < grid->PegaTam(); i++)
		{
			delete [] GridNos[i];
		}
		delete [] GridNos;
	}

	NoAtual = NULL;
	GridNos = NULL;

	/************************************************/
	/*Aloca o grid de nos de acordo com o mapa      */
	/************************************************/
    GridNos = new CIIANoEstrela*[grid->PegaTam()];
	for(int i = 0; i < grid->PegaTam(); i++)
	{
        GridNos[i] = new CIIANoEstrela[grid->PegaTam()];
		for(int j = 0; j < grid->PegaTam(); j++)
		{
			GridNos[i][j].PosNoX  = i;
			GridNos[i][j].PosNoY  = j;
			GridNos[i][j].n_custo = INT_MAX;
		}
	}

	/*************************/
	/*Atribui inicio da busca*/
	/*************************/
	grid->PegaIni(x, y);
	NoInicio = &GridNos[x][y];

	/*************************/
	/*Atribui fim  da  busca */
	/*************************/
	grid->PegaFim(x, y);
	NoFim   = &GridNos[x][y];

	/*******************************/
	/*Calcula a primeira estimativa*/
	/*******************************/
	NoInicio->g = 0;		
	NoInicio->h = estimativa( NoInicio );
	NoInicio->f = NoInicio->g + NoInicio->h;

	/******************************************/
	/*Inclui o inicio da busca na lista aberta*/
	/******************************************/
	lista_aberta.entrafila(NoInicio);
}

/**************************************/
/*Realiza o calculo da euristica      */
/**************************************/
int CIIAestrela::estimativa(CIIANoEstrela *origem)
{
	int est;
	
	/***************************************************************/
	/*Calcula a distancia euclidiada deste ponto ate o fim da busca*/
	/***************************************************************/
	est = (int)floorf(sqrtf((float)(origem->PosNoX - NoFim->PosNoX)*
		                           (origem->PosNoX - NoFim->PosNoX)+ 
						    (float)(origem->PosNoY - NoFim->PosNoY)*
							       (origem->PosNoY - NoFim->PosNoY)));

	/********************************************************/
	/*Aplica multiplicador para aumentar o peso da euristica*/
	/********************************************************/
	return (int)(est*PesoEuristica);
}
