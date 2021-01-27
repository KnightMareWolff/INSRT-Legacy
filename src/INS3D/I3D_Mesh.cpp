/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :Metodos de tratamento de malhas geometricas (Meshs)        */
/*Data de Criação     :01/08/2014                                                 */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
/*25/02/2016 - Retirado tratamento de FeedbackBuffer do calculo da Borda          */
/*13/03/2016 - Inserido coleta e calculo volume na extracao feedback              */
/**********************************************************************************/
#include "I3D_GlobalDef.h"
#include "I3D_Mesh.h"

/************************************************************/
/************************************************************/
CI3DMesh::~CI3DMesh()
{
    LimpaFaces();

    if(MeshType == IGL_MESH_HEIGHTMAP ||
       MeshType == IGL_MESH_SKINNED   )
       {
          execGL(IGL_SH_DELBUFFERS,2,I3D_SkinVboIds);
       }
}
/************************************************************/
/************************************************************/
CI3DMesh::CI3DMesh()
{
    Faces               =NULL;
    I3D_QtdFaces        =0;
    Status              =0;
    PolygonMode         =IGL_RENDER_TRIANGLES ;
    WindingMode         =IGL_WINMODE_CCW      ;
    GeometryMode        =IGL_GEOMETRY_STATIC  ;
    ProjectionMode      =IGL_PROJECTION_PERSP ;
    MeshType            =IGL_MESH_CLASSIC     ;
    RenderMode          =IGL_MODE_RENDER      ;
    ConstructionMode    =IGL_POLYMODE_LEFT    ;
    ShadingMode         =IGL_SHADING_MODE_FLAT;

    I3D_SkinVertexBuffer    = NULL;
    I3D_SkinVertexIndices   = NULL;
    I3D_SkinFeedbackBuffer  = NULL;
    I3D_QtdVerticesSkin = 0;
    I3D_QtdIndicesSkin  = 0;
    I3D_QtdFdkVertsSkin = 0;
    I3D_QtdFacesSkin    = 0;

    bMultiTexture=true;

    I3D_Material =    0; //Material Default

    //Como não sabemos qual shader é ainda apontamos para o Core
    SetaShader(INSSH::pISHProgramManager->ProgramId("CoreRender"));
}

/************************************************************/
/************************************************************/
CI3DMesh::CI3DMesh(int I3D_ProgramId)
{
    Faces               =NULL;
    I3D_QtdFaces        =0;
    Status              =0;
    PolygonMode         =IGL_RENDER_TRIANGLES ;
    WindingMode         =IGL_WINMODE_CCW      ;
    GeometryMode        =IGL_GEOMETRY_STATIC  ;
    ProjectionMode      =IGL_PROJECTION_PERSP ;
    MeshType            =IGL_MESH_CLASSIC     ;
    RenderMode          =IGL_MODE_RENDER      ;
    ConstructionMode    =IGL_POLYMODE_LEFT    ;
    ShadingMode         =IGL_SHADING_MODE_FLAT;

    I3D_SkinVertexBuffer    = NULL;
    I3D_SkinVertexIndices   = NULL;
    I3D_SkinFeedbackBuffer  = NULL;
    I3D_QtdVerticesSkin = 0;
    I3D_QtdIndicesSkin  = 0;
    I3D_QtdFdkVertsSkin = 0;
    I3D_QtdFacesSkin    = 0;

    bMultiTexture=true;

    I3D_Material        =    0; //Material Default

    SetaShader(I3D_ProgramId);
}
/*
CI3DMesh::CI3DMesh(const CI3DMesh &i3dMesh )
{

    I3D_QtdFaces = i3dMesh.I3D_QtdFaces ;
    I3D_BordaMesh= i3dMesh.I3D_BordaMesh;

    AdicionaFaces(I3D_QtdFaces);

    for(int i=0;i<I3D_QtdFaces;i++)
    {
        Faces[i] = i3dMesh.Faces[i];
    }

    Status         = i3dMesh.Status         ;
    PolygonMode    = i3dMesh.PolygonMode    ;
    MaterialMode   = i3dMesh.MaterialMode   ;
    ShadingMode    = i3dMesh.ShadingMode    ;
    GeometryMode   = i3dMesh.GeometryMode   ;
    WindingMode    = i3dMesh.WindingMode    ;
    ProjectionMode = i3dMesh.ProjectionMode ;
    MeshType       = i3dMesh.MeshType       ;
    RenderMode     = i3dMesh.RenderMode     ;

}
*/

