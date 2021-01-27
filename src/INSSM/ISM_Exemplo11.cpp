/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :Exemplo de Utilização de Volumes                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "ISM_Exemplo11.h"
#include "IUT_GerenciadorPath.h"

CISMExemplo11::CISMExemplo11(QOpenGLContext *pI3DContext):
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

CISMExemplo11::CISMExemplo11(QGLContext *pI3DContext):
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

CISMExemplo11::~CISMExemplo11()
{
    delete pLuzAmbiente;
    delete pEsfera01;
    delete pEsfera02;
    delete pEsfera03;
    delete pCubo01;
    delete pCubo02;
    delete pSky;
}

bool CISMExemplo11::Inicializa()
{
    direction = 3.0f;
    colidiu = false;
    /***********************************************/
    /*Cria a Camera                                */
    /***********************************************/
    pCam = new CI3DCamera          ;//Instancia uma nova camera
    pCam   ->Inicializa()          ;//Inicializa a camera com valores default
    pCam   ->I3D_Velocidade = 10.0f;//seta a velocidade da camera

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

    CriaMateriais();
    CriaObjetos();


    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo11::Render(float pTimeElapsed)
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

    AtualizaCena();
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

    pEsfera03->Render(IGL_MODE_RENDER     ,
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
    pCubo02->Update();

    Collision(pTimeElapsed);
    if(!japosicionou)
    {
       SetIniPos(pCam,pSky->I3D_Pos);
       japosicionou = true;
    }

    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();

    return true;
}

bool CISMExemplo11::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,30000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo11::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo11::MoverCamera(int pAction)
{
    /****************************************/
    /*Processa as teclas pressionadas       */
    /****************************************/
    switch(pAction)
    {
       case ISM_INPUT_MOVE_FOWARD:
       {
          pCam->MoverCamera(50.0f);
       }break;
       case ISM_INPUT_MOVE_BACKWARD:
       {
          pCam->MoverCamera(-50.0f);
       }break;
       case ISM_INPUT_MOVE_STRAFELFT:
       {
          pCam->CameraStrafe(-50.0f);;
       }break;
       case ISM_INPUT_MOVE_STRAFERGT:
       {
          pCam->CameraStrafe(50.0f);
       }break;
    }
    return true;
}

bool CISMExemplo11::InputKey(int pKey)
{
    /****************************************/
    /*Processa as teclas pressionadas       */
    /****************************************/
    switch(pKey)
    {
       case ISM_W_KEY:
       {
          pCam->MoverCamera(50.0f);
       }break;
       case ISM_S_KEY:
       {
          pCam->MoverCamera(-50.0f);
       }break;
       case ISM_A_KEY:
       {
          pCam->CameraStrafe(-50.0f);;
       }break;
       case ISM_D_KEY:
       {
          pCam->CameraStrafe(50.0f);
       }break;
    }
    return true;
}

bool CISMExemplo11::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
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

bool CISMExemplo11::AtualizaCena()
{
    CIMTMatriz mtxTransf;
    CIMTVetor  dest;

    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    mtxTransf.RotateY(0.01f,pEsfera01->I3D_Pos,true);
    dest = pLuzAmbiente->PegaPos() * mtxTransf;
    pLuzAmbiente->SetaPos(dest);
    pLuzAmbiente->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),IGL_LIGHT_CHANNEL_01);

    /************************************/
    /*Atualiza Todos os Obj   do cenario*/
    /************************************/
    pCubo01->Rotate(true,CIMTVetor(0.0f , direction,0.0f),pEsfera01->I3D_Pos);
    pCubo02->Rotate(true,CIMTVetor(0.0f ,-direction,0.0f),pEsfera01->I3D_Pos);

    pEsfera01->Rotate(false,CIMTVetor( 0.0f ,-1.0f,0.0f),pEsfera01->I3D_Pos);
    pEsfera02->Rotate(false,CIMTVetor( 0.0f ,-1.0f,0.0f),pEsfera02->I3D_Pos);
    pEsfera03->Rotate(false,CIMTVetor( 0.0f ,-1.0f,0.0f),pEsfera02->I3D_Pos);


    return true;
}

bool CISMExemplo11::CriaMateriais()
{
    /***********************************************/
    /*Adiciona os materiais da Cena                */
    /***********************************************/
    //Inclui Material a ser usado pelos Cubos
    IdMatCubo=INSMA::pINSMAMaterialManager->AddMaterial("Material Esferas",IGL_MATERIAL_TEXTURE);
    INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                             IGL_TEXTURE_LINEAR);

    //Inclui Material a ser usado pelos Cubos
    IdMatEsfera=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubos",IGL_MATERIAL_TEXTURE);
    INSMA::pINSMAMaterialManager->AddTextura(IdMatEsfera,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Ladrilho_Misterio.bmp",
                                             IGL_TEXTURE_LINEAR);

    //Cria Material da SkyBox
    IdMatSky=INSMA::pINSMAMaterialManager->AddMaterial("Material SkyBox",IGL_MATERIAL_CUBEMAP);

    INSMA::pINSMAMaterialManager->AddCubeMap(IdMatSky,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-right.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-left.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-top.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-bottom.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-back.png",
                                             CIUTGerenciadorPath::IUT_PathWorld + "Sky-box/WhiteDwarf/wd-front.png" );
    return true;
}

bool CISMExemplo11::CriaObjetos()
{
    /*************************/
    /*Cria Uma SkyBox        */
    /*************************/
    pSky     = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                              CIMTVetor(4096.0f,4096.0f,4096.0f),
                              IGL_WINMODE_CCW);

    pSky->I3D_Mesh->SetaMaterial(IdMatSky);
    pSky->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_STATIC);

    CIMTVetor PosIni = pSky->I3D_Pos;
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pEsfera01           = new CI3DEsfera(CIMTVetor( PosIni.x,
                                                    PosIni.y,
                                                    PosIni.z));
    pEsfera01->I3D_Mesh->SetaMaterial(IdMatEsfera);
    pEsfera01->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pEsfera02           = new CI3DEsfera(CIMTVetor( PosIni.x - 7.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f));
    pEsfera02->I3D_Mesh->SetaMaterial(IdMatEsfera);
    pEsfera02->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pEsfera03           = new CI3DEsfera(CIMTVetor( PosIni.x + 7.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f));
    pEsfera03->I3D_Mesh->SetaMaterial(IdMatEsfera);
    pEsfera03->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pCubo01             = new CI3DCubo  (CIMTVetor( PosIni.x + 14.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f),
                                         CIMTVetor( 2.5f, 2.5f, 2.5f),
                                         IGL_WINMODE_CW             );

    pCubo01->I3D_Mesh->SetaMaterial(IdMatCubo);
    pCubo01->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_STATIC);

    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pCubo02             = new CI3DCubo  (CIMTVetor( PosIni.x - 14.0f,
                                                    PosIni.y + 0.0f,
                                                    PosIni.z + 0.0f),
                                         CIMTVetor( 2.5f, 2.5f, 2.5f),
                                         IGL_WINMODE_CW             );

    pCubo02->I3D_Mesh->SetaMaterial(IdMatCubo);
    pCubo02->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_PHYSICS);

    return true;

}

bool CISMExemplo11::Collision(float pTimeElapsed)
{
    if(pCubo01->Collision(pCubo02,pTimeElapsed))
    {
        direction = direction * (-1);
    }
    return true;
}
