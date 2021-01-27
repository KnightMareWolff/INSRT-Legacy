/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "INS3D.h"
#include "IUT_GerenciadorPath.h"

INS3D::INS3D(QOpenGLContext *context)
{
   pINSGLPlatInterface = new INSGL         (context            );
   pINSSHPlatInterface = new INSSH         (pINSGLPlatInterface);
   pINSMAPlatInterface = new INSMA         (                   );

   QString Vendor = pINSGLPlatInterface->PegaVendor();

   pINSCLPlatInterface = new INSCLInterface(context,Vendor);
   pINSMAPlatInterface->Inicializa();

   //Cria a interface Vulkan
   //pINSVKPlatInterface = new INSVKInterface();

}

INS3D::INS3D(QGLContext *context)
{
   pINSGLPlatInterface = new INSGL         (context            );
   pINSSHPlatInterface = new INSSH         (pINSGLPlatInterface);
   pINSMAPlatInterface = new INSMA         (                   );

   QString Vendor = pINSGLPlatInterface->PegaVendor();

   pINSCLPlatInterface = new INSCLInterface(context,Vendor);
   pINSMAPlatInterface->Inicializa();
}

bool INS3D::ReadPixels(int x,int y, GLchar *res)
{
   pINSGLPlatInterface->execGL(IGL_FRAMEBUFFER_PIXEL,x,y,res);
   return true;
}

bool INS3D::CalculaPVMatriz(CIMTMatriz pI3D_MatrizModel,CIMTMatriz &pIMT_PVMatriz)
{
   return pINSGLPlatInterface->CalculaPVMMatrix(pI3D_MatrizModel,pIMT_PVMatriz,true);
}

void INS3D::EnableStates()
{
    pINSGLPlatInterface->execGL(IGL_SH_ENABLESTATES);
}

void INS3D::DisableStates()
{
    pINSGLPlatInterface->execGL(IGL_SH_DISABLESTATES);
}

void INS3D::CriaFenceSync(GLsync &pI3D_GLSync)
{
    pINSGLPlatInterface->FenceSync(pI3D_GLSync);
}

void INS3D::WaitFenceSync(GLsync pI3D_GLSync)
{
    pINSGLPlatInterface->WaitSync(pI3D_GLSync);
}

void INS3D::Enable(int ProgramId, int iState)
{
    pINSGLPlatInterface->execGL(IGL_SH_ENABLE,ProgramId,iState);
}

void INS3D::Disable(int ProgramId,int iState)
{
    pINSGLPlatInterface->execGL(IGL_SH_DISABLE,ProgramId,iState);
}

void INS3D::UpdateHardDC()
{
    //Atualiza o Device context OpenGL das placas de video
    pINSCLPlatInterface->execCL(ICL_EXEC_UPDATE_GL_CTXT);
}
