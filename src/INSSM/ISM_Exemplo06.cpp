/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Utilização de Picking
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "ISM_Exemplo06.h"
#include "IUT_GerenciadorPath.h"

CISMExemplo06::CISMExemplo06(QOpenGLContext *pI3DContext):
    CISMCenario(pI3DContext)
{
    japosicionou=false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo06::CISMExemplo06(QGLContext *pI3DContext):
    CISMCenario(pI3DContext)
{
    japosicionou=false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo06::~CISMExemplo06()
{
    delete pLuzAmbiente;
    delete pSky;
    delete pCubo01;
    delete pCubo02;
    delete pCubo03;
}

bool CISMExemplo06::Inicializa()
{
    /***********************************************/
    /*Cria a Camera                                */
    /***********************************************/
    pCam = new CI3DCamera          ;//Instancia uma nova camera
    pCam   ->Inicializa()          ;//Inicializa a camera com valores default
    pCam   ->I3D_Velocidade = 25.0f;//seta a velocidade da camera

    /***********************************************/
    /*Adiciona os materiais da Cena                */
    /***********************************************/
    int IdMatCubo01,IdMatCubo02,IdMatCubo03;

    //Inclui Material a ser usado pelo Cubo 01
    IdMatCubo01=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo01",IGL_MATERIAL_TEXTURE);

    INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo01,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->SetaRejeicaoCor(IdMatCubo01,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

    //Inclui Material a ser usado pelo Cubo 02
    IdMatCubo02=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo02",IGL_MATERIAL_TEXTURE);

    INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo02,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Blocos_Madeira.bmp",
                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->SetaRejeicaoCor(IdMatCubo02,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

    //Inclui Material a ser usado pelo Cubo 03
    IdMatCubo03=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo03",IGL_MATERIAL_TEXTURE);

    INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo03,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Escritas_Cripta.bmp",
                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->SetaRejeicaoCor(IdMatCubo03,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

    /***********************************************/
    /*Cria as Luzes utilizadas no cenario          */
    /***********************************************/
    pLuzAmbiente = new CI3DLuz();
    pLuzAmbiente->SetaPos(CIMTVetor(0.0f,0.0f,0.0f));
    pLuzAmbiente->Prepara(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);

    /*************************/
    /*Cria Uma SkyBox        */
    /*************************/
    pSky     = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                              CIMTVetor(512.0f,512.0f,512.0f),
                              IGL_WINMODE_CCW);

    //pSky->AddTexturas(CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png"   ,
    //                  CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png"  ,
    //                  CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png"  ,
    //                  CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" ,
    //                  CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png" ,
    //                  CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png" );

    pSky->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    /*****************************************************************/
    /*Cria um novo cubo na posição (0,0,0) com dimensão (10,10,10) no*/
    /*sentido anti horário                                           */
    /*****************************************************************/
    pCubo01           = new CI3DCubo  (CIMTVetor( 0.0f, 0.0f, 0.0f),
                                       CIMTVetor(10.0f,10.0f,10.0f),
                                       IGL_WINMODE_CW             );

    /*****************************************************************/
    /*Adiciona uma textura ao Cubo                                   */
    /*****************************************************************/
    pCubo01->I3D_Mesh->SetaMaterial(IdMatCubo01);
    pCubo01->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    pCubo01->SetaSelecao(true);

    /*****************************************************************/
    /*Cria um novo cubo na posição (0,0,0) com dimensão (10,10,10) no*/
    /*sentido anti horário                                           */
    /*****************************************************************/
    pCubo02           = new CI3DCubo  (CIMTVetor(20.0f, 0.0f, 0.0f),
                                       CIMTVetor(10.0f,10.0f,10.0f),
                                       IGL_WINMODE_CW             );

    /*****************************************************************/
    /*Adiciona uma textura ao Cubo                                   */
    /*****************************************************************/
    pCubo02->I3D_Mesh->SetaMaterial(IdMatCubo02);
    pCubo02->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    pCubo02->SetaSelecao(true);

    /*****************************************************************/
    /*Cria um novo cubo na posição (0,0,0) com dimensão (10,10,10) no*/
    /*sentido anti horário                                           */
    /*****************************************************************/
    pCubo03           = new CI3DCubo  (CIMTVetor(-20.0f, 0.0f, 0.0f),
                                       CIMTVetor( 10.0f,10.0f,10.0f),
                                       IGL_WINMODE_CW             );

    /*****************************************************************/
    /*Adiciona uma textura ao Cubo                                   */
    /*****************************************************************/
    pCubo03->I3D_Mesh->SetaMaterial(IdMatCubo03);
    pCubo03->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    pCubo03->SetaSelecao(true);


    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo06::Render(float pTimeElapsed)
{
    /*******************************************************************/
    /*Configura os Estados Iniciais da Maquina de Estado da OpenGL     */
    /*O Loop Principal de Renderização de Objetos deve ser colocado    */
    /*Entre o Inicio e o Fim deste Bloco                               */
    /*******************************************************************/
    /*Inicio do Bloco Principal OPENGL*/
    EnableOGLStates();

    /********************************************************************/
    /*Atualiza a Camera (O Posicionamento precisa ficar dentro do Bloco)*/
    /********************************************************************/
    pCam->PosicionaCamera();

    /*****************************/
    /*Renderiza a SkyBox         */
    /*****************************/
    pSky->Render(IGL_MODE_RENDER     ,
                 IGL_RENDER_TRIANGLES,
                 IGL_SHADING_MODE_NOONE);

    /************************************************/
    /*Renderiza os objetos principais do exemplo    */
    /************************************************/
    if(!pCubo01->I3D_Selecionado)
    {
       pCubo01->Render(IGL_MODE_RENDER     ,
                       IGL_RENDER_TRIANGLES,
                       IGL_SHADING_MODE_SMOOTH);
    }

    if(!pCubo02->I3D_Selecionado)
    {
       pCubo02->Render(IGL_MODE_RENDER     ,
                       IGL_RENDER_TRIANGLES,
                       IGL_SHADING_MODE_SMOOTH);
    }

    if(!pCubo03->I3D_Selecionado)
    {
       pCubo03->Render(IGL_MODE_RENDER     ,
                       IGL_RENDER_TRIANGLES,
                       IGL_SHADING_MODE_SMOOTH);
    }
    /********************************************************/
    /*Atualiza Todos os Controles do Cenario                */
    /*Basicamente Durante a Renderização são estabelacidos  */
    /*objetos que controlam o comportamento geral do cenario*/
    /*como luzes ambiente que afetam as cores dos materiais */
    /*de cada objeto na cena, bem como a forma de shading   */
    /*Este metodo é responsavel em atualizar estes controles*/
    /********************************************************/
    AtualizaCena();

    if(!japosicionou)
    {
       SetIniPos(pCam,pSky->I3D_Pos);
       japosicionou = true;
    }

    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();

    return true;
}

bool CISMExemplo06::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,3000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo06::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo06::Seleciona(int x, int y)
{
    GLchar res[4];
    EnableOGLStates();

    pCubo01->SetaIdSelecao(1);
    pCubo02->SetaIdSelecao(2);
    pCubo03->SetaIdSelecao(3);
    /************************************************/
    /*Renderiza os objetos principais do exemplo    */
    /************************************************/
    pCubo01->Render(IGL_MODE_SELECTION_PRIMI,
                    IGL_RENDER_TRIANGLES,
                    IGL_SHADING_MODE_SMOOTH);
    pCubo02->Render(IGL_MODE_SELECTION_PRIMI,
                    IGL_RENDER_TRIANGLES,
                    IGL_SHADING_MODE_SMOOTH);
    pCubo03->Render(IGL_MODE_SELECTION_PRIMI,
                    IGL_RENDER_TRIANGLES,
                    IGL_SHADING_MODE_SMOOTH);

    ReadPixels(x,y,res);

    switch(res[0])
    {
       case 1:{pCubo01->SetaSelecionado(true);}break;
       case 2:{pCubo02->SetaSelecionado(true);}break;
       case 3:{pCubo03->SetaSelecionado(true);}break;
       default:
       {
           pCubo01->SetaSelecionado(false);
           pCubo02->SetaSelecionado(false);
           pCubo03->SetaSelecionado(false);
       }
    }

    DisableOGLStates();

    return true;
}

bool CISMExemplo06::MoverCamera(int pAction)
{
    /****************************************/
    /*Processa as teclas pressionadas       */
    /****************************************/
    switch(pAction)
    {
       case ISM_INPUT_MOVE_FOWARD:
       {
          pCam->MoverCamera(150.0f);
       }break;
       case ISM_INPUT_MOVE_BACKWARD:
       {
          pCam->MoverCamera(-150.0f);
       }break;
       case ISM_INPUT_MOVE_STRAFELFT:
       {
          pCam->CameraStrafe(-150.0f);;
       }break;
       case ISM_INPUT_MOVE_STRAFERGT:
       {
          pCam->CameraStrafe(150.0f);
       }break;
    }
    return true;
}

bool CISMExemplo06::InputKey(int pKey)
{
    /****************************************/
    /*Processa as teclas pressionadas       */
    /****************************************/
    switch(pKey)
    {
       case ISM_W_KEY:
       {
          pCam->MoverCamera(150.0f);
       }break;
       case ISM_S_KEY:
       {
          pCam->MoverCamera(-150.0f);
       }break;
       case ISM_A_KEY:
       {
          pCam->CameraStrafe(-150.0f);;
       }break;
       case ISM_D_KEY:
       {
          pCam->CameraStrafe(150.0f);
       }break;
    }
    return true;
}

bool CISMExemplo06::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 60.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMExemplo06::AtualizaCena()
{
    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    pLuzAmbiente->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);
    return true;
}
