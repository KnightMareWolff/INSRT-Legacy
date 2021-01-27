/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "INSCR.h"
#include "SCR_Objetos.h"

extern bool                   bInicializado ;
extern bool                   bRodando      ;
extern bool                   PipeUpd       ;
extern vector<INS_MODEL_PIPE> ModelPipeline ;
extern bool                   LockPipeline  ;
extern vector<INS_FUNC>       ListaFuncoes  ;
extern QFuture<void>          f1            ;

#define RANGE_RANDOMICO 150

/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
CICRActor::CICRActor()
{
    //ICR_ActorName = "Default";
    ICR_ActorPos  = CICRPosition(0,0,0);
}
/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
CICRActor::CICRActor(char         *pICR_Name      ,
                     CICRPosition *pICR_Position  ,
                     int           pICR_ActorType)
{
    ICR_ActorName = new char[strlen(pICR_Name)];
    strcpy(ICR_ActorName,pICR_Name);

    //Dispara uma Trigger de Input permanente
    CISMCenario *pCenario=NULL;

    pCenario = INSCR::PegaSM();

    pCenario->AddTrigger(IUT_TRIGGER_PL_CREATE,"Actor","Spawn");
    pCenario->AddParametroTrigger(IUT_TRIGGER_PL_CREATE,
                                         "Spawn",
                                         CIUTParametroTrigger(IUT_TRIGGER_TP_INT,pICR_ActorType));
    pCenario->AddParametroTrigger(IUT_TRIGGER_PL_CREATE,
                                         "Spawn",
                                         CIUTParametroTrigger(IUT_TRIGGER_TP_VECTOR         ,
                                                              CIMTVetor(pICR_Position->mPosX,
                                                                        pICR_Position->mPosY,
                                                                        pICR_Position->mPosZ)));

    ICR_ActorPos.mPosX = pICR_Position->mPosX;
    ICR_ActorPos.mPosY = pICR_Position->mPosY;
    ICR_ActorPos.mPosZ = pICR_Position->mPosZ;
}
/**************************************/
/*                                    */
/**************************************/
CICRActor::~CICRActor()
{
    ICR_ActorPos  = CICRPosition(0,0,0);
    delete [] ICR_ActorName;
    ICR_ActorName   = NULL;
}

/**************************************/
/*     */
/**************************************/
char* CICRActor::GetName()
{
    return ICR_ActorName;
}

/**************************************/
/**/
/**************************************/
void  CICRActor::SetName(char *pICR_Name)
{
    if(ICR_ActorName) delete [] ICR_ActorName;

    ICR_ActorName = new char[strlen(pICR_Name)];
    strcpy(ICR_ActorName,pICR_Name);
}

/**************************************/
/**/
/**************************************/
void CICRActor::SetPos(CICRPosition *pos)
{
    ICR_ActorPos.mPosX = pos->mPosX;
    ICR_ActorPos.mPosY = pos->mPosY;
    ICR_ActorPos.mPosZ = pos->mPosZ;
}

/**************************************/
/* */
/**************************************/
CICRPosition CICRActor::GetPos()
{
    return ICR_ActorPos;
}

/**************************************/
/**/
/**************************************/
void CICRActor::Walk(CICRPosition *tgt)
{
    tgt=NULL;
    //ROTINAS PARA ANDAR
}

/**************************************/
/**/
/**************************************/
void CICRActor::Stop()
{

    //ROTINAS PARA PARAR O MODELO

}

CICRPosition::CICRPosition()
{
    mPosX = 0;
    mPosY = 0;
    mPosZ = 0;
}

CICRPosition::CICRPosition(float PosX,float PosY,float PosZ)
{
    mPosX = PosX;
    mPosY = PosY;
    mPosZ = PosZ;
}
/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
CICRPosition::~CICRPosition()
{

}

/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
CICRCamera::CICRCamera()
{
    mPos  = CICRPosition(0,0,0);
}
/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
CICRCamera::CICRCamera(CICRPosition *pos)
{
    mPos.mPosX = pos->mPosX;
    mPos.mPosY = pos->mPosY;
    mPos.mPosZ = pos->mPosZ;
}
/**************************************/
/*                                    */
/**************************************/
CICRCamera::~CICRCamera()
{
    mPos  = CICRPosition(0,0,0);
}

/**************************************/
/*                                    */
/**************************************/
void CICRCamera::Move(int D)
{
    switch(D)
    {
         case ICR_FRONT : INSCR::PegaSM()->MoverCamera(ISM_INPUT_MOVE_FOWARD   ); break;
         case ICR_BACK  : INSCR::PegaSM()->MoverCamera(ISM_INPUT_MOVE_BACKWARD ); break;
         case ICR_LEFT  : INSCR::PegaSM()->MoverCamera(ISM_INPUT_MOVE_STRAFELFT); break;
         case ICR_RIGHT : INSCR::PegaSM()->MoverCamera(ISM_INPUT_MOVE_STRAFERGT); break;
    }
}

/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
bool ICR_SystemOk()
{
    if(INSCR::PegaSM()->CenarioInicializado())
    {
        //Após o Core ser inicializado podemos liberar
        //O sistema para criar uma Thread Lua e
        //Copiar o State Lua Principal
        INSCR::PegaSM()->LiberaLua();
        return true;
    }
    return false;
}

/**************************************/
/*Atribui custo para o NoEstrela      */
/**************************************/
bool ICR_SystemRunning()
{
    if(!INSCR::PegaSM()->SistemaLivre())
    {
       return false;
    }
    else
    {
       return true;
    }

}

/**************************************/
/*Registra um Modelo no sistema       */
/**************************************/
void ICR_RegisterKbFunction(int tcl,char *nmFunc)
{
    //Dispara uma Trigger de Input permanente
    INSCR::PegaSM()->AddTrigger(IUT_TRIGGER_PL_INPUT,nmFunc,nmFunc);
    INSCR::PegaSM()->AddParametroTrigger(IUT_TRIGGER_PL_INPUT,
                                         nmFunc,
                                         CIUTParametroTrigger(IUT_TRIGGER_TP_INT,tcl));
}

void ICR_ShutDown()
{
    bRodando=false;
    exit(0);
}

void ICR_HoldPipelines()
{
    LockPipeline = true;
}

void ICR_FreePipelines()
{
    LockPipeline = false;
}
