/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMT_GlobalDef.h"
#include "IMT_Vetor.h"
#include "IMT_Plano.h"
#include "IMT_Matriz.h"


CIMTVetor2 CIMTVetor2::operator-  ( const CIMTVetor2& vec ) const
{
    return CIMTVetor2( x - vec.x, y - vec.y );
}
/*********************************************************************/
/*rotinas para Vetor4                                                */
/*********************************************************************/
CIMTVetor4::CIMTVetor4( )
{
    // Reset required variables.
    x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
}

CIMTVetor4::CIMTVetor4( const CIMTVetor4 & vec )
{
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
}

CIMTVetor4::CIMTVetor4( float _x, float _y, float _z, float _w)
{
    x = _x; y = _y; z = _z; w = _w;
}


CIMTVetor4::operator float * ()
{
    return (float*)&x;
}

CIMTVetor4::operator const float * () const
{
    return (const float*)&x;
}

CIMTVetor4 CIMTVetor4::operator+  () const
{
    return *this;
}

CIMTVetor4 CIMTVetor4::operator-  () const
{
    return CIMTVetor4( -x, -y, -z, -w );
}

CIMTVetor4& CIMTVetor4::operator+= ( const CIMTVetor4& vec )
{
    x += vec.x; y += vec.y; z += vec.z; w += vec.w;
    return *this;
}

CIMTVetor4& CIMTVetor4::operator-= ( const CIMTVetor4& vec )
{
    x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w;
    return *this;
}

CIMTVetor4& CIMTVetor4::operator*= ( const float& Value  )
{
    x *= Value; y *= Value; z *= Value; w *= Value;
    return *this;
}

CIMTVetor4& CIMTVetor4::operator/= ( const float& Value  )
{
    float fValue = 1.0f / Value;
    x *= fValue; y *= fValue; z *= fValue; w *= fValue;
    return *this;
}

CIMTVetor4 CIMTVetor4::operator+  ( const CIMTVetor4& vec ) const
{
    return CIMTVetor4( x + vec.x, y + vec.y, z + vec.z, w + vec.w );
}

CIMTVetor4 CIMTVetor4::operator-  ( const CIMTVetor4& vec ) const
{
    return CIMTVetor4( x - vec.x, y - vec.y, z - vec.z, w - vec.w );
}

CIMTVetor4 CIMTVetor4::operator*  ( const float& Value  ) const
{
    return CIMTVetor4( x * Value, y * Value, z * Value, w * Value );
}

CIMTVetor4 CIMTVetor4::operator/  ( const float& Value  ) const
{
    float fValue = 1.0f / Value;
    return CIMTVetor4( x * fValue, y * fValue, z * fValue, w * fValue );
}

CIMTVetor4& CIMTVetor4::operator=  ( const CIMTVetor4& vec )
{
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
    return *this;
}

bool CIMTVetor4::operator== ( const CIMTVetor4& vec ) const
{
    return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
}

bool CIMTVetor4::operator!= ( const CIMTVetor4& vec ) const
{
    return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
}

CIMTVetor4 operator * (float Value, const CIMTVetor4& vec )
{
    return CIMTVetor4( vec.x * Value, vec.y * Value, vec.z * Value, vec.w * Value );
}

bool CIMTVetor4::IsEmpty() const
{
    return (x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f);
}

bool CIMTVetor4::SetBaryCentric( const CIMTVetor4& V1, const CIMTVetor4& V2, const CIMTVetor4& V3, const float& f, const float& g )
{
    x = V1.x + f * (V2.x - V1.x) + g * (V3.x - V1.x);
    y = V1.y + f * (V2.y - V1.y) + g * (V3.y - V1.y);
    z = V1.z + f * (V2.z - V1.z) + g * (V3.z - V1.z);
    w = V1.w + f * (V2.w - V1.w) + g * (V3.w - V1.w);

    return true;
}

