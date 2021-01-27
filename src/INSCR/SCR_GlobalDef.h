#ifndef SCR_GLOBALDEF_H
#define SCR_GLOBALDEF_H

#include <QtGui>
#include <QtOpenGL>
/**********************/
/*Includes da ISM     */
/**********************/
#include "../INSMT/INSMT.h"
/**********************/
/*Includes da ISM     */
/**********************/
#include "../INSSM/INSSM.h"
/**********************/
/*Includes da IUT     */
/**********************/
#include "../INSUT/INSUT.h"
/**********************/
/*Includes da IUT     */
/**********************/
#include "../INSMA/INSMA.h"
/**********************/
/*Includes da ICL     */
/**********************/
#include "../INSCL/INSCL.h"

/**************************/
/*Includes da Lua e Tolua */
/**************************/
extern "C" {
#include <../../extools/lua522/lua.h>
#include <../../extools/lua522/lualib.h>
#include <../../extools/lua522/lauxlib.h>
}

#include <../../extools/tolua/tolua.h>

typedef struct func
{
    string Funcao;
    int     tecla ;
}INS_FUNC;

typedef struct modelpipe
{
    string    Nome       ;
    CIMTVetor pos        ;
    string    NomeTextura;
}INS_MODEL_PIPE;

#endif // SCR_GLOBALDEF_H
