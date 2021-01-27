/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "INSSL.h"

INSSL::INSSL()
{
}

INSSL::INSSL(int ModoCarregamento, int IdProjeto)
{
    switch(ModoCarregamento)
    {
    case ISL_EDITOR_MODE:
    {
        CarregaModoEditor();
    }break;
    case ISL_QQUICK_MODE:
    {
        CarregaModoQuick();
    }break;
    case ISL_RUNTIME_MODE:
    {
        CarregaModoRuntime(IdProjeto);
    }break;
    }//fim switch
}

INSSL::~INSSL()
{
    delete pINSSMPlatInterface;//Interface Inicialização Gerenciamento Cenario
    delete pINSPLPlatInterface;//Interface Inicialização Camada de Apresentação
    delete pINSCRPlatInterface;//Interface Inicialização Camada de Scripts
}

void INSSL::CarregaModoEditor()
{
    mEditorWindow         = new CIPLEditorMainWindow;

    CIPLEditorGLWidget  *teste;

    teste = (CIPLEditorGLWidget*)mEditorWindow->centralWidget();

    pINSSMPlatInterface   = new INSSM(mEditorWindow->PegaContexto() ,
                                      "EditorProject"              );

    mEditorWindow->atribuiCenario(pINSSMPlatInterface->PegaCenario());
}

void INSSL::CarregaModoRuntime(int IdProjeto)
{
    /*****************************************/
    /*Instancia a janela principal do sistema*/
    /*****************************************/
    mRuntimeWindow = new CIPLRuntimeWindow;
    /*******************************/
    /*Cria um contexto OpenGL Novo */
    /*******************************/
    mContextGL = new QOpenGLContext();
    mContextGL->create();
    /**********************************************/
    /*Pega o Formato OpenGL disponivel em Hardware*/
    /**********************************************/
    mFormatoGL  = new QSurfaceFormat();
   *mFormatoGL  = mContextGL->format();

    int opengltype;
    switch(mFormatoGL->renderableType())
    {
      case QSurfaceFormat::OpenGL   : { opengltype = 0; }break;
      case QSurfaceFormat::OpenGLES : { opengltype = 1; }break;
      case QSurfaceFormat::OpenVG   : { opengltype = 2; }break;
    }

    mFormatoGL->setDepthBufferSize(5000);
    /***********************************************/
    /*Atribui este formato a ser utilizado pela win*/
    /***********************************************/
    mRuntimeWindow->setFormat(*mFormatoGL);
    /***********************************************/
    /*Atribui o contexto ATUAL a janela OpenGL     */
    /***********************************************/
    mContextGL->makeCurrent(mRuntimeWindow);
    /**********************************************************/
    /*Mapeia e verifica se o Hardware possui as extensões     */
    /*Obrigatórias para o Bom Funcionamento do sistema.       */
    /**********************************************************/
#ifdef Q_OS_WIN
    if(!mContextGL->hasExtension("GL_EXT_direct_state_access"))
    {
        qWarning() << "Seu Hardware não possui suporte a extensão OpenGL GL_EXT_direct_state_access.";
        //QMessageBox::information(0, "Insane RT Framework",
        //                            "OpenGL GL_EXT_direct_state_access - Hardware Não Suportado.");
        //exit(-1);
    }
    if(!mContextGL->hasExtension("GL_ARB_multitexture"))
    {
        qWarning() << "Seu Hardware não possui suporte a extensão OpenGL GL_EXT_direct_state_access.";
        QMessageBox::information(0, "Insane RT Framework",
                                    "OpenGL GL_EXT_direct_state_access - Hardware Não Suportado.");
        exit(-1);
    }
#endif

    /********************************************************/
    /*Inicializa plataforma de Gerenciamento de Cenario(SM) */
    /********************************************************/
    switch(IdProjeto)
    {
       case  0:{pINSSMPlatInterface = new INSSM(mContextGL,"DemoProject");}break;
       case  1:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo01");}break;
       case  2:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo02");}break;
       case  3:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo03");}break;
       case  4:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo04");}break;
       case  5:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo05");}break;
       case  6:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo06");}break;
       case  7:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo07");}break;
       case  8:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo08");}break;
       case  9:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo09");}break;
       case 10:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo10");}break;
       case 11:{pINSSMPlatInterface = new INSSM(mContextGL,"Exemplo11");}break;
    }

    /*********************************************************/
    /*Inicializa Plataforma de Scripts e atribui o SM Criado */
    /*********************************************************/
    switch(IdProjeto)
    {
       case  8:
       case  9:
       case 10:
       {
          pINSCRPlatInterface = new INSCR();
          pINSCRPlatInterface->AtribuiSM(pINSSMPlatInterface->PegaCenario());
       }break;
    }

    /************************************************************************/
    /*Atribui SM Criado e Contexto OpenGL para a camada de apresentação(PL) */
    /************************************************************************/
    mRuntimeWindow->atribuiCenario(pINSSMPlatInterface->PegaCenario());
    mRuntimeWindow->atribuiContexto(mContextGL);
    mRuntimeWindow->initializeGl();
}

