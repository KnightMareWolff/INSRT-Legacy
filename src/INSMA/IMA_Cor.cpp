/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMA_GlobalDef.h"
#include "IMA_Cor.h"


/************************************************************/
/*Nome do Método      : CIMACor()
/*
/*Objetivo            : Construtor Padrão da classe de Cor
/************************************************************/
CIMACor::CIMACor()
{
    cor[0]  =0.0f;
    cor[1]  =0.0f;
    cor[2]  =0.0f;
    cor[3]  =1.0f;
}

/************************************************************/
/*Nome do Método      : CIMACor()
/*
/*Objetivo            : Construtor Alternativo da classe de
/*                      Cor
/************************************************************/
CIMACor::CIMACor(float i3dCorR ,
                 float i3dCorG ,
                 float i3dCorB ,
                 float i3dCorA )
{
    cor[0]  = i3dCorR;
    cor[1]  = i3dCorG;
    cor[2]  = i3dCorB;
    cor[3]  = i3dCorA;
}



/************************************************************/
/*Nome do Método      : SetaCor()
/*
/*Objetivo            : Altera a cor atual.
/*
/************************************************************/
void CIMACor::SetaCor(float i3dCorR ,
                      float i3dCorG ,
                      float i3dCorB ,
                      float i3dCorA )
{
    cor[0]  = i3dCorR;
    cor[1]  = i3dCorG;
    cor[2]  = i3dCorB;
    cor[3]  = i3dCorA;
}

/************************************************************/
/*Nome do Método      : PegaCor()
/*
/*Objetivo            : Retorna Uma Cópia desta Cor.
/*
/************************************************************/
CIMACor CIMACor::PegaCor()
{
    return *this;
}

/************************************************************/
/*Nome do Método      : PegaCor()
/*
/*Objetivo            : Retorna Uma Cópia desta Cor.
/*
/************************************************************/
float * CIMACor::PegaCorRGBA()
{
    return cor;
}

/************************************************************/
/*Nome do Método      : PegaCor()
/*
/*Objetivo            : Retorna Uma Cópia desta Cor.
/*
/************************************************************/
float CIMACor::PegaCorR()
{
    return cor[0];
}


/************************************************************/
/*Nome do Método      : PegaCor()
/*
/*Objetivo            : Retorna Uma Cópia desta Cor.
/*
/************************************************************/
float CIMACor::PegaCorG()
{
    return cor[1];
}


/************************************************************/
/*Nome do Método      : PegaCor()
/*
/*Objetivo            : Retorna Uma Cópia desta Cor.
/*
/************************************************************/
float CIMACor::PegaCorB()
{
    return cor[2];
}


/************************************************************/
/*Nome do Método      : PegaCor()
/*
/*Objetivo            : Retorna Uma Cópia desta Cor.
/*
/************************************************************/
float CIMACor::PegaCorA()
{
    return cor[3];
}

