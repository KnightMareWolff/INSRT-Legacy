#include "ISM_Exemplo10.h"

extern lua_State*  L;

CISMExemplo10::CISMExemplo10(QOpenGLContext *pI3DContext):
    CISMCenario(pI3DContext),
    pListaCubos("Lista Cubos")
{
    japosicionou=false;

    pVideoAvi    = NULL;
    pVideoCamera = NULL;
    pSom         = NULL;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo10::CISMExemplo10(QGLContext *pI3DContext):
    CISMCenario(pI3DContext),
    pListaCubos("Lista Cubos")
{
    japosicionou=false;

    pVideoAvi    = NULL;
    pVideoCamera = NULL;
    pSom         = NULL;

    if(!Inicializa())
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Inicialização do Cenario.");
        exit(0);
    }
}

CISMExemplo10::~CISMExemplo10()
{
    delete pLuzAmbiente;
    delete pSky;
    delete pVideoAvi;
    delete pVideoCamera;
    delete pSom;

    pListaCubos.Limpa();
}

bool CISMExemplo10::Inicializa()
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

    pVideoAvi    = new CIMDVideo(CIUTGerenciadorPath::IUT_PathWorld + "Videos/Texto.avi");
    pVideoCamera = new CIMDVideo( 0                                                            );
    /***********************************************/
    /*Adiciona os materiais da Cena                */
    /***********************************************/
    int IdMatCubo01    ,
        IdMatCubo02    ,
        IdTexturaCubo01,
        IdTexturaCubo02;

    //Inclui Material a ser usado pelo Cubo 01
    IdMatCubo01=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo01",IGL_MATERIAL_TEXTURE);

    IdTexturaCubo01=INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo01,
                                                             CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Caixa.bmp",
                                                             IGL_TEXTURE_LINEAR);

    INSMA::pINSMAMaterialManager->SetaRejeicaoCor(IdMatCubo01,true,CIMACor(0.0f,0.0f,0.0f,1.0f));
    INSMA::pINSMAMaterialManager->RenderToTexture(IdMatCubo01,pVideoAvi);


    //Inclui Material a ser usado pelo Cubo 02
    IdMatCubo02=INSMA::pINSMAMaterialManager->AddMaterial("Material Cubo02",IGL_MATERIAL_TEXTURE);

    IdTexturaCubo02=INSMA::pINSMAMaterialManager->AddTextura(IdMatCubo02,
                                                  CIUTGerenciadorPath::IUT_PathWorld + "Texturas/Ladrilho_Misterio.bmp",
                                                  IGL_TEXTURE_LINEAR);

    //Descomente para pegar o video da Webcam e mostrá-lo na Sky-Box!!!
    INSMA::pINSMAMaterialManager->RenderToTexture(IdMatCubo02,pVideoCamera);

    /*************************/
    /*Cria a SkyBox          */
    /*************************/
    pSky     = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                              CIMTVetor(4096.0f,4096.0f,4096.0f),
                              IGL_WINMODE_CCW);

    pSky->I3D_Mesh->SetaMaterial(IdMatCubo02);
    pSky->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_STATIC);

    CIMTVetor PosIni = pSky->I3D_Pos;
    /*****************************************************************/
    /*Cria um nova esfera na posição (0,0,0)                         */
    /*****************************************************************/
    pListaCubos.Add(new CI3DCubo  (CIMTVetor( PosIni.x,
                                              PosIni.y,
                                              PosIni.z) ,
                                   CIMTVetor( 5.0f, 5.0f, 5.0f),
                                   IGL_WINMODE_CW             ));

    ((CI3DCubo *)pListaCubos.Busca(0))->I3D_Mesh->SetaMaterial(IdMatCubo01);
    ((CI3DCubo *)pListaCubos.Busca(0))->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);

    //Cria uma interface com o sistema Multimídia
    pIMDInterface = new INSMDInterface();

    QString pathsom = QString(CIUTGerenciadorPath::IUT_PathWorld + "Fx/Galinha.mp3");

    pSom = new CIMDSom(pathsom.toStdString().c_str());

    LiberaCenario();
    //Ocorreu tudo bem!
    return true;
}

bool CISMExemplo10::Render(float pTimeElapsed)
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

    /*****************************/
    /*Renderiza a SkyBox         */
    /*****************************/
    pSky->Render(IGL_MODE_RENDER     ,
                 IGL_RENDER_TRIANGLES,
                 IGL_SHADING_MODE_NOONE);

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
       SetIniPos(pCam,pSky->I3D_Pos);
       japosicionou = true;
    }

    //Importantíssimo realizar o update de som para a FMOD frame a frame
    INSMDInterface::Atualiza();
    /*Fim do Bloco Principal OPENGL*/
    DisableOGLStates();

    return true;
}

bool CISMExemplo10::Resize(int w, int h)
{
    /*****************************/
    /*Calcula Frustrum de Camera */
    /*****************************/
    pCam->AtTela=w;
    pCam->LgTela=h;
    pCam->CalculaPerspectiva(1.0f,30000.0f,IGL_PROJECTION_PERSP);

    return true;
}

bool CISMExemplo10::MapeiaMouse(int x, int y)
{
    pCam->MapeiaMouse((float)x ,(float)y);
    return true;
}

bool CISMExemplo10::MoverCamera(int pAction)
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
          pSom->Play(true);
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

bool CISMExemplo10::InputKey(int pKey)
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

bool CISMExemplo10::SetIniPos(CI3DCamera *pCam, CIMTVetor centro)
{
    CIMTVetor posicao;

    /***********************************/
    /*Seta a Posicao Alvo              */
    /***********************************/
    posicao    = CIMTVetor(centro);
    posicao.z += 10.0f;
    /***********************************/
    /*Altera Posicao e View da Camera  */
    /***********************************/
    pCam->I3D_CameraPos  = posicao;
    pCam->I3D_CameraView = centro;

    japosicionou = true;

    return true;
}

bool CISMExemplo10::UpdatePipeline()
{
    CIMTMatriz mtxTransf;
    CIMTVetor  dest;
    /************************************/
    /*Atualiza Todas as Luzes do cenario*/
    /************************************/
    mtxTransf.RotateY(0.01f,pSky->I3D_Pos,true);
    dest = pLuzAmbiente->PegaPos() * mtxTransf;
    pLuzAmbiente->SetaPos(dest);
    pLuzAmbiente->Atualiza(INSSH::pISHProgramManager->ProgramId("CoreRender"),IGL_LIGHT_CHANNEL_01);

    /************************************/
    /*Atualiza Todos os Obj   do cenario*/
    /************************************/
    for(int i=0;i<pListaCubos.Tam();i++)
    {
        ((CI3DCubo *)pListaCubos.Busca(i))->Rotate(true,CIMTVetor(0.0f ,1.0f,0.0f),pSky->I3D_Pos);
        ((CI3DCubo *)pListaCubos.Busca(i))->Rotate(true,CIMTVetor(1.0f ,0.0f,0.0f),pSky->I3D_Pos);
    }

    return true;
}

bool CISMExemplo10::InitPipeline()
{
    if(CenarioInicializado() && !ThreadPipeInicializada())
    {
       CriaThreadLua(L);
    }

    return true;
}

bool CISMExemplo10::InputPipeline()
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

int CISMExemplo10::AddTrigger(int      pTipoTrigger   ,
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

bool CISMExemplo10::AddParametroTrigger(int      pTipoTrigger            ,
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

bool CISMExemplo10::AddParametroTrigger(int      pTipoTrigger            ,
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
