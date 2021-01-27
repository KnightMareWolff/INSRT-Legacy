/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :Exemplo de Cubo 3D utilizando a GUI do Qt
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "ISM_Exemplo02.h"
#include "IUT_GerenciadorPath.h"

CISMExemplo02::CISMExemplo02(QOpenGLContext *pI3DContext):
    CISMCenario(pI3DContext)
{
    japosicionou          =false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo02::CISMExemplo02(QGLContext *pI3DContext):
    CISMCenario(pI3DContext)
{
    japosicionou          =false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo02::~CISMExemplo02()
{
    delete pCubo;
}

bool CISMExemplo02::Inicializa()
{
    //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );//Fundo Preto

    /***********************************************/
    /*Cria a Camera                                */
    /***********************************************/
    pCam = new CI3DCamera          ;//Instancia uma nova camera
    pCam   ->Inicializa()          ;//Inicializa a camera com valores default
    pCam   ->I3D_Velocidade = 25.0f;//seta a velocidade da camera

    /***********************************************/
    /*Adiciona os materiais da Cena                */
    /***********************************************/
    int IndiceMaterial;

    IndiceMaterial=INSMA::pINSMAMaterialManager->AddMaterial("Material Caixa",IGL_MATERIAL_TEXTURE);

    INSMA::pINSMAMaterialManager->AddTextura(IndiceMaterial,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->SetaRejeicaoCor(IndiceMaterial,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

    /***********************************************/
    /*Cria o Cubo                                  */
    /***********************************************/
    /*****************************************************************/
    /*Cria um novo cubo na posição (0,0,0) com dimensão (10,10,10) no*/
    /*sentido anti horário                                           */
    /*****************************************************************/
    pCubo           = new CI3DCubo  (CIMTVetor( 0.0f, 0.0f, 0.0f),
                                     CIMTVetor(10.0f,10.0f,10.0f),
                                     IGL_WINMODE_CW             );

    /*****************************************************************/
    /*Adiciona material ao Cubo                                      */
    /*****************************************************************/
    pCubo->I3D_Mesh->SetaMaterial(IndiceMaterial);
    pCubo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo02::Render(float pTimeElapsed)
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

    pCubo->Render(IGL_MODE_RENDER     ,
                  IGL_RENDER_TRIANGLES,
                  IGL_SHADING_MODE_FLAT);

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
       SetIniPos(pCam,pCubo->I3D_Pos);
       japosicionou = true;
    }

    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();

    return true;
}

bool CISMExemplo02::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,3000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo02::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo02::MoverCamera(int pAction)
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

bool CISMExemplo02::InputKey(int pKey)
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

bool CISMExemplo02::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 30.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMExemplo02::AtualizaCena()
{
    /******************************************/
    /*Neste exemplo não há nenhuma atualização*/
    /******************************************/
    return true;
}

bool CISMExemplo02::RodarCubo(CIMTVetor EixoRotacao)
{
    /******************************************/
    /*Neste exemplo não há nenhuma atualização*/
    /******************************************/
    pCubo->Rotate(true,EixoRotacao,pCubo->I3D_Pos);
    return true;
}


