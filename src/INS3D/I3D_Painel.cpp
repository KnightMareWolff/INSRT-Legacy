/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_Painel.h"


CI3DPainel::CI3DPainel():
    CI3DPrimitivo()
{
    I3D_Mesh->PolygonMode =IGL_RENDER_TRIANGLES;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;
    iTpPainel   =IGL_PAINEL_DEFAULT;

    bPainelInicializado = false;
    I3D_Altura          = 4;
    I3D_Largura         = 4;
    I3D_TamQuad         = 16;
}

CI3DPainel::CI3DPainel(int pWindingMode):
    CI3DPrimitivo()
{
    I3D_Mesh->PolygonMode =IGL_RENDER_TRIANGLES;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;
    iTpPainel   =IGL_PAINEL_DEFAULT;

    I3D_Mesh->WindingMode         = pWindingMode;
    bPainelInicializado = false;
    I3D_Altura          = 4;
    I3D_Largura         = 4;
    I3D_TamQuad         = 16;
}

bool CI3DPainel::SetaTamanho(int pAltura ,int pLargura)
{
    if(bPainelInicializado)
    {
        qWarning() << "Tentativa de inicialização de painel já construido.";
        return false;
    }

    I3D_Altura      = pAltura;
    I3D_Largura     = pLargura;

    Build();
    bPainelInicializado = true;
    return true;
}

void CI3DPainel::Build()
{
    int   NumeroFaces    = ((I3D_Altura-I3D_TamQuad)/I3D_TamQuad) * ((I3D_Largura-I3D_TamQuad)/I3D_TamQuad);
    int   Index          = 0;

    float x,y,z;

    CI3DVertice vertice1,
                vertice2,
                vertice3,
                vertice4;


    I3D_Mesh->AdicionaFaces(NumeroFaces);
    /****************************************/
    /*Adiciona o Total de Vertices do Painel*/
    /****************************************/
    for ( int X = 0;  X < (I3D_Altura - I3D_TamQuad); X +=I3D_TamQuad )
    {
       for ( int Y = 0; Y < (I3D_Largura - I3D_TamQuad ); Y +=I3D_TamQuad )
       {
           I3D_Mesh->Faces[Index]->AdicionaVertices(4,I3D_Mesh->PolygonMode);

           // Embaixo e Esquerda
           x = X;
           y = 0;
           z = Y;

           vertice1                   = CI3DVertice(x, y, z);
           vertice1.I3D_CoordTexturaU = 0.0f;
           vertice1.I3D_CoordTexturaV = 0.0f;
           vertice1.I3D_CoordDetTextU = 0.0f;
           vertice1.I3D_CoordDetTextU = 0.0f;
           vertice1.I3D_CoordLtmTextU = 0.0f;
           vertice1.I3D_CoordLtmTextU = 0.0f;

           // Acima e Esquerda
           x = X;
           y = 0;
           z = Y + I3D_TamQuad ;

           vertice2                   = CI3DVertice(x, y, z);
           vertice2.I3D_CoordTexturaU = 1.0f;
           vertice2.I3D_CoordTexturaV = 0.0f;
           vertice2.I3D_CoordDetTextU = 1.0f;
           vertice2.I3D_CoordDetTextV = 0.0f;
           vertice2.I3D_CoordLtmTextU = 1.0f;
           vertice2.I3D_CoordLtmTextV = 0.0f;

           // Acima e Direita
           x = X + I3D_TamQuad;
           y = 0;
           z = Y + I3D_TamQuad ;

           vertice3                   = CI3DVertice(x, y, z);
           vertice3.I3D_CoordTexturaU = 1.0f;
           vertice3.I3D_CoordTexturaV = 1.0f;
           vertice3.I3D_CoordDetTextU = 1.0f;
           vertice3.I3D_CoordDetTextV = 1.0f;
           vertice3.I3D_CoordLtmTextU = 1.0f;
           vertice3.I3D_CoordLtmTextV = 1.0f;

           // Embaixo e Direita
           x = X + I3D_TamQuad;
           y = 0;
           z = Y;

           vertice4                   = CI3DVertice(x, y, z);
           vertice4.I3D_CoordTexturaU = 0.0f;
           vertice4.I3D_CoordTexturaV = 1.0f;
           vertice4.I3D_CoordDetTextU = 0.0f;
           vertice4.I3D_CoordDetTextV = 1.0f;
           vertice4.I3D_CoordLtmTextU = 0.0f;
           vertice4.I3D_CoordLtmTextV = 1.0f;

           if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
           {
               //Preenchemos o vetor de vertices
               I3D_Mesh->Faces[Index]->Vertices[0]     = vertice1;
               I3D_Mesh->Faces[Index]->Vertices[1]     = vertice2;
               I3D_Mesh->Faces[Index]->Vertices[2]     = vertice3;
               I3D_Mesh->Faces[Index]->Vertices[3]     = vertice4;
           }
           else
           {
               //Preenchemos o vetor de vertices
               I3D_Mesh->Faces[Index]->Vertices[0]     = vertice4;
               I3D_Mesh->Faces[Index]->Vertices[1]     = vertice3;
               I3D_Mesh->Faces[Index]->Vertices[2]     = vertice2;
               I3D_Mesh->Faces[Index]->Vertices[3]     = vertice1;
           }

           //Armazena a coordenada base da textura
           I3D_Mesh->Faces[Index]->I3D_HeightMapXY = CIMTVetor2(x,z);

           I3D_Mesh->Faces[Index]->Triangulariza();
           I3D_Mesh->Faces[Index]->CalculaNormal(true);
           I3D_Mesh->Faces[Index]->CalculaBordaFace();
           Index++;
       }
    }

    I3D_Mesh->SetaShader    (I3D_Shader                          );
    I3D_Mesh->CalculaBorda  (                                    );
    I3D_Mesh->CalculaNrml   (I3D_Mesh->I3D_BordaMesh.PegaCentro());
    BuildTextureCoordSH     (                                    );

    if(iTpPainel == IGL_PAINEL_DEFAULT)
    {
       I3D_Mesh->ConstroiBuffersSH  (                          );
    }

    I3D_Pos = I3D_Mesh->I3D_BordaMesh.PegaCentro();
}

