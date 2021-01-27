/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :Exemplo de Utilização de Volumes                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef CISMEXEMPLO11_H
#define CISMEXEMPLO11_H

#include "ISM_Cenario.h"

class CISMExemplo11 : public CISMCenario
{
private:
    CI3DCamera         *pCam          ;//Camera principal de visualização
    CI3DLuz            *pLuzAmbiente  ;//Luz Ambiente
    CI3DCubo           *pSky          ;//SkyBox
    CI3DEsfera         *pEsfera01     ;//Esfera a ser desenhado
    CI3DEsfera         *pEsfera02     ;//Esfera a ser desenhado
    CI3DEsfera         *pEsfera03     ;//Esfera a ser desenhado
    CI3DCubo           *pCubo01       ;//Esfera a ser desenhado
    CI3DCubo           *pCubo02       ;//Esfera a ser desenhado
    int                 IdMatCubo     ,//Id do Material Cubo
                        IdMatEsfera   ,//Id do Material Esfera
                        IdMatSky      ;//Id do Material SkyBox

    float               direction;
    bool                colidiu;

    bool                japosicionou  ;//Flag informando se ja posicionou a camera

    bool SetIniPos    (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena (                                  );
    bool CriaMateriais(                                  );
    bool CriaObjetos  (                                  );
    bool Collision    (float pTimeElapsed                );

public:
     CISMExemplo11(QOpenGLContext   *pI3DContext);
     CISMExemplo11(QGLContext       *pI3DContext);
    ~CISMExemplo11(                             );

     bool Inicializa     (           );
     bool Render         (float pTimeElapsed);
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
};


#endif // CISMEXEMPLO11_H
