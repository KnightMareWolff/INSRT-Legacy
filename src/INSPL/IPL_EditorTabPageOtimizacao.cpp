#include "IPL_EditorTabPageOtimizacao.h"
#include "IUT_GerenciadorPath.h"
#include <QVBoxLayout>
#include <QLabel>

CIPLEditorTabPageOtimizacao::CIPLEditorTabPageOtimizacao(QWidget *parent) : QWidget(parent)
{
    //Grupo de Criação
    QGroupBox *GrupoCompilacao    = new QGroupBox(tr("Compilador BSP:"));

    QCheckBox *CheckBoxHSR = new QCheckBox(tr("HSR"));
    QCheckBox *CheckBoxBSP = new QCheckBox(tr("BSP"));
    QCheckBox *CheckBoxPRT = new QCheckBox(tr("PRT"));
    QCheckBox *CheckBoxPVS = new QCheckBox(tr("PVS"));
    QCheckBox *CheckBoxTJR = new QCheckBox(tr("TJR"));
    QCheckBox *CheckBoxLTM = new QCheckBox(tr("LTM"));

    QPushButton *AddCompilaBtn = new QPushButton(tr("Compilar Cenário"));

    //Configura Linha HSR/BSP
    QHBoxLayout *LinhaCompHSR = new QHBoxLayout;
    LinhaCompHSR->addWidget(CheckBoxHSR);
    LinhaCompHSR->addWidget(CheckBoxBSP);

    //Configura Linha PRT/PVS
    QHBoxLayout *LinhaCompPRT = new QHBoxLayout;
    LinhaCompPRT->addWidget(CheckBoxPRT);
    LinhaCompPRT->addWidget(CheckBoxPVS);

    //Configura Linha TJR/LTM
    QHBoxLayout *LinhaCompTJR = new QHBoxLayout;
    LinhaCompTJR->addWidget(CheckBoxTJR);
    LinhaCompTJR->addWidget(CheckBoxLTM);

    //Adiciona as linhas no Layout Vertical
    QVBoxLayout *LayoutCompVertical = new QVBoxLayout;
    LayoutCompVertical->addLayout(LinhaCompHSR);
    LayoutCompVertical->addLayout(LinhaCompPRT);
    LayoutCompVertical->addLayout(LinhaCompTJR);
    LayoutCompVertical->addWidget(AddCompilaBtn);


    GrupoCompilacao->setLayout(LayoutCompVertical);

    //Grupo de Parametros de compilação
    QGroupBox *GrupoParametrosComp    = new QGroupBox(tr("Parâmetros de Compilação:"));

    QDial *DialNumDiv = new QDial;
    DialNumDiv->setFocusPolicy(Qt::StrongFocus);

    QDial *DialHeuristica = new QDial;
    DialHeuristica->setFocusPolicy(Qt::StrongFocus);

    //Configura Linha TJR/LTM
    QHBoxLayout *LinhaParametros = new QHBoxLayout;
    LinhaParametros->addWidget(DialNumDiv);
    LinhaParametros->addWidget(DialHeuristica);

    GrupoParametrosComp->setLayout(LinhaParametros);

    //Inclui os Grupos no Layout Principal
    QVBoxLayout *LayoutPrincipal = new QVBoxLayout;
    LayoutPrincipal->addWidget(GrupoCompilacao);
    LayoutPrincipal->addWidget(GrupoParametrosComp);
    setLayout(LayoutPrincipal);

}

