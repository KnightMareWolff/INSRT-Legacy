#ifndef IVK_SISTEMA_H
#define IVK_SISTEMA_H

#include "IVK_GlobalDef.h"
#include "IVK_InstanciaVulkan.h"

class CIVKSistema
{
public:
    CIVKSistema();
private:
    //Propriedades das Extensões do sistema(Instancia Vulkan)
    vector<VkExtensionProperties> IVK_ExtensoesSistema  ;
    unsigned int                  IVK_QtdExtensoes      ;

    //Informações do sistema
    VkApplicationInfo             IVK_InfoSistema       ;

    //Buffer de Extensões para criação de Instancia(Indica extensões desejadas)
    char                        **IVK_ExtensoesDesejadas;

    //Instancia Lógica Vulkan
    CIVKInstanciaVulkan          *IVK_InstanciaVK;

};

#endif // IVK_SISTEMA_H
