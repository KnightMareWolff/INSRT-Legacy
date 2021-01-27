#ifndef CIPLEDITORGLWIDGET_H
#define CIPLEDITORGLWIDGET_H

#include "IPL_GlobalDef.h"
#include <QWidget>


class CIPLEditorGLWidget : public QGLWidget
{

    Q_OBJECT

public:
     CIPLEditorGLWidget(QWidget *parent = 0, QGLWidget *shareWidget = 0);
    ~CIPLEditorGLWidget();
public:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *) { update(); }
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void atribuiCenario (CISMCenario *pScn);

public:
    CISMCenario    *pCenario;//ponteiro para o cenario
    int           timerId;
    float         oldPosX,
                  oldPosY;
    float         actPosX,
                  actPosY;
    bool          mouseBtnPress;
    bool          mInitialized;
    QCursor       mCursor;
    int           vMinor,
                  vMajor;
public slots:


signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
};

#endif // CIPLGLWIDGET_H
