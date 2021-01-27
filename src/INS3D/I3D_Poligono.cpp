/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
/*13/03/2016 - Retirado rotinas de renderização Pipeline Fixa OpenGL              */
/*             Como é uma situação especifica em que placas muito antigas pedem   */
/*             E os laboratorios atuais ja nao tem mais placas assim, caso seja   */
/*             necessário, buscar nos fontes antigos as rotinas novamente         */
/**********************************************************************************/
#include "I3D_GlobalDef.h"
#include "I3D_Poligono.h"

/*******************************************************/
/*Nome do Método      : CI3DPoligono()                 */
/*Objetivo            : Construtor Padrão da classe    */
/*                      Constroi um poligono generico  */
/*                      pronto para uso.               */
/*******************************************************/
CI3DPoligono::CI3DPoligono()
{

    I3D_VertexBuffer  =NULL;
    I3D_FeedbackBuffer=NULL;
    I3D_VertexIndices =NULL;
    Vertices          =NULL;
    Indices           =NULL;
    I3D_IndicesSkin   =NULL;

    I3D_QtdVertices    = 0;
    I3D_QtdIndices     = 0;

    PolyWindingMode    = IGL_WINMODE_CCW;
}

CI3DPoligono::CI3DPoligono(const CI3DPoligono &i3dPoligono )
{
    /*********************************************/
    /*Atributos Comuns entre PF e Shaders        */
    /*********************************************/
    I3D_QtdVertices = i3dPoligono.I3D_QtdVertices;
    I3D_QtdIndices  = i3dPoligono.I3D_QtdIndices;

    AdicionaVertices(I3D_QtdVertices,IGL_RENDER_TRIANGLES);

    for(uint i=0;i<I3D_QtdVertices;i++)
    {
        Vertices[i] = i3dPoligono.Vertices[i];
    }

    PolyWindingMode = i3dPoligono.PolyWindingMode;

    Triangulariza  (    );
    CalculaNormal  (true);
    PreencheBuffers(    );
}
/*******************************************************/
/*Nome do Método      : ~CI3DPoligono()                */
/*Objetivo            : Destrutor Padrão da classe     */
/*                      Constroi um poligono generico  */
/*                      pronto para uso.               */
/*******************************************************/
CI3DPoligono::~CI3DPoligono()
{
    LimpaVertices();
    execGL(IGL_SH_DELBUFFERS,2,I3D_VboIds);
}

void CI3DPoligono::PreencheBuffers()
{
   if(I3D_VertexBuffer!=NULL)
   {
      execGL(IGL_SH_DELBUFFERS,2,I3D_VboIds);
   }
   /******************************************************/
   /*Preenche o vertex buffer comos vertices da aplicação*/
   /******************************************************/
   for(GLuint i=0;i<I3D_QtdVertices;i++)
   {
       I3D_VertexBuffer[i].position   = CIMTVetor (Vertices[i].x,Vertices[i].y,Vertices[i].z);
       I3D_VertexBuffer[i].texCoord   = CIMTVetor2(Vertices[i].I3D_CoordTexturaU,Vertices[i].I3D_CoordTexturaV);
       I3D_VertexBuffer[i].normal     = CIMTVetor (Vertices[i].I3D_PlanarNormal.x,Vertices[i].I3D_PlanarNormal.y,Vertices[i].I3D_PlanarNormal.z);
       I3D_VertexBuffer[i].smooth     = CIMTVetor (Vertices[i].I3D_SmoothNormal.x,Vertices[i].I3D_SmoothNormal.y,Vertices[i].I3D_SmoothNormal.z);
       I3D_VertexBuffer[i].tangente   = CIMTVetor (Vertices[i].I3D_Tangente.x,Vertices[i].I3D_Tangente.y,Vertices[i].I3D_Tangente.z);
       I3D_VertexBuffer[i].bitangente = CIMTVetor (Vertices[i].I3D_BiTangente.x,Vertices[i].I3D_BiTangente.y,Vertices[i].I3D_BiTangente.z);

       //Alimenta o FeedBackBuffer com as coordenadas originais
       I3D_FeedbackBuffer[i].position = CIMTVetor (Vertices[i].x,Vertices[i].y,Vertices[i].z);
   }

   /********************************/
   /*Preenche os indices do buffer */
   /********************************/
   for(GLuint j=0;j<I3D_QtdIndices;j++)
   {
       I3D_VertexIndices[j] = Indices[j];
   }

   execGL(IGL_SH_BUFFERINIT,I3D_VertexBuffer   ,
                            I3D_VertexIndices  ,
                            I3D_QtdVertices    ,
                            I3D_QtdIndices     ,
                            I3D_VboIds         );
}


