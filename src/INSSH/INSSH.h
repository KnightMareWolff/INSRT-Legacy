/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef INSSH_H
#define INSSH_H

#include "ISH_GlobalDef.h"
#include "ISH_VertexShader.h"
#include "ISH_FragmentShader.h"
#include "ISH_GeometryShader.h"
#include "ISH_TessCtrlShader.h"
#include "ISH_TessEvalShader.h"
#include "ISH_ComputeShader.h"
#include "ISH_Program.h"
#include "ISH_ProgramManager.h"

class INSSH
{

public:
     INSSH(                          );
     INSSH(INSGL *pINSGLPlatInterface);
    ~INSSH(                          );

    bool SupportShaders(bool &bSupportVertexShader  ,
                        bool &bSupportFragmentShader,
                        bool &bSupportTessCtrlShader,
                        bool &bSupportTessEvalShader,
                        bool &bSupportGeometryShader,
                        bool &bSupportComputeShader);

    /*******************/
    /*Metodos de apoio */
    /*******************/
     bool SuportaShader         ();
     bool SuportaFeedBackBuffers();

    /*********************************/
    /*Metodos Estaticos de Interface */
    /*********************************/
    static bool Inicializa();
    static CISHProgramManager  *pISHProgramManager;
};

#endif // INSSH_H