/************************************************************/
/************************************************************/
void CI3DMesh::LimpaFaces()
{

    if ( Faces )
    {
        for ( long i = 0; i < I3D_QtdFaces; i++ )
        {
            if ( Faces[i] ) delete Faces[i];
        }
        delete []Faces;
        Faces = NULL;
    }
    I3D_QtdFaces = 0;
}

const CIMTBorda& CI3DMesh::CalculaBorda()
{
    I3D_BordaMesh.Limpa();

    for ( long i = 0; i < I3D_QtdFaces; i++ )
    {
        I3D_BordaMesh.CalculaBordaMesh( Faces[i]->Vertices,
                                        Faces[i]->I3D_QtdVertices ,
                                        sizeof(CI3DVertice)       ,
                                        false                    );
    }

    return I3D_BordaMesh;
}


/************************************************************/
/************************************************************/
void CI3DMesh::CalculaPlnrNrml()
{
   /****************************************/
   /*Para todas as faces deste Mesh        */
   /****************************************/
   for(long i=0;i<I3D_QtdFaces;i++)
   {
      /*******************************************************/
      /*Projetamos a Normal da face a todos os vertices que  */
      /*fazem parte desta face                               */
      /*******************************************************/
      Faces[i]->I3D_NormalFace=Faces[i]->CalculaNormal(true);
   }
}

/************************************************************/
/************************************************************/
void CI3DMesh::CalculaSmthNrml(CIMTVetor centro)
{
   /****************************************/
   /*Para todas as faces deste Mesh        */
   /****************************************/
   for(long i=0;i<I3D_QtdFaces;i++)
   {
      /*******************************************************/
      /*Projetamos a Normal da face a todos os vertices que  */
      /*fazem parte desta face                               */
      /*******************************************************/
      Faces[i]->CalculaNormalSmooth(centro);
   }
}

/************************************************************/
/************************************************************/
void CI3DMesh::InverteNormais()
{
   /****************************************/
   /*Para todas as faces deste Mesh        */
   /****************************************/
   for(long i=0;i<I3D_QtdFaces;i++)
   {
      /*******************************************************/
      /*Projetamos a Normal da face a todos os vertices que  */
      /*fazem parte desta face                               */
      /*******************************************************/
      Faces[i]->I3D_NormalFace=Faces[i]->InverteNormal(true);
   }

   ConstroiBuffersSH();
}

/************************************************************/
/************************************************************/
void CI3DMesh::CalculaTgns()
{
   /****************************************/
   /*Para todas as faces deste Mesh        */
   /****************************************/
   for(long i=0;i<I3D_QtdFaces;i++)
   {
      /*******************************************************/
      /*Projetamos a Normal da face a todos os vertices que  */
      /*fazem parte desta face                               */
      /*******************************************************/
      Faces[i]->CalculaTangentes();
   }
}

void CI3DMesh::ConstroiBuffersSH()
{
   switch(MeshType)
   {
      case IGL_MESH_CLASSIC:
      {
         /****************************************/
         /*Para todas as faces deste Mesh        */
         /****************************************/
         for(long i=0;i<I3D_QtdFaces;i++)
         {
            /*******************************************************/
            /*Projetamos a Normal da face a todos os vertices que  */
            /*fazem parte desta face                               */
            /*******************************************************/
            Faces[i]->PreencheBuffers();
         }
      }break;
      case IGL_MESH_SKINNED:
      case IGL_MESH_HEIGHTMAP:
      {
         PreencheSkin();
      }break;
   }
}

