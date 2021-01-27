#ifndef CIPLEDITORTABWIDGET_H
#define CIPLEDITORTABWIDGET_H

#include <QWidget>
#include <QTabWidget>

class CIPLEditorTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CIPLEditorTabWidget(QWidget *parent = 0);

    QTabWidget *tabWidget;
};

#endif // CIPLEDITORTABWIDGET_H
