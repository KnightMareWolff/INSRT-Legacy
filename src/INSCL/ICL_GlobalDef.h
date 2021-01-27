#ifndef ICL_GLOBALDEF
#define ICL_GLOBALDEF

#include <QtGlobal>

#include "../INSMT/INSMT.h"
#include "../INSUT/INSUT.h"
#include "../INSGL/INSGL.h"

//Mapeia OpenCL Para Windows
#ifdef Q_OS_WIN
   #include <Windows.h>
   #include <wingdi.h>
   #include <CL/cl_gl.h>
   #include <QtPlatformHeaders/QWGLNativeContext>
#endif

using namespace std;

//define para testes
#define DATA_SIZE 1048576

//Indicadores de Execução(Especificam qual o Kernel a ser executado no device)
#define ICL_EXEC_UPDATE_GL_CTXT  201
#define ICL_EXEC_TRANSFORM_GL    202

//Indicadores de Plataforma(Futuramente será usado para direcionar componentes)
#define ICL_PLAT_AMD             1
#define ICL_PLAT_INTEL           2
#define ICL_PLAT_NVIDIA          3

//Indicadores de Uso especifico da Plataforma(Ex:. Graficos,Computação Geral)
#define ICL_PLAT_USAGE_DRAWING   1
#define ICL_PLAT_USAGE_COMPUTE   2

//Indicadores de Device(Futuramente será usado para direcionar devices especificos)
#define ICL_DEV_GPU              1
#define ICL_DEV_CPU              2
#define ICL_DEV_ACEL             3

//Indicadores de componente consumidor(identifica a origem da chamada)
#define ICL_COMP_INS3D             1
#define ICL_COMP_INSCG             2
#define ICL_COMP_INSCR             3
#define ICL_COMP_INSGL             4
#define ICL_COMP_INSGO             5
#define ICL_COMP_INSGZ             6
#define ICL_COMP_INSIA             7
#define ICL_COMP_INSMA             8
#define ICL_COMP_INSMD             9
#define ICL_COMP_INSMT             10
#define ICL_COMP_INSPH             11
#define ICL_COMP_INSPL             12
#define ICL_COMP_INSSH             13
#define ICL_COMP_INSSL             14
#define ICL_COMP_INSSM             15
#define ICL_COMP_INSUT             16

#endif // ICL_GLOBALDEF

