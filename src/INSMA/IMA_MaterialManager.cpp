/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMA_MaterialManager.h"


CIMAMaterialManager::CIMAMaterialManager()
{

   IMA_QtdMateriais   = 0   ;

   AddMaterial("Material Padrão"     , IGL_MATERIAL_TEXTURE);
   AddMaterial("Material Selecionado", IGL_MATERIAL_COLOR  );
}

int CIMAMaterialManager::AddMaterial(QString pIMA_NomeMaterial, int pIMA_MaterialMode)
{
    int             IdDuplicado = 0   ;
    //Caso já exista material com este Nome retorna o ID do material existente
    if ( ChecaDuplicado(pIMA_NomeMaterial,IdDuplicado) ) return IdDuplicado;

    IMA_VetorMateriais.push_back(new CIMAMaterial());
    //Repassa os valores para o Novo material(Usado a Quantidade previa sem incremento como indice do vetor)
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaNomeMaterial(pIMA_NomeMaterial);
    //Define qual sera o material mode usado na renderizacao
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaMaterialMode(pIMA_MaterialMode);

    //Incrementa contador de materiais
    IMA_QtdMateriais += 1;

    //Retorna indice atual onde o material foi alocado
    return IMA_QtdMateriais - 1;
}

int CIMAMaterialManager::AddMaterial(QString pIMA_NomeMaterial     ,
                                     CIMACor pIMA_CorDifusa        ,
                                     CIMACor pIMA_CorAmbiente      ,
                                     CIMACor pIMA_CorEmissiva      ,
                                     CIMACor pIMA_CorSpecular      ,
                                     float   pIMA_Opacidade        ,
                                     float   pIMA_Brilho           ,
                                     int     pIMA_MaterialMode     )
{
    int             IdDuplicado = 0   ;

    //Caso já exista material com este Nome retorna o ID do material existente
    if ( ChecaDuplicado(pIMA_NomeMaterial,IdDuplicado) ) return IdDuplicado;

    //Repassa os valores para o Novo material(Usado a Quantidade previa sem incremento como indice do vetor)
    IMA_VetorMateriais.push_back(new CIMAMaterial());

    IMA_VetorMateriais[IMA_QtdMateriais]->SetaNomeMaterial(pIMA_NomeMaterial);
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaMaterialMode(pIMA_MaterialMode);
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaCorDifusa   (pIMA_CorDifusa   );
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaCorAmbiente (pIMA_CorAmbiente );
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaCorEmissiva (pIMA_CorEmissiva );
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaCorSpecular (pIMA_CorSpecular );
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaOpacidade   (pIMA_Opacidade   );
    IMA_VetorMateriais[IMA_QtdMateriais]->SetaPotencia    (pIMA_Brilho      );

    //Incrementa contador de materiais
    IMA_QtdMateriais += 1;

    //Retorna indice atual onde o material foi alocado
    return IMA_QtdMateriais - 1;
}

bool CIMAMaterialManager::SetaMaterial(int     pI3D_Indice        ,
                                       CIMACor pI3D_CorDifusa     ,
                                       CIMACor pI3D_CorAmbiente   ,
                                       CIMACor pI3D_CorEmissiva   ,
                                       CIMACor pI3D_CorSpecular   ,
                                       float   pI3D_Opacidade     ,
                                       float   pI3D_Brilho        )
{
    //Como o Indice é chave de pesquisa, checamos se o mesmo existe
    if(!ChecaExistente(pI3D_Indice))return false;

    //Repassa os valores para o Novo material pelo indice do vetor
    IMA_VetorMateriais[pI3D_Indice]->SetaCorDifusa   (pI3D_CorDifusa   );
    IMA_VetorMateriais[pI3D_Indice]->SetaCorAmbiente (pI3D_CorAmbiente );
    IMA_VetorMateriais[pI3D_Indice]->SetaCorEmissiva (pI3D_CorEmissiva );
    IMA_VetorMateriais[pI3D_Indice]->SetaCorSpecular (pI3D_CorSpecular );
    IMA_VetorMateriais[pI3D_Indice]->SetaOpacidade   (pI3D_Opacidade   );
    IMA_VetorMateriais[pI3D_Indice]->SetaPotencia    (pI3D_Brilho      );

    return true;
}

