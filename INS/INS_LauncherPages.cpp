#include "INS_LauncherPages.h"
#include "IUT_GerenciadorPath.h"

CINSLauncherEditor::CINSLauncherEditor(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox *configGroup = new QGroupBox(tr("Sobre o Modo Editor:"));

    QString filename = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/LevelEditor.htm";
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    QString output = out.readAll();

    QTextEdit *TextoImagem = new QTextEdit(output);

    TextoImagem->setFixedSize(600,400);

    QVBoxLayout *configLayout = new QVBoxLayout;
    configLayout->addWidget(TextoImagem);
    configGroup->setLayout(configLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(configGroup);
    mainLayout->addStretch(1);
    setLayout(mainLayout);
}

CINSLauncherConfiguration::CINSLauncherConfiguration(QWidget *parent)
    : QWidget(parent)
{
    QGroupBox   *GrupoAtualizacao = new QGroupBox(tr("Paths de Sistema:"));
    QLabel      *LabelPathApp     = new QLabel(tr("Path Instalação:"));
    QLabel      *LabelPathWorld   = new QLabel(tr("Path Resources:"));
    QLineEdit   *LineEditApp      = new QLineEdit(CIUTGerenciadorPath::IUT_PathApp);
    QLineEdit   *LineEditWorld    = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);

    QPushButton *AtualizaPathsBtn = new QPushButton(tr("Atualizar Paths"));

    QString filename = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Config.htm";
    // read from file
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    QString output = out.readAll();

    QTextEdit *TextoImagem = new QTextEdit(output);

    TextoImagem->setFixedSize(600,400);


    //Configura Linha AppPath
    QHBoxLayout *LinhaPathApp = new QHBoxLayout;
    LinhaPathApp->addWidget(LabelPathApp);
    LinhaPathApp->addWidget(LineEditApp);

    //Configura Linha AppWorld
    QHBoxLayout *LinhaPathWorld = new QHBoxLayout;
    LinhaPathWorld->addWidget(LabelPathWorld);
    LinhaPathWorld->addWidget(LineEditWorld);

    //Adiciona as duas linhas no Layout Vertical
    QVBoxLayout *LayoutVertical = new QVBoxLayout;
    LayoutVertical->addLayout(LinhaPathApp);
    LayoutVertical->addLayout(LinhaPathWorld);

    GrupoAtualizacao->setLayout(LayoutVertical);

    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoAtualizacao);
    LayoutPrincipal->addSpacing(12);
    LayoutPrincipal->addWidget(AtualizaPathsBtn);
    LayoutPrincipal->addStretch(1);
    LayoutPrincipal->addWidget(TextoImagem);
    setLayout(LayoutPrincipal);
}

CINSLauncherRuntime::CINSLauncherRuntime(QWidget *parent)
    : QWidget(parent)
{
    GrupoConfiguracao = new QGroupBox(tr("Modo de Execução Runtime:"));

    arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/DemoProject.htm";
    //Lê arquivo htm
    QFile file(arquivo);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Não foi possivel abrir arquivo HTM"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    QString     output = out.readAll();

    TextoImagem = new QTextEdit(output);

    TextoImagem->setFixedSize(600,400);

    LabelProjeto = new QLabel(tr("Projeto:"));
    ComboProjeto = new QComboBox;
    ComboProjeto->addItem(tr("Projeto Demonstração"));
    ComboProjeto->addItem(tr("Exemplo 01"));
    ComboProjeto->addItem(tr("Exemplo 02"));
    ComboProjeto->addItem(tr("Exemplo 03"));
    ComboProjeto->addItem(tr("Exemplo 04"));
    ComboProjeto->addItem(tr("Exemplo 05"));
    ComboProjeto->addItem(tr("Exemplo 06"));
    ComboProjeto->addItem(tr("Exemplo 07"));
    ComboProjeto->addItem(tr("Exemplo 08"));
    ComboProjeto->addItem(tr("Exemplo 09"));
    ComboProjeto->addItem(tr("Exemplo 10"));
    ComboProjeto->addItem(tr("Exemplo 11"));

    ComboProjeto->setCurrentIndex(0);

    //Configura Linha ComboBox
    QHBoxLayout *LinhaComboBox = new QHBoxLayout;
    LinhaComboBox->addWidget(LabelProjeto);
    LinhaComboBox->addWidget(ComboProjeto);

    //Adiciona Linha ComboBox na Coluna do Grupo Configuração
    QVBoxLayout *ColunaGrupo   = new QVBoxLayout;
    ColunaGrupo->addLayout(LinhaComboBox);
    GrupoConfiguracao->setLayout(ColunaGrupo);

    //Adiciona na Coluna Principal do Widget o Grupo Configuração e a pagina htm
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoConfiguracao);
    LayoutPrincipal->addWidget(TextoImagem);
    LayoutPrincipal->addStretch(1);
    setLayout(LayoutPrincipal);

    connect(ComboProjeto, SIGNAL(activated(int)), this, SLOT(CarregaPaginaIndex(int)));
}

void CINSLauncherRuntime::CarregaPaginaIndex(int pagina)
{
    //Carrega html de acordo com a combo
    switch(pagina)
    {
       case  0:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/DemoProject.htm";}break;
       case  1:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo01.htm";}break;
       case  2:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo02.htm";}break;
       case  3:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo03.htm";}break;
       case  4:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo04.htm";}break;
       case  5:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo05.htm";}break;
       case  6:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo06.htm";}break;
       case  7:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo07.htm";}break;
       case  8:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo08.htm";}break;
       case  9:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo09.htm";}break;
       case 10:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo10.htm";}break;
       case 11:{arquivo = CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/Exemplo11.htm";}break;
    }

    //Lê arquivo htm
    QFile file(arquivo);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this, tr("Não foi possivel abrir arquivo HTM"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    QString     output = out.readAll();

    TextoImagem->setText(output);

    //Carrega imagem de acordo com a combo
    switch(pagina)
    {
       case  0:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Logo.jpg");}break;
       case  1:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo01.jpg");}break;
       case  2:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo01.jpg");}break;
       case  3:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo03.jpg");}break;
       case  4:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo04.jpg");}break;
       case  5:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo05.jpg");}break;
       case  6:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo06.jpg");}break;
       case  7:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo07-001.jpg");}break;
       case  8:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo08.jpg");}break;
       case  9:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo10.jpg");}break;
       case 10:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo10.jpg");}break;
       case 11:{ImagemTexto = QImage(CIUTGerenciadorPath::IUT_PathApp + "docs/launcher/imagens/Exemplo10.jpg");}break;
    }

    QTextCursor cursor = TextoImagem->textCursor();
    QTextDocument *document = TextoImagem->document();
    document->addResource(QTextDocument::ImageResource, QUrl("image"), ImagemTexto);
    cursor.insertImage("image");

    TextoImagem->setFixedSize(600,400);
}

int CINSLauncherRuntime::PegaProjetoSelecionado()
{
    return ComboProjeto->currentIndex();
}



