/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :Exemplo de Utilização de Iluminação e Materiais            */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "ISM_Exemplo03.h"
#include "IUT_GerenciadorPath.h"

CISMExemplo03::CISMExemplo03(QOpenGLContext *pI3DContext):
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

CISMExemplo03::CISMExemplo03(QGLContext *pI3DContext):
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

CISMExemplo03::~CISMExemplo03()
{
    delete pLuzAmbiente;
    delete pEsfera01;
    delete pEsfera02;
    delete pCubo01;
    delete pCubo02;
    delete pSky;
    delete pModelo;
}

bool CISMExemplo03::Inicializa()
{
    direction = 1.0f;
    colidiu = false;
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
    pLuzAmbiente->SetaCorDifusa  (CIMACor(0.0f ,0.07f,0.0f ,1.0f));
    pLuzAmbiente->SetaCorSpecular(CIMACor(0.7f ,0.0f ,0.0f ,1.0f));
    pLuzAmbiente->SetaCorAmbiente(CIMACor(0.0f ,0.0f ,0.2f ,1.0f));
    pLuzAmbiente->SetaAtenuacao(0.01f,0.001f,0.0001f);
    pLuzAmbiente->SetaPos(CIMTVetor(60.0f,0.0f,0.0f));
    pLuzAmbiente->Prepara(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);

    /***********************************************/
    /*Adiciona os materiais da Cena                */
    /***********************************************/
    int IdMatCubo01   ,
        IdTexCubo01   ,
        IdMatCubo02   ,
        IdTexCubo02   ,
        IdMatEsf01    ,
        IdTexEsf01    ,
        IdMatEsf02    ,
        IdTexEsf02    ,
        IdMatSky      ,
        IdTexturaSky01,
        IdTexturaSky02,
        IdTexturaSky03,
        IdTexturaSky04,
        IdTexturaSky05,
        IdTexturaSky06;

    //Inclui Material a ser usado pelo Cubo 01
    IdMatCubo01=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo01",IGL_MATERIAL_REFLEXIVE);

    IdTexCubo01=INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo01,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->AddCubeMap(IdMatCubo01,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" );

    //Inclui Material a ser usado pelo Cubo 02
    IdMatCubo02=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo02",IGL_MATERIAL_REFRATIVE);

    IdTexCubo02=INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo02,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Ladrilho_Misterio.bmp",
                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->AddCubeMap(IdMatCubo02,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" );


    INSMA::pINSMAMaterialManager->SetaRejeicaoCor(IdMatCubo02,false,CIMACor(0.0f,0.0f,0.0f,1.0f));


    //Cria Material da SkyBox
    IdMatSky=INSMA::pINSMAMaterialManager->AddMaterial("Material SkyBox Exemplo03",IGL_MATERIAL_CUBEMAP);

    INSMA::pINSMAMaterialManager->AddCubeMap(IdMatSky,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" );
    /*************************/
    /*Cria Uma SkyBox        */
    /*************************/
    pSky     = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                              CIMTVetor(4096.0f,4096.0f,4096.0f),
                              IGL_WINMODE_CCW);

    pSky->I3D_Mesh->SetaMaterial(IdMatSky);
    pSky->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    /*****************************************************************/
    /*Cria Modelo Detalhado(Muitos Vertices                          */
    /*****************************************************************/
    pModelo  = new CI3DModelo(CIUTGerenciadorPath::IUT_PathWorld + "Modelos/Ogro.obj","Material Ogro",false);


    pModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    CIMTVetor PosIni = pModelo->I3D_Pos;
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pEsfera01           = new CI3DEsfera(CIMTVetor( PosIni.x + 7.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f));
    pEsfera01->I3D_Mesh->SetaMaterial(IdMatCubo01);
    pEsfera01->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pEsfera02           = new CI3DEsfera(CIMTVetor( PosIni.x - 7.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f));
    pEsfera02->I3D_Mesh->SetaMaterial(IdMatCubo02);
    pEsfera02->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pCubo01             = new CI3DCubo  (CIMTVetor( PosIni.x + 14.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f),
                                         CIMTVetor( 2.5f, 2.5f, 2.5f),
                                         IGL_WINMODE_CW             );

    pCubo01->I3D_Mesh->SetaMaterial(IdMatCubo01);
    pCubo01->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pCubo02             = new CI3DCubo  (CIMTVetor( PosIni.x - 14.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f),
                                         CIMTVetor( 2.5f, 2.5f, 2.5f),
                                         IGL_WINMODE_CW             );

    pCubo02->I3D_Mesh->SetaMaterial(IdMatCubo02);
    pCubo02->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);


    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo03::Render(float pTimeElapsed)
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
    pSky->Render(IGL_MODE_RENDER        ,
                 IGL_RENDER_TRIANGLES   ,
                 IGL_SHADING_MODE_SMOOTH);
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
    pEsfera01->Render(IGL_MODE_RENDER     ,
                      IGL_RENDER_TRIANGLES,
                      IGL_SHADING_MODE_SMOOTH);

    pEsfera02->Render(IGL_MODE_RENDER     ,
                      IGL_RENDER_TRIANGLES,
                      IGL_SHADING_MODE_SMOOTH);

    pModelo->Render(IGL_MODE_RENDER     ,
                    IGL_RENDER_TRIANGLES,
                    IGL_SHADING_MODE_SMOOTH);

    pCubo01->Render(IGL_MODE_RENDER     ,
                    IGL_RENDER_TRIANGLES,
                    IGL_SHADING_MODE_SMOOTH);

    pCubo02->Render(IGL_MODE_RENDER     ,
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

bool CISMExemplo03::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,30000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo03::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo03::MoverCamera(int pAction)
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

bool CISMExemplo03::InputKey(int pKey)
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

bool CISMExemplo03::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 20.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMExemplo03::AtualizaCena()
{
    CIMTMatriz mtxTransf;
    CIMTVetor  dest;

    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    mtxTransf.RotateY(0.01f,pModelo->I3D_Pos,true);
    dest = pLuzAmbiente->PegaPos() * mtxTransf;
    pLuzAmbiente->SetaPos(dest);
    pLuzAmbiente->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),IGL_LIGHT_CHANNEL_01);

    /************************************/
    /*Atualiza Todos os Obj   do cenario*/
    /************************************/
    pCubo01->Rotate(true,CIMTVetor(0.0f , direction,0.0f),pModelo->I3D_Pos);
    pCubo01->Rotate(true,CIMTVetor(1.0f , 0.0f     ,0.0f),pModelo->I3D_Pos);

    /************************************/
    /*Atualiza Todos os Obj   do cenario*/
    /************************************/
    pCubo02->Rotate(true,CIMTVetor( 0.0f ,-direction,0.0f),pModelo->I3D_Pos);
    pCubo02->Rotate(true,CIMTVetor(-1.0f , 0.0f     ,0.0f),pModelo->I3D_Pos);

    pEsfera01->Rotate(false,CIMTVetor( 0.0f ,-1.0f,0.0f),pEsfera01->I3D_Pos);
    pEsfera02->Rotate(false,CIMTVetor( 0.0f ,-1.0f,0.0f),pEsfera02->I3D_Pos);


    return true;
}



