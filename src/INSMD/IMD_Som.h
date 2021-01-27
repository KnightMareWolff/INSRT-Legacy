#ifndef IMD_SOM_H
#define IMD_SOM_H

#include "IMD_GlobalDef.h"

class CIMDSom
{
public:
     CIMDSom(const char *nome);
    ~CIMDSom(                );

    bool SetaParametros3D(CIMTVetor pPos,CIMTVetor pVel);
    void Play(bool pUpdate);

private:
    CIMTVetor      IMDPosSom;
    CIMTVetor      IMDVelSom;
    bool           IMDPausa ;
};

#endif // IMD_SOM_H