bool CIMAMaterialManager::SetaMaterial(QString pI3D_NomeMaterial  ,
                                       CIMACor pI3D_CorDifusa     ,
                                       CIMACor pI3D_CorAmbiente   ,
                                       CIMACor pI3D_CorEmissiva   ,
                                       CIMACor pI3D_CorSpecular   ,
                                       float   pI3D_Opacidade     ,
                                       float   pI3D_Brilho        )
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    if(!ChecaExistente(pI3D_NomeMaterial))return false;

    for(int i=0;i<IMA_QtdMateriais;i++)
    {
        if(IMA_VetorMateriais[i]->PegaNomeMaterial() == pI3D_NomeMaterial)
        {
            //Repassa os valores para o Novo material pelo indice do vetor
            IMA_VetorMateriais[i]->SetaCorDifusa   (pI3D_CorDifusa   );
            IMA_VetorMateriais[i]->SetaCorAmbiente (pI3D_CorAmbiente );
            IMA_VetorMateriais[i]->SetaCorEmissiva (pI3D_CorEmissiva );
            IMA_VetorMateriais[i]->SetaCorSpecular (pI3D_CorSpecular );
            IMA_VetorMateriais[i]->SetaOpacidade   (pI3D_Opacidade   );
            IMA_VetorMateriais[i]->SetaPotencia    (pI3D_Brilho      );
        }
    }

    return true;
}

bool CIMAMaterialManager::SetaNomeMat(int pI3D_Indice, QString pI3D_NomeMaterial)
{
    IMA_VetorMateriais[pI3D_Indice]->SetaNomeMaterial(pI3D_NomeMaterial);
    return true;
}

bool CIMAMaterialManager::SetaRejeicaoCor(int pI3D_Indice, bool pI3D_Rejeita, CIMACor pI3D_CorAlpha)
{
    IMA_VetorMateriais[pI3D_Indice]->SetaRejeicaoCor(pI3D_Rejeita,pI3D_CorAlpha);
    return true;
}

int CIMAMaterialManager::AddTextura(QString pIMA_NomeMaterial, QString pIMA_NomeTextura , int  pIMA_TextureMode )
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = PegaIndice(pIMA_NomeMaterial);

    if(!ChecaExistente(Indice))return -1;

    return IMA_VetorMateriais[Indice]->AddVetorTextura(pIMA_NomeTextura,pIMA_TextureMode);

}

int CIMAMaterialManager::AddCubeMap(QString pIMA_NomeMaterial,
                                    QString pI3D_NomeTexturaRight,
                                    QString pI3D_NomeTexturaLeft,
                                    QString pI3D_NomeTexturaTop,
                                    QString pI3D_NomeTexturaBottom,
                                    QString pI3D_NomeTexturaBack,
                                    QString pI3D_NomeTexturaFront)
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = PegaIndice(pIMA_NomeMaterial);

    if(!ChecaExistente(Indice))return -1;

    return IMA_VetorMateriais[Indice]->AddCubeMap(pI3D_NomeTexturaRight,
                                                  pI3D_NomeTexturaLeft,
                                                  pI3D_NomeTexturaTop,
                                                  pI3D_NomeTexturaBottom,
                                                  pI3D_NomeTexturaBack,
                                                  pI3D_NomeTexturaFront);
}

int CIMAMaterialManager::AddTextura(int pIMA_Indice, QString pIMA_NomeTextura , int  pIMA_TextureMode )
{
    //Como o Indice é chave de pesquisa, checamos se o mesmo existe
    if(!ChecaExistente(pIMA_Indice))return -1;

    return IMA_VetorMateriais[pIMA_Indice]->AddVetorTextura(pIMA_NomeTextura,pIMA_TextureMode);
}

int CIMAMaterialManager::AddCubeMap(int     pIMA_Indice          ,
                                    QString pI3D_NomeTexturaRight,
                                    QString pI3D_NomeTexturaLeft,
                                    QString pI3D_NomeTexturaTop,
                                    QString pI3D_NomeTexturaBottom,
                                    QString pI3D_NomeTexturaBack,
                                    QString pI3D_NomeTexturaFront)
{
    //Como o Indice é chave de pesquisa, checamos se o mesmo existe
    if(!ChecaExistente(pIMA_Indice))return -1;

    return IMA_VetorMateriais[pIMA_Indice]->AddCubeMap(pI3D_NomeTexturaRight,
                                                       pI3D_NomeTexturaLeft,
                                                       pI3D_NomeTexturaTop,
                                                       pI3D_NomeTexturaBottom,
                                                       pI3D_NomeTexturaBack,
                                                       pI3D_NomeTexturaFront);

}

bool CIMAMaterialManager::AddLayerTex(QString pI3D_NomeMaterial, QString pI3D_NomeTextura, QString pI3D_NomeLayer, int pI3D_CanalTextura)
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = PegaIndice(pI3D_NomeMaterial);
    if(!ChecaExistente(Indice))return false;

    IMA_VetorMateriais[Indice]->AddLayerTextura(pI3D_NomeTextura,pI3D_NomeLayer,pI3D_CanalTextura);

    return true;
}

bool CIMAMaterialManager::AddLayerTex(int pI3D_Indice, QString pI3D_NomeTextura, QString pI3D_NomeLayer, int pI3D_CanalTextura)
{
    //Como o Indice é chave de pesquisa, checamos se o mesmo existe
    if(!ChecaExistente(pI3D_Indice))return false;

    IMA_VetorMateriais[pI3D_Indice]->AddLayerTextura(pI3D_NomeTextura,pI3D_NomeLayer,pI3D_CanalTextura);

    return true;
}

