#ifndef CICLPROGRAMA_H
#define CICLPROGRAMA_H

#include "ICL_GlobalDef.h"
#include "ICL_Kernel.h"

class CICLPrograma
{
public:
     CICLPrograma(cl_context   pICL_DeviceContext ,
                  cl_device_id pICL_DeviceID      ,
                  QString      pICL_FileName      );

    ~CICLPrograma(                                );

     CICLKernel* PegaKernelPorNome(QString pICL_Nome);

     QString ICL_ProgramName;

private:
    cl_program    ICL_ProgramID;

    //controle de compilação
    //Log de Compilação
    char*   program_log;
    size_t  log_size;

    //Kernels para Execução
    cl_uint             ICL_QtdKernels;
    vector<CICLKernel*> ICL_Kernels;
};

#endif // CICLPROGRAMA_H