/************************************************************/
/*Nome do Método      : AdicionaVertices()                  */
/*Objetivo            : Recebe um vetor de vertices e       */
/*                      os respassa para o poligono         */
/************************************************************/
int CI3DPoligono::AdicionaVertices(long i3dQtdVert, int pRenderType)
{

    CI3DVertice        *Buffer    = NULL;
    IGLVertexBuffer    *VtxBuffer = NULL;
    FeedBackData       *FdbBuffer = NULL;

    if ( i3dQtdVert == 0 ) return -1;

    try
    {
        Buffer = new CI3DVertice[ I3D_QtdVertices + i3dQtdVert ];
        if (!Buffer) throw std::bad_alloc(); // VC++ Compat

        if (Vertices)
        {
            memcpy( Buffer, Vertices,I3D_QtdVertices * sizeof(CI3DVertice));
        }

        VtxBuffer = new IGLVertexBuffer[ I3D_QtdVertices + i3dQtdVert ];
        if (!VtxBuffer) throw std::bad_alloc(); // VC++ Compat

        if (I3D_VertexBuffer)
        {
            memcpy( VtxBuffer, I3D_VertexBuffer ,I3D_QtdVertices * sizeof(IGLVertexBuffer));
        }

        FdbBuffer = new FeedBackData[ I3D_QtdVertices + i3dQtdVert ];
        if (!FdbBuffer) throw std::bad_alloc(); // VC++ Compat

        if (I3D_FeedbackBuffer)
        {
            memcpy( FdbBuffer, I3D_FeedbackBuffer ,I3D_QtdVertices * sizeof(FeedBackData));
        }
    }

    catch (...)
    {
        if (Buffer)    delete []Buffer;
        if (VtxBuffer) delete []VtxBuffer;
        if (FdbBuffer) delete []FdbBuffer;
        return -1;
    }

    delete []Vertices;
    Vertices = Buffer;

    delete []I3D_VertexBuffer;
    I3D_VertexBuffer = VtxBuffer;

    delete []I3D_FeedbackBuffer;
    I3D_FeedbackBuffer = FdbBuffer;


    I3D_QtdVertices += i3dQtdVert;

    if(I3D_QtdVertices>=3)
    {
       if(Indices)
       {
           delete []Indices;
           Indices = NULL  ;
           I3D_QtdIndices=0;
       }

       if(I3D_VertexIndices)
       {
           delete []I3D_VertexIndices;
           I3D_VertexIndices = NULL  ;
           I3D_QtdIndices=0;
       }

       if(pRenderType==IGL_RENDER_TRIANGLES      ||
          pRenderType==IGL_RENDER_TRIANGLE_STRIP ||
          pRenderType==IGL_RENDER_TRIANGLE_FAN   )
       {
          AdicionaIndices(((I3D_QtdVertices-2) * 3));
       }
       else if(pRenderType==IGL_RENDER_QUADS)
       {
          AdicionaIndices(I3D_QtdVertices);
       }
    }

    return I3D_QtdVertices - i3dQtdVert;

}

/*******************************************************/
/*Nome do Método      : AdicionaVertices()             */
/*Objetivo            : Recebe um vetor de vertices e  */
/*                      os respassa para o poligono    */
/*******************************************************/
int CI3DPoligono::AdicionaIndices(long i3dQtdInd)
{

    int      *Buffer    = NULL;
    GLuint   *VtxBuffer = NULL;
    GLuint   *SknBuffer = NULL;

    if ( i3dQtdInd == 0 ) return -1;

    try
    {
        Buffer = new int[ I3D_QtdIndices  + i3dQtdInd ];
        if (!Buffer) throw std::bad_alloc(); // VC++ Compativel?

        if (Indices)
        {
            memcpy( Buffer, Indices,I3D_QtdIndices * sizeof(int));
        }

        VtxBuffer = new GLuint[ I3D_QtdIndices  + i3dQtdInd ];
        if (!VtxBuffer) throw std::bad_alloc(); // VC++ Compativel?

        if (I3D_VertexIndices)
        {
            memcpy( VtxBuffer, I3D_VertexIndices,I3D_QtdIndices * sizeof(GLuint));

        }

        SknBuffer = new GLuint[ I3D_QtdIndices  + i3dQtdInd ];
        if (!SknBuffer) throw std::bad_alloc(); // VC++ Compativel?

        if (I3D_IndicesSkin)
        {
            memcpy( SknBuffer, I3D_IndicesSkin ,I3D_QtdIndices * sizeof(GLuint));
        }

    }

    catch (...)
    {
        if (Buffer)    delete []Buffer;
        if (VtxBuffer) delete []VtxBuffer;
        if (SknBuffer) delete []SknBuffer;
        return -1;
    }

    delete []Indices;
    Indices = Buffer;

    delete []I3D_VertexIndices;
    I3D_VertexIndices = VtxBuffer;

    delete []I3D_IndicesSkin;
    I3D_IndicesSkin = SknBuffer;

    I3D_QtdIndices += i3dQtdInd;

    return I3D_QtdIndices - i3dQtdInd;

}

