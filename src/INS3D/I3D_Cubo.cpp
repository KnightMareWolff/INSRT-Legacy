#include "I3D_Cubo.h"


CI3DCubo::CI3DCubo():
    CI3DPrimitivo()
{

}

CI3DCubo::CI3DCubo(CIMTVetor pPos):
    CI3DPrimitivo()
{
    //I3D_Pos       = pPos;
    Translate(pPos,false);
    Build();
}

CI3DCubo::CI3DCubo(CIMTVetor pPos,CIMTVetor pDim):
    CI3DPrimitivo()
{
    I3D_Pos          = pPos;
    I3D_Dim          = pDim;

    Build();
}

CI3DCubo::CI3DCubo(CIMTVetor pPos,CIMTVetor pDim,int pWindingMode):
    CI3DPrimitivo()
{

    I3D_Mesh->WindingMode = pWindingMode;

    I3D_Pos = pPos;
    I3D_Dim = pDim;

    Build();
}

CI3DCubo::CI3DCubo(CIMTVetor pPos,CIMTVetor pDim,int pWindingMode,int pConstructMode):
    CI3DPrimitivo()
{

    I3D_Mesh->WindingMode      = pWindingMode;
    I3D_Mesh->ConstructionMode = pConstructMode;

    I3D_Pos = pPos;
    I3D_Dim = pDim;

    Build();
}

