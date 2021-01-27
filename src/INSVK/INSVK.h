#ifndef INSVK_H
#define INSVK_H

#include "IVK_GlobalDef.h"

/**************************************************************/
/*Adotado acesso estatico , ao inves de acesso direto devido a*/
/*Uma instância da Interface ser capaz de gerenciar inúmeras  */
/*Plataformas, incluindo criação de contextos e Kernels.      */
/*Como a função de interface execCL será espalhada por todo o */
/*sistema através de herança direta , o uso de interface est. */
/*Garante a independencia e acoplamento do componente         */
/**************************************************************/
class INSVKInterface
{
public:
    INSVKInterface();

    //FUNÇÕES DE EXEC
    //void execVK(...);

    //FUNÇÕES DE SUPORTE
    //bool SuportaGLInteroperation();

private:
    //static CICLSistema *pINSCLStaticInterface;
};

#endif // INSVK_H
