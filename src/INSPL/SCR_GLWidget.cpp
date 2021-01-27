#include "SCR_GLWidget.h"

CISMCenario *pCenario;

CSCRGLWidget::CSCRGLWidget(QWidget *parent, QGLWidget *shareWidget)
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
}

CSCRGLWidget::~CSCRGLWidget()
{

}

void CSCRGLWidget::initializeGL()
{
    pCenario = new CISMCenario;
}

void CSCRGLWidget::resizeGL(int w, int h)
{
    if(!pCenario->Resize(w,h))
    {
        //retorno de erro
    }
}

void CSCRGLWidget::paintGL()
{
    makeCurrent();
    pCenario->Render();
}

void CSCRGLWidget::keyPressEvent(QKeyEvent *event)
{
   Q_UNUSED(event);
}
