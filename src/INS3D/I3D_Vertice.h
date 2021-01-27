/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_VERTICE_H
#define I3D_VERTICE_H

#include "I3D_GlobalDef.h"


/************************************************************/
/************************************************************/
class CI3DVertice : public CIMTVetor
{

public:

    CIMTVetor    I3D_SmoothNormal      ;
    CIMTVetor    I3D_PlanarNormal      ;
    CIMTVetor    I3D_Tangente          ;
    CIMTVetor    I3D_BiTangente        ;
    float        I3D_CoordTexturaU     ;
    float        I3D_CoordTexturaV     ;
    float        I3D_CoordDetTextU     ;
    float        I3D_CoordDetTextV     ;
    float        I3D_CoordLtmTextU     ;
    float        I3D_CoordLtmTextV     ;
    int          Status                ;

public:

    ~CI3DVertice             (                             );
     CI3DVertice             (                             );
     CI3DVertice             (const CI3DVertice &i3dVertice);
     CI3DVertice             (float i3dCoordX    ,
                              float i3dCoordY    ,
                              float i3dCoordZ   );
     CI3DVertice             (CIMTVetor& i3dVetor);
     CI3DVertice             (float i3dCoordX    ,
                              float i3dCoordY    ,
                              float i3dCoordZ    ,
                              float i3dTexCoordU ,
                              float i3dTexCoordV);
     bool         Igual      (CI3DVertice i3dVertice);
     CI3DVertice& operator=  (const CI3DVertice& vertice );
};


#endif // I3D_VERTICE_H
