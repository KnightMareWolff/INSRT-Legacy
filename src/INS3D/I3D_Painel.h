/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef I3D_PAINEL_H
#define I3D_PAINEL_H

#include "I3D_Primitivo.h"

class CI3DPainel : public CI3DPrimitivo
{
public:
    CI3DPainel(                );
    CI3DPainel(int pWindingMode);

    bool SetaTamanho (int pAltura    ,int pLargura );

protected:
    void Build              (           );
    void BuildTextureCoordPF(           );
    void BuildTextureCoordSH(           );

    int    I3D_Altura            ;
    int    I3D_Largura           ;
    int    I3D_TamQuad           ;
    bool   bGeometriaInicializada;
    bool   bPainelInicializado   ;
    int    iTpPainel             ;
};

#endif // I3D_PAINEL_H
