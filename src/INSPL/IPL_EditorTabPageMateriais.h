#ifndef CIPLEDITORTABPAGEMATERIAIS_H
#define CIPLEDITORTABPAGEMATERIAIS_H
#include "IPL_GlobalDef.h"
#include "IPL_EditorMaterialPreview.h"
#include <QWidget>
#include <QtWidgets>

class CIPLEditorTabPageMateriais : public QWidget
{
    Q_OBJECT
public:
    explicit CIPLEditorTabPageMateriais(QWidget *parent = 0);

    CIPLEditorMaterialPreview *MaterialWidget;
    QColor Ambiente;
    QColor Difusa;
    QColor Specular;

private slots:
    void rotateOneStep();

};

#endif // CIPLEDITORTABPAGEMATERIAIS_H
