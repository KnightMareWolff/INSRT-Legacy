/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "INSMT.h"


INSMT::INSMT()
{
}
/*
float  bilerp(const float &a,const float &b,const float &c,const float &d, float u, float v)
{
    // Performs a bilinear interpolation.
    //  P(u,v) = e + v(f - e)
    //
    //  where
    //  e = a + u(b - a)
    //  f = c + u(d - c)
    //  u in range [0,1]
    //  v in range [0,1]

    return a * ((1.0f - u) * (1.0f - v))
           + b * (u * (1.0f - v))
           + c * (v * (1.0f - u))
           + d * (u * v);
}

CIMTVetor  bilerp(const CIMTVetor &a,const CIMTVetor &b,const CIMTVetor &c,const CIMTVetor &d, float u, float v)
{
    // Performs a bilinear interpolation.
    //  P(u,v) = e + v(f - e)
    //
    //  where
    //  e = a + u(b - a)
    //  f = c + u(d - c)
    //  u in range [0,1]
    //  v in range [0,1]

    return a * ((1.0f - u) * (1.0f - v))
           + b * (u * (1.0f - v))
           + c * (v * (1.0f - u))
           + d * (u * v);
}

long floatToLong(float f)
{
    // Converts a floating point number into an integer.
    // Fractional values are truncated as in ANSI C.
    // About 5 to 6 times faster than a standard typecast to an integer.
    long fpBits = *reinterpret_cast<const long*>(&f);
    long shift = 23 - (((fpBits & 0x7fffffff) >> 23) - 127);
    long result = ((fpBits & 0x7fffff) | (1 << 23)) >> shift;

    result = (result ^ (fpBits >> 31)) - (fpBits >> 31);
    result &= ~((((fpBits & 0x7fffffff) >> 23) - 127) >> 31);

    return result;
}

float random(float min, float max)
{
    // Returns a random number in range [min,max].
    return min + (max - min) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}
*/
