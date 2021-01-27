#include "IPL_EditorTabPageMateriais.h"
#include <QVBoxLayout>
#include <QLabel>

CIPLEditorTabPageMateriais::CIPLEditorTabPageMateriais(QWidget *parent)
    : QWidget(parent)
{

    Ambiente.setRed  (0);
    Ambiente.setGreen(255);
    Ambiente.setBlue (0);


    Difusa.setRed  (255);
    Difusa.setGreen(0);
    Difusa.setBlue (0);


    Specular.setRed  (0);
    Specular.setGreen(0);
    Specular.setBlue (255);


    //Grupo de Materiais
    QGroupBox *GrupoMateriais = new QGroupBox(tr("Materiais:"));

    QLabel    *LabelComboMateriais = new QLabel(tr("Material:"));
    QComboBox *ComboMateriais      = new QComboBox;
    ComboMateriais->addItem(tr("Latão"));
    ComboMateriais->addItem(tr("Bronze"));
    ComboMateriais->addItem(tr("Cromado"));
    ComboMateriais->addItem(tr("Ouro"));
    ComboMateriais->addItem(tr("Esmeralda"));
    ComboMateriais->addItem(tr("Prata"));
    ComboMateriais->addItem(tr("Plastico"));
    ComboMateriais->addItem(tr("Borracha"));
    ComboMateriais->addItem(tr("Madeira"));

    ComboMateriais->setCurrentIndex(0);

    QPushButton *AplicarMaterialBtn = new QPushButton(tr("Aplicar"));
    QPushButton *NovoMaterialBtn    = new QPushButton(tr("Novo"));

    QPushButton *MaterialAmbBtn     = new QPushButton(tr(""));
    QPushButton *MaterialSpecBtn    = new QPushButton(tr(""));
    QPushButton *MaterialDifBtn     = new QPushButton(tr(""));

    MaterialAmbBtn->setText(QString("%1 ; %2 ; %3").arg(Ambiente.red  ())
                                                   .arg(Ambiente.green())
                                                   .arg(Ambiente.blue ()));
    MaterialAmbBtn->setPalette(QPalette(Ambiente));
    MaterialAmbBtn->setAutoFillBackground(true);

    MaterialSpecBtn->setText(QString("%1 ; %2 ; %3").arg(Specular.red  ())
                                                    .arg(Specular.green())
                                                    .arg(Specular.blue ()));
    MaterialSpecBtn->setPalette(QPalette(Specular));
    MaterialSpecBtn->setAutoFillBackground(true);

    MaterialDifBtn->setText(QString("%1 ; %2 ; %3").arg(Difusa.red  ())
                                                   .arg(Difusa.green())
                                                   .arg(Difusa.blue ()));
    MaterialDifBtn->setPalette(QPalette(Difusa));
    MaterialDifBtn->setAutoFillBackground(true);

    MaterialWidget = new CIPLEditorMaterialPreview(this);
    MaterialWidget->setMinimumSize(150,150);
    MaterialWidget->setMaximumSize(150,150);

    //Linha Material
    QHBoxLayout *LayoutLinhaMaterial = new QHBoxLayout;
    LayoutLinhaMaterial->addWidget(LabelComboMateriais);
    LayoutLinhaMaterial->addWidget(ComboMateriais);

    QVBoxLayout *LayoutMateriaisVertical = new QVBoxLayout;
    LayoutMateriaisVertical->addLayout(LayoutLinhaMaterial);
    LayoutMateriaisVertical->addWidget(AplicarMaterialBtn);
    LayoutMateriaisVertical->addWidget(NovoMaterialBtn);

    QHBoxLayout *LayoutMateriaisHorizontal = new QHBoxLayout;
    LayoutMateriaisHorizontal->addWidget(MaterialWidget);
    LayoutMateriaisHorizontal->addLayout(LayoutMateriaisVertical);

    //Adiciona Linha Botoes cor
    QHBoxLayout *LayoutLinhaCores = new QHBoxLayout;
    LayoutLinhaCores->addWidget(MaterialAmbBtn);
    LayoutLinhaCores->addWidget(MaterialSpecBtn);
    LayoutLinhaCores->addWidget(MaterialDifBtn);

    //Junta preview com botoes cores
    QVBoxLayout *LayoutCoresVertical = new QVBoxLayout;
    LayoutCoresVertical->addLayout(LayoutMateriaisHorizontal);
    LayoutCoresVertical->addLayout(LayoutLinhaCores);

    GrupoMateriais->setLayout(LayoutCoresVertical);

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rotateOneStep()));
    timer->start(20);

    //Grupo de Texturas
    QGroupBox *GrupoTexturas = new QGroupBox(tr("Texturas && Layers:"));

    QLabel      *LabelTextBase    = new QLabel("Base           :");
    QLabel      *LabelTextDetalhe = new QLabel("Detalhe      :");
    QLabel      *LabelTextNormal  = new QLabel("NormalMap :");
    QLabel      *LabelTextCube    = new QLabel("CubeMap    :");
    QLineEdit   *LineEditBase     = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditDetalhe  = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditNormal   = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditCube     = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);

    QPushButton *AtualizaTextBtn   = new QPushButton(tr("Atualizar Texturas"));

    //Configura Linha Base
    QHBoxLayout *LinhaBase = new QHBoxLayout;
    LinhaBase->addWidget(LabelTextBase);
    LinhaBase->addWidget(LineEditBase);

    //Configura Linha Detalhe
    QHBoxLayout *LinhaDetalhe = new QHBoxLayout;
    LinhaDetalhe->addWidget(LabelTextDetalhe);
    LinhaDetalhe->addWidget(LineEditDetalhe);

    //Configura Linha Normal
    QHBoxLayout *LinhaNormal = new QHBoxLayout;
    LinhaNormal->addWidget(LabelTextNormal);
    LinhaNormal->addWidget(LineEditNormal);

    //Configura Linha CubeMap
    QHBoxLayout *LinhaCube = new QHBoxLayout;
    LinhaCube->addWidget(LabelTextCube);
    LinhaCube->addWidget(LineEditCube);

    //Adiciona as duas linhas no Layout Vertical
    QVBoxLayout *LayoutTextVertical = new QVBoxLayout;
    LayoutTextVertical->addLayout(LinhaBase);
    LayoutTextVertical->addLayout(LinhaDetalhe);
    LayoutTextVertical->addLayout(LinhaNormal);
    LayoutTextVertical->addLayout(LinhaCube);
    LayoutTextVertical->addWidget(AtualizaTextBtn);

    GrupoTexturas->setLayout(LayoutTextVertical);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoMateriais);
    LayoutPrincipal->addWidget(GrupoTexturas);
    LayoutPrincipal->addStretch(1);
    setLayout(LayoutPrincipal);

}

void CIPLEditorTabPageMateriais::rotateOneStep()
{
   MaterialWidget->rotateBy(+2 * 16, +2 * 16, -1 * 16);
}
