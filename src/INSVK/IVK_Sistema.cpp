#include "IVK_Sistema.h"

CIVKSistema::CIVKSistema()
{
    VkResult IVK_Retorno;

    //Recupera numero de extensões
    IVK_Retorno = vkEnumerateInstanceExtensionProperties( nullptr, &IVK_QtdExtensoes, nullptr );
    if( (IVK_Retorno != VK_SUCCESS) ||
        (IVK_QtdExtensoes == 0) )
    {
      qWarning() << "Impossivel Obter numero de extensões.";
    }

    //Alimenta o vetor de propriedades de extensão
    IVK_ExtensoesSistema.resize( IVK_QtdExtensoes );
    IVK_Retorno = vkEnumerateInstanceExtensionProperties( nullptr, &IVK_QtdExtensoes, IVK_ExtensoesSistema.data() );
    if( (IVK_Retorno != VK_SUCCESS) ||
        (IVK_QtdExtensoes == 0) )
    {
      qWarning() << "Impossivel Enumerar as extensões obtidas.";
    }

}
