/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_GLOBALDEF_H
#define I3D_GLOBALDEF_H

#include <QtGui>
#include <QtOpenGL>
#include <QOpenGLVersionProfile>
#include <QOpenGLFunctions_1_0>
#include <QOpenGLFunctions_1_1>
#include <QOpenGLFunctions_1_2>
#include <QOpenGLFunctions_1_3>
#include <QOpenGLFunctions_1_4>
#include <QOpenGLFunctions_1_5>
#include <QOpenGLFunctions_2_0>
#include <QOpenGLFunctions_2_1>
#include <qopenglfunctions_3_0>
#include <qopenglfunctions_3_1>
#include <qopenglfunctions_3_2_core>
#include <qopenglfunctions_3_2_compatibility>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLFunctions_3_3_Compatibility>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLFunctions_4_0_Compatibility>
#include <QOpenGLFunctions_4_1_Core>
#include <QOpenGLFunctions_4_1_Compatibility>
#include <QOpenGLFunctions_4_2_Core>
#include <QOpenGLFunctions_4_2_Compatibility>
#include <QOpenGLFunctions_4_3_Core>
#include <QOpenGLFunctions_4_3_Compatibility>

#include "../INSSH/INSSH.h"
#include "../INSMT/INSMT.h"
#include "../INSGL/INSGL.h"
#include "../INSUT/INSUT.h"
#include "../INSMA/INSMA.h"
#include "../INSCL/INSCL.h"
#include "../INSVK/INSVK.h"
#include <time.h>

using namespace std;

//Defines Arvore BSP
#define BLOCO_MEMORIA     100
#define BSP_TYPE_NONSPLIT   0
#define BSP_TYPE_SPLIT      1
//-----------------------------------------------------------------------------
// Compilation Pre-Processor Flags
//-----------------------------------------------------------------------------
#define BSP_NEWSPLITNODES       0       // 1 = New fragments should !!NOT!! inherit UsedAsSplitter state
#define BSP_SHARENODES          1       // 1 = All OnPlane polys should be considered as one node.

// Ensure shared nodes is enabled (just so I don't forget ;)
#if ( BSP_SHARENODES != 1 )
    #error BSP_SHARENODES precisa ser 1!
#endif

//Folha BSP Defines
#define BLOCO_MEMORIA_FOLHA  100

//portal defines
#define FRONT_OWNER         0
#define BACK_OWNER          1
#define NO_OWNER            2

#endif // I3D_GLOBALDEF_H
