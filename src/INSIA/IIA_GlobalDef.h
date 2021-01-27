/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#ifndef IIA_GLOBALDEF_H
#define IIA_GLOBALDEF_H

#include <math.h>

#define NULL            0
#define EPSILON         0.001f   //Valor de tolerancia
#define FUZZY           0.00001f //Valor de Tolerancia
#define PI              3.1415926535897932    //PI
#define TWOPI           6.283185308
#define PiOver180		1.74532925199433E-002f
#define PiUnder180		5.72957795130823E+001f
#define SMALL_NUMBER	0.00001
#define LARGE_NUMBER	1E20
#define SQR(x) ((x) * (x))
#define MAX(a,b) ((a < b) ? (b) : (a))
#define DEG2RAD(a) (((a) * M_PI) / 180.0f)
#define MIN( a, b ) ((a < b)?(a):(b))
#define BLOQUEADO 3000
#define INT_MAX   2147483647

#endif // GLOBALDEF_H
