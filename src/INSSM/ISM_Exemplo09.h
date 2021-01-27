/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :Exemplo de Utilização de Fisica                            */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef CISMEXEMPLO09_H
#define CISMEXEMPLO09_H

#include "ISM_Cenario.h"
#include "IUT_Lista.h"

class CISMExemplo09 : public CISMCenario
{
private:
    CI3DCamera                      *pCam          ;//Camera principal de visualização
    CI3DLuz                         *pLuzAmbiente  ;//Luz Ambiente
    CIMTVetor                        PosIni        ;
    CIUTLista                        pListaCubos   ;//Lista de Cubos a ser preenchida
    CIUTFilaPrioridade               pInputPipe    ;//Base de Triggers para INPUT
    CIUTFilaPrioridade               pUpdatePipe   ;//Base de Triggers para UPDATE
    CIUTFilaPrioridade               pRenderPipe   ;//Base de Triggers para RENDER
    CIUTFilaPrioridade               pInicioPipe   ;//Base de Triggers para INIT



    bool                japosicionou  ;//Flag informando se ja posicionou a camera

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool UpdatePipeline(                                  );
    bool InitPipeline  (                                  );
    bool InputPipeline (                                  );

public:
     CISMExemplo09(QOpenGLContext   *pI3DContext);
     CISMExemplo09(QGLContext       *pI3DContext);
    ~CISMExemplo09(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );

     /******************************************************/
     /*Rotinas para controle de Pipeline de processamento  */
     /*Obs:.As mesmas serão implementadas virtualmente     */
     /*Na classe Base para utilização pela camada de       */
     /*apresentação Também.                                */
     /******************************************************/
     int  AddTrigger         (int      pTipoTrigger   ,
                              QString  pNomeTrigger   ,
                              QString  pFuncao        );

     bool AddParametroTrigger(int      pTipoTrigger            ,
                              int      pIdTrigger              ,
                              CIUTParametroTrigger  pParametro);

     bool AddParametroTrigger(int      pTipoTrigger            ,
                              QString  pNomeTrigger            ,
                              CIUTParametroTrigger  pParametro);
};

#endif // CISMEXEMPLO09_H
