#ifndef CIPHSPRINGODE_H
#define CIPHSPRINGODE_H

#include "IPH_Ode.h"
#include "IPH_OdeSolver.h"

class CIPHSpringOde : public CIPHOde
{
public:

    float IPH_Mass             ;  //  mass at end of spring
    float IPH_DampCoef         ;  //  damping coefficient
    float IPH_Constant         ;  //  spring constant
    float IPH_InitialDeflection;  //  initial spring deflection

    CIPHSpringOde(float pMass, float pDampCoef, float pConstant, float pDeflection);


    float GetVx  ();
    float GetX   ();
    float GetTime();

    void   UpdatePositionAndVelocity(float pDeltaTime                                        );
    float* GetRightHandSide         (float s, float *q, float *deltaQ, float ds, float qScale);

private:

    CIPHOdeSolver OdeSolver;

};

#endif // CIPHSPRINGODE_H
