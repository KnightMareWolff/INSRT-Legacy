/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_GlobalDef.h"
#include "I3D_Face.h"

/************************************************************/
/************************************************************/
CI3DFace::CI3DFace()
{

    I3D_IndiceMaterial = -1;
    I3D_IndiceTextura  =  0;
    I3D_IndiceMesh     = -1;
    I3D_IndiceLightMap =  0;
    I3D_FaceProgramId  =  0;

    Status=true;

    texturizado  =false;
    lightmap     =false;

    //Estes atributos provavelmente não serão usados mais , pois com a
    //evolução de shaders virou trabalho inútil...
    ScalaTextura=CIMTVetor(1.0f,1.0f,1.0f);
    TransTextura=CIMTVetor(0.0f,0.0f,0.0f);
    AngulTextura=CIMTVetor(0.0f,0.0f,0.0f);

}

CI3DFace::CI3DFace(const CI3DFace &i3dFace )
{

    I3D_NormalFace    =i3dFace.I3D_NormalFace;
    I3D_IndiceTextura =i3dFace.I3D_IndiceTextura;
    I3D_IndiceMaterial=i3dFace.I3D_IndiceMaterial;
    I3D_IndiceMesh    =i3dFace.I3D_IndiceMesh;
    I3D_IndiceLightMap=i3dFace.I3D_IndiceLightMap;
    I3D_HeightMapXY   =i3dFace.I3D_HeightMapXY;
    I3D_FaceProgramId =i3dFace.I3D_FaceProgramId;

    Status    =i3dFace.Status;
    BordaFace =i3dFace.BordaFace;

    texturizado =i3dFace.texturizado  ;//Texturizado?
    lightmap    =i3dFace.lightmap     ;//Contem Lightmap?
    textProj    =i3dFace.textProj     ;//Qual e a projecao?
    ScalaTextura=i3dFace.ScalaTextura ;//Qual e a Scala?
    TransTextura=i3dFace.TransTextura ;//Qual e o Offset?
    AngulTextura=i3dFace.AngulTextura ;//Qual e o Angulo?
}

/************************************************************/
/************************************************************/
CI3DFace::~CI3DFace()
{

}

/************************************************************/
/*Nome do Método      : SetaIndMesh()
/*
/*Objetivo            : Seta o indice de referencia do mesh
/*                      que possui esta face.
/*
/************************************************************/
bool CI3DFace::Divide(const CIMTPlano& Plano ,
                      CI3DFace *DivisorFrente,
                      CI3DFace *DivisorAtras )
{

    CI3DPoligono::Divide(Plano,DivisorFrente,DivisorAtras);
    /*
    if(!CKbcPoligono::Divide(Plano,DivisorFrente,DivisorAtras))
    {
        return false;
    }
    */

    if(DivisorFrente)
    {

       DivisorFrente->I3D_NormalFace    =I3D_NormalFace    ;
       DivisorFrente->I3D_IndiceMaterial=I3D_IndiceMaterial;
       DivisorFrente->I3D_IndiceMesh    =I3D_IndiceMesh    ;
       DivisorFrente->I3D_IndiceTextura =I3D_IndiceTextura ;
       DivisorFrente->I3D_IndiceLightMap=I3D_IndiceLightMap;
       DivisorFrente->I3D_HeightMapXY   =I3D_HeightMapXY   ;
       DivisorFrente->I3D_FaceProgramId =I3D_FaceProgramId ;
       DivisorFrente->Status            =Status            ;
       DivisorFrente->textProj          =textProj          ;
       DivisorFrente->texturizado       =texturizado       ;
       DivisorFrente->AngulTextura      =AngulTextura      ;
       DivisorFrente->TransTextura      =TransTextura      ;
       DivisorFrente->ScalaTextura      =ScalaTextura      ;
    }

    if(DivisorAtras)
    {

       DivisorAtras->I3D_NormalFace    =I3D_NormalFace    ;
       DivisorAtras->I3D_IndiceMaterial=I3D_IndiceMaterial;
       DivisorAtras->I3D_IndiceMesh    =I3D_IndiceMesh    ;
       DivisorAtras->I3D_IndiceTextura =I3D_IndiceTextura ;
       DivisorAtras->I3D_IndiceLightMap=I3D_IndiceLightMap;
       DivisorAtras->I3D_HeightMapXY   =I3D_HeightMapXY   ;
       DivisorAtras->I3D_FaceProgramId =I3D_FaceProgramId ;
       DivisorAtras->Status            =Status            ;
       DivisorAtras->textProj          =textProj;
       DivisorAtras->texturizado       =texturizado;
       DivisorAtras->AngulTextura      =AngulTextura;
       DivisorAtras->TransTextura      =TransTextura;
       DivisorAtras->ScalaTextura      =ScalaTextura;
    }

    return true;
}

