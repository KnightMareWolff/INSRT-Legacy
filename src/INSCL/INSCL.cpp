#include "INSCL.h"

//Inicialização da Instância Estatica
CICLSistema* INSCLInterface::pINSCLStaticInterface=NULL;

/****************************************/
/*Rotinas de Inicialização de Interface */
/****************************************/
INSCLInterface::INSCLInterface()
{
}

INSCLInterface::INSCLInterface(QGLContext *pContext, QString pICL_DefaultGPUVendor)
{
    pINSCLStaticInterface = new CICLSistema(pContext,pICL_DefaultGPUVendor);
}

INSCLInterface::INSCLInterface(QOpenGLContext *pContext, QString pICL_DefaultGPUVendor)
{
    pINSCLStaticInterface = new CICLSistema(pContext,pICL_DefaultGPUVendor);
}

void INSCLInterface::execCL(int pICL_Function)
{
    switch(pICL_Function)
    {
       case ICL_EXEC_UPDATE_GL_CTXT:
       {
          pINSCLStaticInterface->UpdateHardwareDevices();
       }break;
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
       }
    }
}

void INSCLInterface::execCL(int pICL_Function, IGLVertexBuffer *pICL_Buffer, uint pICL_BufferSize, CIMTMatriz *pICL_Transform)
{
    switch(pICL_Function)
    {
       case ICL_EXEC_TRANSFORM_GL:
       {
          pINSCLStaticInterface->TransformBufferGL(pICL_Buffer,pICL_BufferSize,pICL_Transform);
       }break;
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
       }
    }
}

void INSCLInterface::execCL(int pICL_Function, uint pICL_BufferId, uint pICL_BufferSize, CIMTMatriz *pICL_Transform)
{
    switch(pICL_Function)
    {
       case ICL_EXEC_TRANSFORM_GL:
       {
          pINSCLStaticInterface->TransformBufferGL(pICL_BufferId,pICL_BufferSize,pICL_Transform);
       }break;
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
       }
    }
}

bool INSCLInterface::SuportaGLInteroperation()
{
    bool tICL_InteropSupported;
    bool tICL_HeterogeneousSupported;
    bool tICL_AuxiliarySupported;

    pINSCLStaticInterface->ExtraiIndicadores(tICL_InteropSupported,tICL_HeterogeneousSupported,tICL_AuxiliarySupported);

    return tICL_InteropSupported;
}

bool INSCLInterface::SuportaHWOptimization()
{
    bool tICL_InteropSupported;
    bool tICL_HeterogeneousSupported;
    bool tICL_AuxiliarySupported;

    pINSCLStaticInterface->ExtraiIndicadores(tICL_InteropSupported,tICL_HeterogeneousSupported,tICL_AuxiliarySupported);

    if(tICL_HeterogeneousSupported || tICL_AuxiliarySupported)return true;
    return false;
}
