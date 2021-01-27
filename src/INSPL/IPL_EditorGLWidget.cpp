#include "IPL_EditorGLWidget.h"


CIPLEditorGLWidget::CIPLEditorGLWidget(QWidget *parent, QGLWidget *shareWidget)
    : QGLWidget(parent, shareWidget)
{
    /***********************************************/
    /*Seta este widget com o contexto OpenGL atual */
    /***********************************************/
    makeCurrent();

    /***********************************************/
    /*                                             */
    /***********************************************/
    timerId = startTimer(20);

    /***********************************************/
    /*Configura o nome da janela                   */
    /***********************************************/
    setWindowTitle(tr("Insane RT Framework"));


    pCenario = NULL;
}

CIPLEditorGLWidget::~CIPLEditorGLWidget()
{

}

void CIPLEditorGLWidget::initializeGL()
{

}

void CIPLEditorGLWidget::resizeGL(int w, int h)
{
    /*******************************************************/
    /*Informa a nova dimensão da tela para o componente 3D */
    /*poder calcular novamente as dimensoes e configuracoes*/
    /*de perspectiva necessarias para o desenho dos objetos*/
    /*******************************************************/
    if(mInitialized)
    {
       if(!pCenario->Resize(w, h))
       {
           QMessageBox::information(0, "Insane RT Framework",
                                       "Erro ao Dimensionar o Cenario 3D.");
       }
    }
}

void CIPLEditorGLWidget::paintGL()
{
    makeCurrent();
    /**********************************************/
    /*Renderiza a Cena Atual                      */
    /**********************************************/
    if(mInitialized)
    {
       pCenario->Render();
    }
}

void CIPLEditorGLWidget::keyPressEvent(QKeyEvent *event)
{
    setFocus();
    switch(event->key())
    {
       case Qt::Key_A :{pCenario->InputKey(ISM_A_KEY);}break;
       case Qt::Key_B :{pCenario->InputKey(ISM_B_KEY);}break;
       case Qt::Key_C :{pCenario->InputKey(ISM_C_KEY);}break;
       case Qt::Key_D :{pCenario->InputKey(ISM_D_KEY);}break;
       case Qt::Key_E :{pCenario->InputKey(ISM_E_KEY);}break;
       case Qt::Key_F :{pCenario->InputKey(ISM_F_KEY);}break;
       case Qt::Key_G :{pCenario->InputKey(ISM_G_KEY);}break;
       case Qt::Key_H :{pCenario->InputKey(ISM_H_KEY);}break;
       case Qt::Key_I :{pCenario->InputKey(ISM_I_KEY);}break;
       case Qt::Key_J :{pCenario->InputKey(ISM_J_KEY);}break;
       case Qt::Key_K :{pCenario->InputKey(ISM_K_KEY);}break;
       case Qt::Key_L :{pCenario->InputKey(ISM_L_KEY);}break;
       case Qt::Key_M :{pCenario->InputKey(ISM_M_KEY);}break;
       case Qt::Key_N :{pCenario->InputKey(ISM_N_KEY);}break;
       case Qt::Key_O :{pCenario->InputKey(ISM_O_KEY);}break;
       case Qt::Key_P :{pCenario->InputKey(ISM_P_KEY);}break;
       case Qt::Key_Q :{pCenario->InputKey(ISM_Q_KEY);}break;
       case Qt::Key_R :{pCenario->InputKey(ISM_R_KEY);}break;
       case Qt::Key_S :{pCenario->InputKey(ISM_S_KEY);}break;
       case Qt::Key_T :{pCenario->InputKey(ISM_T_KEY);}break;
       case Qt::Key_U :{pCenario->InputKey(ISM_U_KEY);}break;
       case Qt::Key_V :{pCenario->InputKey(ISM_V_KEY);}break;
       case Qt::Key_W :{pCenario->InputKey(ISM_W_KEY);}break;
       case Qt::Key_X :{pCenario->InputKey(ISM_X_KEY);}break;
       case Qt::Key_Y :{pCenario->InputKey(ISM_Y_KEY);}break;
       case Qt::Key_Z :{pCenario->InputKey(ISM_Z_KEY);}break;
       case Qt::Key_Escape:
       {
       //bRodando = false;
       //exit(0);
       }
    }
}

void CIPLEditorGLWidget::mouseMoveEvent(QMouseEvent *event)
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
          pCenario->MapeiaMouse(actPosX,actPosY);
       }
    }

    oldPosX= point.x();
    oldPosY= point.y();

}

void CIPLEditorGLWidget::mousePressEvent(QMouseEvent *event)
{
    QPoint point,centro;

    point = event->pos();

    this->setFocus();
    //centro.rx() = width() / 2;
    //centro.ry() = height()/ 2;

    //mCursor.setPos(centro);

    //oldPosX = centro.x();
    //oldPosY = centro.y();
    oldPosX = point.x();
    oldPosY = point.y();

    mouseBtnPress = true;
}

void CIPLEditorGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point;

    point= event->pos();

    oldPosX= point.x();
    oldPosY= point.y();

    mouseBtnPress = false;
}

void CIPLEditorGLWidget::atribuiCenario(CISMCenario *pScn)
{
    pCenario      = pScn;
    mInitialized  = true;
}
