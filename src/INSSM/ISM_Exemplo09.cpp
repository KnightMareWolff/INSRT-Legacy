#include "ISM_Exemplo09.h"

extern lua_State*  L;

CISMExemplo09::CISMExemplo09(QOpenGLContext *pI3DContext):
    CISMCenario(pI3DContext),
    pListaCubos("Lista Cubos")
{
    japosicionou=false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo09::CISMExemplo09(QGLContext *pI3DContext):
    CISMCenario(pI3DContext),
    pListaCubos("Lista Cubos")
{
    japosicionou=false;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo09::~CISMExemplo09()
{
    delete pLuzAmbiente;
}

bool CISMExemplo09::Inicializa()
{
    /***********************************************/
    /*Cria a Camera                                */
    /***********************************************/
    pCam = new CI3DCamera          ;//Instancia uma nova camera
    pCam   ->Inicializa()          ;//Inicializa a camera com valores default
    pCam   ->I3D_Velocidade = 25.0f;//seta a velocidade da camera

    /***********************************************/
    /*Cria as Luzes utilizadas no cenario          */
    /***********************************************/
    pLuzAmbiente = new CI3DLuz();
    pLuzAmbiente->SetaPos(CIMTVetor(60.0f,0.0f,0.0f));
    pLuzAmbiente->Prepara(INSSH::pISHProgramManager->ProgramId("CoreRender"),0);

    /***********************************************/
    /*Adiciona os materiais da Cena                */
    /***********************************************/
    int IdMatCubo01;

    //Inclui Material a ser usado pelo Cubo 01
    IdMatCubo01=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo01",IGL_MATERIAL_TEXTURE);

    INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo01,
                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                             IGL_TEXTURE_LINEAR);


    PosIni = CIMTVetor(0.0f,0.0f,0.0f);
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pListaCubos.Add(new CI3DCubo  (CIMTVetor( PosIni.x + 14.0f ,
                                              PosIni.y + 0.0f  ,
                                              PosIni.z + 0.0f) ,
                                         CIMTVetor( 2.5f, 2.5f, 2.5f),
                                         IGL_WINMODE_CW             ));

    ((CI3DCubo *)pListaCubos.Busca(0))->I3D_Mesh->SetaMaterial(IdMatCubo01);
    ((CI3DCubo *)pListaCubos.Busca(0))->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    LiberaCenario();
    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo09::Render(float pTimeElapsed)
{
    /*******************************************************************/
    /*Configura os Estados Iniciais da Maquina de Estado da OpenGL     */
    /*O Loop Principal de Renderização de Objetos deve ser colocado    */
    /*Entre o Inicio e o Fim deste Bloco                               */
    /*******************************************************************/
    /*Inicio do Bloco Principal OPENGL*/
    EnableOGLStates();

    /*************************************/
    /*Pipeline de Inicialização Dinâmica */
    /*************************************/
    InitPipeline();
    InputPipeline();
    /********************************************************************/
    /*Atualiza a Camera (O Posicionamento precisa ficar dentro do Bloco)*/
    /********************************************************************/
    pCam->PosicionaCamera();

    for(int i=0;i<pListaCubos.Tam();i++)
    {
        ((CI3DCubo *)pListaCubos.Busca(i))->Render(IGL_MODE_RENDER     ,
                                                   IGL_RENDER_TRIANGLES,
                                                   IGL_SHADING_MODE_SMOOTH);
    }

    /****************************/
    /*Pipeline de Atualização   */
    /****************************/
    UpdatePipeline();

    if(!japosicionou)
    {
       SetIniPos(pCam,PosIni);
       japosicionou = true;
    }

    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();

    return true;
}

bool CISMExemplo09::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,3000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo09::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo09::MoverCamera(int pAction)
{
    /****************************************/
    /*Processa as teclas pressionadas       */
    /****************************************/
    switch(pAction)
    {
       case ISM_INPUT_MOVE_FOWARD:
       {
          pCam->MoverCamera(150.0f);
       }break;
       case ISM_INPUT_MOVE_BACKWARD:
       {
          pCam->MoverCamera(-150.0f);
       }break;
       case ISM_INPUT_MOVE_STRAFELFT:
       {
          pCam->CameraStrafe(-150.0f);;
       }break;
       case ISM_INPUT_MOVE_STRAFERGT:
       {
          pCam->CameraStrafe(150.0f);
       }break;
    }
    return true;
}

bool CISMExemplo09::InputKey(int pKey)
{
    CIUTTrigger *trigger;

    for(unsigned int i=0 ; i< pInputPipe.Tam();i++)
    {
        trigger = (CIUTTrigger *)pInputPipe.busca(i);

        if(trigger->IUT_EstadoTrigger == IUT_TRIGGER_ST_NULO    ||
           trigger->IUT_EstadoTrigger == IUT_TRIGGER_ST_INATIVO )
        {
            if(trigger->IUT_ParametrosTrigger.size()>0)
            {
                if(trigger->IUT_ParametrosTrigger[0].IUT_DadoInt == pKey)
                {
                    trigger->Ativar();
                }
            }
        }
    }

    return true;
}

bool CISMExemplo09::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 20.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMExemplo09::UpdatePipeline()
{
    CIMTMatriz mtxTransf;
    CIMTVetor  dest;
    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    mtxTransf.RotateY(0.01f,PosIni,true);
    dest = pLuzAmbiente->PegaPos() * mtxTransf;
    pLuzAmbiente->SetaPos(dest);
    pLuzAmbiente->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),IGL_LIGHT_CHANNEL_01);

    /************************************/
    /*Atualiza Todos os Obj   do cenario*/
    /************************************/
    for(int i=0;i<pListaCubos.Tam();i++)
    {
        ((CI3DCubo *)pListaCubos.Busca(i))->Rotate(true,CIMTVetor(0.0f ,1.0f,0.0f),((CI3DCubo *)pListaCubos.Busca(i))->I3D_Pos);
        ((CI3DCubo *)pListaCubos.Busca(i))->Rotate(true,CIMTVetor(1.0f ,0.0f,0.0f),((CI3DCubo *)pListaCubos.Busca(i))->I3D_Pos);
    }


    return true;
}

