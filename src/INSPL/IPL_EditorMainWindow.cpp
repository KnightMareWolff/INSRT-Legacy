#include "IPL_EditorMainWindow.h"
#include "IPL_EditorWindow.h"
#include "IPL_EditorMaterialPreview.h"
#include "IPL_EditorTabPageMateriais.h"
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>

CIPLEditorMainWindow::CIPLEditorMainWindow()
{
    CriaAcoes();
    CriaMenus();
    CriaBarras();
    CriaBarraStatus();
    CriaDocking();

    setMenuBar(mBarraMenu);

    if (!centralWidget())
    {
        setCentralWidget((QWidget *)new CIPLEditorWindow(this));
    }

    this->setWindowIcon(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/insicon.png"));
}

void CIPLEditorMainWindow::CriaAcoes()
{

    mAcaoNovo = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/new.png"), tr("&Novo"), this);
    mAcaoNovo->setShortcuts(QKeySequence::New);
    mAcaoNovo->setStatusTip(tr("Cria Novo Cenário"));
    //connect(mAcaoNovo, SIGNAL(triggered()), this, SLOT(newFile()));

    mAcaoAbrir = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/open.png"), tr("&Abrir"), this);
    mAcaoAbrir->setShortcuts(QKeySequence::Open);
    mAcaoAbrir->setStatusTip(tr("Carrega Novo Cenário"));
    //connect(mAcaoNovo, SIGNAL(triggered()), this, SLOT(newFile()));


    mAcaoSalvar = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/save.png"), tr("&Salvar"), this);
    mAcaoSalvar->setShortcuts(QKeySequence::Save);
    mAcaoSalvar->setStatusTip(tr("Salva Cenário Atual"));
    //connect(mAcaoNovo, SIGNAL(triggered()), this, SLOT(newFile()));


    mAcaoSalvarComo = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/save.png"), tr("&Salvar Como..."), this);
    mAcaoSalvarComo->setShortcuts(QKeySequence::SaveAs);
    mAcaoSalvarComo->setStatusTip(tr("Salva Cenário Atual Com Outro Nome"));
    //connect(mAcaoNovo, SIGNAL(triggered()), this, SLOT(newFile()));


    mAcaoSair = new QAction(tr("S&air"), this);
    mAcaoSair->setShortcuts(QKeySequence::Quit);
    mAcaoSair->setStatusTip(tr("Fechar a Aplicação"));
    //connect(mAcaoSair, SIGNAL(triggered()), this, SLOT(close()));


    mAcaoCortar = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/cut.png"), tr("&Cortar"), this);
    mAcaoCortar->setShortcuts(QKeySequence::Cut);
    mAcaoCortar->setStatusTip(tr("Recortar Objeto"));
    //connect(mAcaoCortar, SIGNAL(triggered()), this, SLOT(newFile()));


    mAcaoCopiar = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/copy.png"), tr("Co&piar"), this);
    mAcaoCopiar->setShortcuts(QKeySequence::Cut);
    mAcaoCopiar->setStatusTip(tr("Copiar Objeto"));
    //connect(mAcaoCortar, SIGNAL(triggered()), this, SLOT(newFile()));


    mAcaoColar = new QAction(QIcon(CIUTGerenciadorPath::IUT_PathWorld + "Icones/paste.png"), tr("Co&lar"), this);
    mAcaoColar->setShortcuts(QKeySequence::Paste);
    mAcaoColar->setStatusTip(tr("Colar Objeto"));
    //connect(mAcaoCortar, SIGNAL(triggered()), this, SLOT(newFile()));


    mAcaoSobre = new QAction(tr("&Sobre..."), this);
    mAcaoSobre->setStatusTip(tr("Exibe Informações sobre a Ferramenta"));
    //connect(mAcaoSobre, SIGNAL(triggered()), this, SLOT(about()));
}
void CIPLEditorMainWindow::CriaMenus()
{
    //Instancia Barra de Menu
    mBarraMenu     = new QMenuBar;

    //Cria o Menu Arquivo e inclui as ações
    mMenuArquivo   = mBarraMenu->addMenu(tr("&Arquivo"));
    mMenuArquivo->addAction(mAcaoNovo);
    mMenuArquivo->addAction(mAcaoAbrir);
    mMenuArquivo->addAction(mAcaoSalvar);
    mMenuArquivo->addAction(mAcaoSalvarComo);
    mMenuArquivo->addSeparator();
    mMenuArquivo->addAction(mAcaoSair);

    //Cria o Menu Editar e inclui as ações
    mMenuEditar    = mBarraMenu->addMenu(tr("&Editar"));
    mMenuEditar->addAction(mAcaoCortar);
    mMenuEditar->addAction(mAcaoCopiar);
    mMenuEditar->addAction(mAcaoColar);

    //Cria o Menu Sobre e inclui as ações
    mMenuSobre     = mBarraMenu->addMenu(tr("&Sobre"));
    mMenuSobre->addAction(mAcaoSobre);
}
void CIPLEditorMainWindow::CriaBarras()
{
    mToolBarArquivo = addToolBar(tr("Arquivo"));
    mToolBarArquivo->addAction(mAcaoNovo);
    mToolBarArquivo->addAction(mAcaoAbrir);
    mToolBarArquivo->addAction(mAcaoSalvar);
    mToolBarArquivo->setIconSize(QSize(50,50));

    mToolBarEditar = addToolBar(tr("Editar"));
    mToolBarEditar->addAction(mAcaoCortar);
    mToolBarEditar->addAction(mAcaoCopiar);
    mToolBarEditar->addAction(mAcaoColar);
    mToolBarEditar->setIconSize(QSize(50,50));
}
void CIPLEditorMainWindow::CriaBarraStatus()
{
   statusBar()->showMessage(tr("Pronto para Uso!"));
}

void CIPLEditorMainWindow::CriaDocking()
{
    QDockWidget *dock = new QDockWidget(tr("Ferramentas"), this);

    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    tabFerramentas = new CIPLEditorTabWidget(dock);

    dock->setWidget(tabFerramentas);

    addDockWidget(Qt::LeftDockWidgetArea, dock);
}

void CIPLEditorMainWindow::atribuiCenario(CISMCenario *pScn)
{
    CIPLEditorWindow *central = (CIPLEditorWindow *)this->centralWidget();
    central->atribuiCenario(pScn);
}


QGLContext * CIPLEditorMainWindow::PegaContexto()
{
    CIPLEditorWindow *central = (CIPLEditorWindow *)this->centralWidget();
    return central->PegaContexto();
}

