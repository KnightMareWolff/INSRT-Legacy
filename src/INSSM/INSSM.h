#ifndef INSSM_H
#define INSSM_H

#include "ISM_GlobalDef.h"
#include "ISM_Cenario.h"

class INSSM
{
public:
    INSSM(QOpenGLContext   *pI3DContext,QString pNomeCenario);
    INSSM(QGLContext       *pI3DContext, QString pNomeCenario);

    CISMCenario* PegaCenario();
private:
    CISMCenario* pCenario;
};

#endif // INSSM_H
