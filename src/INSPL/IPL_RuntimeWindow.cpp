/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "IPL_RuntimeWindow.h"
#include <QOpenGLContext>
#include <QTimer>


CIPLRuntimeWindow::CIPLRuntimeWindow()
{
    /*******************************************/
    /*Sem a chamada do metodo create deste com */
    /*ponente a inicialização das funções open */
    /*GL não funcionam já que as mesmas utili  */
    /*zam inicialização da GUI para funcionar  */
    /*******************************************/
    create();

    mInitialized = false;
    /***********************************************/
    /*Informa que teremos uma superficie OpenGL    */
    /***********************************************/
    setSurfaceType(OpenGLSurface);
    /***********************************************/
    /*Configura o nome da janela                   */
    /***********************************************/
    setTitle(tr("Insane RT Framework"));
    setCursor(mCursor);

    /***********************************************/
    /*Conecta os Slots de Janela(Ver referencias Qt*/
    /***********************************************/
    connect(this, SIGNAL(widthChanged (int)), this, SLOT(resizeGl()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGl()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(RenderScene()));
    timer->start(0);

    elapsedtimer = new QElapsedTimer();
    elapsedtimer->start();

    mouseBtnPress=false;

    setIcon(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/insicon.png"));
}

CIPLRuntimeWindow::~CIPLRuntimeWindow()
{
}

void CIPLRuntimeWindow::initializeGl()
{
    mInitialized    =true;
}

void CIPLRuntimeWindow::atribuiCenario(CISMCenario *pScn)
{
    p3DCenario = pScn;
}

void CIPLRuntimeWindow::atribuiContexto(QOpenGLContext *pCtxt)
{
    mCtxt = pCtxt;
}

void CIPLRuntimeWindow::paintGl()
{
    if(mInitialized)
    {
       /**********************************************/
       /*Estabelece contexto atual                   */
       /**********************************************/
       mCtxt->makeCurrent(this);
       /**********************************************/
       /*Atualiza os Devices em Hardware             */
       /**********************************************/
       p3DCenario->UpdateHardwareDC();
       /**********************************************/
       /*Renderiza a Cena Atual                      */
       /**********************************************/
       p3DCenario->Render(TimeElapsed);
       /*************************************************************/
       /*Transfere para a Tela o conteudo dos pixels gerados pela   */
       /*renderização e que estão salvos no FrameBuffer atual OpenGL*/
       /*************************************************************/
       mCtxt->swapBuffers(this);
    }
}

void CIPLRuntimeWindow::resizeGl()
{
    /**********************************************/
    /*Seta o contexto OpenGL que a plataforma     */
    /*Conseguiu criar, como contexto atual        */
    /**********************************************/
    mCtxt->makeCurrent(this);

    /*******************************************************/
    /*Informa a nova dimensão da tela para o componente 3D */
    /*poder calcular novamente as dimensoes e configuracoes*/
    /*de perspectiva necessarias para o desenho dos objetos*/
    /*******************************************************/
    if(mInitialized)
    {
       if(!p3DCenario->Resize(width(), height()))
       {
           QMessageBox::information(0, "Insane RT Framework",
                                       "Erro ao Dimensionar o Cenario 3D.");
       }
    }
}

void CIPLRuntimeWindow::RenderScene()
{
   TimeElapsed  = elapsedtimer->restart();
   TimeElapsed /= 1000;
   paintGl();
}


void CIPLRuntimeWindow::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
       case Qt::Key_A :{p3DCenario->InputKey(ISM_A_KEY);}break;
       case Qt::Key_B :{p3DCenario->InputKey(ISM_B_KEY);}break;
       case Qt::Key_C :{p3DCenario->InputKey(ISM_C_KEY);}break;
       case Qt::Key_D :{p3DCenario->InputKey(ISM_D_KEY);}break;
       case Qt::Key_E :{p3DCenario->InputKey(ISM_E_KEY);}break;
       case Qt::Key_F :{p3DCenario->InputKey(ISM_F_KEY);}break;
       case Qt::Key_G :{p3DCenario->InputKey(ISM_G_KEY);}break;
       case Qt::Key_H :{p3DCenario->InputKey(ISM_H_KEY);}break;
       case Qt::Key_I :{p3DCenario->InputKey(ISM_I_KEY);}break;
       case Qt::Key_J :{p3DCenario->InputKey(ISM_J_KEY);}break;
       case Qt::Key_K :{p3DCenario->InputKey(ISM_K_KEY);}break;
       case Qt::Key_L :{p3DCenario->InputKey(ISM_L_KEY);}break;
       case Qt::Key_M :{p3DCenario->InputKey(ISM_M_KEY);}break;
       case Qt::Key_N :{p3DCenario->InputKey(ISM_N_KEY);}break;
       case Qt::Key_O :{p3DCenario->InputKey(ISM_O_KEY);}break;
       case Qt::Key_P :{p3DCenario->InputKey(ISM_P_KEY);}break;
       case Qt::Key_Q :{p3DCenario->InputKey(ISM_Q_KEY);}break;
       case Qt::Key_R :{p3DCenario->InputKey(ISM_R_KEY);}break;
       case Qt::Key_S :{p3DCenario->InputKey(ISM_S_KEY);}break;
       case Qt::Key_T :{p3DCenario->InputKey(ISM_T_KEY);}break;
       case Qt::Key_U :{p3DCenario->InputKey(ISM_U_KEY);}break;
       case Qt::Key_V :{p3DCenario->InputKey(ISM_V_KEY);}break;
       case Qt::Key_W :{p3DCenario->InputKey(ISM_W_KEY);}break;
       case Qt::Key_X :{p3DCenario->InputKey(ISM_X_KEY);}break;
       case Qt::Key_Y :{p3DCenario->InputKey(ISM_Y_KEY);}break;
       case Qt::Key_Z :{p3DCenario->InputKey(ISM_Z_KEY);}break;
       case Qt::Key_Escape:
       {
          //bRodando = false;
          p3DCenario->InterrompeExecucao();
          exit(0);
       }
   }
}


void CIPLRuntimeWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point,centro;
    centro.rx() = width ()>>1;
    centro.ry() = height()>>1;
    point= event->pos();
    actPosX = (float)(point.y() - oldPosY ) / 3.0f;
    actPosY = (float)(point.x() - oldPosX ) / 3.0f;
    if(mInitialized)
    {
       if(mouseBtnPress)
       {
          p3DCenario->MapeiaMouse(actPosX,actPosY);
       }
    }
    oldPosX= point.x();
    oldPosY= point.y();
}

void CIPLRuntimeWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint point,centro;
    point = event->pos();
    //centro.rx() = width() / 2;
    //centro.ry() = height()/ 2;

    p3DCenario->Seleciona(point.x(),point.y());

    //mCursor.setPos(centro);
    //oldPosX = centro.x();
    //oldPosY = centro.y();

    oldPosX = point.x();
    oldPosY = point.y();

    mouseBtnPress = true;
}
void CIPLRuntimeWindow::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point;

    point= event->pos();

    oldPosX= point.x();
    oldPosY= point.y();

    mouseBtnPress = false;
}


