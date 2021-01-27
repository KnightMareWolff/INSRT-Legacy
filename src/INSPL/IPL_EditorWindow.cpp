#include "IPL_EditorGLWidget.h"
#include "IPL_EditorWindow.h"
#include "IPL_EditorMainWindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>

CIPLEditorWindow::CIPLEditorWindow(CIPLEditorMainWindow *mw)
    :mainWindow(mw)
{
    glWidget       = new CIPLEditorGLWidget(this);
    //connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
    //connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
    //connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
    //connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
    //connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
    //connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

    QHBoxLayout *LayoutHorizontal = new QHBoxLayout;
    LayoutHorizontal->addWidget(glWidget);

    QVBoxLayout *LayoutPrincipal   = new QVBoxLayout;
    LayoutPrincipal->addLayout(LayoutHorizontal);
    setLayout(LayoutPrincipal);

    setWindowTitle(tr("Insane RT Level Editor"));
}

void CIPLEditorWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        glWidget->keyPressEvent(e);
}

void CIPLEditorWindow::atribuiCenario(CISMCenario *pScn)
{
    glWidget->pCenario = pScn;
}

QGLContext* CIPLEditorWindow::PegaContexto()
{
    return glWidget->context();
}

CIPLEditorGLWidget* CIPLEditorWindow::PegaWidget()
{
    return glWidget;
}
