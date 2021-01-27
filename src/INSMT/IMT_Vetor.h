/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IMT_VETOR_H
#define IMT_VETOR_H

class CIMTPlano;
class CIMTMatriz;

class CIMTVetor2
{
public:

    CIMTVetor2( ) { }
    CIMTVetor2( const CIMTVetor2 & vec ) {x = vec.x; y = vec.y; }
    CIMTVetor2( float _x, float _y ) { x = _x; y = _y; }

    CIMTVetor2  operator-  ( const CIMTVetor2& vec ) const;

    union {
        struct {
            float    x;
            float    y;
        };
        float v[2];
    };
};

class CIMTVetor4
{
public:

    CIMTVetor4( );
    CIMTVetor4( const CIMTVetor4 & vec );
    CIMTVetor4( float _x, float _y, float _z, float _w);

    union {
        struct {
            float    x;
            float    y;
            float    z;
            float    w;
        };
        float v[4];
    };

    bool                IsEmpty() const;
    bool                SetBaryCentric( const CIMTVetor4& V1, const CIMTVetor4& V2, const CIMTVetor4& V3, const float& f, const float& g );
    bool                SetCatmullRom( const CIMTVetor4& V1, const CIMTVetor4& V2, const CIMTVetor4& V3, const CIMTVetor4& V4, const float& s );
    bool                SetHermite( const CIMTVetor4& V1, const CIMTVetor4& T1, const CIMTVetor4& V2, const CIMTVetor4& T2, const float& s );
    CIMTVetor4          Lerp( const CIMTVetor4& V1, const float& s ) const;
    CIMTVetor4          Maximize( const CIMTVetor4& V1 ) const;
    CIMTVetor4          Minimize( const CIMTVetor4& V1 ) const;
    CIMTVetor4&         Scale( const float &Scale );
    CIMTVetor4          Cross( const CIMTVetor4& V1, const CIMTVetor4& V2 ) const;
    float               Dot( const CIMTVetor4& vec ) const;
    float               Length() const;
    float               SquareLength() const;
    CIMTVetor4          Transform( const CIMTMatriz& mtx ) const;
    bool                FuzzyCompare( const CIMTVetor4& vecCompare,  const float& Tolerance) const;
    CIMTVetor4&         Normalize();

    CIMTVetor4  operator+  ( const CIMTVetor4& vec ) const;
    CIMTVetor4  operator-  ( const CIMTVetor4& vec ) const;
    CIMTVetor4  operator*  ( const float& Value  ) const;
    CIMTVetor4  operator/  ( const float& Value  ) const;

    CIMTVetor4& operator+= ( const CIMTVetor4& vec );
    CIMTVetor4& operator-= ( const CIMTVetor4& vec );
    CIMTVetor4& operator/= ( const float& Value  );
    CIMTVetor4& operator*= ( const float& Value  );

    CIMTVetor4  operator+  () const;
    CIMTVetor4  operator-  () const;
    CIMTVetor4& operator=  ( const CIMTVetor4& vec );
    bool      operator== ( const CIMTVetor4& vec ) const;
    bool      operator!= ( const CIMTVetor4& vec ) const;

    operator float * ();
    operator const float * () const;

    friend CIMTVetor4 operator * (float Value, const CIMTVetor4& vec );
};

class CIMTVetor
{
public:

    CIMTVetor( );
    CIMTVetor( const CIMTVetor & vetor );
    CIMTVetor( float _x, float _y, float _z );

    union {
        struct {
            float    x;
            float    y;
            float    z;
        };
        float v[3];
    };

    bool                SetBaryCentric ( const CIMTVetor& V1, const CIMTVetor& V2, const CIMTVetor& V3, const float& f, const float& g );
    bool                SetCatmullRom  ( const CIMTVetor& V1, const CIMTVetor& V2, const CIMTVetor& V3, const CIMTVetor& V4, const float& s );
    bool                SetHermite     ( const CIMTVetor& V1, const CIMTVetor& T1, const CIMTVetor& V2, const CIMTVetor& T2, const float& s );
    CIMTVetor           Lerp           ( const CIMTVetor& V1, const float& s) const;
    CIMTVetor           Maximize       ( const CIMTVetor& V1   ) const;
    CIMTVetor           Minimize       ( const CIMTVetor& V1   ) const;
    CIMTVetor&          Scale          ( const float &Scale    );
    CIMTVetor4          Transform      ( const CIMTMatriz& mtx ) const;
    CIMTVetor           TransformCoord ( const CIMTMatriz& mtx ) const;
    CIMTVetor           TransformNormal( const CIMTMatriz& mtx ) const;

    bool                Vazio          (                                 ) const;
    CIMTVetor           ProdutoVetorial( const CIMTVetor& V1             ) const;
    float               ProdutoEscalar ( const CIMTVetor& vetor          ) const;
    float               Magnitude      (                                 ) const;
    float               MeiaMagnitude  (                                 ) const;
    bool                Compara        (const CIMTVetor& vetorComparacao,
                                        const float& tolerancia          ) const;
    CIMTVetor&          Normalizar     (                                 )      ;
    float               Distancia      (const CIMTVetor& vetor           ) const;
    double              AnguloEntre    (const CIMTVetor& kbcVetor        ) const;
    float               DistanciaPlano (const CIMTPlano& Plane           ) const;
    float               DistanciaPlano (const CIMTPlano& Plane   , const CIMTVetor& Direction ) const;
    float               DistanciaLinha (const CIMTVetor& vecStart, const CIMTVetor& vecEnd    ) const;

    CIMTVetor  operator+  ( const CIMTVetor& vetor ) const;
    CIMTVetor  operator-  ( const CIMTVetor& vetor ) const;
    CIMTVetor  operator*  ( const CIMTVetor& vetor ) const;
    CIMTVetor  operator*  ( const CIMTMatriz& mtx ) const;
    CIMTVetor  operator*  ( const float& Valor  ) const;
    CIMTVetor  operator/  ( const float& Valor  ) const;

    CIMTVetor& operator+= ( const CIMTVetor& vetor );
    CIMTVetor& operator-= ( const CIMTVetor& vetor );
    CIMTVetor& operator/= ( const float& Valor  );
    CIMTVetor& operator*= ( const CIMTMatriz& mtx );
    CIMTVetor& operator*= ( const float& Valor  );

    CIMTVetor  operator+  () const;
    CIMTVetor  operator-  () const;
    CIMTVetor& operator=  ( const CIMTVetor& vetor );
    bool       operator== ( const CIMTVetor& vetor ) const;
    bool       operator!= ( const CIMTVetor& vetor ) const;

    operator float * ();
    operator const float * () const;

    friend CIMTVetor operator * (float Valor, const CIMTVetor& vetor );
};


#endif // IMT_VETOR_H