void CI3DMesh::PreencheSkin()
{
     switch(MeshType)
     {
        case IGL_MESH_SKINNED    :{PreencheSkinModel();}break;
        case IGL_MESH_HEIGHTMAP  :{PreencheSkinModel();}break;
     }
}

void CI3DMesh::PreencheSkinModel()
{
    GLuint iQtdIndicesSkin=0,
           iQtdVerticesSkin=0;

    GLuint Index=0;

    /******************************************************/
    /*Calcula Qtd Vertices e Indices                      */
    /*Para um modelo importado de arquivos(provenientes   */
    /*da grande maioria dos softwares de modelagem 3D     */
    /*Todos os meshs vem como um unico buffer de vertices */
    /*com um unico buffer de indices triangularizados.    */
    /*Portando já que em nosso modelos temos poligonos    */
    /*triangularizados(que podem ser tanto triangulos,quad*/
    /*etc..temos que calcular os totais face a face já que*/
    /*podemos gerar outros tipos de malha como heightmaps */
    /******************************************************/
    for(long i=0;i<I3D_QtdFaces;i++)
    {
        I3D_QtdFacesSkin++;
        for(GLuint j=0;j<Faces[i]->I3D_QtdVertices;j++)
        {
           iQtdVerticesSkin++;
        }
        for(GLuint k=0;k<Faces[i]->I3D_QtdIndices;k++)
        {
           iQtdIndicesSkin++;
        }
    }

    /*******************************************************/
    /*Aloca espaço para a transferencia dos buffers        */
    /*******************************************************/
    AlocaSkinBuffer(iQtdVerticesSkin,iQtdIndicesSkin);
    /******************************************************/
    /*Preenche o vertex buffer comos vertices da aplicação*/
    /******************************************************/
    for(long i=0;i<I3D_QtdFaces;i++)
    {
       for(GLuint j=0;j<Faces[i]->I3D_QtdVertices;j++)
       {
          I3D_SkinVertexBuffer[Index].position   = CIMTVetor (Faces[i]->Vertices[j].x,Faces[i]->Vertices[j].y,Faces[i]->Vertices[j].z);
          I3D_SkinVertexBuffer[Index].texCoord   = CIMTVetor2(Faces[i]->Vertices[j].I3D_CoordTexturaU,Faces[i]->Vertices[j].I3D_CoordTexturaV);
          I3D_SkinVertexBuffer[Index].normal     = CIMTVetor (Faces[i]->Vertices[j].I3D_PlanarNormal.x,Faces[i]->Vertices[j].I3D_PlanarNormal.y,Faces[i]->Vertices[j].I3D_PlanarNormal.z);
          I3D_SkinVertexBuffer[Index].smooth     = CIMTVetor (Faces[i]->Vertices[j].I3D_SmoothNormal.x,Faces[i]->Vertices[j].I3D_SmoothNormal.y,Faces[i]->Vertices[j].I3D_SmoothNormal.z);
          I3D_SkinVertexBuffer[Index].tangente   = CIMTVetor (Faces[i]->Vertices[j].I3D_Tangente.x,Faces[i]->Vertices[j].I3D_Tangente.y,Faces[i]->Vertices[j].I3D_Tangente.z);
          I3D_SkinVertexBuffer[Index].bitangente = CIMTVetor (Faces[i]->Vertices[j].I3D_BiTangente.x,Faces[i]->Vertices[j].I3D_BiTangente.y,Faces[i]->Vertices[j].I3D_BiTangente.z);

          //PREENCHE O FEEDBACKBUFFER
          I3D_SkinFeedbackBuffer[Index].position = CIMTVetor (Faces[i]->Vertices[j].x,Faces[i]->Vertices[j].y,Faces[i]->Vertices[j].z);

          Index++;
       }
    }

    Index=0;//zera o index para nova recursão

    /********************************/
    /*Preenche os indices do buffer */
    /********************************/
    for(long i=0;i<I3D_QtdFaces;i++)
    {
       for(GLuint j=0;j<Faces[i]->I3D_QtdIndices;j++)
       {
          //É recuperado aqui os indices originais da Skin
          I3D_SkinVertexIndices[Index] = Faces[i]->I3D_IndicesSkin[j];
          Index++;
       }
    }

    IniSkinBuffer();
}

