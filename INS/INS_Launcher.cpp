#include "INS_Launcher.h"
#include "INS_LauncherPages.h"
#include "IUT_GerenciadorPath.h"
#include <QtWidgets>



CINSLauncher::CINSLauncher()
{
    //Inicializa o Modo e Runtime Default
    mModoExecucao  =0;
    mProjetoRuntime=0;

    WidgetModosExecucao = new QListWidget;
    WidgetModosExecucao->setViewMode(QListView::IconMode);
    WidgetModosExecucao->setIconSize(QSize(200, 100));
    WidgetModosExecucao->setMovement(QListView::Static);
    WidgetModosExecucao->setMaximumWidth(210);
    WidgetModosExecucao->setSpacing(5);

    WidgetPaginas = new QStackedWidget;
    WidgetPaginas->addWidget(new CINSLauncherEditor);
    WidgetPaginas->addWidget(new CINSLauncherRuntime);
    WidgetPaginas->addWidget(new CINSLauncherConfiguration);

    QPushButton *aplicar = new QPushButton(tr("Aplicar"));

    createIcons();
    WidgetModosExecucao->setCurrentRow(0);

    connect(aplicar, SIGNAL(clicked()), this, SLOT(aplicarSelecao()));

    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(WidgetModosExecucao);
    horizontalLayout->addWidget(WidgetPaginas, 1);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(aplicar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(horizontalLayout);
    mainLayout->addStretch(1);
    mainLayout->addSpacing(12);
    mainLayout->addLayout(buttonsLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Insane RT Launcher"));
    setWindowIcon(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/insicon.png"));
}

void CINSLauncher::createIcons()
{
    QListWidgetItem *configButton = new QListWidgetItem(WidgetModosExecucao);
    configButton->setIcon(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/LevelEditor.png"));
    configButton->setText(tr("Insane Level Editor"));
    configButton->setTextAlignment(Qt::AlignHCenter);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(WidgetModosExecucao);
    updateButton->setIcon(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/Runtime.png"));
    updateButton->setText(tr("Simulação Runtime"));
    updateButton->setTextAlignment(Qt::AlignHCenter);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(WidgetModosExecucao);
    queryButton->setIcon(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/Setup.png"));
    queryButton->setText(tr("Configuração"));
    queryButton->setTextAlignment(Qt::AlignHCenter);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(WidgetModosExecucao,
            SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),
            this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}

void CINSLauncher::changePage(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (!current)
        current = previous;

    WidgetPaginas->setCurrentIndex(WidgetModosExecucao->row(current));
}

void CINSLauncher::aplicarSelecao()
{
    mModoExecucao  = WidgetModosExecucao->currentRow();
    if(mModoExecucao==1)
    {
       CINSLauncherRuntime *Runtime;
       Runtime = (CINSLauncherRuntime *)WidgetPaginas->currentWidget();
       mProjetoRuntime= Runtime->PegaProjetoSelecionado();
    }

    if(mModoExecucao==0 || mModoExecucao==1)
    {
        close();
    }
}