bool CI3DFace::GeraPoligono( const CIMTPlano& Plane, const CIMTBorda& Bounds )
{
    // Chame a Implementação Base
    if (!CI3DPoligono::GeraPoligono( Plane, Bounds )) return false;

    // Copia valores Remanescentes
    I3D_NormalFace = Plane.IMT_NormalPlano;

    // Successo
    return true;
}

void CI3DFace::Renderiza(int iRenderMode, int iPolygonMode, int iShadingMode , int iGeometryMode)
{
    if(Status)
    {
       CI3DPoligono::Renderiza(I3D_FaceProgramId ,iRenderMode,iPolygonMode,iShadingMode,iGeometryMode);
    }
}

void CI3DFace::SetaVertice(int index,CI3DVertice vert)
{
    Vertices[index]=vert;
}

void CI3DFace::CalculaBordaFace(  )
{
    BordaFace.Limpa();

    BordaFace.CalculaBordaMesh( Vertices           ,
                                I3D_QtdVertices    ,
                                sizeof(CI3DVertice),
                                false              );

}

CIMTPlano CI3DFace::PegaPlano(  )
{
    CIMTVetor PtoCentral;
    PtoCentral = CIMTVetor(Vertices[0].x,Vertices[0].y,Vertices[0].z);

    for ( unsigned int i = 1; i < I3D_QtdVertices; i++ )
    {
       PtoCentral += Vertices[i];
    }

    PtoCentral /= I3D_QtdVertices;

    return CIMTPlano( I3D_NormalFace , PtoCentral );
}

bool CI3DFace::CruzamentoRaio(const CIMTVetor& RayStart ,
                              const CIMTVetor& RayDir   )
{
    CIMTPlano Plano;
    CIMTVetor Ponto;
    float     intervalo;

    Plano=PegaPlano();

    if(!Plano.CruzamentoRaio(RayStart,RayDir,&intervalo))
    {
        return false;
    }

    Ponto= RayStart + (RayDir * intervalo);

    return EstaContido(Ponto);
}

bool CI3DFace::CruzamentoPontos(const CIMTVetor& RayStart ,
                                const CIMTVetor& RayEnd   ,
                                      CIMTVetor& ponto    )
{
    CIMTPlano Plano;
    CIMTVetor Ponto,intercecao;
    float     porcentagem;

    Plano=PegaPlano();

    if(!Plano.CruzamentoRaio(RayStart,RayEnd,intercecao,&porcentagem))
    {
        return false;
    }

    ponto=intercecao;

    return EstaContido(intercecao);
}

bool CI3DFace::CruzamentoRaio(const CIMTVetor& RayStart ,
                              const CIMTVetor& RayDir   ,
                                    CIMTVetor& ponto    )
{
    CIMTPlano Plano;
    float     intervalo;

    Plano=PegaPlano();

    if(!Plano.CruzamentoRaio(RayStart,RayDir,&intervalo))
    {
        return false;
    }

    ponto= RayStart + (RayDir * intervalo);

    return EstaContido(ponto);
}
