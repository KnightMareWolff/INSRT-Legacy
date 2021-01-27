#include "IMD_Som.h"

extern float IMD_FATOR_DISTANCIA    =1.0f;    //Fator de Distancia(m/s)
extern float IMD_FATOR_DISTANCIAMIN =0.5f;    //Distancia Minima do som
extern float IMD_FATOR_DISTANCIAMAX =5000.0f; //Distancia Maxima do som

CIMDSom::CIMDSom(const char *nome)
{
}

CIMDSom::~CIMDSom()
{
}

bool CIMDSom::SetaParametros3D(CIMTVetor pPos, CIMTVetor pVel)
{
    IMDPosSom = pPos;
    IMDVelSom = pVel;
    return true;
}

void CIMDSom::Play(bool pUpdate)
{
}
