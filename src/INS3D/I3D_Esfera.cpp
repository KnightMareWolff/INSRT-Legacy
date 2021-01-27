#include "I3D_Esfera.h"


CI3DEsfera::CI3DEsfera():
    CI3DPrimitivo()
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;
}

CI3DEsfera::CI3DEsfera(CIMTVetor pPos):
    CI3DPrimitivo(pPos)
{
    Build();
}

void CI3DEsfera::Build()
{
    CI3DVertice *VerticesTemporarios =NULL  ;
    CI3DVertice *VerticeAtual        =NULL  ;
    ulong		 IndexFace           = 0    ;
    int          mNumeroBandas       = 20   ;
    float        fRaio               = 0    ;
    CIMTVetor    centro              = I3D_Pos ;


    float Altura,Largura,Profundidade;


    Largura      = I3D_Dim.x;
    Altura       = I3D_Dim.y;
    Profundidade = I3D_Dim.z;

    fRaio        = Altura / 2;
    IndexFace    = 0;

    /*****************************************************************/
    /*Cria Vertices temporarios para armazenar os vertices da Esfera */
    /*****************************************************************/
    VerticesTemporarios = new CI3DVertice [ (mNumeroBandas - 1) * mNumeroBandas + 2];

    //atribui ao vertice atual o endereço de memoria dos vertices temporarios
    VerticeAtual        = VerticesTemporarios ;

    //Cria o Vertice inicial do Topo da Esfera(Central e acima dos outros vertices)
   *VerticeAtual        = CI3DVertice ( 0.0f  + centro.x ,
                                        fRaio + centro.y ,
                                        0.0f  + centro.z);

    //Atenção! Incrementa endereço de memoria dos vertices temporarios.
    VerticeAtual ++;

    //Calcula o componente alpha
    float alpha  = PI / mNumeroBandas;
    float alphaB = alpha;

    //Computa o valor Y para manter cada vertice ABAIXO do vertice centrald do segmento.
    float Y  = fRaio * cosf(alphaB);

    //Computa o fator X/Z(Funciona como Raio do plano XZ)
    float xz = fRaio * sinf(alphaB);

    //Componente alpha temporario para incrementarmos ao redor da Banda.
    float tAlpha=0;

    /************************************************************************/
    /*Realiza os calculos para a Formação dos Segmentos  da Esfera          */
    /*Basicamente a ideia inicial é sempre ter o vertice inicial 0          */
    /*Apos isto irmos circulando as bandas e criando os vertices ate formar */
    /*o Segmento Final.                                                     */
    /*Todos os segmentos serao incluidos neste vetor temporario de vertices */
    /*No qual apos todos os calculos realizados podemos percorrer todo o    */
    /*vetor formando finalmente nosso objeto, ou seja:                      */
    /* Topo -> Corpo -> Base                                                */
    /*Se verificarmos tanto o topo como a base possuem seu vertice inicial  */
    /*no centro e triangularizado, ao inves de termos quads                 */
    /*este objeto representa bem a necessidade de uma classe poligono para  */
    /*o tratamento de criação/renderização de objetos, onde no caso de nossa*/
    /*esfera temos um "Mix" de dois tipos de faces(triangulos e quads) no   */
    /*mesmo objeto.                                                         */
    /************************************************************************/
    //Proximo  vertice disponivel
    int iv = 1	;
    //Primeiro vertice DESTE Segmento
    int iv1= iv;

    //Percorre a primeiro Segmento(Topo)
    for (int i = 0; i < mNumeroBandas ; i++)
    {
        //Calcula a posicao do vertice
        VerticeAtual->x = (xz * sinf(tAlpha)) + centro.x;
        VerticeAtual->y =   Y + centro.y;
        VerticeAtual->z = (xz * cosf(tAlpha)) + centro.z;

        //Atenção! Incrementa endereço de memoria dos vertices temporarios.
        VerticeAtual ++;

        //atualiza o indexador de vertice de inicio do proximo segmento.(proximo vertice livre)
        iv ++;

        //Incrementa o alpha temporario
        tAlpha += alpha * 2;
    }

    //aloca a quantidade necessaria de faces para este segmento(uma face para cada banda)
    I3D_Mesh->AdicionaFaces(mNumeroBandas);

    //percorre cada face e cria os vertices do objeto(segmento TOPO)
    for (int i = 0; i < mNumeroBandas ; i++)
    {
        //Para cada face do topo teremos 3 vertices
        I3D_Mesh->Faces[IndexFace]->AdicionaVertices ( 3,IGL_RENDER_TRIANGLES );

        I3D_Mesh->Faces[IndexFace]->SetaVertice (0, VerticesTemporarios[ iv1 + ( i      % mNumeroBandas)]);
        I3D_Mesh->Faces[IndexFace]->SetaVertice (1, VerticesTemporarios[ iv1 + ((i + 1) % mNumeroBandas)]);
        I3D_Mesh->Faces[IndexFace]->SetaVertice (2, VerticesTemporarios[             0                  ]);

        I3D_Mesh->Faces[IndexFace]->Triangulariza();

        I3D_Mesh->Faces[IndexFace]->CalculaNormal(true);
        I3D_Mesh->Faces[IndexFace]->CalculaNormalSmooth(centro);

        //Faces[IndexFace]->cor.SetaCor(0,0.5f,0.5f,1.0f);

        //incrementa face do segmento
        IndexFace ++;

    }

    //Percorre o segundo Segmento(Corpo),isolando o Topo e Base
    for (int nBanda = 1; nBanda < mNumeroBandas - 1 ; nBanda ++)
    {
        //incrementa componente alpha
        alphaB += alpha;

        //Computa valor Y
        Y  = fRaio * cosf(alphaB);

        //Computa o fator X/Z(Funciona como Raio do plano XZ)
        xz = fRaio * sinf(alphaB);

        //Componente alpha temporario para incrementarmos ao redor do Segmento.
        tAlpha = 0;

        //Primeiro vertice DESTE Segmento
        iv1 = iv;

        /***********************************************************************************/
        /*atribui ao vertice atual o endereço de memoria dos vertices temporarios apontando*/
        /*para o primeiro vertice livre apos o processamento do Segmento TOPO              */
        /***********************************************************************************/
        VerticeAtual= &VerticesTemporarios [iv1] ;


        //Calcula os vertices temporarios da banda incrementando os vertices temporarios
        for ( int i=0 ; i< mNumeroBandas ; i++)
        {
            //Calcula a posicao do vertice
            VerticeAtual->x = (xz * sinf(tAlpha)) + centro.x;
            VerticeAtual->y =   Y + centro.y;
            VerticeAtual->z = (xz * cosf(tAlpha)) + centro.z;

            //Atenção! Incrementa endereço de memoria dos vertices temporarios.
            VerticeAtual ++;

            //atualiza o index de vertice de inicio do proximo segmento.(prox vertice livre)
            iv ++;

            //Componente alpha temporario para incrementarmos ao redor do Segmento.
            tAlpha += alpha * 2;

        }

        //aloca a quantidade necessaria de faces para este segmento(uma face para cada banda)
        I3D_Mesh->AdicionaFaces(mNumeroBandas);

        //percorre cada face e cria os vertices do objeto(segmento CORPO)
        for ( int i=0; i< mNumeroBandas ; i++ )
        {
            //Para cada face do topo teremos 4 vertices
            I3D_Mesh->Faces[IndexFace]->AdicionaVertices ( 4,IGL_RENDER_TRIANGLES );

            I3D_Mesh->Faces[IndexFace]->SetaVertice (0, VerticesTemporarios[ iv1 + (i % mNumeroBandas)]);
            I3D_Mesh->Faces[IndexFace]->SetaVertice (1, VerticesTemporarios[ iv1 + ((i + 1) % mNumeroBandas)]);
            I3D_Mesh->Faces[IndexFace]->SetaVertice (2, VerticesTemporarios[ iv1 - mNumeroBandas + ((i + 1) % mNumeroBandas) ]);
            I3D_Mesh->Faces[IndexFace]->SetaVertice (3, VerticesTemporarios[ iv1 - mNumeroBandas + (i % mNumeroBandas) ]);

            I3D_Mesh->Faces[IndexFace]->Triangulariza();

            I3D_Mesh->Faces[IndexFace]->CalculaNormal(true);
            I3D_Mesh->Faces[IndexFace]->CalculaNormalSmooth(centro);
            //Faces[IndexFace]->cor.SetaCor(0,0.5f,0.5f,1.0f);

            IndexFace ++;

        }

    }

    /********************************************************************/
    /*Neste ponto do Algoritmo temos somente que criar o ultimo segmento*/
    /*que representa a base da esfera                                   */
    /********************************************************************/
    //Primeiro vertice DESTE Segmento
    iv1=iv;

    /***********************************************************************************/
    /*atribui ao vertice atual o endereço de memoria dos vertices temporarios apontando*/
    /*para o primeiro vertice livre apos o processamento do Segmento BASE              */
    /***********************************************************************************/
    VerticeAtual=&VerticesTemporarios [iv1];

    //Vertice Central para construção da Base ABAIXO dos vertices da face
    *VerticeAtual = CI3DVertice ( 0.0f  + centro.x ,
                                 -fRaio + centro.y ,
                                  0.0f  + centro.z);

    //Atenção! Incrementa endereço de memoria dos vertices temporarios.
    VerticeAtual++;

    //atualiza o index de vertice de inicio do proximo segmento.(prox vertice livre)
    iv++;

    //aloca a quantidade necessaria de faces para este segmento(uma face para cada banda)
    I3D_Mesh->AdicionaFaces(mNumeroBandas);

    //percorre cada face e cria os vertices do objeto(segmento BASE)
    for (int i = 0; i < mNumeroBandas ; i++)
    {
        //Para cada face do topo teremos 3 vertices, como no TOPO
        I3D_Mesh->Faces[IndexFace]->AdicionaVertices ( 3,IGL_RENDER_TRIANGLES );

        I3D_Mesh->Faces[IndexFace]->SetaVertice (0, VerticesTemporarios[ iv1]);
        I3D_Mesh->Faces[IndexFace]->SetaVertice (1, VerticesTemporarios[ iv1	- mNumeroBandas + ((i + 1) % mNumeroBandas)]);
        I3D_Mesh->Faces[IndexFace]->SetaVertice (2, VerticesTemporarios[ iv1	- mNumeroBandas + ( i  % mNumeroBandas)]);

        I3D_Mesh->Faces[IndexFace]->Triangulariza();
        I3D_Mesh->Faces[IndexFace]->CalculaNormal(true);
        I3D_Mesh->Faces[IndexFace]->CalculaNormalSmooth(centro);
        //Faces[IndexFace]->cor.SetaCor(0,0.5f,0.5f,1.0f);

        IndexFace ++;
    }

    //UFA! Processo terminado, agora é limpar a sujeira...
    delete [] VerticesTemporarios;

    //Calcula estruturas de Controle do Objeto.
    //ChecaWindingMode (INS_FACE_MIXED);
    I3D_Mesh->SetaShader       (I3D_Shader);
    I3D_Mesh->CalculaBorda     (      ); //Calcula a Borda da Esfera
    I3D_Mesh->CalculaNrml      (centro); //Calcula as Normais da Esfera
    BuildTextureCoord          (      ); //Calcula as Coordenadas de Textura da Esfera
    I3D_Mesh->CalculaTgns      (      ); //Calcula as Tangentes do Cubo(Tangente e BiTangente)
    I3D_Mesh->ConstroiBuffersSH(      ); //Aloca os Buffers na GPU da Placa de Video

    I3D_Pos = I3D_Mesh->I3D_BordaMesh.PegaCentro(); //Seta a Posição do Objeto por garantia...
}

void CI3DEsfera::BuildTextureCoord()
{
    CIMTVetor centro = I3D_Pos;

    for(long i=0 ; i < I3D_Mesh->I3D_QtdFaces ; i++)
    {
       I3D_Mesh->Faces[i]->CalculaBordaFace();

       for ( unsigned int j = 0; j < I3D_Mesh->Faces[i]->I3D_QtdVertices ; j++ )
       {
          CIMTVetor offset = I3D_Mesh->Faces[i]->Vertices[j] - centro;

          offset.Normalizar();

          I3D_Mesh->Faces[i]->Vertices[j].I3D_CoordTexturaU = asinf(offset.y)/PI+0.5f ;
          I3D_Mesh->Faces[i]->Vertices[j].I3D_CoordTexturaV = asinf(offset.x)/PI+0.5f ;
       }
    }
}
