/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef SCR_RUNTIMEWINDOW_H
#define SCR_RUNTIMEWINDOW_H

#include <QWindow>
#include "IPL_GlobalDef.h"

class CIPLRuntimeWindow : public QOpenGLWindow
{
    Q_OBJECT
public:
     CIPLRuntimeWindow();
    ~CIPLRuntimeWindow();

    void initializeGl();
    void atribuiCenario(CISMCenario *pScn);
    void atribuiContexto(QOpenGLContext *pCtxt);

protected slots:
    void resizeGl();
    void paintGl();
    void RenderScene();
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *);

private:

    CISMCenario    *p3DCenario;//ponteiro para o cenario
    QOpenGLContext *mCtxt;     //ponteiro para o contexto

    QTimer        *timer;
    QElapsedTimer *elapsedtimer;
    float         TimeElapsed;
    float         oldPosX,
                  oldPosY;
    float         actPosX,
                  actPosY;
    bool          mouseBtnPress;
    bool          mInitialized;
    QCursor       mCursor;
    int           vMinor,
                  vMajor;

};

#endif // SCR_OPENGLWINDOW_H
