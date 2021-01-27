#include "ISM_DemoProject.h"
#include "IUT_GerenciadorPath.h"

CISMDemoProject::CISMDemoProject(QOpenGLContext *pI3DContext):
    CISMCenario(pI3DContext)
{
    japosicionou          =false;
    bObjetosInicializados =false;
    luainicializado       =false;
    bFxTocou              =false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMDemoProject::CISMDemoProject(QGLContext *pI3DContext):
    CISMCenario(pI3DContext)
{
    japosicionou          =false;
    bObjetosInicializados =false;
    luainicializado       =false;
    bFxTocou              =false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMDemoProject::~CISMDemoProject()
{
    delete pCubo;

}

bool CISMDemoProject::Inicializa()
{
    //glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );//Fundo Preto

    /***********************************************/
    /*Cria a Camera                                */
    /***********************************************/
    pCam = new CI3DCamera;
    pCam->Inicializa();
    pCam->I3D_Velocidade = 25.0f;

    /***********************************************/
    /*Cria as Luzes utilizadas no cenario          */
    /***********************************************/
    pLuzAmbiente = new CI3DLuz();

    //pLuzAmbiente->SetaCorAmbiente(CI3DCor  (100.5f   , 100.5f  , 100.5f   ,1.0f));
    pLuzAmbiente->Prepara(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);

    pMundo = new CIGOMundo();
    pAtor  = new CIGOAtor ();
    pBrush = new CIGOBrush();

    bObjetosInicializados = true;

    return true;
}

bool CISMDemoProject::Render(float pTimeElapsed)
{
    GLsync localsync;

    CriaFenceSync(localsync);
    /*******************************************************************/
    /*Configura os Estados Iniciais da Maquina de Estado da OpenGL     */
    /*O Loop Principal de Renderização de Objetos deve ser colocado    */
    /*Entre o Inicio e o Fim deste Bloco                               */
    /*******************************************************************/
    /*Inicio do Bloco Principal OPENGL*/
    EnableOGLStates();
    EnableOGLCW();


    /********************************************************************/
    /*Atualiza a Camera (O Posicionamento precisa ficar dentro do Bloco)*/
    /********************************************************************/
    float currenttime,timeelapsed;
    pCam->PosicionaCamera(currenttime,timeelapsed);

    if(bObjetosInicializados)
    {


       pBrush->Render();
       pAtor ->Render();
       pMundo->Render();
       //pCam->CalculaPerspectiva(10.0f,5000.0f,IGL_PROJECTION_ORTHO);
       //pCaixaAmbiental->Render();
       //pCam->CalculaPerspectiva(10.0f,5000.0f,IGL_PROJECTION_PERSP);

       /********************************************************/
       /*Atualiza Todos os Controles do Cenario                */
       /*Basicamente Durante a Renderização são estabelacidos  */
       /*objetos que controlam o comportamento geral do cenario*/
       /*como luzes ambiente que afetam as cores dos materiais */
       /*de cada objeto na cena, bem como a forma de shading   */
       /*Este metodo é responsavel em atualizar estes controles*/
       /********************************************************/
       AtualizaCena();

    }



    if(!japosicionou)
    {
       SetIniPos(pCam,CIMTVetor(0.0f,0.0f,0.0f));
       japosicionou = true;
    }

    WaitFenceSync(localsync);
    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();



    return true;
}

bool CISMDemoProject::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,50000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMDemoProject::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMDemoProject::MoverCamera(int pAction)
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

bool CISMDemoProject::InputKey(int pKey)
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

bool CISMDemoProject::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 90.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMDemoProject::AtualizaCena()
{
    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    pLuzAmbiente   ->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);
    /**************************************/
    /*Atualiza Todos os objetos do cenario*/
    /**************************************/
    //pCubo  ->Translate(pCaixaAmbiental->PegaCentro(),false);
    //pCubo  ->Rotate   (false,CIMTVetor(0.0f,1.0f,0.0f),pCaixaAmbiental->PegaCentro());

    //pCaixaAmbiental->Animar();

    return true;
}