/********************************************************/
/*Nome do Método      : AdicionaVertices()              */
/*Objetivo            : Recebe um vetor de vertices e   */
/*                      os respassa para o poligono     */
/********************************************************/
long CI3DPoligono::InsereVertice( unsigned long nVertexPos )
{
    /***********************************************************/
    /*ATENÇÃO! UTILIZADO RENDER POLYGON DEVIDO A NAO USAR INDEX*/
    /***********************************************************/
    if ( AdicionaVertices( 1 , IGL_RENDER_POLYGON) < 0 ) return -1;

    if ( nVertexPos != I3D_QtdVertices - 1 )
    {
        memmove( &Vertices[nVertexPos + 1], &Vertices[nVertexPos], ((I3D_QtdVertices-1) - nVertexPos) *  sizeof(CI3DVertice) );
    }

    Vertices[ nVertexPos ] = CI3DVertice( 0.0f, 0.0f, 0.0f );

    return nVertexPos;

}

/*****************************************/
/*Nome do Método      : LimpaVertices()  */
/*Objetivo            : Limpa o poligono */
/*****************************************/
void CI3DPoligono::LimpaVertices()
{
    if ( Vertices )
    {
        delete []Vertices;
        Vertices = NULL;
    }

    if(Indices)
    {
        delete []Indices;
        Indices = NULL;
    }

    I3D_QtdVertices  = 0;
    I3D_QtdIndices   = 0;
}

/***************************************************************/
/*Nome do Método      : CalculaNormal()                        */
/*Objetivo            : Calcula a normal do poligono , ou seja */
/*                      diz para onde ele está apontando...    */
/***************************************************************/
CIMTVetor CI3DPoligono::CalculaNormal(bool bUpdate)
{

    CIMTVetor   i3dLadoA      ,
                i3dLadoB      ,
                i3dMelhorLadoA,
                i3dMelhorLadoB,
                i3dRetaNormal ;

    float       i3dMelhorAngulo    ,
                i3dAnguloTemporario;
    /******************************************/
    /*Inicializamos com um angulo absurdo     */
    /******************************************/
    i3dMelhorAngulo=99999.0f;
    /******************************************/
    /*Realiza as verif. em todos os Vertices  */
    /******************************************/
    for ( GLuint i = 0; i < I3D_QtdVertices - 2; i++ )
    {
        /******************************************/
        /*Cria os lados para o produto escalar    */
        /******************************************/
        i3dLadoA = (Vertices[i+1] - Vertices[0]).Normalizar();
        i3dLadoB = (Vertices[i+2] - Vertices[0]).Normalizar();
        /*******************************************/
        /*Realiza o produto escalar entre os   dois*/
        /*Lados e obtemos o angulo entre estes dois*/
        /*Lados                                    */
        /*******************************************/
        i3dAnguloTemporario = fabsf(i3dLadoA.ProdutoEscalar(i3dLadoB));
        /********************************************/
        /*Quanto menor o angulo entre eles Melhor...*/
        /********************************************/
        if ( i3dAnguloTemporario < i3dMelhorAngulo)
        {
            i3dMelhorAngulo = i3dAnguloTemporario;
            i3dMelhorLadoA  = i3dLadoA;
            i3dMelhorLadoB  = i3dLadoB;
        }
    }
    /********************************************/
    /*Realiza o produto vetorial entre os dois  */
    /*Melhores vetores encontrados e finalmente */
    /*obtemos a reta Normal do poligono         */
    /********************************************/
    i3dRetaNormal = i3dMelhorLadoA.ProdutoVetorial(i3dMelhorLadoB);
    i3dRetaNormal.Normalizar();

    /******************************************/
    /*Atualiza os vertices do Poligono        */
    /******************************************/
    if(bUpdate)
    {
       for ( GLuint i = 0; i < I3D_QtdVertices ; i++ )
       {
          Vertices[i].I3D_PlanarNormal = i3dRetaNormal;
       }
    }

    return i3dRetaNormal;
}

