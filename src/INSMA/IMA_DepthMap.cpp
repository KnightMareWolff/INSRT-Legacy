/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMA_DepthMap.h"

CIMADepthMap::~CIMADepthMap()
{
    IMA_Escala  = 1.0f;
    IMA_TamMapa = 0;
    IMA_TamQuad = 0;
    IMA_Alturas.clear();
}

CIMADepthMap::CIMADepthMap():
    IMA_TamMapa(0),
    IMA_TamQuad(0),
    IMA_Escala(1.0f)
{

}

CIMADepthMap::CIMADepthMap(int pIMA_Tam, int pIMA_TamQuad, float pIMA_Escala)
{
    //Inicializa parametros de construção
    IMA_Escala  = pIMA_Escala;
    IMA_TamMapa = pIMA_Tam;
    IMA_TamQuad = pIMA_TamQuad;

    //Aloca o tamanho de mapa de alturas
    IMA_Alturas.resize(IMA_TamMapa * IMA_TamMapa);

    //Zera as alturas para inicio.
    memset(&IMA_Alturas[0],0, IMA_Alturas.size());

    GeraFractal(1.2f);
}

CIMADepthMap::CIMADepthMap(QString pIMA_NomeArquivo, int pIMA_TamQuad, float pIMA_Escala)
{
    I3D_Imagem = imread(pIMA_NomeArquivo.toStdString(),CV_LOAD_IMAGE_COLOR);

    if(I3D_Imagem.rows != I3D_Imagem.cols)
    {
        //erro de inicialização
    }
    //Inicializa parametros de construção
    IMA_Escala  = pIMA_Escala;
    IMA_TamMapa = I3D_Imagem.rows;
    IMA_TamQuad = pIMA_TamQuad;

    //flip(I3D_Imagem,I3D_Imagem,0);
    //cvtColor(I3D_Imagem,I3D_Imagem,CV_8UC3);

    //Aloca o tamanho de mapa de alturas
    IMA_Alturas.resize(IMA_TamMapa * IMA_TamMapa);

    //Zera as alturas para inicio.
    memset(&IMA_Alturas[0],0, IMA_Alturas.size());

    GeraFractal(1.2f);
}


int   CIMADepthMap::PegaTam   ()
{
   return IMA_TamMapa;
}

int   CIMADepthMap::PegaQuad  ()
{
   return IMA_TamQuad;
}

float CIMADepthMap::PegaEscala()
{
    return IMA_Escala;
}

float *CIMADepthMap::PegaAlturas()
{
    return &IMA_Alturas[0];
}

float CIMADepthMap::PegaAltura(float pIMA_X , float pIMA_Z)
{
    // Given a (x, z) position on the rendered height map this method
    // calculates the exact height of the height map at that (x, z)
    // position using bilinear interpolation.

    pIMA_X /= static_cast<float>(IMA_TamQuad);
    pIMA_Z /= static_cast<float>(IMA_TamQuad);

    assert(pIMA_X >= 0.0f && pIMA_X < float(IMA_TamMapa));
    assert(pIMA_Z >= 0.0f && pIMA_Z < float(IMA_TamMapa));

    long  ix = INSMT::floatToLong(pIMA_X);
    long  iz = INSMT::floatToLong(pIMA_Z);

    float topLeft     = IMA_Alturas[PegaIndice(ix, iz)] * IMA_Escala;
    float topRight    = IMA_Alturas[PegaIndice(ix + 1, iz)] * IMA_Escala;
    float bottomLeft  = IMA_Alturas[PegaIndice(ix, iz + 1)] * IMA_Escala;
    float bottomRight = IMA_Alturas[PegaIndice(ix + 1, iz + 1)] * IMA_Escala;
    float percentX    = pIMA_X - static_cast<float>(ix);
    float percentZ    = pIMA_Z - static_cast<float>(iz);

    return INSMT::bilerp(topLeft, topRight, bottomLeft, bottomRight, percentX, percentZ);
}

float CIMADepthMap::PegaAlturaPixel(float pIMA_X   ,  float pIMA_Z)
{
    return IMA_Alturas[pIMA_Z * IMA_TamMapa + pIMA_X];
}

void CIMADepthMap::PegaNormal (float pIMA_X   ,  float pIMA_Z , CIMTVetor &pIMA_Normal)
{
    // Given a (x, z) position on the rendered height map this method
    // calculates the exact normal of the height map at that (x, z) position
    // using bilinear interpolation.

    pIMA_X /= static_cast<float>(IMA_TamQuad);
    pIMA_Z /= static_cast<float>(IMA_TamQuad);

    assert(pIMA_X >= 0.0f && pIMA_X < float(IMA_TamMapa));
    assert(pIMA_Z >= 0.0f && pIMA_Z < float(IMA_TamMapa));

    long ix = INSMT::floatToLong(pIMA_X);
    long iz = INSMT::floatToLong(pIMA_Z);

    float percentX = pIMA_X - static_cast<float>(ix);
    float percentZ = pIMA_Z - static_cast<float>(iz);

    CIMTVetor topLeft;
    CIMTVetor topRight;
    CIMTVetor bottomLeft;
    CIMTVetor bottomRight;

    PegaNormalPixel(ix, iz, topLeft);
    PegaNormalPixel(ix + 1, iz, topRight);
    PegaNormalPixel(ix, iz + 1, bottomLeft);
    PegaNormalPixel(ix + 1, iz + 1, bottomRight);

    pIMA_Normal = INSMT::bilerp(topLeft, topRight, bottomLeft, bottomRight, percentX, percentZ);
    pIMA_Normal.Normalizar();
}

