/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMT_GlobalDef.h"
#include "IMT_Plano.h"

/************************************************************/
/************************************************************/
CIMTPlano::CIMTPlano()
{
    IMT_NormalPlano      = CIMTVetor( 0.0f, 0.0f, 0.0f );
    IMT_DistanciaPlano    = 0.0f;
}

/************************************************************/
/*Nome do Método      : CIMTPlano()                         */
/*                                                          */
/*Objetivo            : Construtor Alternativo da classe    */
/*                      CIMTPlano.                          */
/*                      Seu objetivo é possibilitar criar   */
/*                      um plano tendo em mãos a distância ,*/
/*                      e a normal.                         */
/************************************************************/
CIMTPlano::CIMTPlano( const CIMTVetor& vecNormal, float fDistance )
{
    IMT_NormalPlano       = vecNormal; IMT_NormalPlano.Normalizar();
    IMT_DistanciaPlano    = fDistance;
}

/**************************************************************/
/*Nome do Método      : CIMTPlano()                           */
/*                                                            */
/*Objetivo            : Construtor Alternativo da classe      */
/*                      CIMTPlano.                            */
/*                      Seu objetivo é possibilitar criar     */
/*                      um plano tendo em mãos a posicao de , */
/*                      um vertice qualquer que esteja contido*/
/*                      em um poligono qualquer e sua normal. */
/**************************************************************/
CIMTPlano::CIMTPlano( const CIMTVetor& vecNormal, const CIMTVetor& vecPointOnPlane )
{
    IMT_NormalPlano       = vecNormal;

    IMT_NormalPlano.Normalizar();

    IMT_DistanciaPlano    = vecPointOnPlane.ProdutoEscalar(IMT_NormalPlano);
}

/*************************************************************/
/*Nome do Método      : PegaPtoNoPlano()                     */
/*                                                           */
/*Objetivo            : Retorna um ponto que esteja no plano.*/
/*************************************************************/
CIMTVetor CIMTPlano::PegaPtoNoPlano( ) const
{
    return IMT_NormalPlano * IMT_DistanciaPlano;
}

/********************************************************************/
/*Nome do Método      : ClassificaPonto()                           */
/*                                                                  */
/*Objetivo            : Classifica um ponto passado com relação     */
/*                      a este plano.                               */
/*                      Ele pode estar:                             */
/*                      Na frente , Atrás ou estar no mesmo plano   */
/*                                                                  */
/*Obs:                  Opcionalmente pode-se passar o endereço de  */
/*                      uma variável float caso queira obter não a- */
/*                      penas a posição com relação a este plano mas*/
/*                      também a que distância ele fica do plano... */
/********************************************************************/
CLASSIFICACAO CIMTPlano::ClassificaPonto( const CIMTVetor& vecPoint, float * Dist ) const
{
    float result	= vecPoint.ProdutoEscalar(IMT_NormalPlano) - IMT_DistanciaPlano;
    if (Dist) *Dist = result;
    if ( result < -EPSILON ) return ATRAS;
    if ( result > EPSILON  ) return FRENTE;
    return COPLANAR;
}

/********************************************************************/
/*Nome do Método      : ClassificaPoligono()                        */
/*                                                                  */
/*Objetivo            : Classifica um poligono passado com relação  */
/*                      a este plano.                               */
/*                      Ele pode estar:                             */
/*                      Na frente , Atrás ou estar no mesmo plano   */
/********************************************************************/
CLASSIFICACAO CIMTPlano::ClassificaPoligono( const CIMTVetor pVertices[], unsigned long VertexCount, unsigned long VertexStride ) const
{
    unsigned char  *pVerts  = (unsigned char*)pVertices;
    unsigned long   Infront = 0, Behind = 0, OnPlane=0;
    float	        result  = 0;


    for ( unsigned long i = 0; i < VertexCount; i++, pVerts += VertexStride )
    {

        result = (*(CIMTVetor*)pVerts).ProdutoEscalar( IMT_NormalPlano ) - IMT_DistanciaPlano;

        if (result > EPSILON )
        {
            //WDW
            Infront++;
        }
        else if (result < -EPSILON)
        {
            //WDW
            Behind++;
        }
        else
        {
            OnPlane++;
            Infront++;
            Behind++;
        }
    }


    if ( OnPlane == VertexCount ) return COPLANAR;
    if ( Behind  == VertexCount ) return ATRAS;
    if ( Infront == VertexCount ) return FRENTE;
    return CRUZANDO;
}


/*****************************************************************/
/*Nome do Método      : ClassificaEsfera()                       */
/*                                                               */
/*Objetivo            : Classifica uma esfera passada com relação*/
/*                      a este plano.                            */
/*                      Ele pode estar:                          */
/*                      Na frente , Atrás ...etc....             */
/*****************************************************************/
CLASSIFICACAO CIMTPlano::ClassificaEsfera(const CIMTVetor& i3dPosicao,float i3dRaio , float *i3dDistancia) const
{
    float d = -i3dPosicao.ProdutoEscalar(IMT_NormalPlano);

    *i3dDistancia = (IMT_NormalPlano.x * i3dPosicao.x +
                     IMT_NormalPlano.y * i3dPosicao.y +
                     IMT_NormalPlano.z * i3dPosicao.z +
                     d               );


    if(fabsf(*i3dDistancia) < i3dRaio)
        return CRUZANDO;

    else if(*i3dDistancia >= i3dRaio)
        return FRENTE;

    return ATRAS;
}