/*****************************************************/
/*Nome do Método      : InverteNormal()              */
/*Objetivo            : Inverte a normal do poligono */
/*****************************************************/
CIMTVetor CI3DPoligono::InverteNormal(bool bUpdate)
{

    CIMTVetor   i3dLadoA      ,
                i3dLadoB      ,
                i3dMelhorLadoA,
                i3dMelhorLadoB,
                i3dRetaNormal ;

    float       i3dMelhorAngulo    ,
                i3dAnguloTemporario;
    /******************************************/
    /*Inicializamos com um angulo absurdo     */
    /******************************************/
    i3dMelhorAngulo=99999.0f;
    /******************************************/
    /*Realiza as verif. em todos os Vertices  */
    /******************************************/
    for ( GLuint i = 0; i < I3D_QtdVertices - 2; i++ )
    {
        /******************************************/
        /*Cria os lados para o produto escalar    */
        /******************************************/
        i3dLadoA = (Vertices[i+1] - Vertices[0]).Normalizar();
        i3dLadoB = (Vertices[i+2] - Vertices[0]).Normalizar();
        /*******************************************/
        /*Realiza o produto escalar entre os   dois*/
        /*Lados e obtemos o angulo entre estes dois*/
        /*Lados                                    */
        /*******************************************/
        i3dAnguloTemporario = fabsf(i3dLadoA.ProdutoEscalar(i3dLadoB));
        /********************************************/
        /*Quanto menor o angulo entre eles Melhor...*/
        /********************************************/
        if ( i3dAnguloTemporario < i3dMelhorAngulo)
        {
            i3dMelhorAngulo = i3dAnguloTemporario;
            i3dMelhorLadoA  = i3dLadoA;
            i3dMelhorLadoB  = i3dLadoB;
        }
    }
    /********************************************/
    /*Realiza o produto vetorial entre os dois  */
    /*Melhores vetores encontrados e finalmente */
    /*obtemos a reta Normal do poligono         */
    /********************************************/
    i3dRetaNormal = i3dMelhorLadoA.ProdutoVetorial(i3dMelhorLadoB);
    i3dRetaNormal.Normalizar();

    if(bUpdate)
    {
       for ( GLuint i = 0; i < I3D_QtdVertices ; i++ )
       {
          Vertices[i].I3D_PlanarNormal = -i3dRetaNormal;
       }
    }

    return -i3dRetaNormal;
}

bool CI3DPoligono::InvertePoligono()
{
    int			Counter	= 1;
    CI3DVertice *TVerts = NULL;

    // Cria vetor de vertices temporario
    TVerts = new CI3DVertice[I3D_QtdVertices];
    // copia vertice 0 no vetor
    TVerts[0] = Vertices[0];

    Counter = 1;
    // copia os vertices em ordem reversa no vetor
    for ( int k = I3D_QtdVertices; k > 1; k--, Counter++ )
    {
        TVerts[Counter] = Vertices[k - 1];
    }
    // Copia os vertices novamente no vetor de vertices.
    for ( uint l = 0;l<I3D_QtdVertices;l++)
    {
        Vertices[l]=TVerts[l];
    }

    memcpy( Vertices[0], &TVerts[0], I3D_QtdVertices * sizeof(CI3DVertice));
    delete []TVerts;

    //Elimina o buffer atual
    execGL(IGL_SH_DELBUFFERS,2,I3D_VboIds);

    Triangulariza  (    );
    CalculaNormal  (true);
    return true;
}

/***************************************************************/
/*Nome do Método      : CalculaNormal()                        */
/*Objetivo            : Calcula a normal do poligono , ou seja */
/*                      diz para onde ele está apontando...    */
/***************************************************************/
bool CI3DPoligono::CalculaNormalSmooth(CIMTVetor centro)
{
    /************************************************************/
    /*Calcula a Normal do Vertice Baseado no Centro do Objeto   */
    /*Para os calculos de Smooth foi escolhido esta abordagem   */
    /*Pois ate o momento estamos trabalhando com objetos        */
    /*concavos apontando para fora.                             */
    /*No caso de objetos mais detalhados que contenham partes   */
    /*concavas é necessário mudar o algoritmo para uma media    */
    /*das normais de face geradas na adjacencia de cada vertice.*/
    /************************************************************/
    for ( GLuint i = 0; i < I3D_QtdVertices; i++ )
    {
        CIMTVetor   i3dRetaNormal ;
        i3dRetaNormal = ( centro - Vertices[i]).Normalizar();
        Vertices[i].I3D_SmoothNormal = -i3dRetaNormal;
    }

    return true;
}

/***************************************************************/
/*Nome do Método      : CalculaNormal()                        */
/*Objetivo            : Calcula a normal do poligono , ou seja */
/*                      diz para onde ele está apontando...    */
/***************************************************************/
bool CI3DPoligono::CalculaTangentes()
{

    CIMTVetor   V0, V1, V2;
    CIMTVetor2 UV0,UV1,UV2;

    /******************************************/
    /*Realiza as verif. em todos os Vertices  */
    /******************************************/
    for ( GLuint i = 0; i < I3D_QtdIndices; i+=3 )
    {
        V0 = Vertices[Indices[i+0]];
        V1 = Vertices[Indices[i+1]];
        V2 = Vertices[Indices[i+2]];

        UV0 = CIMTVetor2(Vertices[Indices[i+0]].I3D_CoordDetTextU,Vertices[Indices[i+0]].I3D_CoordDetTextV);
        UV1 = CIMTVetor2(Vertices[Indices[i+1]].I3D_CoordDetTextU,Vertices[Indices[i+1]].I3D_CoordDetTextV);
        UV2 = CIMTVetor2(Vertices[Indices[i+2]].I3D_CoordDetTextU,Vertices[Indices[i+2]].I3D_CoordDetTextV);

        CIMTVetor deltaPos1 = V1-V0;
        CIMTVetor deltaPos2 = V2-V0;

        CIMTVetor2 deltaUV1 = UV1-UV0;
        CIMTVetor2 deltaUV2 = UV2-UV0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

        CIMTVetor tangente   = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        CIMTVetor bitangente = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        Vertices[Indices[i+0]].I3D_Tangente = tangente;
        Vertices[Indices[i+1]].I3D_Tangente = tangente;
        Vertices[Indices[i+2]].I3D_Tangente = tangente;

        Vertices[Indices[i+0]].I3D_BiTangente = bitangente;
        Vertices[Indices[i+1]].I3D_BiTangente = bitangente;
        Vertices[Indices[i+2]].I3D_BiTangente = bitangente;

    }

    return true;
}