bool CIMAMaterialManager::AddLayerTex(int pI3D_Indice, int pI3D_IndiceTextura, QString pI3D_NomeLayer, int pI3D_CanalTextura)
{
    //Como o Indice é chave de pesquisa, checamos se o mesmo existe
    if(!ChecaExistente(pI3D_Indice))return false;

    IMA_VetorMateriais[pI3D_Indice]->AddLayerTextura(pI3D_IndiceTextura,pI3D_NomeLayer,pI3D_CanalTextura);

    return true;
}

bool CIMAMaterialManager::Prepara(int pIMA_ProgramId,int pI3D_Indice)
{
    if(!ChecaExistente(pI3D_Indice))return false;

    IMA_VetorMateriais[pI3D_Indice]->Prepara(pIMA_ProgramId);

    return true;
}

bool CIMAMaterialManager::Prepara(int pIMA_ProgramId,int pI3D_Indice,int pI3D_IndiceTextura)
{
    if(!ChecaExistente(pI3D_Indice))return false;

    IMA_VetorMateriais[pI3D_Indice]->Prepara(pIMA_ProgramId,pI3D_IndiceTextura);

    return true;
}

bool CIMAMaterialManager::Prepara(int pIMA_ProgramId,QString pI3D_NomeMaterial)
{
    int Indice = PegaIndice(pI3D_NomeMaterial);

    if(!ChecaExistente(Indice))return false;

    IMA_VetorMateriais[Indice]->Prepara(pIMA_ProgramId);

    return true;
}

bool CIMAMaterialManager::Prepara(int pIMA_ProgramId, QString pI3D_NomeMaterial, int pI3D_IndiceTextura)
{
    int Indice = PegaIndice(pI3D_NomeMaterial);

    if(!ChecaExistente(Indice))return false;

    IMA_VetorMateriais[Indice]->Prepara(pIMA_ProgramId,pI3D_IndiceTextura);

    return true;
}

bool CIMAMaterialManager::ChecaDuplicado(QString pI3D_NomeMaterial,int &IdExistente)
{
    for(int i=0;i<IMA_QtdMateriais;i++)
    {
        if(IMA_VetorMateriais[i]->PegaNomeMaterial() == pI3D_NomeMaterial)
        {
            IdExistente = i;
            return true;
        }
    }

    IdExistente = -1;

    return false;
}

bool CIMAMaterialManager::ChecaExistente(QString pI3D_NomeMaterial)
{
    for(int i=0;i<IMA_QtdMateriais;i++)
    {
        if(IMA_VetorMateriais[i]->PegaNomeMaterial() == pI3D_NomeMaterial)
        {
            return true;
        }
    }
    return false;
}

bool CIMAMaterialManager::ChecaExistente(int pI3D_Indice)
{
    if(pI3D_Indice < 0                 )return false;
    if(pI3D_Indice > IMA_QtdMateriais-1)return false;

    return true;
}

int CIMAMaterialManager::PegaIndice(QString pI3D_NomeMaterial)
{
    for(int i=0;i<IMA_QtdMateriais;i++)
    {
        if(IMA_VetorMateriais[i]->PegaNomeMaterial() == pI3D_NomeMaterial)
        {
            return i;
        }
    }
    return -1;
}

int CIMAMaterialManager::PegaQtdTexturas(int pI3D_Indice)
{
    if(!ChecaExistente(pI3D_Indice))return 0;

    return IMA_VetorMateriais[pI3D_Indice]->PegaQtdTexturas();
}

int CIMAMaterialManager::PegaQtdTexturas(QString pI3D_NomeMaterial)
{
    if(!ChecaExistente(pI3D_NomeMaterial))return 0;
    int Indice = PegaIndice(pI3D_NomeMaterial);

    return IMA_VetorMateriais[Indice]->PegaQtdTexturas();
}

int CIMAMaterialManager::PegaQtdMateriais()
{
    return IMA_VetorMateriais.size();
}

bool CIMAMaterialManager::RenderToTexture(QString      pIMA_NomeMaterial  ,
                                          CIMDVideo   *pIMA_Video         )
{
    if(!ChecaExistente(pIMA_NomeMaterial))return false;
    int Indice = PegaIndice(pIMA_NomeMaterial);

    IMA_VetorMateriais[Indice]->RenderToTexture(pIMA_Video);

    return true;
}

bool CIMAMaterialManager::RenderToTexture(int          pIMA_Indice        ,
                                          CIMDVideo   *pIMA_Video         )
{
    if(!ChecaExistente(pIMA_Indice))return false;

    IMA_VetorMateriais[pIMA_Indice]->RenderToTexture(pIMA_Video);

    return true;
}
