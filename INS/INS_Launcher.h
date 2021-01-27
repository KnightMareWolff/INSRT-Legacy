#ifndef CINSLAUNCHER_H
#define CINSLAUNCHER_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QListWidget;
class QListWidgetItem;
class QStackedWidget;
QT_END_NAMESPACE

class CINSLauncher : public QDialog
{
    Q_OBJECT

public:
    CINSLauncher();

    int mModoExecucao;
    int mProjetoRuntime;

public slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
    void aplicarSelecao();

private:
    void createIcons();

    QListWidget    *WidgetModosExecucao;
    QStackedWidget *WidgetPaginas;
};

#endif // CINSLauncher_H