/************************************************************/
/*Nome do Método      : Triangulariza()                     */
/*Objetivo            : Indexa Poligonos por triangulo      */
/************************************************************/
void CI3DPoligono::Triangulariza()
{

    GLuint  Index;
    GLuint  i3dVerticeA  ,
            i3dVerticeB  ,
            i3dVerticeC  ;

    for ( Index = 0; Index < (this->I3D_QtdIndices)/3; Index++ )
    {
        if ( Index == 0 )
        {
            i3dVerticeA = Index;
            i3dVerticeB = Index+1;
            i3dVerticeC = Index+2;
        }
        else
        {
              i3dVerticeB   = i3dVerticeC;
              i3dVerticeC++              ;
        }

        Indices[ Index*3   ]=i3dVerticeA;
        Indices[(Index*3)+1]=i3dVerticeB;
        Indices[(Index*3)+2]=i3dVerticeC;
    }
}

/************************************************************/
/*Nome do Método      : Quadrangulariza()                   */
/*Objetivo            : Indexa Poligono por Quads           */
/************************************************************/
void CI3DPoligono::Quadrangulariza()
{

    GLuint         Index;
    GLuint         i3dVerticeA  ,
                   i3dVerticeB  ,
                   i3dVerticeC  ,
                   i3dVerticeD  ;

    for ( Index = 0; Index < this->I3D_QtdIndices; Index+=4 )
    {


        i3dVerticeA = Index  ;
        i3dVerticeB = Index+1;
        i3dVerticeC = Index+2;
        i3dVerticeD = Index+3;

        Indices[Index  ]=i3dVerticeA;
        Indices[Index+1]=i3dVerticeB;
        Indices[Index+2]=i3dVerticeC;
        Indices[Index+3]=i3dVerticeD;
    }
}

/************************************************************/
/*Nome do Método      : Renderiza()                         */
/*Objetivo            : Renderiza o Poligono.               */
/************************************************************/
void CI3DPoligono::Renderiza(int iProgramId,int iRenderMode, int iPolygonMode, int iShadingMode, int iGeometryMode)
{
    switch(iRenderMode)
    {
       case IGL_MODE_RENDER         : {execGL(IGL_SH_UNIINT,iProgramId,"modo_renderizacao",0);}break;
       case IGL_MODE_SELECTION_PRIMI:
       case IGL_MODE_SELECTION_MESHS:
       case IGL_MODE_SELECTION_FACES:
       {
           execGL(IGL_SH_UNIINT,iProgramId,"modo_renderizacao",1);
       }break;
       default:{execGL(IGL_SH_UNIINT,iProgramId,"modo_renderizacao",0);}break;
    }

    switch(iShadingMode)
    {
       case IGL_SHADING_MODE_FLAT  : {execGL(IGL_SH_UNIINT,iProgramId,"modo_iluminacao",0);}break;
       case IGL_SHADING_MODE_SMOOTH: {execGL(IGL_SH_UNIINT,iProgramId,"modo_iluminacao",1);}break;
       case IGL_SHADING_MODE_DIFLAT: {execGL(IGL_SH_UNIINT,iProgramId,"modo_iluminacao",2);}break;
       case IGL_SHADING_MODE_DIFOTH: {execGL(IGL_SH_UNIINT,iProgramId,"modo_iluminacao",3);}break;
       case IGL_SHADING_MODE_NOONE : {execGL(IGL_SH_UNIINT,iProgramId,"modo_iluminacao",4);}break;
       default:{execGL(IGL_SH_UNIINT,iProgramId,"modo_iluminacao",0);}break;
    }

    if(iGeometryMode == IGL_GEOMETRY_PHYSICS)
    {
       execGL(IGL_SH_RENDERBUFFERS,iPolygonMode,I3D_QtdVertices,I3D_QtdIndices,iProgramId,I3D_VboIds,false,NULL);
       //execGL(IGL_SH_RENDERBUFFERS,iPolygonMode,I3D_QtdVertices,I3D_QtdIndices,iProgramId,I3D_VboIds,true ,I3D_FeedbackBuffer);
    }
    else
    {
       execGL(IGL_SH_RENDERBUFFERS,iPolygonMode,I3D_QtdVertices,I3D_QtdIndices,iProgramId,I3D_VboIds,false,NULL);
    }
}

