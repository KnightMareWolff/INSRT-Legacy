#ifndef CICLKERNEL_H
#define CICLKERNEL_H

#include "ICL_GlobalDef.h"

class CICLKernel
{
public:
     CICLKernel(cl_kernel  pICL_KernelID);
    ~CICLKernel();

    cl_kernel  ICL_KernelID      ;
    cl_uint    ICL_QtdArgumentos ;
    char       ICL_NomeFuncao[32];

    cl_mem           ICL_BufferIn    ;
    cl_mem           ICL_BufferOut   ;
    cl_uint          ICL_GLBufferSize;
    cl_float16       ICL_TransfMatrix;
    IGLVertexBuffer *ICL_VertexBuffer;

    void PreparaParametro(cl_context pICL_DeviceContext,IGLVertexBuffer *pGLBuffer  ,uint pGLBufferSize,CIMTMatriz *pTransfMatrix);
    void PreparaParametro(cl_context pICL_DeviceContext,uint             pGLBufferId,uint pGLBufferSize,CIMTMatriz *pTransfMatrix);

    void ExecutaKernel   (cl_command_queue pICL_DeviceCommandQueue,IGLVertexBuffer *pGLBuffer  );
    void ExecutaKernel   (cl_command_queue pICL_DeviceCommandQueue,uint             pGLBufferId);
};

#endif // CICLKERNEL_H
