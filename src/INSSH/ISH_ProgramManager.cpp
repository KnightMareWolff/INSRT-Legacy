/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "ISH_ProgramManager.h"

CISHProgramManager::CISHProgramManager()
{
   ISH_QtdProgramas = 0;
}

CISHProgramManager::CISHProgramManager(INSGL *pISHGLPlat)
{
   pISHGLPlatInterface = pISHGLPlat;

   ISH_QtdProgramas = 0;

   int tISH_ProgId = AddProgram("CoreRender");

#ifdef Q_OS_WIN
       switch(pISHGLPlatInterface->PegaVersao())
       {
          case IGL_OGL_V40:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs40.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs40.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
          case IGL_OGL_V41:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs41.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs41.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
          case IGL_OGL_V42:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs42.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs42.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
          case IGL_OGL_V43:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs43.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs43.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
          case IGL_OGL_V44:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs44.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs44.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
          case IGL_OGL_V45:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs45.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs45.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
          default:
          {
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/vs/pc/ins3dvs45.glsl",ISH_VERTEX_SHADER_TYPE);
             AddShader(tISH_ProgId,CIUTGerenciadorPath::IUT_PathWorld + "Shaders/fs/pc/ins3dfs45.glsl",ISH_FRAGMENT_SHADER_TYPE);
          }break;
       }
#endif
       /***************************************************************/
       /*Versão dos shaders para Mobile!!!                            */
       /***********************************************************************************************/
#ifdef Q_OS_ANDROID
       AddShader(tISH_ProgId,":/world/Shaders/vs/android/ins3dvs.glsl",ISH_VERTEX_SHADER_TYPE);
       AddShader(tISH_ProgId,":/world/Shaders/fs/android/ins3dfs.glsl",ISH_FRAGMENT_SHADER_TYPE);
#endif

#ifdef Q_OS_MAC
       AddShader(tISH_ProgId,":/world/Shaders/vs/mac/ins3dvs.glsl",ISH_VERTEX_SHADER_TYPE);
       AddShader(tISH_ProgId,":/world/Shaders/fs/mac/ins3dfs.glsl",ISH_FRAGMENT_SHADER_TYPE);
#endif

       Compile();
}

int CISHProgramManager::AddProgram(QString pISH_NomeProgram )
{
    int             IdDuplicado = 0   ;
    //Caso já exista material com este Nome retorna o ID do material existente
    if ( ChecaDuplicado(pISH_NomeProgram,IdDuplicado) ) return IdDuplicado;

    ISH_Programas.push_back(new CISHProgram());
    //Repassa os valores para o Novo material(Usado a Quantidade previa sem incremento como indice do vetor)
    ISH_Programas[ISH_QtdProgramas]->ISH_NomeProgram = pISH_NomeProgram;

    //Incrementa contador de materiais
    ISH_QtdProgramas += 1;

    //Retorna indice atual onde o material foi alocado
    return ISH_QtdProgramas - 1;
}

void CISHProgramManager::AddShader(QString pISH_NomeProgram,QString pISH_NomeShader,int pISH_TpShader)
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = PegaIndice(pISH_NomeProgram);

    if(!ChecaExistente(Indice))return;

    ISH_Programas[Indice]->AddShader(pISH_NomeShader,pISH_TpShader);
}

void CISHProgramManager::AddShader(int pISH_Indice,QString pISH_NomeShader,int pISH_TpShader)
{
    if(!ChecaExistente(pISH_Indice))return;

    ISH_Programas[pISH_Indice]->AddShader(pISH_NomeShader,pISH_TpShader);
}

void CISHProgramManager::Compile()
{
    for(int i=0 ; i<ISH_Programas.size();i++)
    {
        if(ISH_Programas[i]->ISH_Feedback)
        {
            pISHGLPlatInterface->AddTransformFeedback(ISH_Programas[i]->programId());
        }

        ISH_Programas[i]->link();
        ISH_Programas[i]->bind();
    }
}

uint CISHProgramManager::ProgramId(QString pISH_NomeProgram)
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = PegaIndice(pISH_NomeProgram);

    return ISH_Programas[Indice]->programId();
}

bool CISHProgramManager::ChecaDuplicado(QString pISH_NomeProgram, int &pISH_IndiceExistente)
{
    for(int i=0;i<ISH_QtdProgramas;i++)
    {
        if(ISH_Programas[i]->ISH_NomeProgram == pISH_NomeProgram)
        {
            pISH_IndiceExistente = i;
            return true;
        }
    }

    pISH_IndiceExistente = -1;

    return false;
}

bool CISHProgramManager::ChecaExistente(QString pISH_NomeProgram)
{
    for(int i=0;i<ISH_QtdProgramas;i++)
    {
        if(ISH_Programas[i]->ISH_NomeProgram == pISH_NomeProgram)
        {
            return true;
        }
    }
    return false;
}

bool CISHProgramManager::ChecaExistente(int pISH_Indice)
{
    if(pISH_Indice < 0                 )return false;
    if(pISH_Indice > ISH_QtdProgramas-1)return false;

    return true;
}

int CISHProgramManager::PegaIndice(QString pISH_NomeProgram)
{
    for(int i=0;i<ISH_QtdProgramas;i++)
    {
        if(ISH_Programas[i]->ISH_NomeProgram == pISH_NomeProgram)
        {
            return i;
        }
    }
    return -1;
}
