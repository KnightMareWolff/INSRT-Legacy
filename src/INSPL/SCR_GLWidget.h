#ifndef SCR_GLWIDGET_H
#define SCR_GLWIDGET_H
#include "globaldef.h"
#include "ISM_Cenario.h"

class CSCRGLWidget : public QGLWidget
{

    Q_OBJECT

public:
     explicit CSCRGLWidget(QWidget *parent = 0, QGLWidget *shareWidget = 0);
    ~CSCRGLWidget();
public:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *) { update(); }
    void mousePressEvent(QMouseEvent *) { killTimer(timerId); }
    void mouseReleaseEvent(QMouseEvent *) { timerId = startTimer(20); }
    void keyPressEvent(QKeyEvent *event);

public:
    int           timerId;
};


#endif // SCR_GLWIDGET_H
