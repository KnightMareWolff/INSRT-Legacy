#ifndef CICLPLATAFORMA_H
#define CICLPLATAFORMA_H

#include "ICL_GlobalDef.h"
#include "ICL_Device.h"

class CICLPlataforma
{
public:
    CICLPlataforma(cl_platform_id pICL_PlatformID,QString pICL_DefaultGPUVendor);

    void execDevice(IGLVertexBuffer *pICL_Buffer  , uint pICL_BufferSize, CIMTMatriz *pICL_Transform);
    void execDevice(uint             pICL_BufferId, uint pICL_BufferSize, CIMTMatriz *pICL_Transform);

    // ---- Métodos Públicos Auxiliares ----
    int  CountDevicesByType   (int pICL_DeviceType);
    bool VerificaGPUPrimaria  (                   );
    bool VerificaGPUSecundaria(                   );
    bool VerificaCPUAuxiliar  (                   );

private:
    cl_platform_id ICL_PlatformID;

    //atributos de descrição da plataforma
    char*   ICL_Profile;
    char*   ICL_Versao;
    char*   ICL_Nome;
    char*   ICL_Vendor;
    char*   ICL_Extensoes;

    //atributos de controle
    cl_uint         ICL_QtdDevices; //quantidade de devices na plataforma
    cl_device_id*   ICL_ListaID;    //Lista de ID´s de devices na plataforma

    //Lista de Devices da Plataforma
    vector<CICLDevice*> ICL_Devices;
};

#endif // CICLPLATAFORMA_H
