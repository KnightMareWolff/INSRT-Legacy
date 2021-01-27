#ifndef ISM_GLOBALDEF_H
#define ISM_GLOBALDEF_H

#include "../INSMD/INSMD.h"
#include "../INSSH/INSSH.h"
#include "../INS3D/INS3D.h"
#include "../INSGZ/INSGZ.h"
#include "../INSUT/INSUT.h"
#include "../INSGO/INSGO.h"
#include "../INSMA/INSMA.h"
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

/**************************************/
/*INS Input Actions                   */
/**************************************/
#define ISM_INPUT_MOVE_FOWARD     1
#define ISM_INPUT_MOVE_BACKWARD   2
#define ISM_INPUT_MOVE_STRAFELFT  3
#define ISM_INPUT_MOVE_STRAFERGT  4
#define ISM_INPUT_PLAY_SOUND      5
#define ISM_INPUT_ROT_X           6
#define ISM_INPUT_ROT_Y           7
#define ISM_INPUT_ROT_Z           8

#define ISM_ESC_KEY  0
#define ISM_A_KEY    1
#define ISM_B_KEY    2
#define ISM_C_KEY    3
#define ISM_D_KEY    4
#define ISM_E_KEY    5
#define ISM_F_KEY    6
#define ISM_G_KEY    7
#define ISM_H_KEY    8
#define ISM_I_KEY    9
#define ISM_J_KEY    10
#define ISM_K_KEY    11
#define ISM_L_KEY    12
#define ISM_M_KEY    13
#define ISM_N_KEY    14
#define ISM_O_KEY    15
#define ISM_P_KEY    16
#define ISM_Q_KEY    17
#define ISM_R_KEY    18
#define ISM_S_KEY    19
#define ISM_T_KEY    20
#define ISM_U_KEY    21
#define ISM_V_KEY    22
#define ISM_W_KEY    23
#define ISM_X_KEY    24
#define ISM_Y_KEY    25
#define ISM_Z_KEY    26


#endif // ISM_GLOBALDEF_H