bool CISMExemplo09::InitPipeline()
{
    if(CenarioInicializado() && !ThreadPipeInicializada())
    {
       CriaThreadLua(L);
    }

    return true;
}

bool CISMExemplo09::InputPipeline()
{
    CIUTTrigger *trigger;
    /*******************************************************************/
    /*Executa funções REGISTRADAS Lua pertencentes ao pipeline de Input*/
    /*******************************************************************/
    if(SistemaLivre())
    {
       for(unsigned int i=0;i<pInputPipe.Tam();i++)
       {
          trigger = (CIUTTrigger *)pInputPipe.busca(i);

          if(trigger->IUT_EstadoTrigger == IUT_TRIGGER_ST_ATIVO )
          {
             //Sinaliza que está executando o trigger
             trigger->Executando();

             //Busca a função Lua e executa
             lua_getglobal(PegaThreadLua(),trigger->IUT_FuncaoTrigger.toStdString().c_str());
             lua_pcall(PegaThreadLua    (),0,0,0);

             //Sinaliza que executou a trigger
             trigger->Desativar();
          }
       }
    }

    return true;
}

int CISMExemplo09::AddTrigger(int      pTipoTrigger   ,
                              QString  pNomeTrigger   ,
                              QString  pFuncao        )
{
    switch(pTipoTrigger)
    {
       case IUT_TRIGGER_PL_INICIO:
       {
          pInicioPipe.entrafila(new CIUTTrigger(pTipoTrigger,
                                                pNomeTrigger,
                                                pFuncao)    , 1 , QString("Trigger %1").arg(pInicioPipe.Tam()+1) );
          return pInicioPipe.Tam()-1;
       }break;
       case IUT_TRIGGER_PL_INPUT:
       {
          pInputPipe.entrafila(new CIUTTrigger(pTipoTrigger,
                                               pNomeTrigger,
                                               pFuncao)    , 1 , pFuncao);
          return pInputPipe.Tam()-1;
       }break;
       case IUT_TRIGGER_PL_RENDER:
       {
          pRenderPipe.entrafila(new CIUTTrigger(pTipoTrigger,
                                                pNomeTrigger,
                                                pFuncao)    , 1 , QString("Trigger %1").arg(pRenderPipe.Tam()+1));
          return pRenderPipe.Tam()-1;
       }break;
       case IUT_TRIGGER_PL_UPDATE:
       {
          pUpdatePipe.entrafila(new CIUTTrigger(pTipoTrigger,
                                                pNomeTrigger,
                                                pFuncao)    , 1 , QString("Trigger %1").arg(pUpdatePipe.Tam()+1));
          return pUpdatePipe.Tam()-1;
       }break;
    }

    //Não é para acontecer mas....
    return -1;
}

bool CISMExemplo09::AddParametroTrigger(int      pTipoTrigger            ,
                                        int      pIdTrigger              ,
                                        CIUTParametroTrigger  pParametro)
{
    CIUTTrigger* temp;

    switch(pTipoTrigger)
    {
       case IUT_TRIGGER_PL_INICIO:
       {
          temp = (CIUTTrigger *)pInicioPipe.busca(pIdTrigger);
       }break;
       case IUT_TRIGGER_PL_INPUT:
       {
          temp = (CIUTTrigger *)pInputPipe.busca(pIdTrigger);
       }break;
       case IUT_TRIGGER_PL_RENDER:
       {
          temp = (CIUTTrigger *)pRenderPipe.busca(pIdTrigger);
       }break;
       case IUT_TRIGGER_PL_UPDATE:
       {
          temp = (CIUTTrigger *)pUpdatePipe.busca(pIdTrigger);
       }break;
    }

    if(temp!=NULL)
    {
        temp->IUT_ParametrosTrigger.push_back(pParametro);
        return true;
    }
    return false;
}

bool CISMExemplo09::AddParametroTrigger(int      pTipoTrigger            ,
                                        QString  pNomeTrigger            ,
                                        CIUTParametroTrigger  pParametro)
{
    CIUTTrigger* temp;

    switch(pTipoTrigger)
    {
       case IUT_TRIGGER_PL_INICIO:
       {
          temp = (CIUTTrigger *)pInicioPipe.busca(pNomeTrigger);
       }break;
       case IUT_TRIGGER_PL_INPUT:
       {
          temp = (CIUTTrigger *)pInputPipe.busca(pNomeTrigger);
       }break;
       case IUT_TRIGGER_PL_RENDER:
       {
          temp = (CIUTTrigger *)pRenderPipe.busca(pNomeTrigger);
       }break;
       case IUT_TRIGGER_PL_UPDATE:
       {
          temp = (CIUTTrigger *)pUpdatePipe.busca(pNomeTrigger);
       }break;
    }

    if(temp!=NULL)
    {
        temp->IUT_ParametrosTrigger.push_back(pParametro);
        return true;
    }
    return false;
}