void CI3DMesh::AlocaSkinBuffer(int i3dQtdVertices, int i3dQtdIndices)
{

    IGLVertexBuffer    *VtxBuffer  = NULL;
    FeedBackData       *FdbBuffer  = NULL;
    GLuint             *VtxIndices = NULL;

    if ( i3dQtdVertices == 0 ) return;

    try
    {
        VtxBuffer = new IGLVertexBuffer[ i3dQtdVertices + I3D_QtdVerticesSkin ];
        if (!VtxBuffer) throw std::bad_alloc(); // VC++ Compat

        if (I3D_SkinVertexBuffer)
        {
            memcpy( VtxBuffer, I3D_SkinVertexBuffer ,i3dQtdVertices * sizeof(IGLVertexBuffer));
        }

        FdbBuffer = new FeedBackData[ i3dQtdVertices + I3D_QtdVerticesSkin];
        if (!FdbBuffer) throw std::bad_alloc(); // VC++ Compat

        if (I3D_SkinFeedbackBuffer)
        {
            memcpy( FdbBuffer, I3D_SkinFeedbackBuffer ,i3dQtdVertices * sizeof(FeedBackData));
        }

        VtxIndices = new GLuint[ i3dQtdIndices + I3D_QtdIndicesSkin];
        if (!VtxIndices) throw std::bad_alloc(); // VC++ Compativel?

        if (I3D_SkinVertexIndices)
        {
            memcpy( VtxIndices, I3D_SkinVertexIndices ,i3dQtdIndices * sizeof(GLuint));

        }
    }

    catch (...)
    {
        if (VtxBuffer ) delete []VtxBuffer ;
        if (FdbBuffer ) delete []FdbBuffer ;
        if (VtxIndices) delete []VtxIndices;
        return;
    }

    delete []I3D_SkinVertexBuffer;
    I3D_SkinVertexBuffer = VtxBuffer;

    delete []I3D_SkinFeedbackBuffer;
    I3D_SkinFeedbackBuffer = FdbBuffer;

    delete []I3D_SkinVertexIndices;
    I3D_SkinVertexIndices = VtxIndices;

    I3D_QtdVerticesSkin += i3dQtdVertices;
    I3D_QtdIndicesSkin  += i3dQtdIndices;

}

void CI3DMesh::IniSkinBuffer()
{
    execGL(IGL_SH_BUFFERINIT,I3D_SkinVertexBuffer   ,
                             I3D_SkinVertexIndices  ,
                             I3D_QtdVerticesSkin    ,
                             I3D_QtdIndicesSkin     ,
                             I3D_SkinVboIds         );
}

void CI3DMesh::InverteWindingMode()
{
   /****************************************/
   /*Para todas as faces deste Mesh        */
   /****************************************/
   for(long i=0;i<I3D_QtdFaces;i++)
   {
       Faces[i]->InvertePoligono();
   }

   switch(WindingMode)
   {
      case IGL_WINMODE_CCW :{WindingMode = IGL_WINMODE_CW ;}break;
      case IGL_WINMODE_CW  :{WindingMode = IGL_WINMODE_CCW;}break;
   }
}

void CI3DMesh::SetaWindingMode(int iWindingMode)
{
   /****************************************/
   /*Para todas as faces deste Mesh        */
   /****************************************/
   for(long i=0;i<I3D_QtdFaces;i++)
   {
      Faces[i]->PolyWindingMode = iWindingMode;
   }

   WindingMode = iWindingMode;
}