/************************************************************/
/*Nome do Método      : HabilitaVertices()                  */
/*Objetivo            : Libera os marcadores de vertice.    */
/************************************************************/
void CI3DPoligono::HabilitaVertices()
{
    for(GLuint i=0 ; i<I3D_QtdVertices;i++)
    {
        Vertices[i].Status=0;
    }
}

/*************************************************************/
/*Nome do Método      : EstaContido()                        */
/*Objetivo            : Diz se um ponto passado esta contido */
/*                      ou nao neste poligono.               */
/*************************************************************/
bool CI3DPoligono::EstaContido(CIMTVetor   i3dVertice)
{

    const double i3dFator  = 0.99;
    double i3dAngulo = 0.0 ;
    CIMTVetor A, B;

    for (GLuint i = 0; i < I3D_QtdVertices; i++)
    {

        A = Vertices[i] - i3dVertice;
        B = Vertices[(i + 1) % I3D_QtdVertices] - i3dVertice;

        i3dAngulo += A.AnguloEntre(B);

    }

    if(i3dAngulo >= (i3dFator * (2.0 * PI)))
        return true;

    return false;

}

/***********************************************************/
/*Nome do Método      : Existe()                           */
/*Objetivo            : Diz se ele é igual a algum destes..*/
/***********************************************************/
bool CI3DPoligono::Existe(CI3DVertice  i3dVertice)
{

    for (GLuint i = 0; i < I3D_QtdVertices; i++)
    {
        if(Vertices[i].Igual(i3dVertice))
        {
            return true;
        }
    }

    return false;
}

/*************************************************************/
/*Nome do Método      : Degenerado()                         */
/*Objetivo            : Diz se ele é um poligono degenerado..*/
/*************************************************************/
bool CI3DPoligono::Degenerado() const
{
    CIMTVetor PreviousEdge, CurrentEdge;

    unsigned long CurrentVertex = 0;
    float         Dot;

    if (!Vertices || I3D_QtdVertices < 3 ) return false;

    PreviousEdge = Vertices[0] - Vertices[I3D_QtdVertices - 1];
    PreviousEdge.Normalizar();

    for ( GLuint i = 0; i < I3D_QtdVertices; i++ )
    {
        CurrentVertex = (i+1) % I3D_QtdVertices;
        CurrentEdge = Vertices[CurrentVertex] - Vertices[i];
        CurrentEdge.Normalizar();

        Dot = CurrentEdge.ProdutoEscalar(PreviousEdge);
        if ( fabsf(Dot) > 0.999999f ) return true;

        PreviousEdge = CurrentEdge;

    }

    return false;
}

/*************************************************************/
/*Nome do Método      : Convexo()                            */
/*Objetivo            : Diz se ele é um poligono convexo     */
/*************************************************************/
bool CI3DPoligono::Convexo()
{
    unsigned long Flag = 0, CurrentVertex = 0;
    float         Dot;

    //Valida a Face
    if (!Vertices || I3D_QtdVertices < 3 ) return false;

    //Calcula o Primeiro Edge
    CIMTVetor PreviousEdge,
              CurrentEdge ,
              CrossProduct,
              Normal = CalculaNormal(false);

    PreviousEdge = (Vertices[0] - Vertices[I3D_QtdVertices - 1]);
    PreviousEdge.Normalizar();

    //Percorre todos os Edges
    for ( unsigned long i = 0; i < I3D_QtdVertices; i++ )
    {
        CurrentVertex = (i+1) % I3D_QtdVertices;
        CurrentEdge = (Vertices[CurrentVertex] - Vertices[i]);
        CurrentEdge.Normalizar();

        //Calcula o produto vetorial entre os dois vetores
        CrossProduct = CurrentEdge.ProdutoVetorial(PreviousEdge);

        //Calcula o angulo entre a normal do poligono e o Produto vetorial
        Dot = CrossProduct.ProdutoEscalar(Normal);
        if ( Dot < -1e-5f ) Flag |= 1;
        else if ( Dot > +1e-5f ) Flag |= 2;

        //Se os cruzamentos não estiverem apontando sempre para a mesma direcao
        //é concavo
        //TODO: ACERTAR ESTE TRATAMENTO PARA QUE FUNCIONE ASSIM!
        if ( Flag == 3 ) return false;

        //Armazena o proximo edge
        PreviousEdge = CurrentEdge;

    }

    //É Convexo
    return true;

}