void CIMADepthMap::PegaNormalPixel(float pIMA_X   ,  float pIMA_Z , CIMTVetor &pIMA_Normal)
{
    // Returns the normal at the specified location on the height map.
    // The normal is calculated using the properties of the height map.
    // This approach is much quicker and more elegant than triangulating the
    // height map and averaging triangle surface normals.

    if (pIMA_X > 0 && pIMA_X < IMA_TamMapa - 1)
        pIMA_Normal.x = PegaAlturaPixel(pIMA_X - 1, pIMA_Z) - PegaAlturaPixel(pIMA_X + 1, pIMA_Z);
    else if (pIMA_X > 0)
        pIMA_Normal.x = 2.0f * (PegaAlturaPixel(pIMA_X - 1, pIMA_Z) - PegaAlturaPixel(pIMA_X, pIMA_Z));
    else
        pIMA_Normal.x = 2.0f * (PegaAlturaPixel(pIMA_X, pIMA_Z) - PegaAlturaPixel(pIMA_X + 1, pIMA_Z));

    if (pIMA_Z > 0 && pIMA_Z < IMA_TamMapa - 1)
        pIMA_Normal.z = PegaAlturaPixel(pIMA_X, pIMA_Z - 1) - PegaAlturaPixel(pIMA_X, pIMA_Z + 1);
    else if (pIMA_Z > 0)
        pIMA_Normal.z = 2.0f * (PegaAlturaPixel(pIMA_X, pIMA_Z - 1) - PegaAlturaPixel(pIMA_X, pIMA_Z));
    else
        pIMA_Normal.z = 2.0f * (PegaAlturaPixel(pIMA_X, pIMA_Z) - PegaAlturaPixel(pIMA_X, pIMA_Z + 1));

    pIMA_Normal.y = 2.0f * IMA_TamQuad;
    pIMA_Normal.Normalizar();

}

void CIMADepthMap::GeraFractal(float pIMA_Roughness)
{
    // Generates a fractal height field using the diamond-square (midpoint
    // displacement) algorithm. Note that only square height fields work with
    // this algorithm.
    //
    // Based on article and associated code:
    // "Fractal Terrain Generation - Midpoint Displacement" by Jason Shankel
    // (Game Programming Gems I, pp.503-507).

    srand(static_cast<unsigned int>(time(0)));

    std::fill(IMA_Alturas.begin(), IMA_Alturas.end(), 0.0f);

    int p1, p2, p3, p4, mid;
    float dH = IMA_TamMapa * 0.5f;
    float dHFactor = powf(2.0f, -pIMA_Roughness);
    float minH = 0.0f, maxH = 0.0f;

    for (int w = IMA_TamMapa; w > 0; dH *= dHFactor, w /= 2)
    {
        // Diamond Step.
        for (int z = 0; z < IMA_TamMapa; z += w)
        {
            for (int x = 0; x < IMA_TamMapa; x += w)
            {
                p1  = PegaIndice(x, z);
                p2  = PegaIndice(x + w, z);
                p3  = PegaIndice(x + w, z + w);
                p4  = PegaIndice(x, z + w);
                mid = PegaIndice(x + w / 2, z + w / 2);

                IMA_Alturas[mid] = INSMT::random(-dH, dH) + (IMA_Alturas[p1] + IMA_Alturas[p2] + IMA_Alturas[p3] + IMA_Alturas[p4]) * 0.25f;

                minH = min(minH, IMA_Alturas[mid]);
                maxH = max(maxH, IMA_Alturas[mid]);
            }
        }

        // Square step.
        for (int z = 0; z < IMA_TamMapa; z += w)
        {
            for (int x = 0; x < IMA_TamMapa; x += w)
            {
                p1  = PegaIndice(x, z);
                p2  = PegaIndice(x + w, z);
                p3  = PegaIndice(x + w / 2, z - w / 2);
                p4  = PegaIndice(x + w / 2, z + w / 2);
                mid = PegaIndice(x + w / 2, z);

                IMA_Alturas[mid] = INSMT::random(-dH, dH) + (IMA_Alturas[p1] + IMA_Alturas[p2] + IMA_Alturas[p3] + IMA_Alturas[p4]) * 0.25f;

                minH = min(minH, IMA_Alturas[mid]);
                maxH = max(maxH, IMA_Alturas[mid]);

                p1  = PegaIndice(x, z);
                p2  = PegaIndice(x, z + w);
                p3  = PegaIndice(x + w / 2, z + w / 2);
                p3  = PegaIndice(x - w / 2, z + w / 2);
                mid = PegaIndice(x, z + w / 2);

                IMA_Alturas[mid] = INSMT::random(-dH, dH) + (IMA_Alturas[p1] + IMA_Alturas[p2] + IMA_Alturas[p3] + IMA_Alturas[p4]) * 0.25f;

                minH = min(minH, IMA_Alturas[mid]);
                maxH = max(maxH, IMA_Alturas[mid]);
            }
        }
    }

    FiltroSmooth();

    // Normalize height field so altitudes fall into range [0,255].
    for (int i = 0; i < IMA_TamMapa * IMA_TamMapa; ++i)
        IMA_Alturas[i] = 255.0f * (IMA_Alturas[i] - minH) / (maxH - minH);

}

