#include "IPH_OdeSolver.h"

CIPHOdeSolver::CIPHOdeSolver()
{

}

void CIPHOdeSolver::RungeKutta4(CIPHOde *ode, float ds)
{
     //  Define some convenience variables to make the
     //  code more readable
     int j;
     int numEqns = ode->IPH_OdeNumEquacoes;
     float  VarIndep;
     float* VarDepVec;
     float* dq1 = new float[numEqns];
     float* dq2 = new float[numEqns];
     float* dq3 = new float[numEqns];
     float* dq4 = new float[numEqns];

     //  Retrieve the current values of the dependent
     //  and independent variables.
     VarIndep  = ode->IPH_VarIndep;
     VarDepVec = ode->GetAllQ();

     // Compute the four Runge-Kutta steps, The return
     // value of getRightHandSide method is an array of
     // delta-q values for each of the four steps.
     dq1 = ode->GetRightHandSide(VarIndep            , VarDepVec, VarDepVec  , ds, 0.0f);
     dq2 = ode->GetRightHandSide(VarIndep + 0.5f * ds, VarDepVec, dq1        , ds, 0.5f);
     dq3 = ode->GetRightHandSide(VarIndep + 0.5f * ds, VarDepVec, dq2        , ds, 0.5f);
     dq4 = ode->GetRightHandSide(VarIndep + ds       , VarDepVec, dq3        , ds, 1.0f);

     //  Update the dependent and independent variable values
     //  at the new dependent variable location and store the
     //  values in the ODE object arrays.
     ode->IPH_VarIndep = VarIndep + ds;

     for(j=0; j<numEqns; ++j)
     {

       VarDepVec[j] = VarDepVec[j] + (dq1[j] + 2.0f * dq2[j] + 2.0f * dq3[j] + dq4[j])/6.0f;

       ode->SetQ(j,VarDepVec[j]);

     }

     return;
}
