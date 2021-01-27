#include "IGO_Mundo.h"

CIGOMundo::CIGOMundo():
    IGO_Mundo("Grafo do Mundo")
{
    pGrafo01 = new CIUTGrafo<CIGONivel>("Grafo Nivel 01");
    pGrafo02 = new CIUTGrafo<CIGONivel>("Grafo Nivel 02");

    pNivel01 = new CIGONivel();
    pNivel01->AddTerreno();


    pNivel02 = new CIGONivel();
    pNivel02->AddFonte();
    pNivel02->AddTexto();

    pNivel03 = new CIGONivel();
    pNivel03->AddSky  ();

    pGrafo01->AddDados(pNivel01);
    pGrafo02->AddDados(pNivel02);

    IGO_Mundo.AddDados(pNivel03);
    IGO_Mundo.AddFilho(pGrafo01);
    IGO_Mundo.AddFilho(pGrafo02);
}

void CIGOMundo::Render()
{
    int QtdNiveis = IGO_Mundo.PegaQtdFilhos();

    ((CIGONivel *)IGO_Mundo.PegaDados())->Render();

    for (int i=0 ; i<QtdNiveis ; i++ )
    {
        CIUTGrafo<CIGONivel> *pFilho = IGO_Mundo.PegaFilho(i);

        ((CIGONivel *)pFilho->PegaDados())->Render();
    }
}