bool CIMTVetor4::SetCatmullRom( const CIMTVetor4& V1, const CIMTVetor4& V2, const CIMTVetor4& V3, const CIMTVetor4& V4, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a = -0.5f * sss + ss - 0.5f * s;
    b =  1.5f * sss - 2.5f * ss + 1.0f;
    c = -1.5f * sss + 2.0f * ss + 0.5f * s;
    d =  0.5f * sss - 0.5f * ss;

    x = a * V1.x + b * V2.x + c * V3.x + d * V4.x;
    y = a * V1.y + b * V2.y + c * V3.y + d * V4.y;
    z = a * V1.z + b * V2.z + c * V3.z + d * V4.z;
    w = a * V1.w + b * V2.w + c * V3.w + d * V4.w;

    return true;
}

bool CIMTVetor4::SetHermite( const CIMTVetor4& V1, const CIMTVetor4& T1, const CIMTVetor4& V2, const CIMTVetor4& T2, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a =  2.0f * sss - 3.0f * ss + 1.0f;
    b = -2.0f * sss + 3.0f * ss;
    c =  sss - 2.0f * ss + s;
    d =  sss - ss;

    x = a * V1.x + b * V2.x + c * T1.x + d * T2.x;
    y = a * V1.y + b * V2.y + c * T1.y + d * T2.y;
    z = a * V1.z + b * V2.z + c * T1.z + d * T2.z;
    w = a * V1.w + b * V2.w + c * T1.w + d * T2.w;

    return true;
}
CIMTVetor4 CIMTVetor4::Lerp( const CIMTVetor4& V1, const float& s ) const
{
    return CIMTVetor4( x + s * (V1.x - x), y + s * (V1.y - y), z + s * (V1.z - z), w + s * (V1.w - w));
}

CIMTVetor4 CIMTVetor4::Maximize( const CIMTVetor4& V1 ) const
{
    return CIMTVetor4( (x > V1.x) ? x : V1.x, (y > V1.y) ? y : V1.y, (z > V1.z) ? z : V1.z, (w > V1.w) ? w : V1.w );
}

CIMTVetor4 CIMTVetor4::Minimize( const CIMTVetor4& V1 ) const
{
    return CIMTVetor4( (x < V1.x) ? x : V1.x, (y < V1.y) ? y : V1.y, (z < V1.z) ? z : V1.z, (w < V1.w) ? w : V1.w );
}

CIMTVetor4& CIMTVetor4::Scale( const float &Scale )
{
    x *= Scale; y *= Scale; z *= Scale; w *= Scale;
    return *this;
}

CIMTVetor4 CIMTVetor4::Cross( const CIMTVetor4& V1, const CIMTVetor4& V2 ) const
{
    float   a, b, c, d, e, f;

    a = V1.x * V2.y - V1.y * V2.x;
    b = V1.x * V2.z - V1.z * V2.x;
    c = V1.x * V2.w - V1.w * V2.x;
    d = V1.y * V2.z - V1.z * V2.y;
    e = V1.y * V2.w - V1.w * V2.y;
    f = V1.z * V2.w - V1.w * V2.z;

    return CIMTVetor4( ( f * y - e * z + d * w),
                     (-f * x - c * z + b * w),
                     ( e * x - c * y + a * w),
                     (-d * x - b * y + a * z));
}

