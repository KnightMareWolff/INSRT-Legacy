#ifndef IPH_ODESOLVER_H
#define IPH_ODESOLVER_H

#include "IPH_Ode.h"

class CIPHOdeSolver
{
public:
    CIPHOdeSolver();

    void RungeKutta4(CIPHOde *ode, float ds);

};

#endif // CIPHODESOLVER_H
