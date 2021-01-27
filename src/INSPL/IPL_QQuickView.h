#ifndef CIPLQQUICKWINDOW_H
#define CIPLQQUICKWINDOW_H

#include "IPL_GlobalDef.h"
#include <QQuickView>
#include <QQuickWidget>

class CIPLQQuickView : public QQuickView
{
    Q_OBJECT

public:
     CIPLQQuickView();
    ~CIPLQQuickView();

    void initializeGl();
    void atribuiCenario(CISMCenario *pScn);
    void atribuiContexto(QOpenGLContext *pCtxt);

protected slots:
    void resizeGl();
    void paintGl();
    void updateScene();
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *);


private:

    CISMCenario    *p3DCenario;//ponteiro para o cenario
    QOpenGLContext *mCtxt;     //ponteiro para o contexto

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

    QQuickWidget *m_quickWidget;

};

#endif // CIPLQQUICKWINDOW_H
