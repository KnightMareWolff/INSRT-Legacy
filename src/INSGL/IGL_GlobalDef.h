#ifndef IGL_GLOBALDEF_H
#define IGL_GLOBALDEF_H

#include <QtGlobal>
#include <QtGui>
#include <QtOpenGL>

#include "../INSMT/INSMT.h"

/***********************************/
/*defines privados para mapeamento */
/*da versao openGL                 */
/***********************************/
#define IGL_OGL_V10 10
#define IGL_OGL_V11 11
#define IGL_OGL_V12 12
#define IGL_OGL_V13 13
#define IGL_OGL_V14 14
#define IGL_OGL_V15 15
#define IGL_OGL_V20 20
#define IGL_OGL_V21 21
#define IGL_OGL_V30 30
#define IGL_OGL_V31 31
#define IGL_OGL_V32 32
#define IGL_OGL_V33 33
#define IGL_OGL_V40 40
#define IGL_OGL_V41 41
#define IGL_OGL_V42 42
#define IGL_OGL_V43 43
#define IGL_OGL_V44 44
#define IGL_OGL_V45 45
#define IGL_OGL_C99 99

#define IGL_SH_BUFFERINIT        201
#define IGL_SH_DELBUFFERS        202
#define IGL_SH_RENDERBUFFERS     203
#define IGL_SH_PERSPECTIVE       204
#define IGL_SH_LOOKAT            205
#define IGL_SH_MODELMTX          206
#define IGL_SH_ENABLESTATES      207
#define IGL_SH_DISABLESTATES     208
#define IGL_SH_ACTIVETEXTURE     209
#define IGL_SH_DISACTTEXTURE     210
#define IGL_SH_UNIINT            211
#define IGL_SH_ORTHO             212
#define IGL_SH_LIGHT_POINT       213
#define IGL_SH_LIGHT_SPOT        214
#define IGL_SH_LIGHT_DIRECTIONAL 215
#define IGL_SH_MATERIAL          216
#define IGL_SH_UNIVEC3FLOAT      217
#define IGL_SH_UNIVEC4FLOAT      218
#define IGL_SH_ENABLE            219
#define IGL_SH_DISABLE           220
#define IGL_SH_COLORMATERIAL     221
#define IGL_SH_TEXTUREDMATERIAL  222
#define IGL_SH_MIXEDMATERIAL     223
#define IGL_SH_NMAPMATERIAL      224
#define IGL_SH_REFLMATERIAL      225
#define IGL_SH_REFRMATERIAL      226
#define IGL_SH_CUBEMAPMATERIAL   227
#define IGL_SH_FINISH            228
#define IGL_SH_DELTEXTURE        229

/*****************************************/
/*Defines Para aplicação:                */
/*Estes defines facilitam a tradução e   */
/*manutencao dos diversos tipos de dados */
/*comuns na programacao 3D e que podem   */
/*ser definidos em diversos drivers 3D   */
/*E NAO SOMENTE NA OPENGL diminuindo o   */
/*forte acoplamento representado por tais*/
/*estruturas no modelo de aplicacao 3D   */
/*****************************************/

#define IGL_RENDER_TRIANGLES            1
#define IGL_RENDER_TRIANGLE_STRIP       2
#define IGL_RENDER_TRIANGLE_FAN         3
#define IGL_RENDER_TRIANGLES_ARRAY      4
#define IGL_RENDER_TRIANGLE_STRIP_ARRAY 5
#define IGL_RENDER_TRIANGLE_FAN_ARRAY   6
#define IGL_RENDER_POLYGON              7
#define IGL_RENDER_QUADS                8
#define IGL_RENDER_POINTS               9

#define IGL_POLYGON_INDEXED             1
#define IGL_POLYGON_NONINDEXED          2
#define IGL_POLYGON_AUTOTEXTURE         3

#define IGL_PROJECTION_PERSP            1
#define IGL_PROJECTION_ORTHO            2

#define IGL_GEOMETRY_DINAMIC            0
#define IGL_GEOMETRY_STATIC             1
#define IGL_GEOMETRY_PHYSICS            3

