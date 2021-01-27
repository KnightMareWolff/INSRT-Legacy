#ifndef INSMA_H
#define INSMA_H

#include "IMA_GlobalDef.h"
#include "IMA_Material.h"
#include "IMA_Textura.h"
#include "IMA_MaterialManager.h"
#include "IMA_TextureManager.h"
#include "IMA_DepthMap.h"
#include "IMA_ColorMap.h"

class INSMA
{

public:
    INSMA();
    static bool Inicializa();
    static CIMAMaterialManager  *pINSMAMaterialManager;
    static CIMATextureManager   *pINSMATextureManager;
};

#endif // INSMA_H
