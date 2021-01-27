#ifndef CIPLEDITORWINDOW_H
#define CIPLEDITORWINDOW_H

#include "IPL_GlobalDef.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
class QPushButton;
QT_END_NAMESPACE

class CIPLEditorGLWidget;
class CIPLEditorMainWindow;
class CIPLOpenGLWindow;

class CIPLEditorWindow : public QWidget
{
    Q_OBJECT
public:
    CIPLEditorWindow(CIPLEditorMainWindow *mw);

    void                 atribuiCenario(CISMCenario *pScn);
    QGLContext*          PegaContexto  (                 );
    CIPLEditorGLWidget*  PegaWidget    (                 );

protected:
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

private:
    CIPLEditorGLWidget     *glWidget;
    CIPLEditorMainWindow   *mainWindow;
};

#endif // CIPLWINDOW_H