#define IGL_MATERIAL_COLOR              1
#define IGL_MATERIAL_TEXTURE            2
#define IGL_MATERIAL_LIGHT              3
#define IGL_MATERIAL_MIXED              4
#define IGL_MATERIAL_NORMALMAP          5
#define IGL_MATERIAL_REFLEXIVE          6
#define IGL_MATERIAL_REFRATIVE          7
#define IGL_MATERIAL_RENDERTOTEXTURE    8
#define IGL_MATERIAL_CUBEMAP            9
//Windingmode esta sendo configurado junto com material em função Enable para facilitar
//Portanto deve seguir a mesma sequencia de Case.
#define IGL_WINMODE_CW                  10
#define IGL_WINMODE_CCW                 11

//No Modo de Construção escolhemos construção RightHand ou LeftHand
#define IGL_POLYMODE_LEFT         0
#define IGL_POLYMODE_RIGHT        1

#define IGL_MESH_CLASSIC          1
#define IGL_MESH_SKINNED          2
#define IGL_MESH_HEIGHTMAP        3

#define IGL_MODE_RENDER           1
#define IGL_MODE_SELECTION_PRIMI  2
#define IGL_MODE_SELECTION_MESHS  3
#define IGL_MODE_SELECTION_FACES  4

#define IGL_COR_R                 1
#define IGL_COR_G                 2
#define IGL_COR_B                 3
#define IGL_COR_A                 4

#define IGL_LIGHT_COLOR_AMB       1
#define IGL_LIGHT_COLOR_SPEC      2
#define IGL_LIGHT_COLOR_DIF       3

#define IGL_SHADING_MODE_FLAT     0
#define IGL_SHADING_MODE_SMOOTH   1
#define IGL_SHADING_MODE_DIFLAT   2
#define IGL_SHADING_MODE_DIFOTH   3
#define IGL_SHADING_MODE_NOONE    4

#define IGL_LIGHT_CHANNEL_01      0
#define IGL_LIGHT_CHANNEL_02      1
#define IGL_LIGHT_CHANNEL_03      2
#define IGL_LIGHT_CHANNEL_04      3
#define IGL_LIGHT_CHANNEL_05      4
#define IGL_LIGHT_CHANNEL_06      5
#define IGL_LIGHT_CHANNEL_07      6
#define IGL_LIGHT_CHANNEL_08      7
#define IGL_LIGHT_CHANNEL_09      8
#define IGL_LIGHT_CHANNEL_10      9

#define IGL_FACE_TRIANGLES        0
#define IGL_FACE_QUADS            1
#define IGL_FACE_POLYGON          2

#define IGL_FRAMEBUFFER_PIXEL     0

#define IGL_PLANO_TOPO            0
#define IGL_PLANO_ABAIXO          1
#define IGL_PLANO_ESQUERDO        2
#define IGL_PLANO_DIREITO         3
#define IGL_PLANO_FRENTE          4
#define IGL_PLANO_ATRAS           5

#define IGL_TRANSF_ROT            1
#define IGL_TRANSF_SCL            2
#define IGL_TRANSF_TRL            3

#define IGL_TEXTURE_CLAMP         1
#define IGL_TEXTURE_LINEAR        2
#define IGL_TEXTURE_GEN_ST        3
#define IGL_TEXTURE_CREATE        4
#define IGL_TEXTURE_PREP          5
#define IGL_TEXTURE_RENDER        6
#define IGL_TEXTURE_CUBEMAP       7


#define IGL_PAINEL_DEFAULT        1
#define IGL_PAINEL_FACES          2
#define IGL_PAINEL_RELEVO         3

struct IGLVertexBuffer
{
    CIMTVetor  position;
    CIMTVetor2 texCoord;
    CIMTVetor  normal;
    CIMTVetor  smooth;
    CIMTVetor  tangente;
    CIMTVetor  bitangente;
};

struct FeedBackData
{
    CIMTVetor  position;
};

static const char * tf_varyings[] =
{
  "f_position"
};

#endif // IGL_GLOBALDEF_H