/***************************************************************/
/*Nome do Método      : CalculaNrml()                          */
/*Objetivo            : Unificar o calculo de todas as normais */
/*                      tornando o sistema independente de     */
/*                      calculos externos para suas normais.   */
/***************************************************************/
void CI3DMesh::CalculaNrml(CIMTVetor smooth)
{
    CalculaPlnrNrml(      );
    CalculaSmthNrml(smooth);
}

void CI3DMesh::Render(int pRenderMode, int pPolygonMode, int pShadingMode)
{
    PolygonMode  = pPolygonMode;
    ShadingMode  = pShadingMode;
    RenderMode   = pRenderMode;

    /****************************************************/
    /*Na renderização de seleção o Id de identificação  */
    /*É usado como pixel de identificação no Framebuffer*/
    /****************************************************/
    if(RenderMode==IGL_MODE_SELECTION_MESHS)
    {
        execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"color_pick",iIdMesh);
    }

    /******************************************/
    /*Prepara a textura para renderização     */
    /******************************************/
    if(pINSMAMaterialManager->PegaQtdTexturas(I3D_Material)==I3D_QtdFaces)
    {
        for(long i=0;i<I3D_QtdFaces;i++)
        {
           pINSMAMaterialManager->Prepara(I3D_MeshProgramId,I3D_Material,i);
           RenderizaFace(i);
        }
    }
    else
    {
        pINSMAMaterialManager->Prepara(I3D_MeshProgramId,I3D_Material);
        /******************************************/
        /*Desenha o Objeto Já Inicializado        */
        /******************************************/
        switch(MeshType)
        {
           case IGL_MESH_CLASSIC:
           {
              RenderizaFaces();
           }break;
           case IGL_MESH_SKINNED:
           case IGL_MESH_HEIGHTMAP:
           {
              RenderizaSkin();
           }break;
           default:{RenderizaFaces();}break;
        }
    }


    if(GeometryMode == IGL_GEOMETRY_PHYSICS)
    {
       ProcessaFeedback();
    }

    /********************************************/
    /*Em caso de Multiplos Layers em uma textura*/
    /*Os canais usados permanecem ativos ate que*/
    /*sejam desabilitados, onde caso o proximo  */
    /*objeto não tenha layers acaba pegando uma */
    /*textura inexistente(branca)               */
    /********************************************/
    if(bMultiTexture)
    {
        execGL(IGL_SH_ACTIVETEXTURE,I3D_MeshProgramId,GL_TEXTURE0);
        execGL(IGL_SH_DISABLE      ,I3D_MeshProgramId,GL_TEXTURE_2D);
        execGL(IGL_SH_ACTIVETEXTURE,I3D_MeshProgramId,GL_TEXTURE1);
        execGL(IGL_SH_DISABLE      ,I3D_MeshProgramId,GL_TEXTURE_2D);
        execGL(IGL_SH_ACTIVETEXTURE,I3D_MeshProgramId,GL_TEXTURE2);
        execGL(IGL_SH_DISABLE      ,I3D_MeshProgramId,GL_TEXTURE_2D);
        execGL(IGL_SH_ACTIVETEXTURE,I3D_MeshProgramId,GL_TEXTURE3);
        execGL(IGL_SH_DISABLE      ,I3D_MeshProgramId,GL_TEXTURE_2D);
    }
    else
    {
        execGL(IGL_SH_ACTIVETEXTURE,I3D_MeshProgramId,GL_TEXTURE0);
        execGL(IGL_SH_DISABLE      ,I3D_MeshProgramId,GL_TEXTURE_2D);
    }
}

/************************************************************/
/************************************************************/
void CI3DMesh::RenderizaFaces()
{
    if(MeshType == IGL_MESH_CLASSIC)
    {
       for(long i=0;i<I3D_QtdFaces;i++)
       {
          Faces[i]->Renderiza(RenderMode,PolygonMode,ShadingMode,GeometryMode);
       }
    }
}

