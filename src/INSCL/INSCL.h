#ifndef INSCL_H
#define INSCL_H

#include "ICL_GlobalDef.h"
#include "ICL_Sistema.h"

/**************************************************************/
/*Adotado acesso estatico , ao inves de acesso direto devido a*/
/*Uma instância da Interface ser capaz de gerenciar inúmeras  */
/*Plataformas, incluindo criação de contextos e Kernels.      */
/*Como a função de interface execCL será espalhada por todo o */
/*sistema através de herança direta , o uso de interface est. */
/*Garante a independencia e acoplamento do componente         */
/**************************************************************/
class INSCLInterface
{
public:
    INSCLInterface(                        );
    INSCLInterface(QOpenGLContext *pContext,QString pICL_DefaultGPUVendor);
    INSCLInterface(QGLContext     *pContext,QString pICL_DefaultGPUVendor);

    void execCL(int pICL_Function                                                                                  );
    void execCL(int pICL_Function, IGLVertexBuffer *pICL_Buffer  , uint pICL_BufferSize, CIMTMatriz *pICL_Transform);
    void execCL(int pICL_Function, uint             pICL_BufferId, uint pICL_BufferSize, CIMTMatriz *pICL_Transform);
    
    bool SuportaGLInteroperation();
    bool SuportaHWOptimization  ();


private:
    static CICLSistema *pINSCLStaticInterface;
};

#endif // INSCL_H
