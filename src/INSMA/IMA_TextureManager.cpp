/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMA_TextureManager.h"

CIMATextureManager::CIMATextureManager()
{
   I3D_QtdTexturas   = 0   ;
   I3D_PathTexturas  = CIUTGerenciadorPath::IUT_PathWorld + "Texturas/";

   AddTextura( I3D_PathTexturas + "DefaultBase.bmp"    , IGL_TEXTURE_LINEAR  );
   AddTextura( I3D_PathTexturas + "DefaultDetalhe.bmp" , IGL_TEXTURE_LINEAR  );
   AddTextura( I3D_PathTexturas + "DefaultNormal.bmp"  , IGL_TEXTURE_LINEAR  );
   AddTextura( I3D_PathTexturas + "DefaultCubeMap.bmp" , IGL_TEXTURE_LINEAR  );
   AddTextura( I3D_PathTexturas + "DefaultLightMap.bmp", IGL_TEXTURE_LINEAR  );
   AddTextura( I3D_PathTexturas + "DefaultColorMap.bmp", IGL_TEXTURE_LINEAR  );
}

CIMATextureManager::~CIMATextureManager()
{
    for(int i=0;i<I3D_QtdTexturas;i++)
    {
        I3D_VetorTexturas[i]->RemoveTextura();
    }

    I3D_VetorTexturas.clear();
}

int CIMATextureManager::AddTextura(QString pI3D_NomeTextura,int pIMA_TextureMode)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( ChecaDuplicado(pI3D_NomeTextura,IdDuplicado) ) return IdDuplicado;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    I3D_VetorTexturas.push_back(new CIMATextura());
    I3D_VetorTexturas[I3D_QtdTexturas]->CriaTextura(pI3D_NomeTextura,pIMA_TextureMode);

    //incrementa a quantidade de texturas
    I3D_QtdTexturas += 1;

    //retorna o indice atual da nova textura
    return I3D_QtdTexturas - 1;
}

int CIMATextureManager::AddCubeMap(QString pIMA_NomeRight,
                                   QString pIMA_NomeLeft,
                                   QString pIMA_NomeTop,
                                   QString pIMA_NomeBottom,
                                   QString pIMA_NomeBack,
                                   QString pIMA_NomeFront)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( ChecaDuplicado(pIMA_NomeRight,IdDuplicado) ) return IdDuplicado;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    I3D_VetorTexturas.push_back(new CIMATextura());
    I3D_VetorTexturas[I3D_QtdTexturas]->CriaCubeMap(pIMA_NomeRight,
                                                    pIMA_NomeLeft,
                                                    pIMA_NomeTop,
                                                    pIMA_NomeBottom,
                                                    pIMA_NomeBack,
                                                    pIMA_NomeFront);

    //incrementa a quantidade de texturas
    I3D_QtdTexturas += 1;

    //retorna o indice atual da nova textura
    return I3D_QtdTexturas - 1;
}

int CIMATextureManager::AddLayerTextura(QString pI3D_NomeTextura, QString pI3D_NomeLayer, int pI3D_CanalLayer)
{
    //Pega o Indice da Textura Base
    int Indice = PegaIndice(pI3D_NomeTextura);
    if(!ChecaExistente(Indice))return -1;

    //Adiciona o Layer na Base Unica de Texturas e retorna o Indice dela
    int IndiceLayer = AddTextura(pI3D_NomeLayer,IGL_TEXTURE_LINEAR);

    //Adiciona o Indice do Layer na Textura no Canal especificado
    I3D_VetorTexturas[Indice]->AddLayer(IndiceLayer,pI3D_CanalLayer);

    //Retorna o Indice da Textura Layer caso seja preciso utiliza-la posteriormente
    return IndiceLayer;
}

