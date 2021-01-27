/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_LUZ_H
#define I3D_LUZ_H

#include "I3D_GlobalDef.h"
#include "IMA_Cor.h"

enum I3DTIPOLUZ
{
    LIGHTTYPE_POINT,
    LIGHTTYPE_SPOT,
    LIGHTTYPE_DIRECTIONAL,
    LIGHTTYPE_AMBIENTE,
};

/************************************************************/
/************************************************************/
class CI3DLuz : public INSGL
{

private:

    I3DTIPOLUZ   tipo;
    bool		 ligada;
    int          canal;

    CIMTVetor4    pos;
    CIMTVetor4    dir;

    CIMACor       I3D_CorDifusa  ;
    CIMACor       I3D_CorAmbiente;
    CIMACor       I3D_CorSpecular;

    float Expoente;
    float CutOff;

    float AtenuacaoConstante;
    float AtenuacaoLinear;
    float AtenuacaoQuadratica;

public:
    CI3DLuz(I3DTIPOLUZ m_tipo  ){tipo  = m_tipo ;}
    CI3DLuz(int        m_canal ){canal = m_canal;}
    CI3DLuz                  ();
    CIMACor PegaCorDifusa    ();
    CIMACor PegaCorAmbiente  ();
    CIMACor PegaCorSpecular  ();
    float   PegaAttQuadratica();
    float   PegaAttConstante ();
    float   PegaAttLinear    ();
    float   PegaExpoente     (){return Expoente;}
    float   PegaCutOff       (){return CutOff;}
    CIMTVetor PegaDir        ();
    CIMTVetor PegaPos        ();
    int     PegaTipo         (){return tipo;}
    void    SetaCorDifusa    (CIMACor i3dCorDifusa  );
    void    SetaCorAmbiente  (CIMACor i3dCorAmbiente);
    void    SetaCorSpecular  (CIMACor i3dCorSpecular);
    void    SetaPos          (CIMTVetor        m_pos);
    void    SetaDir          (CIMTVetor        m_dir);

    void    ConfiguraSpot   (float Exp         ,
                             float Cut);

    void    SetaAtenuacao   (float Constant  ,
                             float Linear    ,
                             float Quadratic);

    void    SetaTipo        (I3DTIPOLUZ m_tipo){tipo = m_tipo;}

    void    Prepara         (int pI3D_ProgramId,int   Indice   );
    void    Atualiza        (int pI3D_ProgramId,int   Indice   );

    void    Liga();
    void    Desliga();
    bool    EstaLigada();

private:

    void PreparaLuzPonto      (int pI3D_ProgramId,GLenum ThisGLLight);
    void PreparaLuzSpot       (int pI3D_ProgramId,GLenum ThisGLLight);
    void PreparaLuzDirectional(int pI3D_ProgramId,GLenum ThisGLLight);

};

inline void CI3DLuz::Liga()
{
    ligada = true;
}

inline void CI3DLuz::Desliga()
{
    ligada = false;
}

#endif // I3D_LUZ_H
