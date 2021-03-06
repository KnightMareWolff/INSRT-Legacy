#include "ICL_Sistema.h"

CICLSistema::CICLSistema()
{
    //Zera os contadores do sistema heterogêneo.
    ICL_CPUCounter = 0;
    ICL_GPUCounter = 0;
    ICL_ACECounter = 0;

    //Inicializa Flags de Computação Heterogênea
    ICL_InteropComputing  = false;
    ICL_HeterogComputing  = false;
    ICL_AuxiliaryComputing= false;
}

CICLSistema::CICLSistema(QOpenGLContext *pContext,QString pICL_DefaultGPUVendor)
{
    cl_int  ICL_Error;

    //Repassa qual é o Vendor da GPU Default do sistema
    ICL_DefaultGPUVendor = pICL_DefaultGPUVendor;

    //Zera os contadores do sistema heterogêneo.
    ICL_CPUCounter = 0;
    ICL_GPUCounter = 0;
    ICL_ACECounter = 0;

    //Inicializa Flags de Computação Heterogênea
    ICL_InteropComputing  = false;
    ICL_HeterogComputing  = false;
    ICL_AuxiliaryComputing= false;

    //Coleta Qual é o Contexto OpenGL Nativo do sistema
    QVariant nativeHandle = pContext->nativeHandle();

    if (!nativeHandle.isNull() && nativeHandle.canConvert<QWGLNativeContext>())
    {
        ICL_ContextoGLNativo = nativeHandle.value<QWGLNativeContext>();

        //ICL_GLRC             = ICL_ContextoGLNativo.context();
        ICL_GLRC             = wglGetCurrentContext();

        ICL_HWND             = ICL_ContextoGLNativo.window ();

        //ICL_HDC              = GetDC(ICL_HWND);
        ICL_HDC              = wglGetCurrentDC();
    }


    //Pega o Numero de Plataformas disponiveis
    ICL_Error = clGetPlatformIDs(0, NULL, &ICL_QtdPlataformas);
    if(ICL_Error != CL_SUCCESS)
    {
       qWarning() << "Não foi possivel Obter Nenhuma Plataforma Heterogenea.";
       exit(1);
    }

    //aloca o numero necessario de platform ids
    ICL_ListaID = new cl_platform_id[ICL_QtdPlataformas];

    //Pega os ID´s de das plataformas
    ICL_Error = clGetPlatformIDs(ICL_QtdPlataformas, ICL_ListaID , NULL);
    if(ICL_Error != CL_SUCCESS)
    {
       qWarning() << "Não foi possivel Obter Os Ids de Plataforma Heterogenea.";
       exit(1);
    }

    //Inicializa a lista de Plataformas do sistema construindo a partir do ID da Plataforma
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        ICL_Plataformas.push_back(new CICLPlataforma(ICL_ListaID[i],ICL_DefaultGPUVendor));
    }

    ExtraiContadores();
    ExtraiIndices   ();

    qWarning() << "Plataforma Heterogênea Criada.";
    qWarning() << "Contadores:";
    qWarning() << "GPU´s detectadas:" << ICL_GPUCounter ;
    qWarning() << "CPU´s detectadas:" << ICL_GPUCounter ;
    qWarning() << "ACE´s detectadas:" << ICL_ACECounter ;
    qWarning() << "=================";
    qWarning() << "Indice Graphics     :" << ICL_GraphicsPlat ;
    qWarning() << "Indice Heterogeneous:" << ICL_Heterogeneus ;
    qWarning() << "Indice Auxiliary    :" << ICL_Auxiliary ;
}

CICLSistema::CICLSistema(QGLContext *pContext, QString pICL_DefaultGPUVendor)
{

    //Zera os contadores do sistema heterogêneo.
    ICL_CPUCounter = 0;
    ICL_GPUCounter = 0;
    ICL_ACECounter = 0;

    //Inicializa Flags de Computação Heterogênea
    ICL_InteropComputing  = false;
    ICL_HeterogComputing  = false;
    ICL_AuxiliaryComputing= false;

    QVariant nativeHandle = pContext->contextHandle()->nativeHandle();

    if (!nativeHandle.isNull() && nativeHandle.canConvert<QWGLNativeContext>())
    {
        ICL_ContextoGLNativo = nativeHandle.value<QWGLNativeContext>();

        //ICL_GLRC             = ICL_ContextoGLNativo.context();
        ICL_GLRC             = wglGetCurrentContext();

        ICL_HWND             = ICL_ContextoGLNativo.window ();

        //ICL_HDC              = GetDC(ICL_HWND);
        ICL_HDC              = wglGetCurrentDC();
    }
}

void CICLSistema::UpdateHardwareDevices()
{
    ICL_GLRC  = wglGetCurrentContext();
    ICL_HDC   = wglGetCurrentDC();
}

void CICLSistema::TransformBufferGL(IGLVertexBuffer *pICL_Buffer, uint pICL_BufferSize, CIMTMatriz *pICL_Transform)
{
   ICL_Plataformas[ICL_Heterogeneus]->execDevice(pICL_Buffer,pICL_BufferSize,pICL_Transform);
}

void CICLSistema::TransformBufferGL(uint pICL_BufferId, uint pICL_BufferSize, CIMTMatriz *pICL_Transform)
{
   ICL_Plataformas[ICL_GraphicsPlat]->execDevice(pICL_BufferId,pICL_BufferSize,pICL_Transform);
}

void CICLSistema::ExtraiContadores()
{
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        ICL_CPUCounter += ICL_Plataformas[i]->CountDevicesByType(ICL_DEV_CPU);
        ICL_GPUCounter += ICL_Plataformas[i]->CountDevicesByType(ICL_DEV_GPU);
        ICL_ACECounter += ICL_Plataformas[i]->CountDevicesByType(ICL_DEV_ACEL);
    }
}

void CICLSistema::ExtraiIndices()
{
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        if(ICL_Plataformas[i]->VerificaGPUPrimaria())
        {
            ICL_GraphicsPlat = i;
            ICL_InteropComputing = true;
        }

        if(ICL_Plataformas[i]->VerificaGPUSecundaria())
        {
            ICL_Heterogeneus = i;
            ICL_HeterogComputing = true;
        }

        if(ICL_Plataformas[i]->VerificaCPUAuxiliar())
        {
            ICL_Auxiliary = i;
            ICL_AuxiliaryComputing = true;
        }
    }
}

void CICLSistema::ExtraiIndicadores(bool &pICL_InteropComputing, bool &pICL_HeterogComputing, bool &pICL_AuxiliaryComputing)
{
    pICL_InteropComputing   = ICL_InteropComputing;
    pICL_HeterogComputing   = ICL_HeterogComputing;
    pICL_AuxiliaryComputing = ICL_AuxiliaryComputing;
}