int CIMATextureManager::AddLayerTextura(int pI3D_IdTextura, QString pI3D_NomeLayer, int pI3D_CanalLayer)
{
    //Pega o Indice da Textura Base
    if(!ChecaExistente(pI3D_IdTextura))return -1;

    //Adiciona o Layer na Base Unica de Texturas e retorna o Indice dela
    int IndiceLayer = AddTextura(pI3D_NomeLayer,IGL_TEXTURE_LINEAR);

    //Adiciona o Indice do Layer na Textura no Canal especificado
    I3D_VetorTexturas[pI3D_IdTextura]->AddLayer(IndiceLayer,pI3D_CanalLayer);

    //Retorna o Indice da Textura Layer caso seja preciso utiliza-la posteriormente
    return IndiceLayer;
}

bool CIMATextureManager::AddLayerTextura(int pI3D_IdTextura, int pI3D_IdLayer, int pI3D_CanalLayer)
{
    //Pega o Indice da Textura Base
    if(!ChecaExistente(pI3D_IdTextura))return false;
    if(!ChecaExistente(pI3D_IdLayer  ))return false;

    //Adiciona o Indice do Layer na Textura no Canal especificado
    I3D_VetorTexturas[pI3D_IdTextura]->AddLayer(pI3D_IdLayer,pI3D_CanalLayer);

    //Retorna o Indice da Textura Layer caso seja preciso utiliza-la posteriormente
    return true;
}

bool CIMATextureManager::Prepara(int pIMA_IdTextura, int pIMA_ProgramId)
{
    I3D_VetorTexturas[pIMA_IdTextura]->Prepara(pIMA_ProgramId);
    return true;
}

int CIMATextureManager::PegaLayerTextura(int pIMA_IdTextura, int pIMA_CanalLayer)
{
    return I3D_VetorTexturas[pIMA_IdTextura]->PegaLayerTextura(pIMA_CanalLayer);
}

bool CIMATextureManager::PegaPropriedades(         int  pIMA_IdTextura ,
                                          unsigned int &pIMA_OpenGLId  ,
                                          unsigned int &pIMA_Altura    ,
                                          unsigned int &pIMA_Largura   ,
                                          unsigned int &pIMA_Formato   )
{
    pIMA_OpenGLId = I3D_VetorTexturas[pIMA_IdTextura]->I3D_IdT;
    pIMA_Altura   = I3D_VetorTexturas[pIMA_IdTextura]->I3D_Altura;
    pIMA_Largura  = I3D_VetorTexturas[pIMA_IdTextura]->I3D_Largura;
    pIMA_Formato  = I3D_VetorTexturas[pIMA_IdTextura]->I3D_Formato;
    return true;
}

unsigned char* CIMATextureManager::PegaDados(int  pIMA_IdTextura)
{
    return I3D_VetorTexturas[pIMA_IdTextura]->I3D_Imagem.ptr();
}

bool CIMATextureManager::ChecaDuplicado(QString pI3D_NomeTextura,int &IdExistente)
{
    for(int i=0;i<I3D_QtdTexturas;i++)
    {
        if(I3D_VetorTexturas[i]->I3D_NomeTextura == pI3D_NomeTextura)
        {
            IdExistente = i;
            return true;
        }
    }

    IdExistente = -1;

    return false;
}

bool CIMATextureManager::ChecaExistente(QString pI3D_NomeTextura)
{
    for(int i=0;i<I3D_QtdTexturas;i++)
    {
        if(I3D_VetorTexturas[i]->I3D_NomeTextura == pI3D_NomeTextura)
        {
            return true;
        }
    }
    return false;
}

bool CIMATextureManager::ChecaExistente(int pI3D_Indice)
{
    if(pI3D_Indice < 0                )return false;
    if(pI3D_Indice > I3D_QtdTexturas-1)return false;

    return true;
}

int CIMATextureManager::PegaIndice(QString pI3D_NomeTextura)
{
    for(int i=0;i<I3D_QtdTexturas;i++)
    {
        if(I3D_VetorTexturas[i]->I3D_NomeTextura == pI3D_NomeTextura)
        {
            return i;
        }
    }
    return -1;
}

bool CIMATextureManager::RenderToTexture(int pIMA_IdTextura, CIMDVideo *pIMA_Video)
{
    I3D_VetorTexturas[pIMA_IdTextura]->RenderToTexture(pIMA_Video);
    return true;
}