/**********************************************************************/
/*Nome do Método      : CruzamentoRaio()                              */
/*                                                                    */
/*Objetivo            : Determina se este plano cruza uma deter-      */
/*                      minada reta ou não.                           */
/*                      opcionalmente pode-se passar uma variavel     */
/*                      float para se obter a porcentagem em que      */
/*                      ocorre a interseçao , ou seja um multipli     */
/*                      cador que pode ser utilizado em cjto com      */
/*                      outras variaveis para calculos em poligonos.  */
/*                      e também um vetor onde pode se obter o ponto  */
/*                      onde a intersecção ocorre...                  */
/**********************************************************************/
bool CIMTPlano::CruzamentoRaio( const CIMTVetor& RayStart,  const CIMTVetor& RayEnd, CIMTVetor& Intersection, float * pPercentage ) const
{
    CIMTVetor    Direction, L1, Point;
    float       linelength, dist_from_plane;
    float       Percent;

    Direction.x = RayEnd.x - RayStart.x;
    Direction.y = RayEnd.y - RayStart.y;
    Direction.z = RayEnd.z - RayStart.z;

    linelength = Direction.ProdutoEscalar(IMT_NormalPlano);
    if (fabsf( linelength ) < EPSILON ) return false;

    Point = PegaPtoNoPlano();
    L1.x = Point.x - RayStart.x;
    L1.y = Point.y - RayStart.y;
    L1.z = Point.z - RayStart.z;

    dist_from_plane = L1.ProdutoEscalar(IMT_NormalPlano);

    Percent = dist_from_plane / linelength;

    if ( Percent < 0.0f || Percent > 1.0f ) return false;

    Intersection.x = RayStart.x + Direction.x * Percent;
    Intersection.y = RayStart.y + Direction.y * Percent;
    Intersection.z = RayStart.z + Direction.z * Percent;

    if( pPercentage ) *pPercentage = Percent;

    return true;
}

/**********************************************************************/
/*Nome do Método      : CruzamentoRaio()                              */
/*                                                                    */
/*Objetivo            : Determina se este plano cruza uma deter-      */
/*                      minada reta ou não.                           */
/*                      opcionalmente pode-se passar uma variavel     */
/*                      float para se obter a porcentagem em que      */
/*                      ocorre a interseçao , ou seja um multipli     */
/*                      cador que pode ser utilizado em cjto com      */
/*                      outras variaveis para calculos em poligonos.  */
/*                      e também um vetor onde pode se obter o ponto  */
/*                      onde a intersecção ocorre...                  */
/**********************************************************************/
bool CIMTPlano::CruzamentoRaio( const CIMTVetor& RayStart,  const CIMTVetor& RayDir, float * Intervalo ) const
{
    float ProjRayLength = RayDir.ProdutoEscalar(IMT_NormalPlano);

    if ( ProjRayLength > -1e-5f ) return false;


    float Distance = CIMTVetor(RayStart - PegaPtoNoPlano()).ProdutoEscalar(IMT_NormalPlano);

    *Intervalo = Distance / -ProjRayLength;

    if ( *Intervalo < 0.0f || *Intervalo > 1.0f ) return false;

    return true;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CLASSIFICACAO CIMTPlano::ClassificaLinha( const CIMTVetor& Point1, const CIMTVetor& Point2 ) const
{
    int		Infront = 0, Behind = 0, OnPlane=0;
    float	result  = 0;

    result = Point1.ProdutoEscalar( IMT_NormalPlano ) - IMT_DistanciaPlano;

    if (result > EPSILON ) {
        Infront++;
    } else if (result < -EPSILON) {
        Behind++;
    } else {
        OnPlane++;
        Infront++;
        Behind++;
    }

    result = Point2.ProdutoEscalar( IMT_NormalPlano ) - IMT_DistanciaPlano;

    if (result > EPSILON ) {
        Infront++;
    } else if (result < -EPSILON) {
        Behind++;
    } else {
        OnPlane++;
        Infront++;
        Behind++;
    }

    if ( OnPlane == 2 ) return COPLANAR;
    if ( Behind  == 2 ) return ATRAS;
    if ( Infront == 2 ) return FRENTE;
    return CRUZANDO;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CIMTPlano::MesmoLado( const CIMTVetor& vecNormal ) const
{
    if ( fabsf((IMT_NormalPlano.x - vecNormal.x) +
               (IMT_NormalPlano.y - vecNormal.y) +
               (IMT_NormalPlano.z - vecNormal.z)) < 0.1f) return true;

    return false;
}
