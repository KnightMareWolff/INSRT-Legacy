/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef SCR_OBJETOS_H
#define SCR_OBJETOS_H

/*************************************/
/*Defines Específicos para Cameras   */
/*************************************/
#define ICR_FRONT    0
#define ICR_BACK     1
#define ICR_LEFT     2
#define ICR_RIGHT    3

#define ICR_ESC_KEY  0
#define ICR_A_KEY    1
#define ICR_B_KEY    2
#define ICR_C_KEY    3
#define ICR_D_KEY    4
#define ICR_E_KEY    5
#define ICR_F_KEY    6
#define ICR_G_KEY    7
#define ICR_H_KEY    8
#define ICR_I_KEY    9
#define ICR_J_KEY    10
#define ICR_K_KEY    11
#define ICR_L_KEY    12
#define ICR_M_KEY    13
#define ICR_N_KEY    14
#define ICR_O_KEY    15
#define ICR_P_KEY    16
#define ICR_Q_KEY    17
#define ICR_R_KEY    18
#define ICR_S_KEY    19
#define ICR_T_KEY    20
#define ICR_U_KEY    21
#define ICR_V_KEY    22
#define ICR_W_KEY    23
#define ICR_X_KEY    24
#define ICR_Y_KEY    25
#define ICR_Z_KEY    26

class CICRPosition
{
public:

    float mPosX;
    float mPosY;
    float mPosZ;

    CICRPosition(                                );
    CICRPosition(float PosX,float PosY,float PosZ);
   ~CICRPosition(                                );
};

class CICRActor
{
public:

    CICRPosition ICR_ActorPos;
    int          ICR_ActorId;
    char *       ICR_ActorName;

    CICRActor(                             );
    CICRActor(char         *pICR_Name      ,
              CICRPosition *pICR_Position  ,
              int           pICR_ActorType );
   ~CICRActor(                             );

    char*         GetName(                           );
    void          SetName(char         *pICR_Name    );
    void          SetPos (CICRPosition *pICR_Position);
    CICRPosition  GetPos (                           );
    void          Walk   (CICRPosition *pICR_Position);
    void          Stop   (                           );
};

class CICRCamera
{
public:

    CICRPosition mPos;

    CICRCamera(                  );
    CICRCamera(CICRPosition *pos );
   ~CICRCamera(                  );

    void   Move(int D);
};

bool        ICR_SystemOk          (                     );
bool        ICR_SystemRunning     (                     );
void        ICR_RegisterKbFunction(int  tcl,char *nmFunc);
void        ICR_ShutDown          (                     );
void        ICR_HoldPipelines     (                     );
void        ICR_FreePipelines     (                     );

#endif // SCR_OBJETOS_H