void CI3DCubo::Build()
{
    CIMTVetor   centro,dimensao,vertice0,vertice1,vertice2,vertice3;
    float       Altura,Largura,Profundidade;

    /***********************************/
    /*Fixando Dimensão e Centro        */
    /***********************************/
    centro   = I3D_Pos;
    dimensao = I3D_Dim;


    //Calcula o Diâmetro de cada dimensão do Cubo(x=Altura,y=Largura,z=Profundidade)
    Largura     = dimensao.x / 2.0f;
    Altura      = dimensao.y / 2.0f;
    Profundidade= dimensao.z / 2.0f;

    I3D_Mesh->AdicionaFaces(6);
    /*****************************/
    /*Desenha a Topo             */
    /*****************************/
    I3D_Mesh->Faces[0]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

    if(I3D_Mesh->ConstructionMode==IGL_POLYMODE_RIGHT)
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Largura,Altura,-Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor( Largura,Altura,-Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Largura,Altura, Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor(-Largura,Altura, Profundidade));

       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
          I3D_Mesh->Faces[0]->Vertices[0].x = vertice3.x;
          I3D_Mesh->Faces[0]->Vertices[0].y = vertice3.y;
          I3D_Mesh->Faces[0]->Vertices[0].z = vertice3.z;

          I3D_Mesh->Faces[0]->Vertices[1].x = vertice2.x;
          I3D_Mesh->Faces[0]->Vertices[1].y = vertice2.y;
          I3D_Mesh->Faces[0]->Vertices[1].z = vertice2.z;

          I3D_Mesh->Faces[0]->Vertices[2].x = vertice1.x;
          I3D_Mesh->Faces[0]->Vertices[2].y = vertice1.y;
          I3D_Mesh->Faces[0]->Vertices[2].z = vertice1.z;

          I3D_Mesh->Faces[0]->Vertices[3].x = vertice0.x;
          I3D_Mesh->Faces[0]->Vertices[3].y = vertice0.y;
          I3D_Mesh->Faces[0]->Vertices[3].z = vertice0.z;

          I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
          I3D_Mesh->Faces[0]->Vertices[0].x = vertice0.x;
          I3D_Mesh->Faces[0]->Vertices[0].y = vertice0.y;
          I3D_Mesh->Faces[0]->Vertices[0].z = vertice0.z;
          I3D_Mesh->Faces[0]->Vertices[1].x = vertice1.x;
          I3D_Mesh->Faces[0]->Vertices[1].y = vertice1.y;
          I3D_Mesh->Faces[0]->Vertices[1].z = vertice1.z;
          I3D_Mesh->Faces[0]->Vertices[2].x = vertice2.x;
          I3D_Mesh->Faces[0]->Vertices[2].y = vertice2.y;
          I3D_Mesh->Faces[0]->Vertices[2].z = vertice2.z;
          I3D_Mesh->Faces[0]->Vertices[3].x = vertice3.x;
          I3D_Mesh->Faces[0]->Vertices[3].y = vertice3.y;
          I3D_Mesh->Faces[0]->Vertices[3].z = vertice3.z;
          I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }
    else
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Altura,Largura,-Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor(-Altura,Largura, Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Altura,Largura, Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor( Altura,Largura,-Profundidade));

       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
           I3D_Mesh->Faces[0]->Vertices[0].x = vertice0.x;
           I3D_Mesh->Faces[0]->Vertices[0].y = vertice0.y;
           I3D_Mesh->Faces[0]->Vertices[0].z = vertice0.z;
           I3D_Mesh->Faces[0]->Vertices[1].x = vertice1.x;
           I3D_Mesh->Faces[0]->Vertices[1].y = vertice1.y;
           I3D_Mesh->Faces[0]->Vertices[1].z = vertice1.z;
           I3D_Mesh->Faces[0]->Vertices[2].x = vertice2.x;
           I3D_Mesh->Faces[0]->Vertices[2].y = vertice2.y;
           I3D_Mesh->Faces[0]->Vertices[2].z = vertice2.z;
           I3D_Mesh->Faces[0]->Vertices[3].x = vertice3.x;
           I3D_Mesh->Faces[0]->Vertices[3].y = vertice3.y;
           I3D_Mesh->Faces[0]->Vertices[3].z = vertice3.z;
           I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaV = 0;

       }
       else
       {
           I3D_Mesh->Faces[0]->Vertices[0].x = vertice3.x;
           I3D_Mesh->Faces[0]->Vertices[0].y = vertice3.y;
           I3D_Mesh->Faces[0]->Vertices[0].z = vertice3.z;

           I3D_Mesh->Faces[0]->Vertices[1].x = vertice2.x;
           I3D_Mesh->Faces[0]->Vertices[1].y = vertice2.y;
           I3D_Mesh->Faces[0]->Vertices[1].z = vertice2.z;

           I3D_Mesh->Faces[0]->Vertices[2].x = vertice1.x;
           I3D_Mesh->Faces[0]->Vertices[2].y = vertice1.y;
           I3D_Mesh->Faces[0]->Vertices[2].z = vertice1.z;

           I3D_Mesh->Faces[0]->Vertices[3].x = vertice0.x;
           I3D_Mesh->Faces[0]->Vertices[3].y = vertice0.y;
           I3D_Mesh->Faces[0]->Vertices[3].z = vertice0.z;

           I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[0]->Vertices[0].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[0]->Vertices[1].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[0]->Vertices[2].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[0]->Vertices[3].I3D_CoordTexturaV = 0;

       }
    }


    I3D_Mesh->Faces[0]->Triangulariza();
    I3D_Mesh->Faces[0]->CalculaNormal(true);
    I3D_Mesh->Faces[0]->CalculaNormalSmooth(centro);

    /*****************************/
    /*Desenha a Esquerda         */
    /*****************************/
    I3D_Mesh->Faces[1]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

    if(I3D_Mesh->ConstructionMode==IGL_POLYMODE_RIGHT)
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Largura, Altura,-Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor(-Largura, Altura, Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor(-Largura,-Altura, Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor(-Largura,-Altura,-Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
          I3D_Mesh->Faces[1]->Vertices[0].x = vertice3.x;
          I3D_Mesh->Faces[1]->Vertices[0].y = vertice3.y;
          I3D_Mesh->Faces[1]->Vertices[0].z = vertice3.z;
          I3D_Mesh->Faces[1]->Vertices[1].x = vertice2.x;
          I3D_Mesh->Faces[1]->Vertices[1].y = vertice2.y;
          I3D_Mesh->Faces[1]->Vertices[1].z = vertice2.z;
          I3D_Mesh->Faces[1]->Vertices[2].x = vertice1.x;
          I3D_Mesh->Faces[1]->Vertices[2].y = vertice1.y;
          I3D_Mesh->Faces[1]->Vertices[2].z = vertice1.z;
          I3D_Mesh->Faces[1]->Vertices[3].x = vertice0.x;
          I3D_Mesh->Faces[1]->Vertices[3].y = vertice0.y;
          I3D_Mesh->Faces[1]->Vertices[3].z = vertice0.z;
          I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
          I3D_Mesh->Faces[1]->Vertices[0].x = vertice0.x;
          I3D_Mesh->Faces[1]->Vertices[0].y = vertice0.y;
          I3D_Mesh->Faces[1]->Vertices[0].z = vertice0.z;
          I3D_Mesh->Faces[1]->Vertices[1].x = vertice1.x;
          I3D_Mesh->Faces[1]->Vertices[1].y = vertice1.y;
          I3D_Mesh->Faces[1]->Vertices[1].z = vertice1.z;
          I3D_Mesh->Faces[1]->Vertices[2].x = vertice2.x;
          I3D_Mesh->Faces[1]->Vertices[2].y = vertice2.y;
          I3D_Mesh->Faces[1]->Vertices[2].z = vertice2.z;
          I3D_Mesh->Faces[1]->Vertices[3].x = vertice3.x;
          I3D_Mesh->Faces[1]->Vertices[3].y = vertice3.y;
          I3D_Mesh->Faces[1]->Vertices[3].z = vertice3.z;
          I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }
    else
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Altura,-Largura, Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor(-Altura, Largura, Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor(-Altura, Largura,-Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor(-Altura,-Largura,-Profundidade));

       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
           I3D_Mesh->Faces[1]->Vertices[0].x = vertice0.x;
           I3D_Mesh->Faces[1]->Vertices[0].y = vertice0.y;
           I3D_Mesh->Faces[1]->Vertices[0].z = vertice0.z;
           I3D_Mesh->Faces[1]->Vertices[1].x = vertice1.x;
           I3D_Mesh->Faces[1]->Vertices[1].y = vertice1.y;
           I3D_Mesh->Faces[1]->Vertices[1].z = vertice1.z;
           I3D_Mesh->Faces[1]->Vertices[2].x = vertice2.x;
           I3D_Mesh->Faces[1]->Vertices[2].y = vertice2.y;
           I3D_Mesh->Faces[1]->Vertices[2].z = vertice2.z;
           I3D_Mesh->Faces[1]->Vertices[3].x = vertice3.x;
           I3D_Mesh->Faces[1]->Vertices[3].y = vertice3.y;
           I3D_Mesh->Faces[1]->Vertices[3].z = vertice3.z;
           I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaV = 1;

       }
       else
       {
           I3D_Mesh->Faces[1]->Vertices[0].x = vertice3.x;
           I3D_Mesh->Faces[1]->Vertices[0].y = vertice3.y;
           I3D_Mesh->Faces[1]->Vertices[0].z = vertice3.z;
           I3D_Mesh->Faces[1]->Vertices[1].x = vertice2.x;
           I3D_Mesh->Faces[1]->Vertices[1].y = vertice2.y;
           I3D_Mesh->Faces[1]->Vertices[1].z = vertice2.z;
           I3D_Mesh->Faces[1]->Vertices[2].x = vertice1.x;
           I3D_Mesh->Faces[1]->Vertices[2].y = vertice1.y;
           I3D_Mesh->Faces[1]->Vertices[2].z = vertice1.z;
           I3D_Mesh->Faces[1]->Vertices[3].x = vertice0.x;
           I3D_Mesh->Faces[1]->Vertices[3].y = vertice0.y;
           I3D_Mesh->Faces[1]->Vertices[3].z = vertice0.z;
           I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[1]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[1]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[1]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[1]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }  

    I3D_Mesh->Faces[1]->Triangulariza();
    I3D_Mesh->Faces[1]->CalculaNormal(true);
    I3D_Mesh->Faces[1]->CalculaNormalSmooth(centro);

    /*****************************/
    /*Desenha a Atras            */
    /*****************************/
    I3D_Mesh->Faces[2]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

    if(I3D_Mesh->ConstructionMode==IGL_POLYMODE_RIGHT)
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Largura, Altura, Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor( Largura, Altura, Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Largura,-Altura, Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor(-Largura,-Altura, Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
          I3D_Mesh->Faces[2]->Vertices[0].x = vertice3.x;
          I3D_Mesh->Faces[2]->Vertices[0].y = vertice3.y;
          I3D_Mesh->Faces[2]->Vertices[0].z = vertice3.z;
          I3D_Mesh->Faces[2]->Vertices[1].x = vertice2.x;
          I3D_Mesh->Faces[2]->Vertices[1].y = vertice2.y;
          I3D_Mesh->Faces[2]->Vertices[1].z = vertice2.z;
          I3D_Mesh->Faces[2]->Vertices[2].x = vertice1.x;
          I3D_Mesh->Faces[2]->Vertices[2].y = vertice1.y;
          I3D_Mesh->Faces[2]->Vertices[2].z = vertice1.z;
          I3D_Mesh->Faces[2]->Vertices[3].x = vertice0.x;
          I3D_Mesh->Faces[2]->Vertices[3].y = vertice0.y;
          I3D_Mesh->Faces[2]->Vertices[3].z = vertice0.z;
          I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
          I3D_Mesh->Faces[2]->Vertices[0].x = vertice0.x;
          I3D_Mesh->Faces[2]->Vertices[0].y = vertice0.y;
          I3D_Mesh->Faces[2]->Vertices[0].z = vertice0.z;
          I3D_Mesh->Faces[2]->Vertices[1].x = vertice1.x;
          I3D_Mesh->Faces[2]->Vertices[1].y = vertice1.y;
          I3D_Mesh->Faces[2]->Vertices[1].z = vertice1.z;
          I3D_Mesh->Faces[2]->Vertices[2].x = vertice2.x;
          I3D_Mesh->Faces[2]->Vertices[2].y = vertice2.y;
          I3D_Mesh->Faces[2]->Vertices[2].z = vertice2.z;
          I3D_Mesh->Faces[2]->Vertices[3].x = vertice3.x;
          I3D_Mesh->Faces[2]->Vertices[3].y = vertice3.y;
          I3D_Mesh->Faces[2]->Vertices[3].z = vertice3.z;
          I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }
    else
    {
       vertice0 = CIMTVetor(centro + CIMTVetor( Altura,-Largura, Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor( Altura, Largura, Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor(-Altura, Largura, Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor(-Altura,-Largura, Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
           I3D_Mesh->Faces[2]->Vertices[0].x = vertice0.x;
           I3D_Mesh->Faces[2]->Vertices[0].y = vertice0.y;
           I3D_Mesh->Faces[2]->Vertices[0].z = vertice0.z;
           I3D_Mesh->Faces[2]->Vertices[1].x = vertice1.x;
           I3D_Mesh->Faces[2]->Vertices[1].y = vertice1.y;
           I3D_Mesh->Faces[2]->Vertices[1].z = vertice1.z;
           I3D_Mesh->Faces[2]->Vertices[2].x = vertice2.x;
           I3D_Mesh->Faces[2]->Vertices[2].y = vertice2.y;
           I3D_Mesh->Faces[2]->Vertices[2].z = vertice2.z;
           I3D_Mesh->Faces[2]->Vertices[3].x = vertice3.x;
           I3D_Mesh->Faces[2]->Vertices[3].y = vertice3.y;
           I3D_Mesh->Faces[2]->Vertices[3].z = vertice3.z;
           I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaV = 1;
       }
       else
       {
           I3D_Mesh->Faces[2]->Vertices[0].x = vertice3.x;
           I3D_Mesh->Faces[2]->Vertices[0].y = vertice3.y;
           I3D_Mesh->Faces[2]->Vertices[0].z = vertice3.z;
           I3D_Mesh->Faces[2]->Vertices[1].x = vertice2.x;
           I3D_Mesh->Faces[2]->Vertices[1].y = vertice2.y;
           I3D_Mesh->Faces[2]->Vertices[1].z = vertice2.z;
           I3D_Mesh->Faces[2]->Vertices[2].x = vertice1.x;
           I3D_Mesh->Faces[2]->Vertices[2].y = vertice1.y;
           I3D_Mesh->Faces[2]->Vertices[2].z = vertice1.z;
           I3D_Mesh->Faces[2]->Vertices[3].x = vertice0.x;
           I3D_Mesh->Faces[2]->Vertices[3].y = vertice0.y;
           I3D_Mesh->Faces[2]->Vertices[3].z = vertice0.z;
           I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[2]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[2]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[2]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[2]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }

    I3D_Mesh->Faces[2]->Triangulariza();
    I3D_Mesh->Faces[2]->CalculaNormal(true);
    I3D_Mesh->Faces[2]->CalculaNormalSmooth(centro);

    /*****************************/
    /*Desenha a Frente           */
    /*****************************/
    I3D_Mesh->Faces[3]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

    if(I3D_Mesh->ConstructionMode==IGL_POLYMODE_RIGHT)
    {
       vertice0 = CIMTVetor(centro + CIMTVetor( Largura, Altura,-Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor(-Largura, Altura,-Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor(-Largura,-Altura,-Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor( Largura,-Altura,-Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
          I3D_Mesh->Faces[3]->Vertices[0].x = vertice3.x;
          I3D_Mesh->Faces[3]->Vertices[0].y = vertice3.y;
          I3D_Mesh->Faces[3]->Vertices[0].z = vertice3.z;
          I3D_Mesh->Faces[3]->Vertices[1].x = vertice2.x;
          I3D_Mesh->Faces[3]->Vertices[1].y = vertice2.y;
          I3D_Mesh->Faces[3]->Vertices[1].z = vertice2.z;
          I3D_Mesh->Faces[3]->Vertices[2].x = vertice1.x;
          I3D_Mesh->Faces[3]->Vertices[2].y = vertice1.y;
          I3D_Mesh->Faces[3]->Vertices[2].z = vertice1.z;
          I3D_Mesh->Faces[3]->Vertices[3].x = vertice0.x;
          I3D_Mesh->Faces[3]->Vertices[3].y = vertice0.y;
          I3D_Mesh->Faces[3]->Vertices[3].z = vertice0.z;
          I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
          I3D_Mesh->Faces[3]->Vertices[0].x = vertice0.x;
          I3D_Mesh->Faces[3]->Vertices[0].y = vertice0.y;
          I3D_Mesh->Faces[3]->Vertices[0].z = vertice0.z;
          I3D_Mesh->Faces[3]->Vertices[1].x = vertice1.x;
          I3D_Mesh->Faces[3]->Vertices[1].y = vertice1.y;
          I3D_Mesh->Faces[3]->Vertices[1].z = vertice1.z;
          I3D_Mesh->Faces[3]->Vertices[2].x = vertice2.x;
          I3D_Mesh->Faces[3]->Vertices[2].y = vertice2.y;
          I3D_Mesh->Faces[3]->Vertices[2].z = vertice2.z;
          I3D_Mesh->Faces[3]->Vertices[3].x = vertice3.x;
          I3D_Mesh->Faces[3]->Vertices[3].y = vertice3.y;
          I3D_Mesh->Faces[3]->Vertices[3].z = vertice3.z;
          I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }
    else
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Altura,-Largura,-Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor(-Altura, Largura,-Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Altura, Largura,-Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor( Altura,-Largura,-Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
           I3D_Mesh->Faces[3]->Vertices[0].x = vertice0.x;
           I3D_Mesh->Faces[3]->Vertices[0].y = vertice0.y;
           I3D_Mesh->Faces[3]->Vertices[0].z = vertice0.z;
           I3D_Mesh->Faces[3]->Vertices[1].x = vertice1.x;
           I3D_Mesh->Faces[3]->Vertices[1].y = vertice1.y;
           I3D_Mesh->Faces[3]->Vertices[1].z = vertice1.z;
           I3D_Mesh->Faces[3]->Vertices[2].x = vertice2.x;
           I3D_Mesh->Faces[3]->Vertices[2].y = vertice2.y;
           I3D_Mesh->Faces[3]->Vertices[2].z = vertice2.z;
           I3D_Mesh->Faces[3]->Vertices[3].x = vertice3.x;
           I3D_Mesh->Faces[3]->Vertices[3].y = vertice3.y;
           I3D_Mesh->Faces[3]->Vertices[3].z = vertice3.z;
           I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaV = 1;
       }
       else
       {
           I3D_Mesh->Faces[3]->Vertices[0].x = vertice3.x;
           I3D_Mesh->Faces[3]->Vertices[0].y = vertice3.y;
           I3D_Mesh->Faces[3]->Vertices[0].z = vertice3.z;
           I3D_Mesh->Faces[3]->Vertices[1].x = vertice2.x;
           I3D_Mesh->Faces[3]->Vertices[1].y = vertice2.y;
           I3D_Mesh->Faces[3]->Vertices[1].z = vertice2.z;
           I3D_Mesh->Faces[3]->Vertices[2].x = vertice1.x;
           I3D_Mesh->Faces[3]->Vertices[2].y = vertice1.y;
           I3D_Mesh->Faces[3]->Vertices[2].z = vertice1.z;
           I3D_Mesh->Faces[3]->Vertices[3].x = vertice0.x;
           I3D_Mesh->Faces[3]->Vertices[3].y = vertice0.y;
           I3D_Mesh->Faces[3]->Vertices[3].z = vertice0.z;
           I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[3]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[3]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[3]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[3]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }

    I3D_Mesh->Faces[3]->Triangulariza();
    I3D_Mesh->Faces[3]->CalculaNormal(true);
    I3D_Mesh->Faces[3]->CalculaNormalSmooth(centro);


    /*****************************/
    /*Desenha Direita            */
    /*****************************/
    I3D_Mesh->Faces[4]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

    if(I3D_Mesh->ConstructionMode==IGL_POLYMODE_RIGHT)
    {
       vertice0 = CIMTVetor(centro + CIMTVetor( Largura, Altura, Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor( Largura, Altura,-Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Largura,-Altura,-Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor( Largura,-Altura, Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
          I3D_Mesh->Faces[4]->Vertices[0].x = vertice3.x;
          I3D_Mesh->Faces[4]->Vertices[0].y = vertice3.y;
          I3D_Mesh->Faces[4]->Vertices[0].z = vertice3.z;
          I3D_Mesh->Faces[4]->Vertices[1].x = vertice2.x;
          I3D_Mesh->Faces[4]->Vertices[1].y = vertice2.y;
          I3D_Mesh->Faces[4]->Vertices[1].z = vertice2.z;
          I3D_Mesh->Faces[4]->Vertices[2].x = vertice1.x;
          I3D_Mesh->Faces[4]->Vertices[2].y = vertice1.y;
          I3D_Mesh->Faces[4]->Vertices[2].z = vertice1.z;
          I3D_Mesh->Faces[4]->Vertices[3].x = vertice0.x;
          I3D_Mesh->Faces[4]->Vertices[3].y = vertice0.y;
          I3D_Mesh->Faces[4]->Vertices[3].z = vertice0.z;
          I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
          I3D_Mesh->Faces[4]->Vertices[0].x = vertice0.x;
          I3D_Mesh->Faces[4]->Vertices[0].y = vertice0.y;
          I3D_Mesh->Faces[4]->Vertices[0].z = vertice0.z;
          I3D_Mesh->Faces[4]->Vertices[1].x = vertice1.x;
          I3D_Mesh->Faces[4]->Vertices[1].y = vertice1.y;
          I3D_Mesh->Faces[4]->Vertices[1].z = vertice1.z;
          I3D_Mesh->Faces[4]->Vertices[2].x = vertice2.x;
          I3D_Mesh->Faces[4]->Vertices[2].y = vertice2.y;
          I3D_Mesh->Faces[4]->Vertices[2].z = vertice2.z;
          I3D_Mesh->Faces[4]->Vertices[3].x = vertice3.x;
          I3D_Mesh->Faces[4]->Vertices[3].y = vertice3.y;
          I3D_Mesh->Faces[4]->Vertices[3].z = vertice3.z;
          I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }
    else
    {
       vertice0 = CIMTVetor(centro + CIMTVetor( Altura,-Largura,-Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor( Altura, Largura,-Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Altura, Largura, Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor( Altura,-Largura, Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
           I3D_Mesh->Faces[4]->Vertices[0].x = vertice0.x;
           I3D_Mesh->Faces[4]->Vertices[0].y = vertice0.y;
           I3D_Mesh->Faces[4]->Vertices[0].z = vertice0.z;
           I3D_Mesh->Faces[4]->Vertices[1].x = vertice1.x;
           I3D_Mesh->Faces[4]->Vertices[1].y = vertice1.y;
           I3D_Mesh->Faces[4]->Vertices[1].z = vertice1.z;
           I3D_Mesh->Faces[4]->Vertices[2].x = vertice2.x;
           I3D_Mesh->Faces[4]->Vertices[2].y = vertice2.y;
           I3D_Mesh->Faces[4]->Vertices[2].z = vertice2.z;
           I3D_Mesh->Faces[4]->Vertices[3].x = vertice3.x;
           I3D_Mesh->Faces[4]->Vertices[3].y = vertice3.y;
           I3D_Mesh->Faces[4]->Vertices[3].z = vertice3.z;
           I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaV = 1;
       }
       else
       {
           I3D_Mesh->Faces[4]->Vertices[0].x = vertice3.x;
           I3D_Mesh->Faces[4]->Vertices[0].y = vertice3.y;
           I3D_Mesh->Faces[4]->Vertices[0].z = vertice3.z;
           I3D_Mesh->Faces[4]->Vertices[1].x = vertice2.x;
           I3D_Mesh->Faces[4]->Vertices[1].y = vertice2.y;
           I3D_Mesh->Faces[4]->Vertices[1].z = vertice2.z;
           I3D_Mesh->Faces[4]->Vertices[2].x = vertice1.x;
           I3D_Mesh->Faces[4]->Vertices[2].y = vertice1.y;
           I3D_Mesh->Faces[4]->Vertices[2].z = vertice1.z;
           I3D_Mesh->Faces[4]->Vertices[3].x = vertice0.x;
           I3D_Mesh->Faces[4]->Vertices[3].y = vertice0.y;
           I3D_Mesh->Faces[4]->Vertices[3].z = vertice0.z;
           I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[4]->Vertices[0].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[4]->Vertices[1].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[4]->Vertices[2].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[4]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }

    I3D_Mesh->Faces[4]->Triangulariza();
    I3D_Mesh->Faces[4]->CalculaNormal(true);
    I3D_Mesh->Faces[4]->CalculaNormalSmooth(centro);

    /*****************************/
    /*Desenha a Base             */
    /*****************************/
    I3D_Mesh->Faces[5]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

    if(I3D_Mesh->ConstructionMode==IGL_POLYMODE_RIGHT)
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Largura,-Altura, Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor( Largura,-Altura, Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Largura,-Altura,-Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor(-Largura,-Altura,-Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
          I3D_Mesh->Faces[5]->Vertices[0].x = vertice3.x;
          I3D_Mesh->Faces[5]->Vertices[0].y = vertice3.y;
          I3D_Mesh->Faces[5]->Vertices[0].z = vertice3.z;
          I3D_Mesh->Faces[5]->Vertices[1].x = vertice2.x;
          I3D_Mesh->Faces[5]->Vertices[1].y = vertice2.y;
          I3D_Mesh->Faces[5]->Vertices[1].z = vertice2.z;
          I3D_Mesh->Faces[5]->Vertices[2].x = vertice1.x;
          I3D_Mesh->Faces[5]->Vertices[2].y = vertice1.y;
          I3D_Mesh->Faces[5]->Vertices[2].z = vertice1.z;
          I3D_Mesh->Faces[5]->Vertices[3].x = vertice0.x;
          I3D_Mesh->Faces[5]->Vertices[3].y = vertice0.y;
          I3D_Mesh->Faces[5]->Vertices[3].z = vertice0.z;
          I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
          I3D_Mesh->Faces[5]->Vertices[0].x = vertice0.x;
          I3D_Mesh->Faces[5]->Vertices[0].y = vertice0.y;
          I3D_Mesh->Faces[5]->Vertices[0].z = vertice0.z;
          I3D_Mesh->Faces[5]->Vertices[1].x = vertice1.x;
          I3D_Mesh->Faces[5]->Vertices[1].y = vertice1.y;
          I3D_Mesh->Faces[5]->Vertices[1].z = vertice1.z;
          I3D_Mesh->Faces[5]->Vertices[2].x = vertice2.x;
          I3D_Mesh->Faces[5]->Vertices[2].y = vertice2.y;
          I3D_Mesh->Faces[5]->Vertices[2].z = vertice2.z;
          I3D_Mesh->Faces[5]->Vertices[3].x = vertice3.x;
          I3D_Mesh->Faces[5]->Vertices[3].y = vertice3.y;
          I3D_Mesh->Faces[5]->Vertices[3].z = vertice3.z;
          I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaV = 0;
          I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaU = 1;
          I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaV = 1;
          I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaU = 0;
          I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaV = 1;
       }
    }
    else
    {
       vertice0 = CIMTVetor(centro + CIMTVetor(-Altura,-Largura, Profundidade));
       vertice1 = CIMTVetor(centro + CIMTVetor(-Altura,-Largura,-Profundidade));
       vertice2 = CIMTVetor(centro + CIMTVetor( Altura,-Largura,-Profundidade));
       vertice3 = CIMTVetor(centro + CIMTVetor( Altura,-Largura, Profundidade));
       if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
       {
           I3D_Mesh->Faces[5]->Vertices[0].x = vertice0.x;
           I3D_Mesh->Faces[5]->Vertices[0].y = vertice0.y;
           I3D_Mesh->Faces[5]->Vertices[0].z = vertice0.z;
           I3D_Mesh->Faces[5]->Vertices[1].x = vertice1.x;
           I3D_Mesh->Faces[5]->Vertices[1].y = vertice1.y;
           I3D_Mesh->Faces[5]->Vertices[1].z = vertice1.z;
           I3D_Mesh->Faces[5]->Vertices[2].x = vertice2.x;
           I3D_Mesh->Faces[5]->Vertices[2].y = vertice2.y;
           I3D_Mesh->Faces[5]->Vertices[2].z = vertice2.z;
           I3D_Mesh->Faces[5]->Vertices[3].x = vertice3.x;
           I3D_Mesh->Faces[5]->Vertices[3].y = vertice3.y;
           I3D_Mesh->Faces[5]->Vertices[3].z = vertice3.z;
           I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaV = 0;
       }
       else
       {
           I3D_Mesh->Faces[5]->Vertices[0].x = vertice3.x;
           I3D_Mesh->Faces[5]->Vertices[0].y = vertice3.y;
           I3D_Mesh->Faces[5]->Vertices[0].z = vertice3.z;
           I3D_Mesh->Faces[5]->Vertices[1].x = vertice2.x;
           I3D_Mesh->Faces[5]->Vertices[1].y = vertice2.y;
           I3D_Mesh->Faces[5]->Vertices[1].z = vertice2.z;
           I3D_Mesh->Faces[5]->Vertices[2].x = vertice1.x;
           I3D_Mesh->Faces[5]->Vertices[2].y = vertice1.y;
           I3D_Mesh->Faces[5]->Vertices[2].z = vertice1.z;
           I3D_Mesh->Faces[5]->Vertices[3].x = vertice0.x;
           I3D_Mesh->Faces[5]->Vertices[3].y = vertice0.y;
           I3D_Mesh->Faces[5]->Vertices[3].z = vertice0.z;
           I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[5]->Vertices[0].I3D_CoordTexturaV = 0;
           I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaU = 1;
           I3D_Mesh->Faces[5]->Vertices[1].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[5]->Vertices[2].I3D_CoordTexturaV = 1;
           I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaU = 0;
           I3D_Mesh->Faces[5]->Vertices[3].I3D_CoordTexturaV = 0;
       }
    }


    I3D_Mesh->Faces[5]->Triangulariza();
    I3D_Mesh->Faces[5]->CalculaNormal(true);
    I3D_Mesh->Faces[5]->CalculaNormalSmooth(centro);

    I3D_Mesh->SetaShader(I3D_Shader);
    I3D_Mesh->SetaWindingMode  (I3D_Mesh->WindingMode);//Seta WindingMode dos Poligonos
    I3D_Mesh->CalculaBorda     (                     );//Calcula a Borda do Cubo
    I3D_Mesh->CalculaNrml      (centro               );//Calcula as Normais do Cubo(Planares e Smooth)
    I3D_Mesh->CalculaTgns      (                     );//Calcula as Tangentes do Cubo(Tangente e BiTangente)
    I3D_Mesh->ConstroiBuffersSH(                     );//Aloca os Buffers na GPU da Placa de Video

    I3D_Pos = I3D_Mesh->I3D_BordaMesh.PegaCentro(); //Seta a Posição do Objeto
}

