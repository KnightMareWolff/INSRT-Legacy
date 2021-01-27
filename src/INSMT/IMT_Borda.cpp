/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMT_GlobalDef.h"
#include "IMT_Borda.h"
#include "IMT_Plano.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBorda::CIMTBorda( )
{
    Limpa();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBorda::CIMTBorda( const CIMTVetor& vecMin, const CIMTVetor& vecMax )
{
    IMT_MinVetorBorda = vecMin;
    IMT_MaxVetorBorda = vecMax;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBorda::CIMTBorda( float xIMT_MinVetorBorda, float yIMT_MinVetorBorda, float zIMT_MinVetorBorda, float xIMT_MaxVetorBorda, float yIMT_MaxVetorBorda, float zIMT_MaxVetorBorda )
{
    IMT_MinVetorBorda = CIMTVetor( xIMT_MinVetorBorda, yIMT_MinVetorBorda, zIMT_MinVetorBorda );
    IMT_MaxVetorBorda = CIMTVetor( xIMT_MaxVetorBorda, yIMT_MaxVetorBorda, zIMT_MaxVetorBorda );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CIMTBorda::Limpa()
{
    IMT_MinVetorBorda = CIMTVetor(  9999999,  9999999,  9999999 );
    IMT_MaxVetorBorda = CIMTVetor( -9999999, -9999999, -9999999 );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTVetor CIMTBorda::PegaDimensao() const
{
    return IMT_MaxVetorBorda - IMT_MinVetorBorda;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTVetor CIMTBorda::PegaCentro() const
{
    return (IMT_MaxVetorBorda + IMT_MinVetorBorda) / 2;
}

/***************************************************************/
/*Transforma os vetores do volume e retorna o centro atualizado*/
/***************************************************************/
CIMTVetor CIMTBorda::Transform(CIMTMatriz pIMT_Mtx)
{
    IMT_MaxVetorBorda = IMT_MaxVetorBorda * pIMT_Mtx;
    IMT_MinVetorBorda = IMT_MinVetorBorda * pIMT_Mtx;

    return (IMT_MaxVetorBorda + IMT_MinVetorBorda) / 2;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTPlano CIMTBorda::PegaPlano( unsigned long Side ) const
{
    CIMTPlano BordaPlano;

    switch ( Side ) {
        case BORDAS_PLANO_TOPO:
            BordaPlano.IMT_NormalPlano.y = 1;
            BordaPlano.IMT_DistanciaPlano = IMT_MaxVetorBorda.ProdutoEscalar(BordaPlano.IMT_NormalPlano);
            break;
        case BORDAS_PLANO_DIREITO:
            BordaPlano.IMT_NormalPlano.x = 1;
            BordaPlano.IMT_DistanciaPlano = IMT_MaxVetorBorda.ProdutoEscalar(BordaPlano.IMT_NormalPlano);
            break;
        case BORDAS_PLANO_ATRAS:
            BordaPlano.IMT_NormalPlano.z = 1;
            BordaPlano.IMT_DistanciaPlano = IMT_MaxVetorBorda.ProdutoEscalar(BordaPlano.IMT_NormalPlano);
            break;
        case BORDAS_PLANO_ABAIXO:
            BordaPlano.IMT_NormalPlano.y = -1;
            BordaPlano.IMT_DistanciaPlano = IMT_MinVetorBorda.ProdutoEscalar(BordaPlano.IMT_NormalPlano);
            break;
        case BORDAS_PLANO_ESQUERDO:
            BordaPlano.IMT_NormalPlano.x = -1;
            BordaPlano.IMT_DistanciaPlano = IMT_MinVetorBorda.ProdutoEscalar(BordaPlano.IMT_NormalPlano);
            break;
        case BORDAS_PLANO_FRENTE:
            BordaPlano.IMT_NormalPlano.z = -1;
            BordaPlano.IMT_DistanciaPlano = IMT_MinVetorBorda.ProdutoEscalar(BordaPlano.IMT_NormalPlano);
            break;
    }

    return BordaPlano;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBorda& CIMTBorda::CalculaBordaMesh( const CIMTVetor pVertices[], unsigned long VertexCount, unsigned long VertexStride, bool bReset )
{
    CIMTVetor      * vtx;
    unsigned char  * pVerts  = (unsigned char*)pVertices;

    if ( !pVertices ) return *this;

    if ( bReset ) Limpa();

    for ( unsigned long v = 0; v < VertexCount; v++, pVerts += VertexStride )
    {
        vtx = (CIMTVetor*)pVerts;
        if ( vtx->x < IMT_MinVetorBorda.x ) IMT_MinVetorBorda.x = vtx->x;
        if ( vtx->y < IMT_MinVetorBorda.y ) IMT_MinVetorBorda.y = vtx->y;
        if ( vtx->z < IMT_MinVetorBorda.z ) IMT_MinVetorBorda.z = vtx->z;
        if ( vtx->x > IMT_MaxVetorBorda.x ) IMT_MaxVetorBorda.x = vtx->x;
        if ( vtx->y > IMT_MaxVetorBorda.y ) IMT_MaxVetorBorda.y = vtx->y;
        if ( vtx->z > IMT_MaxVetorBorda.z ) IMT_MaxVetorBorda.z = vtx->z;
    }

    ProvaReal();

    //Atribui o Raio de Volume
    IMT_Raio = PegaDimensao().x;

    return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBorda& CIMTBorda::CalculaBordaPonto(const CIMTVetor pPos,
                                        const float     pDimensao,
                                        bool            bReset)
{
    if ( bReset ) Limpa();

    IMT_MinVetorBorda = CIMTVetor(pPos + CIMTVetor(-pDimensao,-pDimensao,-pDimensao));
    IMT_MaxVetorBorda = CIMTVetor(pPos + CIMTVetor( pDimensao, pDimensao, pDimensao));

    //Atribui o Raio de Volume
    IMT_Raio = pDimensao/2;

    return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CIMTBorda::ProvaReal()
{
    float rTemp;
    if ( IMT_MaxVetorBorda.x < IMT_MinVetorBorda.x ) { rTemp = IMT_MaxVetorBorda.x; IMT_MaxVetorBorda.x = IMT_MinVetorBorda.x; IMT_MinVetorBorda.x = rTemp; }
    if ( IMT_MaxVetorBorda.y < IMT_MinVetorBorda.y ) { rTemp = IMT_MaxVetorBorda.y; IMT_MaxVetorBorda.y = IMT_MinVetorBorda.y; IMT_MinVetorBorda.y = rTemp; }
    if ( IMT_MaxVetorBorda.z < IMT_MinVetorBorda.z ) { rTemp = IMT_MaxVetorBorda.z; IMT_MaxVetorBorda.z = IMT_MinVetorBorda.z; IMT_MinVetorBorda.z = rTemp; }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CIMTBorda::PontoNaBorda( const CIMTVetor& Point ) const
{
    if (Point.x < IMT_MinVetorBorda.x || Point.x > IMT_MaxVetorBorda.x) return false;
    if (Point.y < IMT_MinVetorBorda.y || Point.y > IMT_MaxVetorBorda.y) return false;
    if (Point.z < IMT_MinVetorBorda.z || Point.z > IMT_MaxVetorBorda.z) return false;
    return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CIMTBorda::PontoNaBorda( const CIMTVetor& Point, const CIMTVetor& Tolerance ) const
{
    if (Point.x < IMT_MinVetorBorda.x - Tolerance.x || Point.x > IMT_MaxVetorBorda.x + Tolerance.x) return false;
    if (Point.y < IMT_MinVetorBorda.y - Tolerance.y || Point.y > IMT_MaxVetorBorda.y + Tolerance.y) return false;
    if (Point.z < IMT_MinVetorBorda.z - Tolerance.z || Point.z > IMT_MaxVetorBorda.z + Tolerance.z) return false;
    return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBorda& CIMTBorda::operator+= ( const CIMTVetor& vecShift )
{
    IMT_MinVetorBorda += vecShift;
    IMT_MaxVetorBorda += vecShift;
    return *this;
}

float CIMTBorda::Diff(float a, float b)
{
    if(a >= 0 && b >= 0)
    {
        if(a > b)
            return a-b;
        else
            return b-a;
    }
    if(a < 0 && b < 0)
    {
        if( a > b)
            return b-a;
        else
            return a-b;
    }
    if(a >= 0 && b < 0)
        return a-b;
    else
        return b-a;
}

//-----------------------------------------------------------------------------
// Name : CruzamentoRaio()
// Desc : Testa se a Borda é atingida por um Raio
//-----------------------------------------------------------------------------
bool CIMTBorda::CruzamentoRaio( const CIMTVetor& RayStart, const CIMTVetor& RayDir, CIMTVetor * pIntersection /* = NULL */ ) const
{
    return CruzamentoRaio( RayStart, RayDir, CIMTVetor(0,0,0), pIntersection );
}

//-----------------------------------------------------------------------------
// Name : CruzamentoRaio()
// Desc : Testa se a Borda é atingida por um Raio co Margem de Tolerância
//-----------------------------------------------------------------------------
bool CIMTBorda::CruzamentoRaio( const CIMTVetor& RayStart, const CIMTVetor& RayDir, const CIMTVetor& Tolerance, CIMTVetor * pIntersection /* = NULL */ ) const
{
    bool Dentro = true;
    CIMTVetor MaxT = CIMTVetor( -1, -1, -1 );
    CIMTVetor Intersection;

    // Procura Planos Candidatos.
    if ( RayStart.x < IMT_MinVetorBorda.x )
    {
        Intersection.x  = IMT_MinVetorBorda.x;
        Dentro          = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.x) MaxT.x = (IMT_MinVetorBorda.x - RayStart.x) / RayDir.x;
    }
    else if (RayStart.x > IMT_MaxVetorBorda.x)
    {
        Intersection.x  = IMT_MaxVetorBorda.x;
        Dentro		    = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.x) MaxT.x = (IMT_MaxVetorBorda.x - RayStart.x) / RayDir.x;
    }

    if ( RayStart.y < IMT_MinVetorBorda.y )
    {
        Intersection.y  = IMT_MinVetorBorda.y;
        Dentro          = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.y) MaxT.y = (IMT_MinVetorBorda.y - RayStart.y) / RayDir.y;
    }
    else if (RayStart.y > IMT_MaxVetorBorda.y)
    {
        Intersection.y  = IMT_MaxVetorBorda.y;
        Dentro		    = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.y) MaxT.y = (IMT_MaxVetorBorda.y - RayStart.y) / RayDir.y;
    }

    if ( RayStart.z < IMT_MinVetorBorda.z )
    {
        Intersection.z = IMT_MinVetorBorda.z;
        Dentro          = false;
        // Calculate T Distances to candidate planes
        if ((unsigned long&)RayDir.z) MaxT.z = (IMT_MinVetorBorda.z - RayStart.z) / RayDir.z;
    }
    else if (RayStart.z > IMT_MaxVetorBorda.z)
    {
        Intersection.z = IMT_MaxVetorBorda.z;
        Dentro		    = false;
        // Calculate T distances to candidate planes
        if ((unsigned long&)RayDir.z) MaxT.z = (IMT_MaxVetorBorda.z - RayStart.z) / RayDir.z;
    }


    //O Raio Origem está dentro da Bounding Box
    if(Dentro) { if (pIntersection) *pIntersection = RayStart; return true; }

    //Pega o Maximo Valor T para escolha da interceccao
    float *Plane = &MaxT.x;
    if(MaxT.y > *Plane)	Plane = &MaxT.y;
    if(MaxT.z > *Plane)	Plane = &MaxT.z;

    //Checa o candidato final dentro da borda.
    if(((unsigned long&)Plane) & 0x80000000) return false;

    //Faz testes Finais
    if ( &MaxT.x != Plane )
    {
        Intersection.x = RayStart.x + *Plane * RayDir.x;

        if ( Intersection.x < IMT_MinVetorBorda.x - Tolerance.x ||
             Intersection.x > IMT_MaxVetorBorda.x + Tolerance.x ) return false;
    }
    if ( &MaxT.y != Plane )
    {
        Intersection.y = RayStart.y + *Plane * RayDir.y;
        if ( Intersection.y < IMT_MinVetorBorda.y - Tolerance.y ||
             Intersection.y > IMT_MaxVetorBorda.y + Tolerance.y ) return false;
    }
    if ( &MaxT.z != Plane )
    {
        Intersection.z = RayStart.z + *Plane * RayDir.z;
        if ( Intersection.z < IMT_MinVetorBorda.z - Tolerance.z ||
             Intersection.z > IMT_MaxVetorBorda.z + Tolerance.z ) return false;
    }

    //O Raio Atingiu a Borda, repassa o ponto de interceção...
    if (pIntersection) *pIntersection = Intersection;
    return true;
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoBorda()
// Desc : Testa a Intersecção de duas Bordas
//-----------------------------------------------------------------------------
bool CIMTBorda::CruzamentoBorda( const CIMTBorda& Borda ) const
{
    return (IMT_MinVetorBorda.x <= Borda.IMT_MaxVetorBorda.x) &&
           (IMT_MinVetorBorda.y <= Borda.IMT_MaxVetorBorda.y) &&
           (IMT_MinVetorBorda.z <= Borda.IMT_MaxVetorBorda.z) &&
           (IMT_MaxVetorBorda.x >= Borda.IMT_MinVetorBorda.x) &&
           (IMT_MaxVetorBorda.y >= Borda.IMT_MinVetorBorda.y) &&
           (IMT_MaxVetorBorda.z >= Borda.IMT_MinVetorBorda.z);
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoBorda()
// Desc : Testa a Intersecção de duas Bordas com um fator de Tolerância
//-----------------------------------------------------------------------------
bool CIMTBorda::CruzamentoBorda( const CIMTBorda& Borda, const CIMTVetor& Tolerance ) const
{
    return ((IMT_MinVetorBorda.x - Tolerance.x) <= (Borda.IMT_MaxVetorBorda.x + Tolerance.x)) &&
           ((IMT_MinVetorBorda.y - Tolerance.y) <= (Borda.IMT_MaxVetorBorda.y + Tolerance.y)) &&
           ((IMT_MinVetorBorda.z - Tolerance.z) <= (Borda.IMT_MaxVetorBorda.z + Tolerance.z)) &&
           ((IMT_MaxVetorBorda.x + Tolerance.x) >= (Borda.IMT_MinVetorBorda.x - Tolerance.x)) &&
           ((IMT_MaxVetorBorda.y + Tolerance.y) >= (Borda.IMT_MinVetorBorda.y - Tolerance.y)) &&
           ((IMT_MaxVetorBorda.z + Tolerance.z) >= (Borda.IMT_MinVetorBorda.z - Tolerance.z));
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoEsfera()
// Desc : Testa a Intersecção ESFERICA de duas Bordas
//-----------------------------------------------------------------------------
bool CIMTBorda::CruzamentoEsfera( const CIMTBorda& Borda ) const
{
    CIMTVetor   relPos = PegaCentro() - Borda.PegaCentro();

    float  dist = relPos.x * relPos.x +
                  relPos.y * relPos.y +
                  relPos.z * relPos.z;

    float  minDist = IMT_Raio + Borda.IMT_Raio;

    return dist <= minDist * minDist;
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoEsfera()
// Desc : Testa a Intersecção ESFERICA de duas Bordas
//-----------------------------------------------------------------------------
bool CIMTBorda::CruzamentoEsfera( const CIMTBorda& Borda                 ,
                                  float pIMT_TimeElapsed                 ) const
{
    CIMTVetor   relPos = PegaCentro() - Borda.PegaCentro();

    float  dist = relPos.x * relPos.x +
                  relPos.y * relPos.y +
                  relPos.z * relPos.z;

    float  minDist = IMT_Raio + Borda.IMT_Raio;

    return dist <= minDist * minDist;
}

