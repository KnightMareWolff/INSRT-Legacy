#ifndef CISMEDITORPROJECT_H
#define CISMEDITORPROJECT_H
#include "ISM_Cenario.h"

class CISMEditorProject : public CISMCenario
{
private:
    CI3DCamera         *pCam                 ;//Camera principal de visualização
    CI3DCubo           *pCubo                ;//Cubo a ser desenhado
    bool                japosicionou         ;//Flag informando se ja posicionou a camera

    bool SetIniPos     (CI3DCamera *pCam, CIMTVetor centro);
    bool AtualizaCena  (                                  );

public:
     CISMEditorProject(QOpenGLContext   *pI3DContext);
     CISMEditorProject(QGLContext       *pI3DContext);
    ~CISMEditorProject(                             );

     /*******************************************/
     /*Metodos Polimorficos herdados do Cenario */
     /*******************************************/
     bool Inicializa     (           );
     bool Render         (           );
     bool Resize         (int w,int h);
     bool MapeiaMouse    (int x,int y);
     bool MoverCamera    (int pAction);
     bool InputKey       (int pKey   );
     /*******************************************/
     /*Metodos Especificos do Exemplo           */
     /*******************************************/
     bool RodarCubo(CIMTVetor EixoRotacao);
};


#endif // CISMEDITORPROJECT_H
