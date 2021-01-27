/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IMA_ColorMap.h"

CIMAColorMap::CIMAColorMap()
{
    IMA_MapColors[0] [0]=72;  IMA_MapColors[0] [1]=68;  IMA_MapColors[0] [2]=154;
    IMA_MapColors[1] [0]=84;  IMA_MapColors[1] [1]=125; IMA_MapColors[1] [2]=228;
    IMA_MapColors[2] [0]=120; IMA_MapColors[2] [1]=202; IMA_MapColors[2] [2]=172;
    IMA_MapColors[3] [0]=248; IMA_MapColors[3] [1]=205; IMA_MapColors[3] [2]=136;
    IMA_MapColors[4] [0]=223; IMA_MapColors[4] [1]=130; IMA_MapColors[4] [2]=47;
    IMA_MapColors[5] [0]=237; IMA_MapColors[5] [1]=149; IMA_MapColors[5] [2]=91;
    IMA_MapColors[6] [0]=156; IMA_MapColors[6] [1]=193; IMA_MapColors[6] [2]=9;
    IMA_MapColors[7] [0]=180; IMA_MapColors[7] [1]=213; IMA_MapColors[7] [2]=47;
    IMA_MapColors[8] [0]=163; IMA_MapColors[8] [1]=176; IMA_MapColors[8] [2]=112;
    IMA_MapColors[9] [0]=163; IMA_MapColors[9] [1]=176; IMA_MapColors[9] [2]=112;
    IMA_MapColors[10][0]=194; IMA_MapColors[10][1]=161; IMA_MapColors[10][2]=118;
    IMA_MapColors[11][0]=165; IMA_MapColors[11][1]=120; IMA_MapColors[11][2]=71;
    IMA_MapColors[12][0]=183; IMA_MapColors[12][1]=154; IMA_MapColors[12][2]=125;
    IMA_MapColors[13][0]=195; IMA_MapColors[13][1]=189; IMA_MapColors[13][2]=181;
    IMA_MapColors[14][0]=235; IMA_MapColors[14][1]=232; IMA_MapColors[14][2]=227;
    IMA_MapColors[15][0]=225; IMA_MapColors[15][1]=225; IMA_MapColors[15][2]=225;
}

void CIMAColorMap::Build(CIMADepthMap *pIMA_ReferenceMap,QString pIMA_NomeArquivo)
{
    int   pAlturaPixel=0;
    float shade;
    float heightPct;
    unsigned char *pTexWalk;
    QRgb  value;
    float r,g,b;

    QImage ImgColor;//Imagem Base para Texturização(Geracao automatica de textura).

    ImgColor = QImage(pIMA_ReferenceMap->PegaTam(),pIMA_ReferenceMap->PegaTam(), QImage::Format_RGB32);

    /****************************************/
    /*Adiciona o Total de Vertices do Painel*/
    /****************************************/
    for ( int X = 0;  X < (pIMA_ReferenceMap->PegaTam()); X ++)
    {
       for ( int Y = 0; Y < (pIMA_ReferenceMap->PegaTam()); Y ++ )
       {
           shade=0.6f + (0.3f * rand())/RAND_MAX;	// Cria um padraozinho randomico(noise) para o pixel
           heightPct    = pAlturaPixel / 16.0f;
           pAlturaPixel = pIMA_ReferenceMap->PegaAlturaPixel(X,Y);
           pAlturaPixel/=16;
           if ( shade        > 1 )  shade = 1;
           if ( shade        < 0 )  shade = 0;
           if ( pAlturaPixel > 0 )
           {
              r  = (shade * ((heightPct * IMA_MapColors[pAlturaPixel][0]) + ((1.0f-heightPct) * IMA_MapColors[pAlturaPixel-1][0])));
              g  = (shade * ((heightPct * IMA_MapColors[pAlturaPixel][1]) + ((1.0f-heightPct) * IMA_MapColors[pAlturaPixel-1][1])));
              b  = (shade * ((heightPct * IMA_MapColors[pAlturaPixel][2]) + ((1.0f-heightPct) * IMA_MapColors[pAlturaPixel-1][2])));
              value = qRgb(r,g,b);
           }
           else	// Special case for sea.
           {
              r = (shade * IMA_MapColors[0][0]);
              g = (shade * IMA_MapColors[0][1]);
              b = (shade * IMA_MapColors[0][2]);
              value = qRgb(r,g,b);
           }

           ImgColor.setPixel(X,Y,value);
       }
    }

    //PATH DEBBUG VIA COMPILADOR
    //descobrir pq via qrc dá pau...

    if(!ImgColor.save(pIMA_NomeArquivo))
    {
        qWarning() << "Atenção! Erro ao gerar textura automatica Painel!.";
    }

}

