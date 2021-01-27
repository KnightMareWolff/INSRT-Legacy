#include "I3D_Cilindro.h"

CI3DCilindro::CI3DCilindro():
    CI3DPrimitivo()
{
    I3D_Mesh->PolygonMode=IGL_RENDER_POLYGON;
}

CI3DCilindro::CI3DCilindro(CIMTVetor pPos):
    CI3DPrimitivo()
{
    I3D_Pos = pPos;
    Build();
}

void CI3DCilindro::Build()
{
    long        IndexFace;
    CIMTVetor	CoordenadaPonto[2];
    CIMTVetor   Centro;
    int			s , k;

    float       Bordas=12.0f,Camadas=1.0f;

    float       Altura,Largura,Profundidade;

    int	        iNumeroFaces    = Bordas;
    int	        iNumeroPilhas   = Camadas;

    Largura     = I3D_Dim.x;
    Altura      = I3D_Dim.y;
    Profundidade= I3D_Dim.z;
    Centro      = I3D_Pos;

    // Calcula a Altura Largura e Profundidade do Cilindro.
    float LarguraPilha          = Profundidade / (float)iNumeroPilhas;
    float fAlturaCilindro	    = Altura  / 2;
    float fLarguraCilindro	    = Largura / 2;
    float fProfundidadeCilindro = Profundidade  / 2;
    float fPilhaBase			= Centro.y - fProfundidadeCilindro;

    // Calculamos quantas Faces necessarias ((QtdFaces * QtdPilhas) + 2 (Topo e Base Cilindro))
    unsigned long TotalFaces = (iNumeroFaces * iNumeroPilhas) + 2;

    IndexFace=0;

    //aloca todas as faces necessarias
    I3D_Mesh->AdicionaFaces(TotalFaces);

    //Construimos a face base primeiro
    I3D_Mesh->Faces[IndexFace]->AdicionaVertices (iNumeroFaces,IGL_RENDER_TRIANGLES);

    int index = iNumeroFaces;

    //para cada ponto na face
    for ( s = 0; s < iNumeroFaces; s++ )
    {
        index--;

        //calcula valor theta
        float theta = (2 * PI * s)/(iNumeroFaces);

        //gera coordenada do vertice
        I3D_Mesh->Faces[IndexFace]->SetaVertice( index,
                                       CI3DVertice( Centro.x + sinf (theta) * fAlturaCilindro,
                                                    Centro.y - fProfundidadeCilindro,
                                                    Centro.z + cosf (theta) * fLarguraCilindro));


     } // proximo ponto da face

     I3D_Mesh->Faces[IndexFace]->Triangulariza();
     I3D_Mesh->Faces[IndexFace]->I3D_NormalFace = I3D_Mesh->Faces[IndexFace]->CalculaNormal(true);

     //Incrementa para o inicio das faces laterais
     IndexFace++;

     //agora adiciona todas as laterais
     for ( k = 0; k < iNumeroPilhas; k++)
     {
         //para cada face
         for ( s = 0; s < iNumeroFaces; s++)
         {
             //Calcula os thetas do topo e da base thetas
             float theta  = (2 * PI *  s   ) / (iNumeroFaces);
             float theta2 = (2 * PI * (s+1)) / (iNumeroFaces);

             // Pega as duas Coordenadas X e Z para dos edges da Face do poligono
             CoordenadaPonto[0].x = Centro.x + sinf(theta ) * fAlturaCilindro;
             CoordenadaPonto[0].z = Centro.z + cosf(theta ) * fLarguraCilindro;
             CoordenadaPonto[1].x = Centro.x + sinf(theta2) * fAlturaCilindro;
             CoordenadaPonto[1].z = Centro.z + cosf(theta2) * fLarguraCilindro;

             // aloca os 4 vertices da face
             I3D_Mesh->Faces[IndexFace]->AdicionaVertices(4,IGL_RENDER_TRIANGLES);

             // preenche os vertices
             I3D_Mesh->Faces[IndexFace]->SetaVertice(0 , CI3DVertice( CoordenadaPonto[1].x, fPilhaBase             , CoordenadaPonto[1].z ));
             I3D_Mesh->Faces[IndexFace]->SetaVertice(1 , CI3DVertice( CoordenadaPonto[1].x, fPilhaBase+LarguraPilha, CoordenadaPonto[1].z ));
             I3D_Mesh->Faces[IndexFace]->SetaVertice(2 , CI3DVertice( CoordenadaPonto[0].x, fPilhaBase+LarguraPilha, CoordenadaPonto[0].z ));
             I3D_Mesh->Faces[IndexFace]->SetaVertice(3 , CI3DVertice( CoordenadaPonto[0].x, fPilhaBase             , CoordenadaPonto[0].z ));
             I3D_Mesh->Faces[IndexFace]->Triangulariza();
             I3D_Mesh->Faces[IndexFace]->I3D_NormalFace = I3D_Mesh->Faces[IndexFace]->CalculaNormal(true);

             // vai para a proxima face
             IndexFace++;
         }
         //vai para a proxima pilha
         fPilhaBase += LarguraPilha;
     }

     //Construimos agora face topo do cilindro
     I3D_Mesh->Faces[IndexFace]->AdicionaVertices (iNumeroFaces,IGL_RENDER_TRIANGLES);

     //para cada ponto na face
     for ( s = 0; s < iNumeroFaces; s++ )
     {
         //calcula valor theta
         float theta = (2 * PI * s) / (iNumeroFaces);

         //gera coordenada do vertice
         I3D_Mesh->Faces[IndexFace]->SetaVertice( s,
                                        CI3DVertice( Centro.x + sinf (theta) * fAlturaCilindro,
                                                     Centro.y + fProfundidadeCilindro,
                                                     Centro.z + cosf (theta) * fLarguraCilindro));

     } // proximo ponto da face

     I3D_Mesh->Faces[IndexFace]->Triangulariza();
     I3D_Mesh->Faces[IndexFace]->I3D_NormalFace = I3D_Mesh->Faces[IndexFace]->CalculaNormal(true);
     I3D_Mesh->SetaShader       (I3D_Shader);
     I3D_Mesh->CalculaBorda     (      ); //Calcula a Borda da Esfera
     I3D_Mesh->CalculaNrml      (Centro); //Calcula as Normais da Esfera
     BuildTextureCoord          (      ); //Calcula as Coordenadas de Textura da Esfera
     I3D_Mesh->CalculaTgns      (      ); //Calcula as Tangentes do Cubo(Tangente e BiTangente)
     I3D_Mesh->ConstroiBuffersSH(      ); //Aloca os Buffers na GPU da Placa de Video
}

