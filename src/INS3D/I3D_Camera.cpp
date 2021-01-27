#include "I3D_Camera.h"

CI3DCamera::CI3DCamera()
{
    I3D_CameraPos =CIMTVetor(50.00f,1.00f,50.00f);
    I3D_CameraView=CIMTVetor(0.00f,0.00f,0.00f);
    I3D_CameraUp  =CIMTVetor(0.00f,1.00f,0.00f);
    I3D_Velocidade       =25.0f;
    I3D_Intervalo        =0.01f;
    i3dFramesPorSegundo  =0;
    i3dUltimoTempo		 =0;
    i3dTempoFrame        =0;
    LgTela               =800;
    AtTela               =600;
}


void CI3DCamera::Inicializa()
{
    I3D_CameraPos        =CIMTVetor(50.00f,1.00f,50.00f);
    I3D_CameraView       =CIMTVetor(0.00f,0.00f,0.00f);
    I3D_CameraUp         =CIMTVetor(0.00f,1.00f,0.00f);
    I3D_Velocidade       =25.0f;
    I3D_Intervalo        =0.01f;
    i3dFramesPorSegundo  =0;
    i3dUltimoTempo		 =0;
    i3dTempoFrame        =0;
    LgTela               =800;
    AtTela               =600;
}

/************************************************************/
/*Nome do Método      : SetaCamera
/*
/*Objetivo            : Seta a Posição em que a camera se
/*                      encontra.
/************************************************************/
void CI3DCamera::SetaCamera(float i3dPosicaoX ,
                            float i3dPosicaoY ,
                            float i3dPosicaoZ ,
                            float i3dViewX    ,
                            float i3dViewY    ,
                            float i3dViewZ    ,
                            float i3dUpX      ,
                            float i3dUpY      ,
                            float i3dUpZ      )
{

   I3D_CameraPos =CIMTVetor( i3dPosicaoX, i3dPosicaoY , i3dPosicaoZ);
   I3D_CameraView=CIMTVetor( i3dViewX   , i3dViewY    , i3dViewZ   );
   I3D_CameraUp  =CIMTVetor( i3dUpX     , i3dUpY      , i3dUpZ     );

}

/************************************************************/
/*Nome do Método      : PegaDirecao
/*
/*Objetivo            : Pega a direção onde a camera está
/*                      apontando.
/************************************************************/
void CI3DCamera::PegaDirecao(float &i3dPosicaoX,
                             float &i3dPosicaoY,
                             float &i3dPosicaoZ)
{
    CIMTVetor Direcao;

    Direcao=I3D_CameraView - I3D_CameraPos;

    i3dPosicaoX = Direcao.x;
    i3dPosicaoY = Direcao.y;
    i3dPosicaoZ = Direcao.z;

}

/************************************************************/
/*Nome do Método      : PegaDirecao
/*
/*Objetivo            : Pega a direção onde a camera está
/*                      apontando.
/************************************************************/
CIMTVetor CI3DCamera::PegaDirecao()
{
    CIMTVetor Direcao;

    Direcao=I3D_CameraView - I3D_CameraPos;

    return Direcao;
}
/************************************************************/
/*Nome do Método      : MoverCamera
/*
/*Objetivo            : Move a camera para a direção desejada
/************************************************************/
void CI3DCamera::MoverCamera(float i3dDirecao)
{

   CIMTVetor  i3dDir;

   i3dDir=PegaDirecao();
   i3dDir.Normalizar ();

   AtualizaCamera(i3dDir.x, i3dDir.y,i3dDir.z,i3dDirecao);
}

/************************************************************/
/*Nome do Método      : AtualizaCamera
/*
/*Objetivo            : Atualiza a camera
/************************************************************/
void CI3DCamera::AtualizaCamera(float xDir, float yDir, float zDir, float dir)
{
   dir = dir / i3dFramesPorSegundo;

   I3D_CameraPos.x += xDir * dir;
   I3D_CameraPos.y += yDir * dir;
   I3D_CameraPos.z += zDir * dir;

   I3D_CameraView.x += xDir * dir;
   I3D_CameraView.y += yDir * dir;
   I3D_CameraView.z += zDir * dir;
}


/************************************************************/
/*Nome do Método      : Rodar
/*
/*Objetivo            : Roda a camera na direção desejada
/************************************************************/
void CI3DCamera::Rodar(float i3dAnguloDirecao,
                       float i3dPosicaoX     ,
                       float i3dPosicaoY     ,
                       float i3dPosicaoZ     )
{


   CIMTVetor i3dDirVisao ;
   CIMTQuat qRotacao, qVisao, qNovaVisao;

   qRotacao.Rotaciona(i3dAnguloDirecao, i3dPosicaoX, i3dPosicaoY, i3dPosicaoZ);

   i3dDirVisao     = PegaDirecao();

   qVisao.x = i3dDirVisao.x ;
   qVisao.y = i3dDirVisao.y ;
   qVisao.z = i3dDirVisao.z ;
   qVisao.w = 0;

   qNovaVisao = ((qRotacao * qVisao) * qRotacao.Conjugar());

   I3D_CameraView.x = I3D_CameraPos.x + qNovaVisao.x;
   I3D_CameraView.y = I3D_CameraPos.y + qNovaVisao.y;
   I3D_CameraView.z = I3D_CameraPos.z + qNovaVisao.z;


}

