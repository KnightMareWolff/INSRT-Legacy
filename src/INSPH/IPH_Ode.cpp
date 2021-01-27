#include "IPH_Ode.h"

CIPHOde::CIPHOde(int pIPH_NumEq)
{
    IPH_OdeNumEquacoes = pIPH_NumEq;
    IPH_VarDepVec      = new float[IPH_OdeNumEquacoes];
}

float CIPHOde::GetQ(int pIPH_Index)
{
    return IPH_VarDepVec[pIPH_Index];
}

void CIPHOde::SetQ(int pIPH_Index, float pIPH_Valor)
{
    IPH_VarDepVec[pIPH_Index] = pIPH_Valor;
}

float* CIPHOde::GetAllQ()
{
    return IPH_VarDepVec;
}
