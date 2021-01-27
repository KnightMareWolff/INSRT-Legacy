#ifndef CIPLEDITORMATERIALPREVIEW_H
#define CIPLEDITORMATERIALPREVIEW_H

#include "IPL_GlobalDef.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)
QT_FORWARD_DECLARE_CLASS(QOpenGLTexture)

class CIPLEditorMaterialPreview : public QGLWidget, QOpenGLFunctions
{

    Q_OBJECT

public:
     explicit CIPLEditorMaterialPreview(QWidget *parent = 0);
    ~CIPLEditorMaterialPreview();

    void rotateBy     (int xAngle, int yAngle, int zAngle);
    void setClearColor(const QColor &color);

signals:
    void clicked();

protected:
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    void makeObject();

    QColor clearColor;
    QPoint lastPos;
    int xRot;
    int yRot;
    int zRot;
    QOpenGLTexture       *textures[6];
    QOpenGLShaderProgram *program;
    QOpenGLBuffer         vbo;
};

#endif // CIPLEDITORMATERIALPREVIEW_H