void CI3DCamera::MapeiaMouse(float x,float y)
{

    float i3dAnguloY  = 0.0f;
    float i3dAnguloZ  = 0.0f;
    float i3dRotacaoX = 0.0f;

    CIMTVetor i3dVetTemp , i3dEixo;

    i3dAnguloY = -y;
    i3dAnguloZ = -x;

    i3dRotacaoX -= i3dAnguloZ;

    if(i3dRotacaoX > 1.0f)
    {

        i3dRotacaoX = 1.0f;

    }

    if(i3dRotacaoX < -1.0f)
    {

        i3dRotacaoX = -1.0f;

    }

    i3dVetTemp     = PegaDirecao();
    i3dEixo        = i3dVetTemp.ProdutoVetorial(I3D_CameraUp);
    i3dEixo.Normalizar();


    Rodar( i3dAnguloZ,
           i3dEixo.x ,
           i3dEixo.y ,
           i3dEixo.z);

    Rodar(i3dAnguloY, 0, 1 , 0);

}

/************************************************************/
/*Nome do Método      : CameraStrafe
/*
/*Objetivo            : Realiza o strafing da camera
/*
/************************************************************/
void CI3DCamera::CameraStrafe(float i3dDirecao)
{

   CalculaStrafe();
   AtualizaCamera(I3D_CameraStrafe.x,
                  I3D_CameraStrafe.y,
                  I3D_CameraStrafe.z,
                  i3dDirecao);
}

/************************************************************/
/*Nome do Método      : CameraStrafe
/*
/*Objetivo            : Realiza o strafing da camera
/*
/************************************************************/
void CI3DCamera::CalculaStrafe()
{

   CIMTVetor Direcao;

   Direcao=PegaDirecao();
   Direcao.Normalizar ();

   I3D_CameraStrafe=Direcao.ProdutoVetorial(I3D_CameraUp);

}

/************************************************************/
/*Nome do Método      : PosicionaCamera
/*
/*Objetivo            : Posiciona a camera levando-se em con-
/*                      ideração todas as suas coordenadas
/*
/************************************************************/
void CI3DCamera::PosicionaCamera()
{
    execGL(IGL_SH_LOOKAT,INSSH::pISHProgramManager->ProgramId("CoreRender"),I3D_CameraPos,I3D_CameraView,I3D_CameraUp);
    CalculaTempo();
}

/************************************************************/
/*Nome do Método      : PosicionaCamera
/*
/*Objetivo            : Posiciona a camera levando-se em con-
/*                      ideração todas as suas coordenadas
/*
/************************************************************/
void CI3DCamera::PosicionaCamera(float &pI3D_CurrentTime, float &pI3D_TimeLapsed)
{
    execGL(IGL_SH_LOOKAT,INSSH::pISHProgramManager->ProgramId("CoreRender"),I3D_CameraPos,I3D_CameraView,I3D_CameraUp);
    CalculaTempo();

    pI3D_CurrentTime = i3dTempoFrame;
    pI3D_TimeLapsed  = I3D_Intervalo;

}


/************************************************************/
/*Nome do Método      : CalculaFrameRate
/*
/*Objetivo            : Calcula nosso FPS , neste caso estamos
/*                      utilizando para calcular a velocidade
/*                      em algumas situações...
/*
/************************************************************/
void CI3DCamera::CalculaTempo()
{
    float i3dTempoAtual = (float)clock()/CLOCKS_PER_SEC;

    I3D_Intervalo       =  i3dTempoAtual - i3dTempoFrame;
    i3dFramesPorSegundo =  1.0f / I3D_Intervalo;
    i3dTempoFrame       =  i3dTempoAtual;

    //qWarning() << QString("FPS: %1").arg(i3dFramesPorSegundo);
}

/************************************************************/
/*Nome do Método      : ResetaCamera
/*
/*Objetivo            : Inicializa as variaveis responsaveis
/*                      pelos valores de tempo utilizados para
/*                      o calculo da velocidade.
/*
/************************************************************/
void CI3DCamera::ResetaCamera()
{
   I3D_CameraPos        =CIMTVetor(100.00f,300.00f,100.00f);
   I3D_CameraView       =CIMTVetor(0.00f,0.00f,0.00f);
   I3D_CameraUp         =CIMTVetor(0.00f,1.00f,0.00f);
   I3D_Velocidade       =0.5f;
   I3D_Intervalo        =0.0f;
   i3dFramesPorSegundo  =0;
   i3dUltimoTempo		=0;
   i3dTempoFrame        =0;
}

void CI3DCamera::CalculaPerspectiva(float i3dProx,
                                    float i3dDist,
                                    int i3dProjection)
{
    float   CampoVisao = 90.0f;
    /**************************/
    /*Previne divisao por zero*/
    /**************************/
    if(LgTela == 0)
        LgTela = 1;

    switch(i3dProjection)
    {
       case IGL_PROJECTION_PERSP:
       {
          execGL(IGL_SH_PERSPECTIVE,INSSH::pISHProgramManager->ProgramId("CoreRender"),
                                      i3dProx,
                                      i3dDist,
                                      AtTela,
                                      LgTela,
                                      CampoVisao);
       }break;
       case IGL_PROJECTION_ORTHO:
       {
          execGL(IGL_SH_ORTHO,INSSH::pISHProgramManager->ProgramId("CoreRender"),
                                      i3dProx,
                                      i3dDist,
                                      AtTela,
                                      LgTela,
                                      CampoVisao);
       }break;
       default:
       {
          qWarning() << "Perspectiva de camera invalida!";
       }
    }
}
