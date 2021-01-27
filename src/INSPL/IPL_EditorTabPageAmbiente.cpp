#include "IPL_EditorTabPageAmbiente.h"
#include "IUT_GerenciadorPath.h"
#include <QVBoxLayout>
#include <QLabel>

CIPLEditorTabPageAmbiente::CIPLEditorTabPageAmbiente(QWidget *parent) : QWidget(parent)
{
    //Grupo de Criação
    QGroupBox *GrupoCaixaAmbiental = new QGroupBox(tr("Caixa Ambiental:"));

    QCheckBox *CheckBoxSkyBox     = new QCheckBox(tr("Sky-Box"));
    QCheckBox *CheckBoxTerreno    = new QCheckBox(tr("Terreno"));
    QCheckBox *CheckBoxPathFinder = new QCheckBox(tr("PathFinder"));

    QPushButton *AddCaixaAmbBtn = new QPushButton(tr("Add"));

    QVBoxLayout *LayoutCaixaAmbVertical = new QVBoxLayout;
    LayoutCaixaAmbVertical->addWidget(CheckBoxSkyBox);
    LayoutCaixaAmbVertical->addWidget(CheckBoxTerreno);
    LayoutCaixaAmbVertical->addWidget(CheckBoxPathFinder);

    QHBoxLayout *LayoutCaixaAmbHorizontal = new QHBoxLayout;
    LayoutCaixaAmbHorizontal->addLayout(LayoutCaixaAmbVertical);
    LayoutCaixaAmbHorizontal->addWidget(AddCaixaAmbBtn);

    GrupoCaixaAmbiental->setLayout(LayoutCaixaAmbHorizontal);

    //Grupo da SkyBox
    QGroupBox *GrupoSkyBox = new QGroupBox(tr("Parâmetros SkyBox:"));

    QLabel      *LabelPathTopo    = new QLabel(tr("Frente:"));
    QLabel      *LabelPathEsq     = new QLabel(tr("Frente:"));
    QLabel      *LabelPathDir     = new QLabel(tr("Frente:"));
    QLabel      *LabelPathFrente  = new QLabel(tr("Frente:"));
    QLabel      *LabelPathAtras   = new QLabel(tr("Frente:"));
    QLabel      *LabelPathBase    = new QLabel(tr("Frente:"));
    QLineEdit   *LineEditTopo     = new QLineEdit(CIUTGerenciadorPath::IUT_PathApp);
    QLineEdit   *LineEditEsq      = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditDir      = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditFrente   = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditAtras    = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);
    QLineEdit   *LineEditBase     = new QLineEdit(CIUTGerenciadorPath::IUT_PathWorld);

    QPushButton *AtualizaSkyBtn   = new QPushButton(tr("Atualizar Paths"));

    //Configura Linha Topo
    QHBoxLayout *LinhaPathTopo = new QHBoxLayout;
    LinhaPathTopo->addWidget(LabelPathTopo);
    LinhaPathTopo->addWidget(LineEditTopo);

    //Configura Linha Esquerda
    QHBoxLayout *LinhaPathEsq = new QHBoxLayout;
    LinhaPathEsq->addWidget(LabelPathEsq);
    LinhaPathEsq->addWidget(LineEditEsq);

    //Configura Linha Direita
    QHBoxLayout *LinhaPathDir = new QHBoxLayout;
    LinhaPathDir->addWidget(LabelPathDir);
    LinhaPathDir->addWidget(LineEditDir);

    //Configura Linha Frente
    QHBoxLayout *LinhaPathFrente = new QHBoxLayout;
    LinhaPathFrente->addWidget(LabelPathFrente);
    LinhaPathFrente->addWidget(LineEditFrente);

    //Configura Linha Atras
    QHBoxLayout *LinhaPathAtras = new QHBoxLayout;
    LinhaPathAtras->addWidget(LabelPathAtras);
    LinhaPathAtras->addWidget(LineEditAtras);

    //Configura Linha Base
    QHBoxLayout *LinhaPathBase = new QHBoxLayout;
    LinhaPathBase->addWidget(LabelPathBase);
    LinhaPathBase->addWidget(LineEditBase);

    //Adiciona as duas linhas no Layout Vertical
    QVBoxLayout *LayoutSkyVertical = new QVBoxLayout;
    LayoutSkyVertical->addLayout(LinhaPathTopo);
    LayoutSkyVertical->addLayout(LinhaPathEsq);
    LayoutSkyVertical->addLayout(LinhaPathDir);
    LayoutSkyVertical->addLayout(LinhaPathFrente);
    LayoutSkyVertical->addLayout(LinhaPathAtras);
    LayoutSkyVertical->addLayout(LinhaPathBase);
    LayoutSkyVertical->addWidget(AtualizaSkyBtn);

    GrupoSkyBox->setLayout(LayoutSkyVertical);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoCaixaAmbiental);
    LayoutPrincipal->addWidget(GrupoSkyBox);
    setLayout(LayoutPrincipal);

}

