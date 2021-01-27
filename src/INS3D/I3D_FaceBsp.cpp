/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_FaceBsp.h"


CI3DFaceBsp::CI3DFaceBsp()
{

    Divisor       =false ;
    Proximo       =NULL  ;
    IndiceOriginal=-1    ;
    Plano         =-1    ;
    FrameRendered = 0    ;
    Deleted       = false;
    ChildSplit[0] =-1    ;
    ChildSplit[1] =-1    ;
}

CI3DFaceBsp::CI3DFaceBsp(const CI3DFace *kbcFace)
{

    Deleted         = false;
    ChildSplit[0]   = -1;
    ChildSplit[1]   = -1;
    Divisor         = false;
    IndiceOriginal  = -1;
    Proximo         = NULL;
    Plano           = -1;

    I3D_NormalFace     = kbcFace->I3D_NormalFace    ;
    I3D_IndiceTextura  = kbcFace->I3D_IndiceTextura ;
    I3D_IndiceMaterial = kbcFace->I3D_IndiceMaterial;
    I3D_IndiceMesh     = kbcFace->I3D_IndiceMesh    ;
    I3D_IndiceLightMap = kbcFace->I3D_IndiceLightMap;
    I3D_FaceProgramId  = kbcFace->I3D_FaceProgramId ;
    Status             = kbcFace->Status            ;
    textProj           = kbcFace->textProj          ;
    texturizado        = kbcFace->texturizado       ;
    AngulTextura       = kbcFace->AngulTextura      ;
    TransTextura       = kbcFace->TransTextura      ;
    ScalaTextura       = kbcFace->ScalaTextura      ;

    AdicionaVertices( kbcFace->I3D_QtdVertices , IGL_RENDER_TRIANGLES );
    memcpy( Vertices, kbcFace->Vertices,I3D_QtdVertices * sizeof(CI3DVertice));

    Triangulariza();

    PreencheBuffers();

}


bool CI3DFaceBsp::Divide (const CIMTPlano& kbcPlano ,
                          CI3DFaceBsp *DivisorFrente,
                          CI3DFaceBsp *DivisorAtras )
{

      CI3DFace::Divide(kbcPlano,DivisorFrente,DivisorAtras);
      /*
      if(!CKbcFace::Divide(kbcPlano,DivisorFrente,DivisorAtras))
      {
          return false;
      }
      */

      if(DivisorFrente)
      {

         DivisorFrente->Divisor        =Divisor;
         DivisorFrente->Plano          =Plano  ;
         DivisorFrente->IndiceOriginal =IndiceOriginal;
      }

      if(DivisorAtras)
      {

         DivisorAtras->Divisor        =Divisor;
         DivisorAtras->Plano          =Plano  ;
         DivisorAtras->IndiceOriginal =IndiceOriginal;
      }

      return true;
}
