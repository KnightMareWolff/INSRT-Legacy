#ifndef CINSLAUNCHERPAGES_H
#define CINSLAUNCHERPAGES_H

#include <QWidget>
#include <QtWidgets>

class CINSLauncherEditor : public QWidget
{
    Q_OBJECT

public:
    CINSLauncherEditor(QWidget *parent = 0);
};

class CINSLauncherRuntime : public QWidget
{

    Q_OBJECT

public:
    CINSLauncherRuntime(QWidget *parent = 0);
    int PegaProjetoSelecionado();

public slots:
    void CarregaPaginaIndex(int pagina);

private:
    QTextEdit *TextoImagem;
    QImage     ImagemTexto;
    QString    arquivo;
    QLabel    *LabelProjeto ;
    QComboBox *ComboProjeto ;
    QGroupBox *GrupoConfiguracao;
};

class CINSLauncherConfiguration : public QWidget
{
    Q_OBJECT

public:
    CINSLauncherConfiguration(QWidget *parent = 0);
};

#endif // CINSLAUNCHERPAGES_H