/************************************************************/
/************************************************************/
void CI3DMesh::RenderizaFace(int i3dIndice)
{
    if(MeshType == IGL_MESH_CLASSIC)
    {
       Faces[i3dIndice]->Renderiza(RenderMode,PolygonMode,ShadingMode,GeometryMode);
    }
}

/************************************************************/
/************************************************************/
void CI3DMesh::RenderizaSkin()
{
    if(MeshType == IGL_MESH_SKINNED    ||
       MeshType == IGL_MESH_HEIGHTMAP   )
    {
       switch(ShadingMode)
       {
          case IGL_SHADING_MODE_FLAT  : {execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"modo_iluminacao",0);}break;
          case IGL_SHADING_MODE_SMOOTH: {execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"modo_iluminacao",1);}break;
          case IGL_SHADING_MODE_DIFLAT: {execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"modo_iluminacao",2);}break;
          case IGL_SHADING_MODE_DIFOTH: {execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"modo_iluminacao",3);}break;
          case IGL_SHADING_MODE_NOONE : {execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"modo_iluminacao",4);}break;
          default:{execGL(IGL_SH_UNIINT,I3D_MeshProgramId,"modo_iluminacao",0);}break;
       }

       if(GeometryMode == IGL_GEOMETRY_PHYSICS)
       {
          execGL(IGL_SH_RENDERBUFFERS,PolygonMode,I3D_QtdVerticesSkin,I3D_QtdIndicesSkin,I3D_MeshProgramId,I3D_SkinVboIds,true ,I3D_SkinFeedbackBuffer);
          execGL(IGL_SH_RENDERBUFFERS,PolygonMode,I3D_QtdVerticesSkin,I3D_QtdIndicesSkin,I3D_MeshProgramId,I3D_SkinVboIds,false,NULL);
       }
       else
       {
          execGL(IGL_SH_RENDERBUFFERS,PolygonMode,I3D_QtdVerticesSkin,I3D_QtdIndicesSkin,I3D_MeshProgramId,I3D_SkinVboIds,false,NULL);
       }
    }
}
/************************************************************/
/************************************************************/
void CI3DMesh::AdicionaFaces( int i3dQtd )
{
    CI3DFace **FaceBuffer = NULL;

    if ( i3dQtd == 0 ) return;

    try
    {
        FaceBuffer = new CI3DFace*[ I3D_QtdFaces + i3dQtd ];

        if (!FaceBuffer)
        {
            throw std::bad_alloc();
        }

        memset(FaceBuffer,0,(I3D_QtdFaces + i3dQtd) * sizeof(CI3DFace*));

        if (Faces) memcpy( FaceBuffer,Faces, I3D_QtdFaces * sizeof(CI3DFace*));

        for ( long i = 0; i < i3dQtd; i++ )
        {
            FaceBuffer[I3D_QtdFaces + i] = new CI3DFace;
            if (!FaceBuffer[I3D_QtdFaces + i])
            {
                throw std::bad_alloc();
            }

        }

    }

    catch (...)
    {
        if (FaceBuffer)
        {
            for ( long i = 0; i < i3dQtd; i++ )
            {
                if (FaceBuffer[I3D_QtdFaces + i]) delete FaceBuffer[I3D_QtdFaces + i];

            }

            delete []FaceBuffer;

        }

        return ;

    }

    if(Faces)
    {

       delete []Faces;

    }

    Faces         = FaceBuffer;
    I3D_QtdFaces += i3dQtd;

}

void CI3DMesh::SetaMaterial(int pI3D_IndiceMaterial)
{
    //atribui o material para o Mesh e Suas faces
    I3D_Material = pI3D_IndiceMaterial;
    for(long i=0;i<I3D_QtdFaces;i++)
    {
       Faces[i]->I3D_IndiceMaterial = pI3D_IndiceMaterial;
    }
}