unsigned int CIMADepthMap::PegaIndice(int x,int z)
{
    // Given a 2D height map coordinate, this method returns the index
    // into the height map. This method wraps around for coordinates larger
    // than the height map size.
    return (((x + IMA_TamMapa) % IMA_TamMapa) + ((z + IMA_TamMapa) % IMA_TamMapa) * IMA_TamMapa);
}

void  CIMADepthMap::FiltroSmooth()
{
    // Applies a box filter to the height map to smooth it out.

        std::vector<float> source(IMA_Alturas);
        float value = 0.0f;
        float cellAverage = 0.0f;
        int i = 0;
        int bounds = IMA_TamMapa * IMA_TamMapa;

        for (int y = 0; y < IMA_TamMapa; ++y)
        {
            for (int x = 0; x < IMA_TamMapa; ++x)
            {
                value = 0.0f;
                cellAverage = 0.0f;

                i = (y - 1) * IMA_TamMapa + (x - 1);
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = (y - 1) * IMA_TamMapa + x;
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = (y - 1) * IMA_TamMapa + (x + 1);
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = y * IMA_TamMapa + (x - 1);
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = y * IMA_TamMapa + x;
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = y * IMA_TamMapa + (x + 1);
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = (y + 1) * IMA_TamMapa + (x - 1);
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = (y + 1) * IMA_TamMapa + x;
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                i = (y + 1) * IMA_TamMapa + (x + 1);
                if (i >= 0 && i < bounds)
                {
                    value += source[i];
                    cellAverage += 1.0f;
                }

                IMA_Alturas[y * IMA_TamMapa + x] = value / cellAverage;
            }
        }
}

void CIMADepthMap::FiltroBlur(float pIMA_Passos)
{
    // Applies a simple FIR (Finite Impulse Response) filter across the height
    // map to blur it. 'amount' is in range [0,1]. 0 is no blurring, and 1 is
    // very strong blurring.

    float *pPixel = 0;
    float *pPrevPixel = 0;
    int width = IMA_TamMapa;
    int height = IMA_TamMapa;
    int pitch = IMA_TamMapa;

    // Blur horizontally. Both left-to-right, and right-to-left.
    for (int i = 0; i < height; ++i)
    {
        pPrevPixel = &IMA_Alturas[i * pitch];
        // Left-to-right.
        for (int j = 1; j < width; ++j)
        {
            pPixel = &IMA_Alturas[(i * pitch) + j];
            *pPixel = (*pPrevPixel * pIMA_Passos) + (*pPixel * (1.0f - pIMA_Passos));
            pPrevPixel = pPixel;
        }

        pPrevPixel = &IMA_Alturas[(i * pitch) + (width - 1)];

        // Right-to-left.
        for (int j = width - 2; j >= 0; --j)
        {
            pPixel = &IMA_Alturas[(i * pitch) + j];
            *pPixel = (*pPrevPixel * pIMA_Passos) + (*pPixel * (1.0f - pIMA_Passos));
            pPrevPixel = pPixel;
        }
    }

    // Blur vertically. Both top-to-bottom, and bottom-to-top.
    for (int i = 0; i < width; ++i)
    {
        pPrevPixel = &IMA_Alturas[i];

        // Top-to-bottom.
        for (int j = 1; j < height; ++j)
        {
            pPixel = &IMA_Alturas[(j * pitch) + i];
            *pPixel = (*pPrevPixel * pIMA_Passos) + (*pPixel * (1.0f - pIMA_Passos));
            pPrevPixel = pPixel;
        }

        pPrevPixel = &IMA_Alturas[((height - 1) * pitch) + i];

        // Bottom-to-top.
        for (int j = height - 2; j >= 0; --j)
        {
            pPixel = &IMA_Alturas[(j * pitch) + i];
            *pPixel = (*pPrevPixel * pIMA_Passos) + (*pPixel * (1.0f - pIMA_Passos));
            pPrevPixel = pPixel;
        }
    }
}

