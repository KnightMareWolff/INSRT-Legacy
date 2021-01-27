#include "IPL_EditorTabPageObjetos.h"
#include "IPL_EditorMaterialPreview.h"
#include <QVBoxLayout>
#include <QLabel>

CIPLEditorTabPageObjetos::CIPLEditorTabPageObjetos(QWidget *parent)
    : QWidget(parent)
{
    //Grupo de Criação
    QGroupBox *GrupoPrimitivos = new QGroupBox(tr("Primitivos:"));

    QRadioButton *RadioBtnCubo     = new QRadioButton(tr("Cubo"));
    QRadioButton *RadioBtnEsfera   = new QRadioButton(tr("Esfera"));
    QRadioButton *RadioBtnCilindro = new QRadioButton(tr("Cilindro"));

    RadioBtnCubo->setChecked(true);

    QPushButton *AddPrimBtn = new QPushButton(tr("Add"));

    QVBoxLayout *LayoutPrimitivosVertical = new QVBoxLayout;
    LayoutPrimitivosVertical->addWidget(RadioBtnCubo);
    LayoutPrimitivosVertical->addWidget(RadioBtnEsfera);
    LayoutPrimitivosVertical->addWidget(RadioBtnCilindro);

    QHBoxLayout *LayoutPrimitivosHorizontal = new QHBoxLayout;
    LayoutPrimitivosHorizontal->addLayout(LayoutPrimitivosVertical);
    LayoutPrimitivosHorizontal->addWidget(AddPrimBtn);

    GrupoPrimitivos->setLayout(LayoutPrimitivosHorizontal);

    //Grupo de Transformação
    QGroupBox *GrupoTransformacoes = new QGroupBox(tr("Modo de Edição:"));

    QRadioButton *RadioBtnMover      = new QRadioButton(tr("Mover"));
    QRadioButton *RadioBtnRodar      = new QRadioButton(tr("Rodar"));
    QRadioButton *RadioBtnEscalar    = new QRadioButton(tr("Escalar"));
    QRadioButton *RadioBtnSelecionar = new QRadioButton(tr("Selecionar"));

    RadioBtnMover->setChecked(true);

    QHBoxLayout *LayoutTransfHorizontal = new QHBoxLayout;
    LayoutTransfHorizontal->addWidget(RadioBtnMover);
    LayoutTransfHorizontal->addWidget(RadioBtnRodar);
    LayoutTransfHorizontal->addWidget(RadioBtnEscalar);
    LayoutTransfHorizontal->addWidget(RadioBtnSelecionar);

    GrupoTransformacoes->setLayout(LayoutTransfHorizontal);

    //Grupo de Seleção
    QGroupBox *GrupoSelecao = new QGroupBox(tr("Modo de Seleção:"));

    QRadioButton *RadioBtnMesh    = new QRadioButton(tr("Mesh"));
    QRadioButton *RadioBtnFace    = new QRadioButton(tr("Face"));
    QRadioButton *RadioBtnGrupo   = new QRadioButton(tr("Grupo"));

    RadioBtnMesh->setChecked(true);

    QHBoxLayout *LayoutSelHorizontal = new QHBoxLayout;
    LayoutSelHorizontal->addWidget(RadioBtnMesh);
    LayoutSelHorizontal->addWidget(RadioBtnFace);
    LayoutSelHorizontal->addWidget(RadioBtnGrupo);

    GrupoSelecao->setLayout(LayoutSelHorizontal);

    //Grupo de Edição
    QGroupBox *GrupoEdicao = new QGroupBox(tr("Operações Booleanas:"));

    QPushButton *BtnUniao     = new QPushButton(tr("União"));
    QPushButton *BtnIntersec  = new QPushButton(tr("Interseção"));
    QPushButton *BtnDiferenca = new QPushButton(tr("Diferença"));

    QVBoxLayout *LayoutEdicaoVertical = new QVBoxLayout;
    LayoutEdicaoVertical->addWidget(BtnUniao);
    LayoutEdicaoVertical->addWidget(BtnIntersec);
    LayoutEdicaoVertical->addWidget(BtnDiferenca);

    GrupoEdicao->setLayout(LayoutEdicaoVertical);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoPrimitivos);
    LayoutPrincipal->addWidget(GrupoTransformacoes);
    LayoutPrincipal->addWidget(GrupoSelecao);
    LayoutPrincipal->addWidget(GrupoEdicao);
    LayoutPrincipal->addStretch(1);
    setLayout(LayoutPrincipal);

}

