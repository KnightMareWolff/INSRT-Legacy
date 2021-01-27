/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef IIA_MAPA_H
#define IIA_MAPA_H

/*************************************************/
/*Classe responsavel pela manutencao de peso em  */
/*uma determinada posicao do mapa                */
/*************************************************/
class CIIACelulaMapa
{
   public:

   CIIACelulaMapa(                        );
   CIIACelulaMapa(const int custo         );
   CIIACelulaMapa(const CIIACelulaMapa& copia);
   CIIACelulaMapa &operator=(const CIIACelulaMapa& opr);

   int  PegaCusto();
   void SetaCusto(const int custo);

   private:

   int m_custo;

};

/***************************************************/
/*Classe responsavel pela manutencao do mapa onde a*/
/*busca sera realizada                             */
/***************************************************/
class CIIAMapa
{
public:

    CIIAMapa(const int tamanho);

    virtual ~CIIAMapa();

    int  PegaTam();
    int  PegaCusto(const int x, const int y);
    void SetaCusto(const int x, const int y, const int custo);

    void SetaIni(const int x, const int y);
    void PegaIni(int &x, int &y);

    void SetaFim(const int x, const int y);
    void PegaFim(int &x, int &y);

    int  PegaBloqueados();

private:

    CIIACelulaMapa **m_grid;
    int tam;
    int PosIniX;
    int	PosIniY;
    int	PosFimX;
    int	PosFimY;
};


#endif // IIA_MAPA_H