void CI3DMesh::SetaMaterialFace  (int pI3D_IndiceMaterial,int pI3D_IndiceFace)
{
    //atribui o material para a face
    Faces[pI3D_IndiceFace]->I3D_IndiceMaterial = pI3D_IndiceMaterial;
}

void CI3DMesh::SetaShader(int pI3D_ShaderId)
{
    //atribui o material para o Mesh e Suas faces
    I3D_MeshProgramId = pI3D_ShaderId;
    for(long i=0;i<I3D_QtdFaces;i++)
    {
       Faces[i]->I3D_FaceProgramId = I3D_MeshProgramId;
    }
}

void CI3DMesh::SetaShaderFace  (int pI3D_ShaderId,int pI3D_IndiceFace)
{
    //atribui o material para a face
    Faces[pI3D_IndiceFace]->I3D_IndiceMaterial = pI3D_ShaderId;
}

void CI3DMesh::SetaNormalFace(int pI3D_IndiceFace,CIMTVetor pI3D_Normal)
{
    Faces[pI3D_IndiceFace]->I3D_NormalFace = pI3D_Normal;
    for(long i=0;i<Faces[pI3D_IndiceFace]->I3D_QtdVertices;i++)
    {
       Faces[pI3D_IndiceFace]->Vertices[i].I3D_PlanarNormal = pI3D_Normal;
    }
}


void CI3DMesh::SetaTexturaFace  (int pI3D_IndiceTextura,int pI3D_IndiceFace)
{
    //Verifica se há mais de uma textura na lista de texturas do material
    if(pINSMAMaterialManager->PegaQtdTexturas(I3D_Material)>1)
    {
        //caso positibo indica a renderização Face a Face.
        I3D_MultipleTextures = true;
    }
    //atribui o indice da textura no material para a face.
    Faces[pI3D_IndiceFace]->I3D_IndiceTextura = pI3D_IndiceTextura;
}

void CI3DMesh::ProcessaFeedback()
{
    /*****************************************************************/
    /*A função de processamento de feedback exemplifica bem a uti-   */
    /*lização de feedback buffers com a placa de video.              */
    /*Basicamente o funcionamento é:                                 */
    /*01-Eviamos os buffers na inicialização do sistema              */
    /*02-Durante a execução atualizamos as posições do objeto        */
    /*03-Renderizamos o objeto                                       */
    /*04-Coletamos no feedback as posicoes dos vertices transformados*/
    /*   no step de renderização                                     */
    /*05-Atualizamos todos os controles (Joints , posição) baseado na*/
    /*geometria transformada e não na matriz PVM sobre os objetos de */
    /*controle                                                       */
    /*****************************************************************/
    I3D_BordaMesh.Limpa();

    for ( long i = 0; i < I3D_QtdFaces; i++ )
    {
        I3D_BordaMesh.CalculaBordaMesh( (CIMTVetor *)Faces[i]->I3D_FeedbackBuffer  ,
                                        Faces[i]->I3D_QtdVertices ,
                                        sizeof(CIMTVetor)         ,
                                        false                    );
    }

    /******************************************/
    /*Utilizamos a bounding box do objeto     */
    /*desta forma garantimos que a posição    */
    /*do objeto esta exatamente no centro     */
    /*da massa de vertices formada pelo objeto*/
    /******************************************/
    //mPos = I3D_BordaMesh.PegaCentro();
    /********************************************/
    /*Atualizamos a View do Objeto baseado na   */
    /*Matrix de transformação aplicada no objeto*/
    /********************************************/
    //mView= mView * MtxTransf;
    /********************************************************/
    /*calcula as novas normais do objeto para iluminação    */
    /*Obs:.Para que a iluminação funcione corretamente na   */
    /*Pipeline Fixa é necessário realizar update constante  */
    /*das normais do objeto, sendo um dos motivos principais*/
    /*do grande sucesso que a nova plataforma obteve, pois  */
    /*possibilita fazer o Ray-Tracing e calculos vetoriais  */
    /*vertice a vertice sem a necessidade de alterar a      */
    /*aplicação.                                            */
    /********************************************************/
    //CalculaNrml (mPos);
}

