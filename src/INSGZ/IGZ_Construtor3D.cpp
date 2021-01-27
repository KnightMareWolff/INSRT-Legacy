/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "IGZ_Construtor3D.h"


CIGZConstrutor3D::CIGZConstrutor3D()
{
    pSky     = NULL;
    pTerreno = NULL;
    pTexto   = NULL;
    pFonte   = NULL;
    pCubo    = NULL;
}

void CIGZConstrutor3D::Render()
{
    if(pSky)
    {
       pSky->Render(IGL_MODE_RENDER        ,
                    IGL_RENDER_TRIANGLES   ,
                    IGL_SHADING_MODE_NOONE);
    }

    if(pTerreno)
    {
       pTerreno->Render(IGL_MODE_RENDER            ,
                        IGL_RENDER_TRIANGLE_STRIP  ,
                        IGL_SHADING_MODE_FLAT);
    }

    if(pTexto)
    {
       pTexto->Render(IGL_MODE_RENDER     ,
                      IGL_RENDER_TRIANGLES,
                      IGL_SHADING_MODE_FLAT);
    }

    if(pCubo)
    {
        pCubo->Render(IGL_MODE_RENDER     ,
                      IGL_RENDER_TRIANGLES,
                      IGL_SHADING_MODE_FLAT);
    }
}

void CIGZConstrutor3D::Constroi(CIMTVetor pCentro)
{
    pSky->Translate(pCentro,false);
}

CIMTVetor CIGZConstrutor3D::PegaCentro()
{
    return pTerreno->I3D_Pos;
    //return pSky->mPos;
}

CIMTVetor CIGZConstrutor3D::PegaPosTrr(int x, int y)
{
    CIMTVetor pos;
    pos.x=x;
    pos.y=pTerreno->PegaAltura(x,y);
    pos.z=y;
    return pos;
}

void CIGZConstrutor3D::Animar()
{
    pSky->Rotate(true,CIMTVetor(0.0f,0.1f,0.0f),pTerreno->I3D_Pos);
}

bool CIGZConstrutor3D::AddTerreno()
{
    pTerreno = new CI3DPainelHeightMap();

    //Adiciona o HeightMap para a Construção do Terreno(Não é utilizado como textura)
    //pTerreno->AddHeightMap(CIUTGerenciadorPath::IUT_PathWorld + "Terrenos/Piso.bmp");
    pTerreno->AddHeightMap(128,8,1);

    //Cria Os Materiais do Terreno.
    int IdMaterial;
    int IdTexturaBase;

    //Adiciona o material e texturas adicionais do terreno(Utilizados para renderização normal)
    IdMaterial = pINSMAMaterialManager->AddMaterial("Material Terreno Construtor",IGL_MATERIAL_MIXED);

    IdTexturaBase = pINSMAMaterialManager->AddTextura(IdMaterial,
                                                      CIUTGerenciadorPath::IUT_PathWorld + "Terrenos/ColorMap.bmp",
                                                      IGL_TEXTURE_GEN_ST);

    //Adiciona Layer Detail na Textura Base(Id 0)
    pINSMAMaterialManager->AddLayerTex(IdMaterial                                                    ,
                                       IdTexturaBase                                                 ,
                                       CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Piso_Areia.bmp",
                                       IMA_LAYER_CHN_DETAIL                                          );

    pTerreno->I3D_Mesh->SetaMaterial(IdMaterial);

    return true;
}

