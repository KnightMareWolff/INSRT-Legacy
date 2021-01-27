#ifndef INSCR_H
#define INSCR_H

#include "SCR_GlobalDef.h"
#include "SCR_Objetos.h"

class INSCR
{

public:
    INSCR();
   ~INSCR();

    void                 AtribuiSM(CISMCenario *pISMCenario);
    static CISMCenario*  PegaSM   (                        );
private:
    static CISMCenario*  pICRCenario;//ponteiro para o cenario
};

#endif // INSCR_H
