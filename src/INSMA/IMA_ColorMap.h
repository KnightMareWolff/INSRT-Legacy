/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_COLORMAP_H
#define IMA_COLORMAP_H

#include "IMA_GlobalDef.h"
#include "IMA_DepthMap.h"

class CIMAColorMap
{
public:
    CIMAColorMap();

    void Build(CIMADepthMap *pIMA_ReferenceMap, QString pIMA_NomeArquivo);

private:
    float          IMA_MapColors[16][3];//Tabela de Cores(Geracao automatica de textura).
    int            IMA_TamMapa;
    int            IMA_TamQuad;
    float          IMA_Escala ;
    vector<float>  IMA_Cores  ;
};

#endif // CIMACOLORMAP_H