/*************************************************************/
/*Nome do Método      : Divide()                             */
/*Objetivo            : Divide o Poligono por um plano       */
/*************************************************************/
bool CI3DPoligono::Divide(const CIMTPlano&    imtPlano         ,
                                CI3DPoligono *i3dPoligonoFrente,
                                CI3DPoligono *i3dPoligonoAtras )
{


    CIMTVetor       IntersectPoint;
    CI3DVertice     *FrontList = NULL, *BackList = NULL;
    unsigned long   CurrentVertex = 0, Location = 0, i = 0;
    unsigned long   InFront = 0, Behind = 0, OnPlane = 0;
    unsigned long   FrontCounter = 0, BackCounter = 0;
    unsigned long   *PointLocation = NULL;
    float           percent;
    float           distancia;

    //Valida os dados de entrada
    if (!i3dPoligonoFrente && !i3dPoligonoAtras) return true;

    try
    {
        //Aloca vertices para a operação de Split
        PointLocation = new unsigned long[I3D_QtdVertices];
        if (!PointLocation) throw std::bad_alloc();

        if (i3dPoligonoFrente)
        {
            FrontList = new CI3DVertice[I3D_QtdVertices + 1];
            if (!FrontList) throw std::bad_alloc();
        }

        if ( i3dPoligonoAtras )
        {
            BackList = new CI3DVertice[I3D_QtdVertices + 1];
            if (!FrontList) throw std::bad_alloc();
        }

    }

    catch (...)
    {
        //Captura exceções
        if (FrontList)      delete []FrontList;
        if (BackList)       delete []BackList;
        if (PointLocation)  delete []PointLocation;
        return false;
    }

    //Determina todas as posições dos pontos relativo ao plano
    for ( i = 0; i < I3D_QtdVertices; i++)
    {
        //Classifica a posição relativo ao plano
        Location = imtPlano.ClassificaPonto(Vertices[i],&distancia);
        if (Location == FRENTE )
        {
            //WDW
            InFront++;
        }
        else if (Location == ATRAS )
        {
            //WDW
            Behind++;
        }
        else
        {
            OnPlane++;
        }

        //Armazena a localização
        PointLocation[i] = Location;

    }

    //Se não há mais vertices na frente do plano...
    if (!InFront && BackList)
    {
        memcpy(BackList, Vertices,I3D_QtdVertices * sizeof(CI3DVertice));
        BackCounter = I3D_QtdVertices;
    }

    //Se não há mais vertices atrás do plano...
    if (!Behind && FrontList)
    {
        memcpy(FrontList,Vertices,I3D_QtdVertices * sizeof(CI3DVertice));
        FrontCounter = I3D_QtdVertices;
    }

    //Computa a divisão
    if (InFront && Behind)
    {
        for ( i = 0; i < I3D_QtdVertices; i++)
        {
            //Armazena vertice atual atraves do MOD pelo numero de vertices.
            CurrentVertex = (i+1) % I3D_QtdVertices;

            if (PointLocation[i] == COPLANAR )
            {
                if (FrontList) FrontList[FrontCounter++] = Vertices[i];
                if (BackList)  BackList [BackCounter ++] = Vertices[i];
                continue; //Pula para o proximo vertice
            }

            if (PointLocation[i] == FRENTE )
            {
                //WDW
                if (FrontList) FrontList[FrontCounter++] = Vertices[i];
            }
            else
            {
                //WDW
                if (BackList) BackList[BackCounter++] = Vertices[i];

            }

            //Se o proximo vertice nao causa a expansão do plano continua...
            if (PointLocation[CurrentVertex] == COPLANAR || PointLocation[CurrentVertex] == PointLocation[i]) continue;

            //Calcula ponto de intersecção
            imtPlano.CruzamentoRaio(Vertices[i],Vertices[CurrentVertex],IntersectPoint,&percent);

            //Cria o novo vertice e calcula sua posição
            CI3DVertice NewVert = CI3DVertice(IntersectPoint);

            //Interpola coordenadas de textura
            CIMTVetor Delta;
            Delta.x  = Vertices[CurrentVertex].I3D_CoordTexturaU - Vertices[i].I3D_CoordTexturaU;
            Delta.y  = Vertices[CurrentVertex].I3D_CoordTexturaV - Vertices[i].I3D_CoordTexturaV;
            NewVert.I3D_CoordTexturaU = Vertices[i].I3D_CoordTexturaU + ( Delta.x * percent );
            NewVert.I3D_CoordTexturaV = Vertices[i].I3D_CoordTexturaV + ( Delta.y * percent );

            //Interpola a Normal
            Delta = Vertices[CurrentVertex].I3D_PlanarNormal - Vertices[i].I3D_PlanarNormal;
            NewVert.I3D_PlanarNormal=Vertices[i].I3D_PlanarNormal + (Delta*percent);
            NewVert.I3D_PlanarNormal.Normalizar();

            //Interpola a Smooth
            Delta = Vertices[CurrentVertex].I3D_SmoothNormal - Vertices[i].I3D_SmoothNormal;
            NewVert.I3D_SmoothNormal=Vertices[i].I3D_SmoothNormal + (Delta*percent);
            NewVert.I3D_SmoothNormal.Normalizar();

            //Interpola a tangente
            Delta = Vertices[CurrentVertex].I3D_Tangente - Vertices[i].I3D_Tangente;
            NewVert.I3D_Tangente=Vertices[i].I3D_Tangente + (Delta*percent);
            NewVert.I3D_Tangente.Normalizar();

            //Interpola a Bitangente
            Delta = Vertices[CurrentVertex].I3D_BiTangente - Vertices[i].I3D_BiTangente;
            NewVert.I3D_BiTangente=Vertices[i].I3D_BiTangente + (Delta*percent);
            NewVert.I3D_BiTangente.Normalizar();

            //Inclui nas respectivas listas.
            if (BackList)  BackList[BackCounter++]   = NewVert;
            if (FrontList) FrontList[FrontCounter++] = NewVert;

        }
    }

    //Aloca a Face da Frente
    if (FrontCounter && i3dPoligonoFrente)
    {
        //Copia os Vertices para o novo poligono
        i3dPoligonoFrente->AdicionaVertices( FrontCounter , IGL_RENDER_TRIANGLES);
        memcpy(i3dPoligonoFrente->Vertices, FrontList, FrontCounter * sizeof(CI3DVertice));

        i3dPoligonoFrente->Triangulariza();
    }

    //Aloca a Face de Trás
    if (BackCounter && i3dPoligonoAtras)
    {
        //Copia os vertices para o novo poligono
        i3dPoligonoAtras->AdicionaVertices( BackCounter , IGL_RENDER_TRIANGLES );
        memcpy(i3dPoligonoAtras->Vertices, BackList, BackCounter * sizeof(CI3DVertice));

        i3dPoligonoAtras->Triangulariza();

    }

    if(i3dPoligonoFrente){i3dPoligonoFrente->PreencheBuffers();}
    if(i3dPoligonoAtras ){i3dPoligonoAtras ->PreencheBuffers();}

    //Limpa a sujeira...
    if (FrontList)      delete []FrontList;
    if (BackList)       delete []BackList;
    if (PointLocation)  delete []PointLocation;

    //Sucesso!!
    return true;

}