void INSSL::CarregaModoQuick()
{
    /*****************************************/
    /*Instancia a janela principal do sistema*/
    /*****************************************/
    mTelaPrincipalQuickMode = new CIPLQQuickView;
    /*******************************/
    /*Cria um contexto OpenGL Novo */
    /*******************************/
    mContextGL = new QOpenGLContext();
    mContextGL->create();
    /**********************************************/
    /*Pega o Formato OpenGL disponivel em Hardware*/
    /**********************************************/
    mFormatoGL  = new QSurfaceFormat();
   *mFormatoGL  = mContextGL->format();
    /***********************************************/
    /*Atribui este formato a ser utilizado pela win*/
    /***********************************************/
    mTelaPrincipalQuickMode->setFormat(*mFormatoGL);
    /***********************************************/
    /*Atribui o contexto ATUAL a janela OpenGL     */
    /***********************************************/
    mContextGL->makeCurrent(mTelaPrincipalQuickMode);
    /**********************************************************/
    /*Mapeia e verifica se o Hardware possui as extensões     */
    /*Obrigatórias para o Bom Funcionamento do sistema.       */
    /**********************************************************/
#ifdef Q_OS_WIN
    if(!mContextGL->hasExtension("GL_EXT_direct_state_access"))
    {
        qWarning() << "Seu Hardware não possui suporte a extensão OpenGL GL_EXT_direct_state_access.";
        QMessageBox::information(0, "Insane RT Framework",
                                    "OpenGL GL_EXT_direct_state_access - Hardware Não Suportado.");
        //exit(-1);
    }
    if(!mContextGL->hasExtension("GL_ARB_multitexture"))
    {
        qWarning() << "Seu Hardware não possui suporte a extensão OpenGL GL_EXT_direct_state_access.";
        QMessageBox::information(0, "Insane RT Framework",
                                    "OpenGL GL_EXT_direct_state_access - Hardware Não Suportado.");
        exit(-1);
    }
#endif

    /********************************************************/
    /*Inicializa plataforma de Gerenciamento de Cenario     */
    /*Atenção!!!                                            */
    /*Para facilitar os estudos e a confecção dos exercicios*/
    /*No gerenciamento de cenario foi criado uma classe base*/
    /*para que sejam criados diversos cenarios de exemplo   */
    /*Portanto para cada exemplo novo será passado para a   */
    /*Camada de gerenciamento de cenario qual é o cenario   */
    /*a ser carregado.                                      */
    /********************************************************/
    pINSSMPlatInterface = new INSSM(mContextGL,"DemoProject");

    /***************************************/
    /*Inicializa utilizando a OpenGLWindow */
    /***************************************/
    mTelaPrincipalQuickMode->atribuiCenario(pINSSMPlatInterface->PegaCenario());
    mTelaPrincipalQuickMode->atribuiContexto(mContextGL);
    mTelaPrincipalQuickMode->initializeGl();
}

void INSSL::MostraTela(int ModoCarregamento)
{
    switch(ModoCarregamento)
    {
       case ISL_RUNTIME_MODE :
       {
          mRuntimeWindow->showMaximized();
       }break;
       case ISL_EDITOR_MODE :
       {
          mEditorWindow->showMaximized();
       }break;
       case ISL_QQUICK_MODE :
       {
          mTelaPrincipalQuickMode->show();
       }break;
    }
}
