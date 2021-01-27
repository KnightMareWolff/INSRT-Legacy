/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_COR_H
#define IMA_COR_H
/************************************************************/
/************************************************************/
class CIMACor
{

private:

    float cor[4];

public:

    CIMACor();

    CIMACor(float kbcCorR ,
            float kbcCorG ,
            float kbcCorB ,
            float kbcCorA);

    void SetaCor(float kbcCorR ,
                 float kbcCorG ,
                 float kbcCorB ,
                 float kbcCorA );

    float PegaCorR();
    float PegaCorG();
    float PegaCorB();
    float PegaCorA();

    CIMACor PegaCor    ();
    float * PegaCorRGBA();
};

#endif // I3D_CORES_H
