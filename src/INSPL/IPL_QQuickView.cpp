#include "IPL_QQuickView.h"


CIPLQQuickView::CIPLQQuickView()
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
    /*Inicialização do Quick Widget                */
    /***********************************************/
    //QUrl source("qrc:/world/Gui/rotatingsquare.qml");
    //setSource(source);
    //setOpacity(0.7);
    setClearBeforeRendering(false);
    m_quickWidget = new QQuickWidget;

    /***********************************************/
    /*Conecta os Slots de Janela(Ver referencias Qt*/
    /***********************************************/
    connect(this, SIGNAL(widthChanged(int)), this, SLOT(resizeGl()));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGl()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateScene()));
    timer->start(0);

    mouseBtnPress=false;
}

CIPLQQuickView::~CIPLQQuickView()
{
    delete m_quickWidget;
}

void CIPLQQuickView::initializeGl()
{
    mInitialized    =true;
}

void CIPLQQuickView::atribuiCenario(CISMCenario *pScn)
{
    p3DCenario = pScn;
}

void CIPLQQuickView::atribuiContexto(QOpenGLContext *pCtxt)
{
    mCtxt = pCtxt;
}

void CIPLQQuickView::paintGl()
{
    mCtxt->makeCurrent(this);
    /**********************************************/
    /*Renderiza a Cena Atual                      */
    /**********************************************/
    if(mInitialized)
    {
       p3DCenario->Render();
    }
    /*************************************************************/
    /*Transfere para a Tela o conteudo dos pixels gerados pela   */
    /*renderização e que estão salvos no FrameBuffer atual OpenGL*/
    /*************************************************************/
    mCtxt->swapBuffers(this);
}

void CIPLQQuickView::resizeGl()
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

void CIPLQQuickView::updateScene()
{
   paintGl();
}


void CIPLQQuickView::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
      case Qt::Key_W :
      {
         p3DCenario->MoverCamera(ISM_INPUT_MOVE_FOWARD);
      }break;
      case Qt::Key_S :
      {
         p3DCenario->MoverCamera(ISM_INPUT_MOVE_BACKWARD);
      }break;
      case Qt::Key_A :
      {
         p3DCenario->MoverCamera(ISM_INPUT_MOVE_STRAFELFT);
      }break;
      case Qt::Key_D :
      {
         p3DCenario->MoverCamera(ISM_INPUT_MOVE_STRAFERGT);
      }break;
      case Qt::Key_P :
      {
         p3DCenario->MoverCamera(ISM_INPUT_PLAY_SOUND);
      }break;
      case Qt::Key_M :
      {
         if(!m_quickWidget->isVisible())
         {
            m_quickWidget->show();
         }
      }break;
      case Qt::Key_Escape:
      {
        //bRodando = false;
        close();
      }
   }
}


void CIPLQQuickView::mouseMoveEvent(QMouseEvent *event)
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

void CIPLQQuickView::mousePressEvent(QMouseEvent *event)
{
    QPoint point,centro;
    point = event->pos();
    centro.rx() = width() / 2;
    centro.ry() = height()/ 2;
    mCursor.setPos(centro);
    oldPosX = centro.x();
    oldPosY = centro.y();
    mouseBtnPress = true;
}
void CIPLQQuickView::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point;

    point= event->pos();

    oldPosX= point.x();
    oldPosY= point.y();

    mouseBtnPress = false;
}