void CI3DMesh::SetaGeometryMode(int pGeometryMode)
{
    GeometryMode = pGeometryMode;
}

void CI3DMesh::UpdateVertices(CIMTMatriz pIMT_Matrix)
{
    CIMTVetor  vet;
    /***********************************************/
    /*Atualiza os Vertices do Objeto               */
    /***********************************************/

    //for(long i=0;i<I3D_QtdFaces;i++)
    //{
        //TransformBuffer(I3D_MeshProgramId,
        //                Faces[i]->I3D_VboIds[0],
        //                Faces[i]->I3D_QtdVertices,
        //                pIMT_Matrix,
        //                Faces[i]->I3D_VertexBuffer);
    //}

    //qWarning() << "Renderiza Faces!";

    for(long i=0;i<I3D_QtdFaces;i++)
    {
       //Faces[i]->I3D_VertexBuffer = MapBuffer(I3D_MeshProgramId,Faces[i]->I3D_VboIds[0]);

       //execCL(ICL_EXEC_TRANSFORM_GL,Faces[i]->I3D_VertexBuffer,Faces[i]->I3D_QtdVertices,&pIMT_Matrix);
       execCL(ICL_EXEC_TRANSFORM_GL,Faces[i]->I3D_VboIds[0],Faces[i]->I3D_QtdVertices,&pIMT_Matrix);

       //UnMapBuffer(I3D_MeshProgramId,Faces[i]->I3D_VboIds[0],Faces[i]->I3D_VertexBuffer);
    }


}

//-----------------------------------------------------------------------------
// Nome : ConstroiBSP ()
// Desc : Reconstroi o Primitibo baseado em uma Arvore BSP
//-----------------------------------------------------------------------------
bool CI3DMesh::ConstroiBSP( const CI3DArvoreBsp * pTree, bool pReset)
{
    ULONG Contador = 0, i;

    if (!pTree) return false;

    if (pReset)
    {
        LimpaFaces();
    }

    for ( i = 0; i < pTree->PegaQtdFaces(); i++ )
    {
        if ( !pTree->PegaFace(i)->Deleted && pTree->PegaFace(i)->I3D_QtdVertices >= 3 ) Contador++;
    }


    if(Contador==0)
    {
        return true;
    }

    AdicionaFaces( Contador );

    Contador = I3D_QtdFaces - Contador;

    for ( i = 0; i < pTree->PegaQtdFaces(); i++ )
    {
        CI3DFace    * pFace     = Faces[Contador];
        CI3DFaceBsp * pTreeFace = pTree->PegaFace(i);

        if ( pTreeFace->Deleted ) continue;
        if ( pTreeFace->I3D_QtdVertices < 3 ) continue;

        pFace->I3D_IndiceMaterial = pTreeFace->I3D_IndiceMaterial;
        pFace->I3D_IndiceTextura  = pTreeFace->I3D_IndiceTextura;
        pFace->I3D_IndiceMesh     = pTreeFace->I3D_IndiceMesh;
        pFace->I3D_NormalFace     = pTreeFace->I3D_NormalFace;
        pFace->I3D_IndiceLightMap = pTreeFace->I3D_IndiceLightMap;
        pFace->I3D_HeightMapXY    = pTreeFace->I3D_HeightMapXY;
        pFace->I3D_FaceProgramId  = pTreeFace->I3D_FaceProgramId;

        if ( pFace->AdicionaVertices( pTreeFace->I3D_QtdVertices,IGL_RENDER_TRIANGLES) < 0 ) return false;

        memcpy( pFace->Vertices, pTreeFace->Vertices, pFace->I3D_QtdVertices * sizeof(CI3DVertice) );

        pFace->Triangulariza();

        Contador++;
    }

    CalculaBorda     (      );

    return true;
}
