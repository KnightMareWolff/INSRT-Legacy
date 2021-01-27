#include "INSVK.h"


INSVKInterface::INSVKInterface()
{
    vector<VkExtensionProperties> available_extensions;
    vector<string>                desired_extensions;
    vector<VkPhysicalDevice>      available_devices;
    VkInstance                    instance;
    VkApplicationInfo             application_info;
    VkResult                      result;
    VkInstanceCreateInfo          instance_create_info;

    char **used_extensions;

    uint32_t extensions_count = 0;
    uint32_t devices_count = 0;
    result = VK_SUCCESS;


    
    //copia lista de extenções
    used_extensions = new char*[6];

    desired_extensions.resize( extensions_count );
    for(int i=0;i<extensions_count;i++)
    {
       desired_extensions[i] = available_extensions[i].extensionName;

       used_extensions[i] = new char[256];

       strcpy(used_extensions[i],available_extensions[i].extensionName);

       qWarning() << used_extensions[i];
    }

    instance_create_info.sType                  = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instance_create_info.pNext                  = NULL;
    instance_create_info.flags                  = 0;
    instance_create_info.pApplicationInfo       = &application_info;
    instance_create_info.enabledLayerCount      = 0;
    instance_create_info.ppEnabledLayerNames    = NULL;
    instance_create_info.enabledExtensionCount  = 6;
    instance_create_info.ppEnabledExtensionNames= used_extensions;

    result = vkCreateInstance( &instance_create_info,NULL, &instance );
    if( (result != VK_SUCCESS) ||
        (instance == VK_NULL_HANDLE) )
    {
      qWarning() << "Impossivel Criar Instancia VK.";
    }

    //Recupera numero de devices para a instancia
    result = vkEnumeratePhysicalDevices( instance, &devices_count, NULL );
    if( (result != VK_SUCCESS) ||
        (devices_count == 0) )
    {
      qWarning() << "Impossivel Recuperar Numero de Devices Fisicos Disponiveis.";
    }

    available_devices.resize( devices_count );
    result = vkEnumeratePhysicalDevices( instance, &devices_count, available_devices.data() );
    if( (result != VK_SUCCESS) ||
        (devices_count == 0) )
    {
      qWarning() << "Impossivel Recuperar Devices Fisicos Disponiveis.";
    }

    //Pega extensões suportadas por cada device
    for(int i=0;i<devices_count;i++)
    {
        VkPhysicalDevice physical_device = available_devices[i];

        result = vkEnumerateDeviceExtensionProperties( physical_device, nullptr, &extensions_count, nullptr );
        if( (result != VK_SUCCESS) ||
            (extensions_count == 0) )
        {
          qWarning() << "Impossivel Recuperar Numero de Extensões Disponiveis.";
        }

        available_extensions.resize( extensions_count );
        result = vkEnumerateDeviceExtensionProperties( physical_device, nullptr, &extensions_count, available_extensions.data() );
        if( (result != VK_SUCCESS) ||
            (extensions_count == 0) )
        {
          qWarning() << "Impossivel Recuperar Extensões Disponiveis.";
        }

        VkPhysicalDeviceFeatures   device_features;
        VkPhysicalDeviceProperties device_properties;

        //Recupera Features do Device
        vkGetPhysicalDeviceFeatures( physical_device, &device_features );
        //Recupera Propriedades do Device
        vkGetPhysicalDeviceProperties( physical_device, &device_properties );

        qWarning() << device_properties.deviceName ;

        //Recupera as Queue Families do device
        vector<VkQueueFamilyProperties> queue_families;
        uint32_t queue_families_count = 0;

        vkGetPhysicalDeviceQueueFamilyProperties( physical_device, &queue_families_count, NULL );
        if( queue_families_count == 0 )
        {
          qWarning() << "Impossivel Recuperar Numero de queue families.";
        }

        queue_families.resize( queue_families_count );
        vkGetPhysicalDeviceQueueFamilyProperties( physical_device, &queue_families_count, queue_families.data() );
        if( queue_families_count == 0 )
        {
          qWarning() << "Impossivel Recuperar as queue families.";
        }
    }
}
