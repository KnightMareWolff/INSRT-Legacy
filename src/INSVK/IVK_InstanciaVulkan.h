#ifndef IVK_INSTANCIAVULKAN_H
#define IVK_INSTANCIAVULKAN_H

#include "IVK_GlobalDef.h"

class CIVKInstanciaVulkan
{
public:
    CIVKInstanciaVulkan();
private:
    //Instancia Física Vulkan do sistema
    VkInstance  IVK_InstanciaVulkan;
};

#endif // IVK_INSTANCIAVULKAN_H