void CI3DPainel::BuildTextureCoordPF()
{
    GLfloat	fSpan[3];
    GLfloat	fTextureCoord[3];
    int X,Y,Z;
    X=0;Y=1;Z=2;
    float PlusXs, PlusYs, PlusZs;
    float PlusXt, PlusYt, PlusZt;
    float NegXs , NegYs , NegZs ;
    float NegXt , NegYt , NegZt ;
    CIMTBorda borda;

    borda.CalculaBordaMesh(I3D_Mesh->Faces[0]->Vertices,I3D_Mesh->Faces[0]->I3D_QtdVertices,sizeof(CI3DVertice),true);

    fSpan[X] = (GLfloat)fabs(borda.Diff(borda.IMT_MaxVetorBorda.x,borda.IMT_MinVetorBorda.x));
    fSpan[Y] = (GLfloat)fabs(borda.Diff(borda.IMT_MaxVetorBorda.y,borda.IMT_MinVetorBorda.y));
    fSpan[Z] = (GLfloat)fabs(borda.Diff(borda.IMT_MaxVetorBorda.z,borda.IMT_MinVetorBorda.z));

    for ( int v = 0; v < I3D_Mesh->Faces[0]->I3D_QtdVertices ; v++ )
    {
        CIMTVetor dir;

        fTextureCoord[X] = (I3D_Mesh->Faces[0]->Vertices[v].x - borda.IMT_MinVetorBorda.x)/fSpan[X];
        fTextureCoord[Y] = (I3D_Mesh->Faces[0]->Vertices[v].y - borda.IMT_MinVetorBorda.y)/fSpan[Y];
        fTextureCoord[Z] = (I3D_Mesh->Faces[0]->Vertices[v].z - borda.IMT_MinVetorBorda.z)/fSpan[Z];

        PlusXs =   fTextureCoord[Z] ;
        PlusXt =   fTextureCoord[Y] ;

        PlusYs = 1-fTextureCoord[X] ;
        PlusYt =   fTextureCoord[Z] ;

        PlusZs =   fTextureCoord[X] ;
        PlusZt =   fTextureCoord[Y] ;

        NegXs =  1-fTextureCoord[Z] ;
        NegXt =    fTextureCoord[Y] ;

        NegYs =    fTextureCoord[X] ;
        NegYt =    fTextureCoord[Z] ;

        NegZs =    fTextureCoord[X] ;
        NegZt =  1-fTextureCoord[Y] ;

        dir.x = (GLfloat)fabs(I3D_Mesh->Faces[0]->Vertices[v].I3D_PlanarNormal.x);
        dir.y = (GLfloat)fabs(I3D_Mesh->Faces[0]->Vertices[v].I3D_PlanarNormal.y);
        dir.z = (GLfloat)fabs(I3D_Mesh->Faces[0]->Vertices[v].I3D_PlanarNormal.z);

        if(dir.x >= dir.y && dir.x >= dir.z)
        {
           if(I3D_Mesh->Faces[0]->Vertices[v].I3D_PlanarNormal.x > 0)
           {
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaU = PlusXs;
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaV = PlusXt;
           }
           else
           {
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaU = NegXs;
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaV = NegXt;
           }
        }
        else if(dir.y >= dir.x && dir.y >= dir.z)
        {
           if(I3D_Mesh->Faces[0]->Vertices[v].I3D_PlanarNormal.y > 0)
           {
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaU = PlusYs;
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaV = PlusYt;
           }
           else
           {
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaU = NegYs;
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaV = NegYt;
           }
        }
        else
        {
           if(I3D_Mesh->Faces[0]->Vertices[v].I3D_PlanarNormal.z > 0)
           {
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaU = PlusZs;
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaV = PlusZt ;
           }
           else
           {
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaU = NegZs ;
              I3D_Mesh->Faces[0]->Vertices[v].I3D_CoordTexturaV = NegZt ;
           }
        }
     }
}

