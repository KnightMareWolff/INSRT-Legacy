/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "ISH_Program.h"

CISHProgram::CISHProgram()
{
   ISH_NomeProgram = "Programa Default";
   ISH_Feedback    = true;
}

void CISHProgram::AddShader(QString pPath, int pShaderType)
{

  QOpenGLShader *shader;
  QString        log;

  switch (pShaderType)
  {
     case ISH_VERTEX_SHADER_TYPE:
     {
        shader = new CISHVertexShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case ISH_FRAGMENT_SHADER_TYPE:
     {
        shader = new CISHFragmentShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case ISH_GEOMETRY_SHADER_TYPE:
     {
        shader = new CISHGeometryShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case ISH_TESSCTRL_SHADER_TYPE:
     {
        shader = new CISHTessCtrlShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case ISH_TESSEVAL_SHADER_TYPE:
     {
        shader = new CISHTessEvalShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case ISH_COMPUTE_SHADER_TYPE:
     {
        shader = new CISHComputeShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
  }

  if(!addShader(shader))
  {
      //mapeamento de erro;
  }
}

void CISHProgram::AddFeedBack(bool bFeedBack)
{
    ISH_Feedback = bFeedBack;
}