bool CIGZConstrutor3D::AddSky()
{
    int IdMatSky;

    /*************************/
    /*Cria Uma SkyBox        */
    /*************************/
    pSky     = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                              CIMTVetor(4096.0f,4096.0f,4096.0f),
                              IGL_WINMODE_CW);


    IdMatSky=INSMA::pINSMAMaterialManager->AddMaterial("Material SkyBox DemoProject",IGL_MATERIAL_CUBEMAP);

    INSMA::pINSMAMaterialManager->AddCubeMap(IdMatSky,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" );


    pSky->I3D_Mesh->SetaMaterial(IdMatSky);

    pSky->I3D_Mesh->SetaNormalFace(0,CIMTVetor( 0.0f,-1.0f, 0.0f));
    pSky->I3D_Mesh->SetaNormalFace(1,CIMTVetor( 1.0f, 0.0f, 0.0f));
    pSky->I3D_Mesh->SetaNormalFace(2,CIMTVetor( 0.0f, 0.0f,-1.0f));
    pSky->I3D_Mesh->SetaNormalFace(3,CIMTVetor( 0.0f, 0.0f, 1.0f));
    pSky->I3D_Mesh->SetaNormalFace(4,CIMTVetor(-1.0f, 0.0f, 0.0f));
    pSky->I3D_Mesh->SetaNormalFace(5,CIMTVetor( 0.0f, 1.0f, 0.0f));

    pSky->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    return true;
}

bool CIGZConstrutor3D::AddFonte()
{
    pFonte = new CI3DFonte();
    pFonte->AddFont(CIUTGerenciadorPath::IUT_PathWorld + "Fontes/Font.bmp","Fonte Padrão");
    pFonte->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    pFonte->Rotate(true,CIMTVetor(90.0f,0.0f,0.0f),pFonte->I3D_Pos);
    return true;
}

bool CIGZConstrutor3D::AddTexto()
{
    if(!pFonte) return false;

    pTexto = new CI3DTexto(pFonte,"Testando",32);
    pTexto->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    pTexto->Rotate(true,CIMTVetor(90.0f,0.0f,0.0f),pTexto->I3D_Pos);
    pTexto->Translate(CIMTVetor(0.0f,0.0f,-10.0f),false);

    return true;
}

bool CIGZConstrutor3D::AddCubo()
{
    pCubo = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                           CIMTVetor(10.0f,10.0f,10.0f) ,
                           IGL_WINMODE_CCW             );

    //Adiciona o material e texturas adicionais do terreno(Utilizados para renderização normal)
    pCubo->I3D_Mesh->I3D_Material = pINSMAMaterialManager->AddMaterial("Material Cubo Demo Project",IGL_MATERIAL_TEXTURE);

    //Adiciona textura Base do CUBO.
    pINSMAMaterialManager->AddTextura(pCubo->I3D_Mesh->I3D_Material,
                                      CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                      IGL_TEXTURE_LINEAR);

    //Bloqueia rejeição de pixel.
    pINSMAMaterialManager->SetaRejeicaoCor(pCubo->I3D_Mesh->I3D_Material,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

    pCubo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    return true;
}

bool CIGZConstrutor3D::AddCuboLowPoly()
{
    pCubo = new CI3DCubo  (CIMTVetor(10.0f, 0.0f, 0.0f),
                           CIMTVetor(8.0f,18.0f,8.0f)  ,
                           IGL_WINMODE_CCW             ,
                           IGL_POLYMODE_LEFT          );
    /*****************************************************************/
    /*Adiciona uma textura ao Cubo                                   */
    /*****************************************************************/
    //Adiciona o material e texturas adicionais do terreno(Utilizados para renderização normal)
    pCubo->I3D_Mesh->I3D_Material = pINSMAMaterialManager->AddMaterial("Material Cubo Low Poly DemoProject",IGL_MATERIAL_TEXTURE);

    //Adiciona textura Base do terreno.
    pINSMAMaterialManager->AddTextura(pCubo->I3D_Mesh->I3D_Material,
                                      CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Blocos_Madeira.bmp",
                                      IGL_TEXTURE_LINEAR);

    //Bloqueia rejeição de pixel.
    pINSMAMaterialManager->SetaRejeicaoCor(pCubo->I3D_Mesh->I3D_Material,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

    pCubo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    pCubo->SetaSelecao(true);

    return true;
}
