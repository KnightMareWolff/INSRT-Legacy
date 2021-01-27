/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_PainelHeightMap.h"


CI3DPainelHeightMap::CI3DPainelHeightMap():
    CI3DPrimitivo()
{
    //iTpPainel          = IGL_PAINEL_RELEVO;
    I3D_Mesh->MeshType = IGL_MESH_HEIGHTMAP;
    I3D_HeightMap      = NULL;
}

CI3DPainelHeightMap::CI3DPainelHeightMap(int pWindingMode):
    CI3DPrimitivo()
{
    //iTpPainel          = IGL_PAINEL_RELEVO;
    I3D_Mesh->MeshType = IGL_MESH_HEIGHTMAP;
    I3D_HeightMap      = NULL;
}

bool CI3DPainelHeightMap::AddHeightMap(QString  pImgBase)
{
    //if(bPainelInicializado)
    //{
    //    qWarning() << "Tentativa de inicialização de painel já construido.";
    //    return false;
    //}

    //ImgBase      = QImage(pImgBase);
    //I3D_Altura   = ImgBase.height();
    //I3D_Largura  = ImgBase.width();
    Build();
    //bPainelInicializado = true;
    return true;
}

bool CI3DPainelHeightMap::AddHeightMap(int pI3D_TAM, int pI3D_TamQuad, float pI3D_Escala)
{
    I3D_HeightMap = new CIMADepthMap(pI3D_TAM,pI3D_TamQuad,pI3D_Escala);
    Build();
    return true;
}

float CI3DPainelHeightMap::PegaAltura(float pI3D_X, float pI3D_Y)
{
   return I3D_HeightMap->PegaAlturaPixel( pI3D_X , pI3D_Y );
}

void CI3DPainelHeightMap::Build()
{
   int tI3D_Tam         = I3D_HeightMap->PegaTam();
   int tI3D_QtdVertices = (tI3D_Tam * tI3D_Tam);
   int tI3D_QtdIndices  = (tI3D_Tam - 1) * (tI3D_Tam * 2 + 1);

   //Aloca o espaço necessario de vertices e indices na Skin para a construçao do terreno.
   I3D_Mesh->AlocaSkinBuffer(tI3D_QtdVertices,tI3D_QtdIndices);
   GeraVertices();
   GeraIndices();
   GeraColorMap();
   I3D_Mesh->IniSkinBuffer();
   I3D_Mesh->SetaShader(I3D_Shader);
}

void CI3DPainelHeightMap::GeraVertices()
{
    IGLVertexBuffer *pVertex     = 0;
    int              currVertex  = 0;
    int              size        = I3D_HeightMap->PegaTam();
    int              gridSpacing = I3D_HeightMap->PegaQuad();
    float            heightScale = I3D_HeightMap->PegaEscala();
    CIMTVetor        normal;

    for (int z = 0; z < size; ++z)
    {
        for (int x = 0; x < size; ++x)
        {
            currVertex = z * size + x;
            pVertex = &I3D_Mesh->I3D_SkinVertexBuffer[currVertex];

            pVertex->position.x = static_cast<float>(z * gridSpacing);
            pVertex->position.y = I3D_HeightMap->PegaAlturaPixel(z, x) * heightScale;
            pVertex->position.z = static_cast<float>(x * gridSpacing);

            I3D_HeightMap->PegaNormalPixel(z, x, normal);
            pVertex->normal.x = normal.x;
            pVertex->normal.y = normal.y;
            pVertex->normal.z = normal.z;

            pVertex->texCoord.x = static_cast<float>(z) / static_cast<float>(size);
            pVertex->texCoord.y = static_cast<float>(x) / static_cast<float>(size);
        }
    }
}

void CI3DPainelHeightMap::GeraIndices()
{
    int size = I3D_HeightMap->PegaTam();

    unsigned int *pIndex = static_cast<unsigned int *>(I3D_Mesh->I3D_SkinVertexIndices);

    for (int z = 0; z < size - 1; ++z)
    {
        if (z % 2 == 0)
        {
            for (int x = 0; x < size; ++x)
            {
                *pIndex++ = x + z * size;
                *pIndex++ = x + (z + 1) * size;
            }

            // Add degenerate triangles to stitch strips together.
            *pIndex++ = (size - 1) + (z + 1) * size;
        }
        else
        {
            for (int x = size - 1; x >= 0; --x)
            {
                *pIndex++ = x + z * size;
                *pIndex++ = x + (z + 1) * size;
            }

            // Add degenerate triangles to stitch strips together.
            *pIndex++ = (z + 1) * size;
        }
    }
}

void CI3DPainelHeightMap::GeraColorMap()
{
    I3D_ColorMap = new CIMAColorMap ();
    I3D_ColorMap->Build(I3D_HeightMap,CIUTGerenciadorPath::IUT_PathWorld + "Terrenos/ColorMap.bmp");
}