void CI3DPainel::BuildTextureCoordSH()
{
    GLfloat	fSpan[3];
    GLfloat	fTextureCoord[3];
    int X,Y,Z;
    X=0;Y=1;Z=2;
    float PlusXs, PlusYs, PlusZs;
    float PlusXt, PlusYt, PlusZt;
    float NegXs , NegYs , NegZs ;
    float NegXt , NegYt , NegZt ;
    CIMTBorda borda;

    borda.Limpa();
    for ( long i = 0; i < I3D_Mesh->I3D_QtdFaces; i++ )
    {
        borda.CalculaBordaMesh( I3D_Mesh->Faces[i]->Vertices,
                                I3D_Mesh->Faces[i]->I3D_QtdVertices ,
                                sizeof(CI3DVertice)       ,
                                false                    );
    }

    fSpan[X] = (GLfloat)fabs(borda.Diff(borda.IMT_MaxVetorBorda.x,borda.IMT_MinVetorBorda.x));
    fSpan[Y] = (GLfloat)fabs(borda.Diff(borda.IMT_MaxVetorBorda.y,borda.IMT_MinVetorBorda.y));
    fSpan[Z] = (GLfloat)fabs(borda.Diff(borda.IMT_MaxVetorBorda.z,borda.IMT_MinVetorBorda.z));

    for ( int u = 0; u < I3D_Mesh->I3D_QtdFaces ; u++ )
    {
        for ( int v = 0; v < I3D_Mesh->Faces[u]->I3D_QtdVertices ; v++ )
        {
            CIMTVetor dir;

            fTextureCoord[X] = (I3D_Mesh->Faces[u]->Vertices[v].x - borda.IMT_MinVetorBorda.x)/fSpan[X];
            fTextureCoord[Y] = (I3D_Mesh->Faces[u]->Vertices[v].y - borda.IMT_MinVetorBorda.y)/fSpan[Y];
            fTextureCoord[Z] = (I3D_Mesh->Faces[u]->Vertices[v].z - borda.IMT_MinVetorBorda.z)/fSpan[Z];

            PlusXs =   fTextureCoord[Z] ;
            PlusXt =   fTextureCoord[Y] ;

            PlusYs = 1-fTextureCoord[X] ;
            PlusYt =   fTextureCoord[Z] ;

            PlusZs =   fTextureCoord[X] ;
            PlusZt =   fTextureCoord[Y] ;

            NegXs =  1-fTextureCoord[Z] ;
            NegXt =    fTextureCoord[Y] ;

            NegYs =    fTextureCoord[X] ;
            NegYt =    fTextureCoord[Z] ;

            NegZs =    fTextureCoord[X] ;
            NegZt =  1-fTextureCoord[Y] ;

            dir.x = (GLfloat)fabs(I3D_Mesh->Faces[u]->Vertices[v].I3D_PlanarNormal.x);
            dir.y = (GLfloat)fabs(I3D_Mesh->Faces[u]->Vertices[v].I3D_PlanarNormal.y);
            dir.z = (GLfloat)fabs(I3D_Mesh->Faces[u]->Vertices[v].I3D_PlanarNormal.z);

            if(dir.x >= dir.y && dir.x >= dir.z)
            {
                if(I3D_Mesh->Faces[u]->Vertices[v].I3D_PlanarNormal.x > 0)
                {
                    I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaU = PlusXs;
                    I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaV = PlusXt;
                    I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextU = PlusXs;
                    I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextV = PlusXt;
                }
                else
                {
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaU = NegXs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaV = NegXt;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextU = NegXs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextV = NegXt;
                }
            }
            else if(dir.y >= dir.x && dir.y >= dir.z)
            {
                if(I3D_Mesh->Faces[u]->Vertices[v].I3D_PlanarNormal.y > 0)
                {
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaU = PlusYs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaV = PlusYt;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextU = PlusYs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextV = PlusYt;
                }
                else
                {
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaU = NegYs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaV = NegYt;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextU = NegYs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextV = NegYt;
                }
            }
            else
            {
                if(I3D_Mesh->Faces[u]->Vertices[v].I3D_PlanarNormal.z > 0)
                {
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaU = PlusZs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaV = PlusZt ;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextU = PlusZs;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextV = PlusZt ;
                }
                else
                {
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaU = NegZs ;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordTexturaV = NegZt ;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextU = NegZs ;
                   I3D_Mesh->Faces[u]->Vertices[v].I3D_CoordDetTextV = NegZt ;
                }
            }
        }
    }
}
