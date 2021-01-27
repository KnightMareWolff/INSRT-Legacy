/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "IIA_GlobalDef.h"
#include "IIA_Mapa.h"

/**************************************/
/*Construtor do Mapa                  */
/**************************************/
CIIAMapa::CIIAMapa(const int tamanho)
{
    m_grid = NULL;
    m_grid = new CIIACelulaMapa*[tamanho];
    for(int i = 0 ; i < tamanho; i++)
    {
        m_grid[i] = NULL;
        m_grid[i] = new CIIACelulaMapa[tamanho];
    }

    tam = tamanho;

    PosIniX = PosIniY = 0;
    PosFimX = PosFimY = tam - 1;
}

/**************************************/
/*Destrutor do  Mapa                  */
/**************************************/
CIIAMapa::~CIIAMapa()
{
    /******************************/
    /*Limpa toda a memoria alocada*/
    /******************************/
    if(m_grid != NULL)
    {
        for(int i = 0; i < tam; i++)
        {
            if(m_grid[i] != NULL)
            {
                delete [] m_grid[i];
                m_grid[i] = NULL;
            }
        }

        delete [] m_grid;
        m_grid = NULL;
    }
}

/**************************************/
/*Retorna o tamanho do mapa           */
/**************************************/
int  CIIAMapa::PegaTam()
{
    return tam;
}

/**************************************/
/*Retorna o tamanho do mapa           */
/**************************************/
int CIIAMapa::PegaBloqueados()
{
    int custo;
    int qtd=0;

    for(int i = 0; i < tam ; i++)
    {
        for(int j = 0; j < tam ; j++)
        {
            custo=PegaCusto(i,j);
            if(custo==BLOQUEADO)
            {
               qtd++;
            }
        }
    }
    return qtd;
}

/****************************************/
/*Retorna o custo de uma posicao no mapa*/
/****************************************/
int  CIIAMapa::PegaCusto(const int x, const int y)
{
    return m_grid[x][y].PegaCusto();
}

/**************************************/
/*atribui um custo                    */
/**************************************/
void CIIAMapa::SetaCusto(const int x, const int y, const int custo)
{
    m_grid[x][y].SetaCusto(custo);
}

/**************************************/
/*atribui a posicao inicial de busca  */
/**************************************/
void CIIAMapa::SetaIni(const int x, const int y)
{
    PosIniX=x;
    PosIniY=y;
}

/**************************************/
/*retorna posicao inicio              */
/**************************************/
void CIIAMapa::PegaIni(int &x, int &y)
{
   x=PosIniX;
   y=PosIniY;
}

/**************************************/
/*atribui posicao fim do mapa         */
/**************************************/
void CIIAMapa::SetaFim(const int x, const int y)
{
    PosFimX=x;
    PosFimY=y;
}

/**************************************/
/*retorna posicao fim do Mapa         */
/**************************************/
void CIIAMapa::PegaFim(int &x, int &y)
{
    x=PosFimX;
    y=PosFimY;
}


/**************************************/
/*Construtor da celula Mapa           */
/**************************************/
CIIACelulaMapa::CIIACelulaMapa()
{
    m_custo = 1;
}

/**************************************/
/*Construtor da celula Mapa           */
/**************************************/
CIIACelulaMapa::CIIACelulaMapa(const int custo)
{
    m_custo = custo;
}

/**************************************/
/*Construtor de copia                 */
/**************************************/
CIIACelulaMapa::CIIACelulaMapa(const CIIACelulaMapa& copia)
{
    m_custo = copia.m_custo;
}

/**************************************/
/*operador de atribuicao              */
/**************************************/
CIIACelulaMapa &CIIACelulaMapa::operator=(const CIIACelulaMapa& opr)
{
    m_custo = opr.m_custo;

    return (*this);
}

/**************************************/
/*retorna o custo da celula           */
/**************************************/
int  CIIACelulaMapa::PegaCusto()
{
    return m_custo;
}

/**************************************/
/*atribuit o custo na celula          */
/**************************************/
void CIIACelulaMapa::SetaCusto(const int custo)
{
    m_custo = custo;
}

