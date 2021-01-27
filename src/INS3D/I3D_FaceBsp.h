/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_FACEBSP_H
#define I3D_FACEBSP_H

#include "I3D_Face.h"

class CI3DFaceBsp : public CI3DFace
{

public:

    CI3DFaceBsp		*Proximo       ;
    bool		     Divisor       ;
    long             Plano         ;
    long             IndiceOriginal;
    bool             Deleted       ;// Face foi "virtualmente" deletada
    unsigned long    ChildSplit[2] ;// Durante CSG, armazena os dois filhos resultantes
    unsigned long    FrameRendered ;// quando ocorreu ultima renderização


public:

    /******************************************/
    /*Construtores                            */
    /******************************************/
    CI3DFaceBsp ();
    CI3DFaceBsp (const CI3DFace * kbcFace);
   ~CI3DFaceBsp (){}

    virtual bool Divide(const CIMTPlano& kbcPlano  ,
                              CI3DFaceBsp *DivisorFrente ,
                              CI3DFaceBsp *DivisorAtras  );

};

#endif // I3D_FACEBSP_H