/*********************************************************************/
/*Nome do Método      : GeraPoligono()                               */
/*Objetivo            : Gera o Poligono atraves de um plano e volume */
/*********************************************************************/
bool CI3DPoligono::GeraPoligono( const CIMTPlano& Plano, const CIMTBorda& Borda )
{
    CIMTVetor CB, CP, U, V, A;

    //Calcula o Centro da Bounding Box
    CB = Borda.PegaCentro();
    //Calcula a distancia do centro até o plano
    float DistanceToPlano = CB.DistanciaPlano( Plano );
    //Calcula o Centro do Plano
    CP = CB + (Plano.IMT_NormalPlano * -DistanceToPlano );

    //Calcula o Eixo principal
    A = CIMTVetor(0.0f,0.0f,0.0f);
    if( fabs(Plano.IMT_NormalPlano.y) > fabs(Plano.IMT_NormalPlano.z) )
    {
        if( fabs(Plano.IMT_NormalPlano.z)  < fabs(Plano.IMT_NormalPlano.x) )
        {
            A.z = 1;
        }
        else
        {
            A.x = 1;
        }
    }
    else
    {
        if (fabs(Plano.IMT_NormalPlano.y) <= fabs(Plano.IMT_NormalPlano.x) )
        {
            A.y = 1;
        }
        else
        {
            A.x = 1;
        }
    }

    //Gera os vetores UV
    U = A.ProdutoVetorial(Plano.IMT_NormalPlano);
    V = U.ProdutoVetorial(Plano.IMT_NormalPlano);
    U.Normalizar();
    V.Normalizar();

    float Length = (Borda.IMT_MaxVetorBorda  - CB).Magnitude();

    //Scala os vetores UV em metade do diametro da Bounding Box
    U *= Length;
    V *= Length;

    CIMTVetor P[4];
    P[0] = CP + U - V; // Bottom Right
    P[1] = CP + U + V; // Top Right
    P[2] = CP - U + V; // Top Left
    P[3] = CP - U - V; // Bottom Left

    //Aloca novos Vertices
    if (AdicionaVertices( 4 , IGL_RENDER_TRIANGLES) < 0) return false;

    //Insere os vertices no poligono
    for ( int i = 0; i < 4; i++)
    {
        Vertices[i] = CI3DVertice(P[i]);
        Vertices[i].I3D_PlanarNormal = Plano.IMT_NormalPlano;
    }

    //Certifica que os vertices estao no plano(Força Bruta)
    for ( int v = 0; v < 4; v++ )
    {
       float Resultado = Vertices[v].ProdutoEscalar(Plano.IMT_NormalPlano) - Plano.IMT_DistanciaPlano;
       Vertices[v]+=(Plano.IMT_NormalPlano * -Resultado);
    }

    //Realiza a indexação dos vertices em triangulos
    Triangulariza();

    //Sucesso!!!
    return true;
}
