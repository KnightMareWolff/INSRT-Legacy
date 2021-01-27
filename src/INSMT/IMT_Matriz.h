/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMT_MATRIZ_H
#define IMT_MATRIZ_H


#include "IMT_Vetor.h"
#include "IMT_Plano.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef NULL
#define NULL 0
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CIMTMatriz
{
public:

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTMatriz( );
    CIMTMatriz( const CIMTMatriz& mtx );
    CIMTMatriz( float _m11, float _m12, float _m13, float _m14,
                float _m21, float _m22, float _m23, float _m24,
                float _m31, float _m32, float _m33, float _m34,
                float _m41, float _m42, float _m43, float _m44);

    //------------------------------------------------------------
    //------------------------------------------------------------
    float         Determinant() const;
    CIMTMatriz&   Zero();
    CIMTMatriz&   Identity();
    CIMTMatriz    GetInverse( float * pDeterminant = NULL ) const;
    CIMTMatriz&   Invert( float * pDeterminant = NULL );
    bool          IsIdentity() const;
    CIMTMatriz&   RotateAxis( const CIMTVetor& vecAxis, const float& Angle, bool Reset = false );
    CIMTMatriz&   RotateX( const float& Angle, bool Reset = false );
    CIMTMatriz&   RotateX( const float& Angle, const CIMTVetor& Origin,bool Reset = false );
    CIMTMatriz&   RotateY( const float& Angle, bool Reset = false );
    CIMTMatriz&   RotateY( const float& Angle, const CIMTVetor& Origin,bool Reset = false );
    CIMTMatriz&   RotateZ( const float& Angle, bool Reset = false );
    CIMTMatriz&   RotateZ( const float& Angle, const CIMTVetor& Origin,bool Reset = false );
    CIMTMatriz&   Rotate( const float& Yaw, const float& Pitch, const float& Roll, bool Reset = false );
    CIMTMatriz&   Scale( const float& X, const float& Y, const float& Z, bool Reset = false );
    CIMTMatriz&   Scale( const float& X, const float& Y, const float& Z, const CIMTVetor& Origin, bool Reset = false );
    CIMTMatriz&   Translate( const float& X, const float& Y, const float& Z, bool Reset = false );
    CIMTMatriz&   Transpose( );

    bool          SetViewLH  ( const CIMTVetor& vecPos, const CIMTVetor& vecLookDir, const CIMTVetor& vecUpDir, const CIMTVetor& vecRightDir );
    bool          SetLookAtLH( const CIMTVetor& vecPos, const CIMTVetor& vecLookAt, const CIMTVetor& vecUp );
    bool          SetLookAtRH( const CIMTVetor& vecPos, const CIMTVetor& vecLookAt, const CIMTVetor& vecUp );
    bool          SetOrthoLH ( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetOrthoRH ( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetOrthoOffCenterLH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetOrthoOffCenterRH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveFovLH( const float& FovY, const float& Aspect, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveFovRH( const float& FovY, const float& Aspect, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveLH( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveRH( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveOffCenterLH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveOffCenterRH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetReflect( const CIMTPlano& Plane );
    bool          SetShadow( const CIMTVetor4& Light, const CIMTPlano& Plane );


    //------------------------------------------------------------
    //------------------------------------------------------------
    static const CIMTMatriz& GetIdentity();

    //------------------------------------------------------------
    //------------------------------------------------------------
    float&          operator() (int iRow, int iColumn) ;
    float           operator() (int iRow, int iColumn) const;
    CIMTMatriz      operator*  (const CIMTMatriz & mtx ) const;
    CIMTMatriz      operator+  (const CIMTMatriz & mtx ) const;
    CIMTMatriz      operator-  (const CIMTMatriz & mtx ) const;
    CIMTMatriz      operator/  (const float& Value   ) const;
    CIMTMatriz      operator*  (const float& Value   ) const;
    CIMTMatriz&     operator*= (const CIMTMatriz & mtx );
    CIMTMatriz&     operator+= (const CIMTMatriz & mtx );
    CIMTMatriz&     operator-= (const CIMTMatriz & mtx );
    CIMTMatriz&     operator/= (const float & Value  );
    CIMTMatriz&     operator*= (const float & Value  );
    CIMTMatriz      operator-  () const;
    CIMTMatriz      operator+  () const;
    bool            operator== (const CIMTMatriz & mtx ) const;
    bool            operator!= (const CIMTMatriz & mtx ) const;
                    operator const float* () const;
                    operator       float* ();

    //------------------------------------------------------------
    //------------------------------------------------------------
    friend CIMTMatriz operator* (float Value, const CIMTMatriz& mtx);

    //------------------------------------------------------------
    //------------------------------------------------------------
    union  {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };

private:
    //------------------------------------------------------------
    //------------------------------------------------------------
    static float CalculateDeterminant3( float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33);

    //------------------------------------------------------------
    //------------------------------------------------------------
    static CIMTMatriz     m_mtxStaticIdentity;

};

#endif // IMT_MATRIZ_H
