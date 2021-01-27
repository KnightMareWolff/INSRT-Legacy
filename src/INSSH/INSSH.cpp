/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "INSSH.h"

CISHProgramManager*  INSSH::pISHProgramManager = NULL;

INSSH::INSSH()
{

}

INSSH::~INSSH()
{

}

INSSH::INSSH(INSGL *pINSGLPlatInterface)
{
    pISHProgramManager = new CISHProgramManager(pINSGLPlatInterface);
}

bool INSSH::SupportShaders(bool &bSupportVertexShader, bool &bSupportFragmentShader, bool &bSupportTessCtrlShader, bool &bSupportTessEvalShader, bool &bSupportGeometryShader, bool &bSupportComputeShader)
{
    int Count=0;
    if(bSupportVertexShader  = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex)){Count++;}
    if(bSupportFragmentShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment)){Count++;}
    if(bSupportTessCtrlShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::TessellationControl)){Count++;}
    if(bSupportTessEvalShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::TessellationEvaluation)){Count++;}
    if(bSupportGeometryShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Geometry)){Count++;}
    if(bSupportComputeShader = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Compute)){Count++;}

    if(Count>0)
    {
       return true;
    }

    return false;
}

bool INSSH::Inicializa()
{
    pISHProgramManager = new CISHProgramManager();
    return true;
}