float CIMTVetor4::Dot( const CIMTVetor4& vec ) const
{
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

float CIMTVetor4::Length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float CIMTVetor4::SquareLength() const
{
    return x * x + y * y + z * z + w * w;
}

CIMTVetor4 CIMTVetor4::Transform( const CIMTMatriz& mtx ) const
{
    return CIMTVetor4( x * mtx._11 + y * mtx._21 + z * mtx._31 + w * mtx._41,
                     x * mtx._12 + y * mtx._22 + z * mtx._32 + w * mtx._42,
                     x * mtx._13 + y * mtx._23 + z * mtx._33 + w * mtx._43,
                     x * mtx._14 + y * mtx._24 + z * mtx._34 + w * mtx._44 );
}

bool CIMTVetor4::FuzzyCompare( const CIMTVetor4& vecCompare,  const float& Tolerance) const
{
    if ( fabsf(x - vecCompare.x) > Tolerance ) return false;
    if ( fabsf(y - vecCompare.y) > Tolerance ) return false;
    if ( fabsf(z - vecCompare.z) > Tolerance ) return false;
    if ( fabsf(w - vecCompare.w) > Tolerance ) return false;
    return true;
}

CIMTVetor4& CIMTVetor4::Normalize()
{
    float   denom;

    denom = sqrtf(x * x + y * y + z * z + w * w);
    if (fabsf(denom) < 1e-5f) return *this;

    denom = 1.0f / denom;

    x *= denom;
    y *= denom;
    z *= denom;
    w *= denom;

    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor::CIMTVetor( )
{
    // Reset required variables.
    x = 0.0f; y = 0.0f; z = 0.0f;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor::CIMTVetor( const CIMTVetor & vetor )
{
    x = vetor.x; y = vetor.y; z = vetor.z;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor::CIMTVetor( float _x, float _y, float _z)
{
    x = _x; y = _y; z = _z;
}


/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor::operator float * ()
{
    return (float*)&x;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor::operator const float * () const
{
    return (const float*)&x;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator+  () const
{
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator-  () const
{
    return CIMTVetor( -x, -y, -z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor& CIMTVetor::operator+= ( const CIMTVetor& vetor )
{
    x += vetor.x; y += vetor.y; z += vetor.z;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor& CIMTVetor::operator-= ( const CIMTVetor& vetor )
{
    x -= vetor.x; y -= vetor.y; z -= vetor.z;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor& CIMTVetor::operator*= ( const float& Valor  )
{
    x *= Valor; y *= Valor; z *= Valor;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor& CIMTVetor::operator/= ( const float& Valor  )
{
    float fValor = 1.0f / Valor;
    x *= fValor; y *= fValor; z *= fValor;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator+  ( const CIMTVetor& vetor ) const
{
    return CIMTVetor( x + vetor.x, y + vetor.y, z + vetor.z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator-  ( const CIMTVetor& vetor ) const
{
    return CIMTVetor( x - vetor.x, y - vetor.y, z - vetor.z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator*  ( const float& Valor  ) const
{
    return CIMTVetor( x * Valor, y * Valor, z * Valor );
}


/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator*  ( const CIMTVetor& vetor  ) const
{
    return CIMTVetor( x * vetor.x, y * vetor.y, z * vetor.z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::operator/  ( const float& Valor  ) const
{
    float fValor = 1.0f / Valor;
    return CIMTVetor( x * fValor, y * fValor, z * fValor );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor& CIMTVetor::operator=  ( const CIMTVetor& vetor )
{
    x = vetor.x; y = vetor.y; z = vetor.z;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVetor::operator== ( const CIMTVetor& vetor ) const
{
    return (x == vetor.x) && (y == vetor.y) && (z == vetor.z);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVetor::operator!= ( const CIMTVetor& vetor ) const
{
    return (x != vetor.x) || (y != vetor.y) || (z != vetor.z);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor operator * (float Valor, const CIMTVetor& vetor )
{
    return CIMTVetor( vetor.x * Valor, vetor.y * Valor, vetor.z * Valor );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVetor::Vazio() const
{
    return (x == 0.0f) && (y == 0.0f) && (z == 0.0f);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor CIMTVetor::ProdutoVetorial( const CIMTVetor& V1 ) const
{
    return CIMTVetor( y * V1.z - z * V1.y ,
                      z * V1.x - x * V1.z ,
                      x * V1.y - y * V1.x );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
float CIMTVetor::ProdutoEscalar( const CIMTVetor& vetor ) const
{
    return x * vetor.x + y * vetor.y + z * vetor.z;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
float CIMTVetor::Magnitude() const
{
    return sqrtf(x * x + y * y + z * z);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
float CIMTVetor::MeiaMagnitude() const
{
    return x * x + y * y + z * z;
}


/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVetor::Compara( const CIMTVetor& vetorComparacao,  const float& tolerancia) const
{
    if ( fabsf(x - vetorComparacao.x) >= tolerancia ) return false;
    if ( fabsf(y - vetorComparacao.y) >= tolerancia ) return false;
    if ( fabsf(z - vetorComparacao.z) >= tolerancia ) return false;
    return true;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVetor& CIMTVetor::Normalizar()
{
    float   denom;

    denom = sqrtf(x * x + y * y + z * z);
    if (fabsf(denom) < 1e-5f) return *this;

    denom = 1.0f / denom;

    x *= denom;
    y *= denom;
    z *= denom;

    return *this;
}

/************************************************************/
/*Nome do Método    : AnguloEntre                           */
/*                                                          */
/*Objetivo          : Retorna o angulo entre este vetor e   */
/*                    outro vetor passado.                  */
/*                                                          */
/************************************************************/
double CIMTVetor::AnguloEntre(const CIMTVetor& kbcVetor) const
{

    float  kbcProdEsc = ProdutoEscalar(kbcVetor);

    float  kbcMags    = Magnitude() * kbcVetor.Magnitude();

    double kbcAngulo  = acos( kbcProdEsc / kbcMags );

    // Para ter certeza que não e angulo indefinido
    //if(_isnan(kbcAngulo))
    //    return 0;

    // retorna em radianos
    return( kbcAngulo );

}

/*************************************************************/
/*Nome do Método    : Distancia                              */
/*                                                           */
/*Objetivo          : Retorna a Distancia entre este vetor e */
/*                    um vetor passado                       */
/*                                                           */
/*************************************************************/
float CIMTVetor::Distancia(const CIMTVetor& vetor) const
{
    return sqrt((vetor.x - x) * (vetor.x - x) +
                (vetor.y - y) * (vetor.y - y) +
                (vetor.z - z) * (vetor.z - z));

}

//-----------------------------------------------------------------------------
// Name : DistanceToPlane ()
// Desc : Calculates the Distance from the position stored in this vector, and
//        the plane passed to this function.
//-----------------------------------------------------------------------------
float CIMTVetor::DistanciaPlano( const CIMTPlano& Plane ) const
{
    return ProdutoEscalar( Plane.IMT_NormalPlano) - Plane.IMT_DistanciaPlano;
}

//-----------------------------------------------------------------------------
// Name : DistanceToPlane ()
// Desc : Calculates the Distance from the position stored in this vector, and
//        the plane passed to this function, along a ray direction.
//-----------------------------------------------------------------------------
float CIMTVetor::DistanciaPlano( const CIMTPlano& Plane, const CIMTVetor& Direction ) const
{
    float PlaneDistance = ProdutoEscalar( -Plane.IMT_NormalPlano) - Plane.IMT_DistanciaPlano;
    return PlaneDistance * (1 / (-Plane.IMT_NormalPlano).ProdutoEscalar( Direction ));
}

//-----------------------------------------------------------------------------
// Name : DistanceToLine ()
// Desc : Calculates the distance from the position stored in this vector, and
//        the line segment passed into this function.
// Note : Returns a value that is out of range if the point is outside of the
//        extents of vecStart & vecEnd.
//-----------------------------------------------------------------------------
float CIMTVetor::DistanciaLinha( const CIMTVetor& vecStart, const CIMTVetor& vecEnd ) const
{
    CIMTVetor c, v;
    float     d, t;

    // Determine t
    // (the length of the vector from ‘vecStart’ to ‘this’)
    c = *this  - vecStart;
    v = vecEnd - vecStart;
    d = v.Magnitude();

    v.Normalizar();

    t = v.ProdutoEscalar( c );

    // Check to see if ‘t’ is beyond the extents of the line segment
    if (t < 0.01f)     return 99999.0f;
    if (t > d - 0.01f) return 99999.0f;

    // set length of v to t. v is normalized so this is easy
    v.x = vecStart.x + (v.x * t);
    v.y = vecStart.y + (v.y * t);
    v.z = vecStart.z + (v.z * t);

    // Return the distance
    return ((*this) - v).Magnitude();
}

CIMTVetor& CIMTVetor::operator*= ( const CIMTMatriz& mtx )
{
    float   rhw, _x, _y, _z;

    rhw = (x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44);
    if (fabsf(rhw) < 1e-5f) { x = 0; y = 0; z = 0; return *this; }

    rhw = 1.0f / rhw;

    _x = rhw * (x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41);
    _y = rhw * (x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42);
    _z = rhw * (x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43);

    x = _x; y = _y; z = _z;

    return *this;
}

CIMTVetor CIMTVetor::operator*  ( const CIMTMatriz& mtx  ) const
{
    float   rhw;

    rhw = (x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44);
    if (fabsf(rhw) < 1e-5f) return CIMTVetor( 0, 0, 0 );

    rhw = 1.0f / rhw;

    return CIMTVetor( rhw * (x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41),
                     rhw * (x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42),
                     rhw * (x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43));
}


bool CIMTVetor::SetBaryCentric( const CIMTVetor& V1, const CIMTVetor& V2, const CIMTVetor& V3, const float& f, const float& g )
{
    x = V1.x + f * (V2.x - V1.x) + g * (V3.x - V1.x);
    y = V1.y + f * (V2.y - V1.y) + g * (V3.y - V1.y);
    z = V1.z + f * (V2.z - V1.z) + g * (V3.z - V1.z);

    return true;
}

bool CIMTVetor::SetCatmullRom( const CIMTVetor& V1, const CIMTVetor& V2, const CIMTVetor& V3, const CIMTVetor& V4, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a = -0.5f * sss + ss - 0.5f * s;
    b =  1.5f * sss - 2.5f * ss + 1.0f;
    c = -1.5f * sss + 2.0f * ss + 0.5f * s;
    d =  0.5f * sss - 0.5f * ss;

    x = a * V1.x + b * V2.x + c * V3.x + d * V4.x;
    y = a * V1.y + b * V2.y + c * V3.y + d * V4.y;
    z = a * V1.z + b * V2.z + c * V3.z + d * V4.z;

    return true;
}

bool CIMTVetor::SetHermite( const CIMTVetor& V1, const CIMTVetor& T1, const CIMTVetor& V2, const CIMTVetor& T2, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a =  2.0f * sss - 3.0f * ss + 1.0f;
    b = -2.0f * sss + 3.0f * ss;
    c =  sss - 2.0f * ss + s;
    d =  sss - ss;

    x = a * V1.x + b * V2.x + c * T1.x + d * T2.x;
    y = a * V1.y + b * V2.y + c * T1.y + d * T2.y;
    z = a * V1.z + b * V2.z + c * T1.z + d * T2.z;

    return true;
}
CIMTVetor CIMTVetor::Lerp( const CIMTVetor& V1, const float& s ) const
{
    return CIMTVetor( x + s * (V1.x - x), y + s * (V1.y - y), z + s * (V1.z - z) );
}

CIMTVetor CIMTVetor::Maximize( const CIMTVetor& V1 ) const
{
    return CIMTVetor( (x > V1.x) ? x : V1.x, (y > V1.y) ? y : V1.y, (z > V1.z) ? z : V1.z );
}

CIMTVetor CIMTVetor::Minimize( const CIMTVetor& V1 ) const
{
    return CIMTVetor( (x < V1.x) ? x : V1.x, (y < V1.y) ? y : V1.y, (z < V1.z) ? z : V1.z );
}

CIMTVetor& CIMTVetor::Scale( const float &Scale )
{
    x *= Scale; y *= Scale; z *= Scale;
    return *this;
}


CIMTVetor4 CIMTVetor::Transform( const CIMTMatriz& mtx ) const
{
    return CIMTVetor4( x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41,
                       x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42,
                       x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43,
                       x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44 );
}

CIMTVetor CIMTVetor::TransformCoord( const CIMTMatriz& mtx ) const
{
    float   rhw;

    rhw = (x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44);
    if (fabsf(rhw) < 1e-5f) return CIMTVetor( 0, 0, 0 );

    rhw = 1.0f / rhw;

    return CIMTVetor( rhw * (x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41),
                      rhw * (x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42),
                      rhw * (x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43));
}

CIMTVetor CIMTVetor::TransformNormal( const CIMTMatriz& mtx ) const
{
    return CIMTVetor( x * mtx._11 + y * mtx._21 + z * mtx._31,
                      x * mtx._12 + y * mtx._22 + z * mtx._32,
                      x * mtx._13 + y * mtx._23 + z * mtx._33 );
}
