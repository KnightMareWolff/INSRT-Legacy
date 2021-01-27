/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Carregamento de Modelos
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "ISM_Exemplo04.h"
#include "IUT_GerenciadorPath.h"

CISMExemplo04::CISMExemplo04(QOpenGLContext *pI3DContext):
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

CISMExemplo04::CISMExemplo04(QGLContext *pI3DContext):
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

CISMExemplo04::~CISMExemplo04()
{
    delete pLuzAmbiente;
    delete pSky;
    delete pModelo;
}

bool CISMExemplo04::Inicializa()
{
    /***********************************************/
    /*Cria a Camera                                */
    /***********************************************/
    pCam = new CI3DCamera          ;//Instancia uma nova camera
    pCam   ->Inicializa()          ;//Inicializa a camera com valores default
    pCam   ->I3D_Velocidade = 25.0f;//seta a velocidade da camera

    /***********************************************/
    /*Cria as Luzes utilizadas no cenario          */
    /***********************************************/
    pLuzAmbiente = new CI3DLuz();
    pLuzAmbiente->SetaPos(CIMTVetor(60.0f,0.0f,0.0f));
    pLuzAmbiente->SetaCorDifusa(CIMACor(0.0f,1.0f,0.0f,1.0));
    pLuzAmbiente->SetaCorAmbiente(CIMACor(0.0f,1.0f,0.0f,1.0));
    pLuzAmbiente->Prepara(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);

    /*************************/
    /*Cria Uma SkyBox        */
    /*************************/
    pSky     = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                              CIMTVetor(512.0f,512.0f,512.0f),
                              IGL_WINMODE_CCW);


    //Cria Material da SkyBox
    IdMatSky=INSMA::pINSMAMaterialManager->AddMaterial("Material SkyBox",IGL_MATERIAL_CUBEMAP);

    INSMA::pINSMAMaterialManager->AddCubeMap(IdMatSky,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" );


    pSky->I3D_Mesh->SetaMaterial(IdMatSky);
    pSky->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pModelo  = new CI3DModelo(CIUTGerenciadorPath::IUT_PathWorld + "Modelos/Ogro.obj","Material Ogro",false);

    pModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_STATIC);

    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo04::Render(float pTimeElapsed)
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
    /*************************************************************************************************/
    /*Renderiza a esfera de acordo com os parametros de iluminação e materiais                       */
    /*IGL_MATERIAL_COLOR   -> Renderiza Material + Iluminação                                        */
    /*IGL_MATERIAL_TEXTURE -> Renderiza Material + Textura + Iluminação                              */
    /*IGL_MATERIAL_MIXED   -> Renderiza Material + Textura + Iluminação(Mixa Textura com iluminação) */
    /*                                                                                               */
    /*IGL_SHADING_MODE_FLAT  -> Realiza o Shading Phong  Flat  (Normais Planares)                    */
    /*IGL_SHADING_MODE_SMOOTH-> Realiza o Shading Phong  Smooth(Normais partindo do centro)          */
    /*IGL_SHADING_MODE_DIFLAT-> Realiza o Shading Difuso Flat                                        */
    /*IGL_SHADING_MODE_DIFOTH-> Realiza o Shading Difuso Smooth                                      */
    /*                                                                                               */
    /*************************************************************************************************/
    pModelo->Render(IGL_MODE_RENDER     ,
                    IGL_RENDER_TRIANGLES,
                    IGL_SHADING_MODE_SMOOTH);

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
       SetIniPos(pCam,pModelo->I3D_Pos);
       japosicionou = true;
    }

    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();

    return true;
}

bool CISMExemplo04::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,3000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo04::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo04::MoverCamera(int pAction)
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

bool CISMExemplo04::InputKey(int pKey)
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

bool CISMExemplo04::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 15.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMExemplo04::AtualizaCena()
{
    CIMTMatriz mtxTransf;
    CIMTVetor  dest;
    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    mtxTransf.RotateY(-0.01f,pModelo->I3D_Pos,true);
    dest = pLuzAmbiente->PegaPos() * mtxTransf;
    pLuzAmbiente->SetaPos(dest);

    //pModelo->Rotate(true,CIMTVetor(0.0f,1.5f,0.0f),pModelo->mPos);
    /*************************************************************/
    /*Gira a SkyBox um pouco para o efeito de Refração e Reflexão*/
    /*************************************************************/
    //pSky->Rotate(true,CIMTVetor(0.0f,0.5f,0.0f),CIMTVetor(0.0f,0.0f,0.0f));

    pLuzAmbiente->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);
    return true;
}


