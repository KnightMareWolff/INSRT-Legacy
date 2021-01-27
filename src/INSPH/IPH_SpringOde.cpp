#include "IPH_SpringOde.h"

CIPHSpringOde::CIPHSpringOde(float pMass, float pDampCoef, float pConstant, float pDeflection):
    CIPHOde(2)
{
    //  Initialize fields declared in the class.
    IPH_Mass              = pMass;
    IPH_DampCoef          = pDampCoef;
    IPH_Constant          = pConstant;
    IPH_InitialDeflection = pDeflection;

    //  Set the initial conditions of the dependent
    //  variables.
    //  q[0] = vx
    //  q[1] = x;
    SetQ(0   , 0.0f       );
    SetQ(1   , pDeflection);
}

float CIPHSpringOde::GetVx()
{
    return GetQ(0);
}

float CIPHSpringOde::GetX()
{
    return GetQ(1);
}

float CIPHSpringOde::GetTime()
{
    return IPH_VarIndep;
}

void CIPHSpringOde::UpdatePositionAndVelocity(float pDeltaTime)
{
    OdeSolver.RungeKutta4(this, pDeltaTime);
}

float* CIPHSpringOde::GetRightHandSide(float s, float *q, float *deltaQ, float ds, float qScale)
{
    float* dq   = new float[4]; // right-hand side values
    float* newQ = new float[4]; // intermediate dependent variable values.

    //  Compute the intermediate values of the
    //  dependent variables.
    for(int i=0; i<2; ++i)
    {
      newQ[i] = q[i] + qScale*deltaQ[i];
    }

    //  Compute right-hand side values.
    float G = -9.81f;
    dq[0] = ds*G - ds*(IPH_DampCoef * newQ[0] + IPH_Constant * newQ[1]) / IPH_Mass;
    dq[1] = ds*(newQ[0]);

    return dq;
}
