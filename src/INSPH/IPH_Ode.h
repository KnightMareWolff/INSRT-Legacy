#ifndef IPH_ODE_H
#define IPH_ODE_H


class CIPHOde
{
public:
    CIPHOde(int pNumEq);

    int     IPH_OdeNumEquacoes; //  Numero de Equações a resolver
    float  *IPH_VarDepVec     ; //  Vetor de Variaveis dependentes
    float   IPH_VarIndep      ; //  Variável Independente

    float  GetQ   (int pIPH_Index                 );
    void   SetQ   (int pIPH_Index,float pIPH_Valor);
    float* GetAllQ(                               );

    virtual float* GetRightHandSide(float s,float* q,float* deltaQ, float ds, float qScale);

};

#endif // CIPHODE_H
