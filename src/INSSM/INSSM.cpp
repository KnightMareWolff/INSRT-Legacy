#include "INSSM.h"
#include "ISM_DemoProject.h"
#include "ISM_EditorProject.h"
#include "ISM_Exemplo01.h"
#include "ISM_Exemplo02.h"
#include "ISM_Exemplo03.h"
#include "ISM_Exemplo04.h"
#include "ISM_Exemplo05.h"
#include "ISM_Exemplo06.h"
#include "ISM_Exemplo07.h"
#include "ISM_Exemplo08.h"
#include "ISM_Exemplo09.h"
#include "ISM_Exemplo10.h"
#include "ISM_Exemplo11.h"

INSSM::INSSM(QOpenGLContext *pI3DContext, QString pNomeCenario)
{

    if(pNomeCenario == "DemoProject")
    {
       pCenario = new CISMDemoProject(pI3DContext);
       return;
    }

    if(pNomeCenario == "EditorProject")
    {
       pCenario = new CISMEditorProject(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo01")
    {
       pCenario = new CISMExemplo01(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo02")
    {
       pCenario = new CISMExemplo02(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo03")
    {
       pCenario = new CISMExemplo03(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo04")
    {
       pCenario = new CISMExemplo04(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo05")
    {
       pCenario = new CISMExemplo05(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo06")
    {
       pCenario = new CISMExemplo06(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo07")
    {
       pCenario = new CISMExemplo07(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo08")
    {
       pCenario = new CISMExemplo08(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo09")
    {
       pCenario = new CISMExemplo09(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo10")
    {
       pCenario = new CISMExemplo10(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo11")
    {
       pCenario = new CISMExemplo11(pI3DContext);
       return;
    }
    /****************************************************/
    /*Se chegou nesta parte do metodo é porque não achou*/
    /*Nenhum Cenario Válido.                            */
    /****************************************************/
    qWarning() << "Atenção, Nenhum cenario válido foi passado para inicialização!";
    QMessageBox::information(0, "Insane RT Framework",
                                "Atenção, Nenhum cenario válido foi passado para inicialização!");
    exit(0);
}

INSSM::INSSM(QGLContext *pI3DContext, QString pNomeCenario)
{

    if(pNomeCenario == "DemoProject")
    {
       pCenario = new CISMDemoProject(pI3DContext);
       return;
    }

    if(pNomeCenario == "EditorProject")
    {
       pCenario = new CISMEditorProject(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo01")
    {
       pCenario = new CISMExemplo01(pI3DContext);
       return;
    }
    if(pNomeCenario == "Exemplo02")
    {
       pCenario = new CISMExemplo02(pI3DContext);
       return;
    }
    if(pNomeCenario == "Exemplo03")
    {
       pCenario = new CISMExemplo03(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo04")
    {
       pCenario = new CISMExemplo04(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo05")
    {
       pCenario = new CISMExemplo05(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo06")
    {
       pCenario = new CISMExemplo06(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo07")
    {
       pCenario = new CISMExemplo07(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo08")
    {
       pCenario = new CISMExemplo08(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo09")
    {
       pCenario = new CISMExemplo09(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo10")
    {
       pCenario = new CISMExemplo10(pI3DContext);
       return;
    }

    if(pNomeCenario == "Exemplo11")
    {
       pCenario = new CISMExemplo11(pI3DContext);
       return;
    }
    /****************************************************/
    /*Se chegou nesta parte do metodo é porque não achou*/
    /*Nenhum Cenario Válido.                            */
    /****************************************************/
    qWarning() << "Atenção, Nenhum cenario válido foi passado para inicialização!";
    QMessageBox::information(0, "Insane RT Framework",
                                "Atenção, Nenhum cenario válido foi passado para inicialização!");
    exit(0);
}

CISMCenario* INSSM::PegaCenario()
{
    return pCenario;
}
