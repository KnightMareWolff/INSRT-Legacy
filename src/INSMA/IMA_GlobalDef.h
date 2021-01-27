/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMA_GLOBALDEF_H
#define IMA_GLOBALDEF_H

#include <QString>

#include "../INSGL/INSGL.h"
#include "../INSUT/INSUT.h"
#include "../INSMD/INSMD.h"
#include <time.h>

using namespace std;
// OpenCV includes
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
using namespace cv;

class INSMA;

#define IMA_ADD_MATERIAL  100
#define IMA_ADD_TEXTURA   101
#define IMA_PREP_MATERIAL 102

#define IMA_LAYER_CHN_DETAIL 0
#define IMA_LAYER_CHN_NMAP   1
#define IMA_LAYER_CHN_CBMAP  2
#define IMA_LAYER_CHN_LTMAP  3
#define IMA_LAYER_CHN_CLMAP  4

#endif // IMA_GLOBALDEF

