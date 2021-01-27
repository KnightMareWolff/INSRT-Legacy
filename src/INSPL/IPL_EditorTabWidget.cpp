#include "IPL_EditorTabWidget.h"
#include "IPL_EditorTabPageObjetos.h"
#include "IPL_EditorTabPageAmbiente.h"
#include "IPL_EditorTabPageOtimizacao.h"
#include "IPL_EditorTabPageMateriais.h"
#include <QVBoxLayout>


CIPLEditorTabWidget::CIPLEditorTabWidget(QWidget *parent) : QWidget(parent)
{
    tabWidget = new QTabWidget;
    tabWidget->addTab(new CIPLEditorTabPageObjetos   (), tr("Edição"));
    tabWidget->addTab(new CIPLEditorTabPageMateriais (), tr("Materiais"));
    tabWidget->addTab(new CIPLEditorTabPageAmbiente  (), tr("Ambientação"));
    tabWidget->addTab(new CIPLEditorTabPageOtimizacao(), tr("Otimização"));

    tabWidget->setMinimumWidth(300);

    QVBoxLayout *TabLayout = new QVBoxLayout;
    TabLayout->addWidget(tabWidget);
    setLayout(TabLayout);
}