void CI3DCilindro::BuildTextureCoord()
{
    GLfloat	fSpan[3];
    GLfloat	fTextureCoord[3];
    int X,Y,Z;
    X=0;Y=1;Z=2;
    float PlusXs, PlusYs, PlusZs;
    float PlusXt, PlusYt, PlusZt;
    float NegXs , NegYs , NegZs ;
    float NegXt , NegYt , NegZt ;
    CIMTVetor Centro;

    Centro = I3D_Mesh->CalculaBorda().PegaCentro();

    for(long i=0;i < I3D_Mesh->I3D_QtdFaces;i++)
    {

       I3D_Mesh->Faces[i]->CalculaBordaFace();

       fSpan[X] = (GLfloat)fabs(I3D_Mesh->Faces[i]->BordaFace.Diff(I3D_Mesh->Faces[i]->BordaFace.IMT_MaxVetorBorda.x,I3D_Mesh->Faces[i]->BordaFace.IMT_MinVetorBorda.x));
       fSpan[Y] = (GLfloat)fabs(I3D_Mesh->Faces[i]->BordaFace.Diff(I3D_Mesh->Faces[i]->BordaFace.IMT_MaxVetorBorda.y,I3D_Mesh->Faces[i]->BordaFace.IMT_MinVetorBorda.y));
       fSpan[Z] = (GLfloat)fabs(I3D_Mesh->Faces[i]->BordaFace.Diff(I3D_Mesh->Faces[i]->BordaFace.IMT_MaxVetorBorda.z,I3D_Mesh->Faces[i]->BordaFace.IMT_MinVetorBorda.z));

       CIMTVetor Normal = I3D_Mesh->Faces[i]->CalculaNormal(false);

       for ( unsigned int v = 0; v < I3D_Mesh->Faces[i]->I3D_QtdVertices; v++ )
       {
          CIMTVetor dir;

          fTextureCoord[X] = (I3D_Mesh->Faces[i]->Vertices[v].x - I3D_Mesh->Faces[i]->BordaFace.IMT_MinVetorBorda.x)/fSpan[X];
          fTextureCoord[Y] = (I3D_Mesh->Faces[i]->Vertices[v].y - I3D_Mesh->Faces[i]->BordaFace.IMT_MinVetorBorda.y)/fSpan[Y];
          fTextureCoord[Z] = (I3D_Mesh->Faces[i]->Vertices[v].z - I3D_Mesh->Faces[i]->BordaFace.IMT_MinVetorBorda.z)/fSpan[Z];

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

          dir.x = (GLfloat)fabs(Normal.x);
          dir.y = (GLfloat)fabs(Normal.y);
          dir.z = (GLfloat)fabs(Normal.z);

          if(dir.x >= dir.y && dir.x >= dir.z)
          {
             if(Normal.x > 0)
             {
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaU = PlusXs;
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaV = PlusXt;
             }
             else
             {
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaU = NegXs;
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaV = NegXt;
             }
          }
          else if(dir.y >= dir.x && dir.y >= dir.z)
          {
             if(Normal.y > 0)
             {
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaU = PlusYs;
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaV = PlusYt;
             }
             else
             {
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaU = NegYs;
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaV = NegYt;
             }
          }
          else
          {
             if(Normal.z > 0)
             {
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaU = PlusZs;
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaV = PlusZt ;
             }
             else
             {
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaU = NegZs ;
                I3D_Mesh->Faces[i]->Vertices[v].I3D_CoordTexturaV = NegZt ;
             }
          }
       }
    }
}
