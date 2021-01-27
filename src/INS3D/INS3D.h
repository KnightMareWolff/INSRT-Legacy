/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef INS3D_H
#define INS3D_H

#include "I3D_GlobalDef.h"
#include "I3D_Camera.h"
#include "I3D_Face.h"
#include "I3D_Luz.h"
#include "I3D_Mesh.h"
#include "I3D_Poligono.h"
#include "I3D_Vertice.h"
#include "I3D_Primitivo.h"
#include "I3D_Cubo.h"
#include "I3D_Cilindro.h"
#include "I3D_Esfera.h"
#include "I3D_Modelo.h"
#include "I3D_ModeloHierarquico.h"
#include "I3D_ModeloLowPoly.h"
#include "I3D_Painel.h"
#include "I3D_PainelHeightMap.h"
#include "I3D_Fonte.h"
#include "I3D_Texto.h"
#include "I3D_NoBsp.h"
#include "I3D_FaceBsp.h"
#include "I3D_FolhaBsp.h"
#include "I3D_ArvoreBsp.h"
#include "I3D_ProcessadorHSR.h"
#include "I3D_ProcessadorCSG.h"
#include "I3D_ProcessadorPRT.h"
#include "I3D_ProcessadorRON.h"
#include "I3D_ProcessadorPVS.h"
#include "I3D_LightMap.h"

class INS3D
{

public:
    INS3D(QOpenGLContext *context);
    INS3D(QGLContext     *context);

    void        Enable         (int ProgramId,int iState                             );
    void        Disable        (int ProgramId,int iState                             );
    void        EnableStates   (                                                     );
    void        DisableStates  (                                                     );
    void        CriaFenceSync  (GLsync &pI3D_GLSync                                  );
    void        WaitFenceSync  (GLsync  pI3D_GLSync                                  );
    void        UpdateHardDC   (                                                     );
    bool        ReadPixels     (int x, int y, GLchar *res                            );
    bool        CalculaPVMatriz(CIMTMatriz pI3D_MatrizModel,CIMTMatriz &pIMT_PVMatriz);

private:
    INSGL          *pINSGLPlatInterface;//Interface com a placa de Video - OpenGL
    INSMA          *pINSMAPlatInterface;//Interface com o componente de Materiais e Texturas
    INSSH          *pINSSHPlatInterface;//Interface com o componente de Shaders
    INSCLInterface *pINSCLPlatInterface;//Interface de Otimização em Hardware
    INSVKInterface *pINSVKPlatInterface;//Interface Vulkan

    bool bI3DSuportaShaders       ,
         bI3DSuportaVertexShader  ,
         bI3DSuportaFragmentShader,
         bI3DSuportaTessCtrlShader,
         bI3DSuportaTessEvalShader,
         bI3DSuportaGeometryShader,
         bI3DSuportaComputeShader ,
         bI3DSuportaFeedback      ;
};

#endif // INS3D_H
