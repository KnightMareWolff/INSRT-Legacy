#ifndef INSMD_H
#define INSMD_H

#include "IMD_GlobalDef.h"
#include "IMD_Som.h"
#include "IMD_Video.h"
#include "IMD_Sistema.h"
#include "IMD_AudioDevice.h"
#include "IMD_VideoDevice.h"

class INSMDInterface
{

public:
     INSMDInterface();
    ~INSMDInterface();

    static bool SetaFatores3D (float pFatorDoppler  ,float pFatorDistancia,float pFatorRolloff);
    static bool SetaDistancias(float pDistMin       ,float pDistMax                           );
    static bool Atualiza      (                                                               );

private:
    static CIMDSistema *pINSMDStaticInterface;
};

#endif // INSMD_H
