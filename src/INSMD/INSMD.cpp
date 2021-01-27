#include "INSMD.h"

//Inicialização da Instância Estatica
CIMDSistema* INSMDInterface::pINSMDStaticInterface=NULL;

static float  IMD_FATOR_DISTANCIA    =1.0f;    //Fator de Distancia(m/s)
static float  IMD_FATOR_DISTANCIAMIN =0.5f;    //Distancia Minima do som
static float  IMD_FATOR_DISTANCIAMAX =5000.0f; //Distancia Maxima do som
static float  IMD_FATOR_SCALADOPPLER =1.0f;    //Fator de Distancia(m/s)
static float  IMD_FATOR_SCALAROLLOFF =1.0f;    //Distancia Minima do som

unsigned int  IMDVersao;
void         *IMDDadosExtraDriver = 0;

INSMDInterface::INSMDInterface()
{
    pINSMDStaticInterface= new CIMDSistema();
}

INSMDInterface::~INSMDInterface()
{
}

bool INSMDInterface::SetaFatores3D(float pFatorDoppler,float pFatorDistancia,float pFatorRolloff)
{
    return true;
}

bool INSMDInterface::SetaDistancias(float pDistMin,float pDistMax)
{
    IMD_FATOR_DISTANCIAMIN = pDistMin;
    IMD_FATOR_DISTANCIAMAX = pDistMax;
    return true;
}

bool INSMDInterface::Atualiza()
{
    return true;
}
