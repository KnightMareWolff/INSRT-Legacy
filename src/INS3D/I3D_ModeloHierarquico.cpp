#include "I3D_ModeloHierarquico.h"
#include "I3D_Cubo.h"
#include "I3D_Esfera.h"


CI3DNoModelo::CI3DNoModelo(QString pNome)
{
   Nome = pNome;
   pai  = NULL;
   pos=CIMTVetor(0.0f,0.0f,0.0f);
   rot=CIMTVetor(0.0f,0.0f,0.0f);
}

void CI3DNoModelo::AddModelo(CI3DPrimitivo *pModelo)
{
   Modelo.push_back(pModelo);
}

void CI3DNoModelo::AddFilho(CI3DNoModelo* no)
{
    filho.push_back(no);
    no->pai = this;
}



void CI3DNoModelo::RemoveFilho(CI3DNoModelo* no)
{
    filho.remove(no);
    delete no;
}

int CI3DNoModelo::PegaQtdFilhos() const
{
    return (int)filho.size();
}

int CI3DNoModelo::PegaQtdModelos() const
{
    return (int)Modelo.size();
}

CI3DNoModelo* CI3DNoModelo::PegaPai() const
{
    return pai;
}

QString CI3DNoModelo::PegaNome() const
{
    return Nome;
}

void CI3DNoModelo::Translate(CIMTVetor  pTransf)
{
    pos.x=pTransf.x;
    pos.y=pTransf.y;
    pos.z=pTransf.z;
}

void CI3DNoModelo::Rotate(CIMTVetor  pTransf)
{
    rot.x = pTransf.x;
    rot.y = pTransf.y;
    rot.z = pTransf.z;
}


void CI3DNoModelo::InvTransf()
{
        //glRotatef(-rx, 1.0f, 0.0f, 0.0f);
        //glRotatef(-ry, 0.0f, 1.0f, 0.0f);
        //glRotatef(-rz, 0.0f, 0.0f, 1.0f);
        //glTranslated(-tx,-ty,-tz);
}


void CI3DNoModelo::Render(int pRenderMode , int pPolygonMode, int pShadingMode     )
{
    if (this->TemModelo())
    {
        for(int i = 0; i<Modelo.size(); i++)
        {
           Modelo[i]->Render(pRenderMode,pPolygonMode,pShadingMode);
        }
    }

    list<CI3DNoModelo*>::iterator i;

    for(i = filho.begin(); i != filho.end(); i++)
    {
       (*i)->Render(pRenderMode,pPolygonMode,pShadingMode);
    }
}

bool CI3DNoModelo::TemModelo()
{
    if(Modelo.size()>0)return true;
    return false;
}

CI3DModelo* CI3DNoModelo::PegaModelo(int pIdModelo)
{
    if(Modelo.size()>0)
    {
        return (CI3DModelo*)Modelo[pIdModelo];
    }
    return NULL;
}

/********************************************************************/
/*                                                                  */
/********************************************************************/
CI3DModeloHierarquico::CI3DModeloHierarquico()
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON   ;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;

    hierarquia = NULL;

    importador = new CIUTCarregadorArquivos;
    Build();
}

/********************************************************************/
/*                                                                  */
/********************************************************************/
CI3DModeloHierarquico::CI3DModeloHierarquico(QString pNomeArquivo, bool pI3D_MakeLeftHand)
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON   ;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;
    hierarquia = NULL;
    importador = new CIUTCarregadorArquivos;
    Carrega(pNomeArquivo,pI3D_MakeLeftHand);
}

bool CI3DModeloHierarquico::Carrega(QString pNomeArquivo, bool pI3D_MakeLeftHand)
{
    int iQtdMeshs    ,
        iQtdTexturas ,
        iQtdMateriais,
        iQtdAnimacoes,
        iQtdLuzes    ,
        iQtdCameras  ,
        iQtdFaces    ;

    int   iIndice01,iIndice02,iIndice03;
    float fPosX,fPosY,fPosZ,fPosU,fPosV;

    CIMTVetor  vertice0,
               vertice1,
               vertice2,
               tangent0,
               tangent1,
               tangent2,
               bitangt0,
               bitangt1,
               bitangt2;

    CI3DModelo *NovoModelo;

    importador->Importar(pNomeArquivo,pI3D_MakeLeftHand);

    if ( importador->scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE )
    {
        qWarning() << "Este arquivo está incompleto.";
    }

    iQtdMeshs     = importador->scene->mNumMeshes    ;
    iQtdTexturas  = importador->scene->mNumTextures  ;
    iQtdMateriais = importador->scene->mNumMaterials ;
    iQtdAnimacoes = importador->scene->mNumAnimations;
    iQtdLuzes     = importador->scene->mNumLights    ;
    iQtdCameras   = importador->scene->mNumCameras   ;

    if(importador->scene->HasMeshes())
    {
       for(int i=0; i< iQtdMeshs ; i++)
       {
           NovoModelo = new CI3DModelo();

           if(importador->scene->mMeshes[i]->HasFaces())
           {
               iQtdFaces = importador->scene->mMeshes[i]->mNumFaces;
               NovoModelo->I3D_Mesh->AdicionaFaces(iQtdFaces);
           }
           if(importador->scene->mMeshes[i]->HasPositions())
           {
               for(int j=0 ;j<iQtdFaces;j++)
               {
                   iIndice01 = importador->scene->mMeshes[i]->mFaces[j].mIndices[0];
                   iIndice02 = importador->scene->mMeshes[i]->mFaces[j].mIndices[1];
                   iIndice03 = importador->scene->mMeshes[i]->mFaces[j].mIndices[2];

                   fPosX = importador->scene->mMeshes[i]->mVertices[iIndice01].x;
                   fPosY = importador->scene->mMeshes[i]->mVertices[iIndice01].y;
                   fPosZ = importador->scene->mMeshes[i]->mVertices[iIndice01].z;

                   vertice0 = CIMTVetor(fPosX,fPosY,fPosZ);

                   fPosX = importador->scene->mMeshes[i]->mVertices[iIndice02].x;
                   fPosY = importador->scene->mMeshes[i]->mVertices[iIndice02].y;
                   fPosZ = importador->scene->mMeshes[i]->mVertices[iIndice02].z;

                   vertice1 = CIMTVetor(fPosX,fPosY,fPosZ);

                   fPosX = importador->scene->mMeshes[i]->mVertices[iIndice03].x;
                   fPosY = importador->scene->mMeshes[i]->mVertices[iIndice03].y;
                   fPosZ = importador->scene->mMeshes[i]->mVertices[iIndice03].z;

                   vertice2 = CIMTVetor(fPosX,fPosY,fPosZ);

                   NovoModelo->I3D_Mesh->Faces[j]->AdicionaVertices(3,IGL_RENDER_TRIANGLES);

                   NovoModelo->I3D_Mesh->Faces[j]->Vertices[0] = CI3DVertice(vertice0);
                   NovoModelo->I3D_Mesh->Faces[j]->Vertices[1] = CI3DVertice(vertice1);
                   NovoModelo->I3D_Mesh->Faces[j]->Vertices[2] = CI3DVertice(vertice2);

                   //Criado no Poligono original Indices para reconstrução da Skin
                   NovoModelo->I3D_Mesh->Faces[j]->I3D_IndicesSkin[0] = iIndice01;
                   NovoModelo->I3D_Mesh->Faces[j]->I3D_IndicesSkin[1] = iIndice02;
                   NovoModelo->I3D_Mesh->Faces[j]->I3D_IndicesSkin[2] = iIndice03;

                   if(importador->scene->mMeshes[i]->HasTextureCoords(0))
                   {
                       fPosU = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice01].x;
                       fPosV = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice01].y;

                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[0].I3D_CoordTexturaU = fPosU;
                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[0].I3D_CoordTexturaV = fPosV;

                       fPosU = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice02].x;
                       fPosV = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice02].y;

                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[1].I3D_CoordTexturaU = fPosU;
                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[1].I3D_CoordTexturaV = fPosV;

                       fPosU = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice03].x;
                       fPosV = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice03].y;

                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[2].I3D_CoordTexturaU = fPosU;
                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[2].I3D_CoordTexturaV = fPosV;
                   }

                   if(importador->scene->mMeshes[i]->HasTangentsAndBitangents())
                   {
                       fPosX   = importador->scene->mMeshes[i]->mTangents[iIndice01].x;
                       fPosY   = importador->scene->mMeshes[i]->mTangents[iIndice01].y;
                       fPosZ   = importador->scene->mMeshes[i]->mTangents[iIndice01].z;

                       tangent0   = CIMTVetor(fPosX,fPosY,fPosZ);

                       fPosX   = importador->scene->mMeshes[i]->mTangents[iIndice02].x;
                       fPosY   = importador->scene->mMeshes[i]->mTangents[iIndice02].y;
                       fPosZ   = importador->scene->mMeshes[i]->mTangents[iIndice03].z;

                       tangent1   = CIMTVetor(fPosX,fPosY,fPosZ);

                       fPosX   = importador->scene->mMeshes[i]->mTangents[iIndice03].x;
                       fPosY   = importador->scene->mMeshes[i]->mTangents[iIndice03].y;
                       fPosZ   = importador->scene->mMeshes[i]->mTangents[iIndice03].z;

                       tangent2   = CIMTVetor(fPosX,fPosY,fPosZ);

                       fPosX   = importador->scene->mMeshes[i]->mBitangents[iIndice01].x;
                       fPosY   = importador->scene->mMeshes[i]->mBitangents[iIndice01].y;
                       fPosZ   = importador->scene->mMeshes[i]->mBitangents[iIndice01].z;

                       bitangt0   = CIMTVetor(fPosX,fPosY,fPosZ);

                       fPosX   = importador->scene->mMeshes[i]->mBitangents[iIndice02].x;
                       fPosY   = importador->scene->mMeshes[i]->mBitangents[iIndice02].y;
                       fPosZ   = importador->scene->mMeshes[i]->mBitangents[iIndice02].z;

                       bitangt1   = CIMTVetor(fPosX,fPosY,fPosZ);

                       fPosX   = importador->scene->mMeshes[i]->mBitangents[iIndice03].x;
                       fPosY   = importador->scene->mMeshes[i]->mBitangents[iIndice03].y;
                       fPosZ   = importador->scene->mMeshes[i]->mBitangents[iIndice03].z;

                       bitangt2   = CIMTVetor(fPosX,fPosY,fPosZ);

                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[0].I3D_Tangente   = tangent0;
                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[0].I3D_BiTangente = bitangt0;

                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[1].I3D_Tangente   = tangent1;
                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[1].I3D_BiTangente = bitangt1;

                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[2].I3D_Tangente   = tangent2;
                       NovoModelo->I3D_Mesh->Faces[j]->Vertices[2].I3D_BiTangente = bitangt2;
                   }

                   NovoModelo->I3D_Mesh->Faces[j]->Triangulariza();

               }
           }

           if(importador->scene->HasMaterials())
           {
               QString  NomeTextura;
               QString  NomePath;
               QString  NomeArquivo;
               uint     qtdtexturas;
               aiString Path;
               aiString name;
               aiColor3D difusa   (0.f,0.f,0.f);
               aiColor3D ambiente (0.f,0.f,0.f);
               aiColor3D emissiva (0.f,0.f,0.f);
               aiColor3D specular (0.f,0.f,0.f);
               aiColor3D alpha    (0.f,0.f,0.f);
               float     opacidade,brilho;

               aiMaterial* mat = importador->scene->mMaterials[importador->scene->mMeshes[i]->mMaterialIndex];

               //Apenas para testar a quantidade de testuras retornada no arquivo
               qtdtexturas = mat->GetTextureCount(aiTextureType_DIFFUSE);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_SPECULAR);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_AMBIENT);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_EMISSIVE);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_HEIGHT);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_NORMALS);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_SHININESS);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_OPACITY);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_DISPLACEMENT);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_LIGHTMAP);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_REFLECTION);
               //qtdtexturas = mat->GetTextureCount(aiTextureType_UNKNOWN);

               mat->Get(AI_MATKEY_NAME             ,name);
               mat->Get(AI_MATKEY_COLOR_DIFFUSE    ,difusa);
               mat->Get(AI_MATKEY_COLOR_AMBIENT    ,ambiente);
               mat->Get(AI_MATKEY_COLOR_EMISSIVE   ,emissiva);
               mat->Get(AI_MATKEY_COLOR_SPECULAR   ,specular);
               mat->Get(AI_MATKEY_COLOR_TRANSPARENT,alpha);
               mat->Get(AI_MATKEY_OPACITY          ,opacidade);
               mat->Get(AI_MATKEY_SHININESS        ,brilho);

               NovoModelo->I3D_Mesh->I3D_Material = pINSMAMaterialManager->AddMaterial(name.C_Str(),IGL_MATERIAL_TEXTURE);

               pINSMAMaterialManager->SetaMaterial(NovoModelo->I3D_Mesh->I3D_Material   ,
                                                   CIMACor(difusa  .r,difusa  .g,difusa  .b,opacidade) ,
                                                   CIMACor(ambiente.r,ambiente.g,ambiente.b,opacidade)       ,
                                                   CIMACor(emissiva.r,emissiva.g,emissiva.b,opacidade)       ,
                                                   CIMACor(specular.r,specular.g,specular.b,opacidade)       ,
                                                   opacidade      ,
                                                   /*brilho*/1.0f  );

               pINSMAMaterialManager->SetaRejeicaoCor(NovoModelo->I3D_Mesh->I3D_Material,false,CIMACor(0.0f,0.0f,0.0f,1.0f));

               if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
               {
                   NomeTextura         = Path.C_Str();
                   NomePath            = "C:/William/Desenvolvimento/INS3D/world/Texturas/";
                   NomeArquivo         = NomePath + NomeTextura;

                   pINSMAMaterialManager->AddTextura(NovoModelo->I3D_Mesh->I3D_Material,NomeArquivo,IGL_TEXTURE_LINEAR);
               }

           }

           NovoModelo->I3D_Mesh->SetaShader       (I3D_Shader                          );
           NovoModelo->I3D_Mesh->CalculaBorda     (                                    ); //Calcula a Borda do Cubo
           NovoModelo->I3D_Mesh->CalculaNrml      (I3D_Mesh->I3D_BordaMesh.PegaCentro()); //Calcula as Normais do Cubo(Planares e Smooth)

           /************************************************************************/
           /*Atualmente o calculo de tangentes esta sendo realizado pelo importador*/
           /*O calculo de tangentes não está correto ainda e em fase de testes     */
           /************************************************************************/
           //CalculaTgns      (                          ); //Calcula as Tangentes do Cubo(Tangente e BiTangente)

           NovoModelo->I3D_Mesh->ConstroiBuffersSH(); //Aloca os Buffers na GPU da Placa de Video

           NovoModelo->I3D_Pos = NovoModelo->I3D_Mesh->I3D_BordaMesh.PegaCentro(); //Seta a Posição do Objeto

           modelos.push_back(NovoModelo);
       }
    }

    QString  NomeGrupo;
    QString  NomeModelo;
    aiString aiNomeGrupo;
    aiString aiNomeFilho;
    aiString aiNomeModelo;
    aiNode  *aiHirarqNode;
    int      IndiceModelo=0;

    //Constroi a Hierarquia do Modelo
    aiHirarqNode= importador->scene->mRootNode;
    aiNomeGrupo = importador->scene->mRootNode->mName;
    //Cria a Raiz do Modelo
    AddGrupo (aiNomeGrupo.C_Str(),"" );//Cria a Raiz do Modelo

    aiNomeGrupo = aiHirarqNode->mName;

    //Processa os Filhos deste Nó
    if(aiHirarqNode->mNumChildren>0)
    {
        for(unsigned int i=0;i<aiHirarqNode->mNumChildren;i++)
        {
            AddGrupo(aiHirarqNode->mChildren[i]->mName.C_Str()  ,
                                   aiNomeGrupo        .C_Str() );
        }
    }

    if(aiHirarqNode->mNumMeshes>0)
    {
        for(unsigned int i=0;i<aiHirarqNode->mNumMeshes;i++)
        {
            IndiceModelo = aiHirarqNode->mMeshes[i];
            AddModelo(BuscaModeloIndice(IndiceModelo),aiNomeGrupo.C_Str());
        }
    }

    //Processa os Filhos deste Nó
    if(aiHirarqNode->mNumChildren>0)
    {
        for(unsigned int i=0;i<aiHirarqNode->mNumChildren;i++)
        {
            ProcessaFilhoAssimp(aiHirarqNode->mChildren[i]);
        }
    }

    return true;
}

void CI3DModeloHierarquico::ProcessaFilhoAssimp(aiNode *pFilho)
{
    int      IndiceModelo=0;
    aiString aiNomeGrupo;

    aiNomeGrupo = pFilho->mName;

    //Cria os Grupos para cada Filho
    if(pFilho->mNumChildren>0)
    {
        for(unsigned int i=0;i<pFilho->mNumChildren;i++)
        {
            AddGrupo(pFilho->mChildren[i]->mName.C_Str()  ,
                             aiNomeGrupo        .C_Str() );
        }
    }

    if(pFilho->mNumMeshes>0)
    {
        for(unsigned int i=0;i<pFilho->mNumMeshes;i++)
        {
            IndiceModelo = pFilho->mMeshes[i];
            AddModelo(BuscaModeloIndice(IndiceModelo),aiNomeGrupo.C_Str());
        }
    }

    //Processa os Filhos deste Nó
    if(pFilho->mNumChildren>0)
    {
        for(unsigned int i=0;i<pFilho->mNumChildren;i++)
        {
            ProcessaFilhoAssimp(pFilho->mChildren[i]);
        }
    }
}

bool CI3DModeloHierarquico::AddModelo(int pTipo,CI3DNoModelo *pGrupo)
{
   CI3DPrimitivo *NovoModelo;
   switch(pTipo)
   {
      case 0:
      {
         NovoModelo = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                                     CIMTVetor(10.0f,10.0f,10.0f) ,
                                     IGL_WINMODE_CCW             );
         //NovoModelo->AddTextura(":/world/Texturas/Caixa.bmp",false);
         NovoModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
      }break;
      case 2:
      {
         NovoModelo = new CI3DEsfera(CIMTVetor(0.0f,10.0f,0.0f));
         NovoModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
      }break;
   }
   modelos.push_back(NovoModelo);
   if(pGrupo!=NULL)
   {
      pGrupo->AddModelo(NovoModelo);
   }
   else
   {
       if(hierarquia)
       {
          hierarquia->AddModelo(NovoModelo);
       }
   }
   return true;
}

bool CI3DModeloHierarquico::AddModelo(int pTipo,QString  pGrp2 )
{
   CI3DPrimitivo *NovoModelo;
   switch(pTipo)
   {
      case 0:
      {
         NovoModelo = new CI3DCubo  (CIMTVetor(0.0f,0.0f,0.0f),
                                     CIMTVetor(10.0f,10.0f,10.0f) ,
                                     IGL_WINMODE_CCW             );
         //NovoModelo->AddTextura(":/world/Texturas/Caixa.bmp",false);
         NovoModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
      }break;
      case 2:
      {
         NovoModelo = new CI3DEsfera(CIMTVetor(0.0f,20.0f,0.0f));

         NovoModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
      }break;
      case 3:
      {
         NovoModelo = new CI3DEsfera(CIMTVetor(20.0f,20.0f,0.0f));

         NovoModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
      }break;
      case 4:
      {
         NovoModelo = new CI3DEsfera(CIMTVetor(20.0f,20.0f,20.0f));
         NovoModelo->I3D_Mesh->SetaGeometryMode(IGL_GEOMETRY_DINAMIC);
      }break;

   }
   modelos.push_back(NovoModelo);

   if(!pGrp2.isEmpty())
   {
      BuscaGrupo(pGrp2)->AddModelo(NovoModelo);
   }
   else
   {
       if(hierarquia)
       {
          hierarquia->AddModelo(NovoModelo);
       }
   }
   return true;
}

bool CI3DModeloHierarquico::AddModelo(QString  pFile, QString  pGrp2 )
{
   CI3DPrimitivo *NovoModelo;

   NovoModelo = new CI3DModelo(pFile,"Modelo Hierarquico" + (PegaQtdModelos()+1),false);

   modelos.push_back(NovoModelo);

   if(!pGrp2.isEmpty())
   {
      BuscaGrupo(pGrp2)->AddModelo(NovoModelo);
   }
   else
   {
       if(hierarquia)
       {
          hierarquia->AddModelo(NovoModelo);
       }
   }
   return true;
}

bool CI3DModeloHierarquico::AddModelo(CI3DModelo  *pModelo, QString  pGrp2 )
{
   if(!pModelo)return false;
   /*******************************************************/
   /*Verificar Bug!                                       */
   /*Devido a um modelo ser utilizado por diversos fins   */
   /*E para aplicação de Otimizações a inclusão de        */
   /*Modelo na lista principal gerou duplicidade          */
   /*E problemas no processamento Espacial                */
   /*Como os Modelos carregam uma copia propria para poder*/
   /*Renderizar não há necessidade de inclui-los neste    */
   /*ponto mais...                                        */
   /*******************************************************/
   //modelos.push_back(pModelo);

   if(!pGrp2.isEmpty())
   {
      BuscaGrupo(pGrp2)->AddModelo(pModelo);
   }
   else
   {
       if(hierarquia)
       {
          hierarquia->AddModelo(pModelo);
       }
   }
   return true;
}

bool CI3DModeloHierarquico::AddGrupo(QString  pNome,CI3DNoModelo *pGrupo)
{
   CI3DNoModelo *NovoGrupo;

   NovoGrupo = new CI3DNoModelo(pNome);

   grupos.push_back(NovoGrupo);

   if(pGrupo!=NULL)
   {
       Connect(pGrupo->PegaNome(),pNome);
   }
   else
   {
       if(!hierarquia)
       {
          hierarquia = NovoGrupo;
       }
   }

   return true;
}

bool CI3DModeloHierarquico::AddGrupo(QString  pGrp1, QString pGrp2 )
{
   CI3DNoModelo *NovoGrupo;

   NovoGrupo = new CI3DNoModelo(pGrp1);

   grupos.push_back(NovoGrupo);

   if(!pGrp2.isEmpty())
   {
       Connect(pGrp2,pGrp1);
   }
   else
   {
       if(!hierarquia)
       {
          hierarquia = NovoGrupo;
       }
   }

   return true;
}

bool CI3DModeloHierarquico::Connect(QString  pGrp1, QString pGrp2 )
{
     CI3DNoModelo *Grupo1,*Grupo2;

     Grupo1 = BuscaGrupo(pGrp1);
     Grupo2 = BuscaGrupo(pGrp2);

     Grupo1->AddFilho(Grupo2);

     return true;
}

int CI3DModeloHierarquico::PegaQtdGrupos()
{
    return (int)grupos.size();
}

int CI3DModeloHierarquico::PegaQtdModelos(QString pGrp1)
{
    return BuscaGrupo(pGrp1)->PegaQtdModelos();
}

int CI3DModeloHierarquico::PegaQtdModelos(int pIdGrupo)
{
    return BuscaGrupo(pIdGrupo)->PegaQtdModelos();
}

int CI3DModeloHierarquico::PegaQtdModelos()
{
    return (int)modelos.size();
}

CI3DNoModelo * CI3DModeloHierarquico::BuscaGrupo(QString  pNome)
{
   list<CI3DNoModelo*>::iterator i;
   for(i = grupos.begin(); i != grupos.end(); i++)
   {
       if((*i)->PegaNome()==pNome)
       {
          return (*i);
       }
   }
   return NULL;
}

CI3DNoModelo * CI3DModeloHierarquico::BuscaGrupo(int pIdGrupo)
{
    int Id=0;
    list<CI3DNoModelo*>::iterator i;
    for(i = grupos.begin(); i != grupos.end(); i++)
    {
        if(Id==pIdGrupo)
        {
           return (*i);
        }
        Id++;
    }
    return NULL;
}

CI3DModelo * CI3DModeloHierarquico::BuscaModelo(QString  pNome,int pIdModelo)
{
   CI3DNoModelo *pGrupo = BuscaGrupo(pNome);

   if(pGrupo->TemModelo())
   {
      return pGrupo->PegaModelo(pIdModelo);
   }

   return NULL;
}

CI3DModelo * CI3DModeloHierarquico::BuscaModelo(int pIdGrupo,int pIdModelo)
{
    int Id=0;
    list<CI3DNoModelo*>::iterator i;
    for(i = grupos.begin(); i != grupos.end(); i++)
    {
        if(Id==pIdGrupo)
        {
           if((*i)->TemModelo())
           {
              return (*i)->PegaModelo(pIdModelo);
           }
           else
           {
              return NULL;
           }
        }
        Id++;
    }
    return NULL;
}

CI3DModelo * CI3DModeloHierarquico::BuscaModeloIndice(int pIndiceModelo)
{
    int Id=0;
    list<CI3DPrimitivo*>::iterator i;
    for(i = modelos.begin(); i != modelos.end(); i++)
    {
        if(Id==pIndiceModelo)
        {
           return (CI3DModelo *)(*i);
        }
        Id++;
    }
    return NULL;
}

void CI3DModeloHierarquico::Render(int pRenderMode ,int pPolygonMode ,  int pShadingMode)
{
    hierarquia->Render(pRenderMode,pPolygonMode,pShadingMode);
}

void CI3DModeloHierarquico::Build()
{
   //AddGrupo ("Cubo","" );//Cria a Raiz do Modelo
   //AddModelo(0     ,NULL);//Cria o Modelo na Raiz

   //AddGrupo ("Esfera","Cubo"  );//Cria grupo abaixo do Cubo
   //AddModelo(2       ,"Esfera");//Cria o Modelo na Raiz
   //AddModelo(3       ,"Esfera");//Cria o Modelo na Raiz
   //AddModelo(4       ,"Esfera");//Cria o Modelo na Raiz

    AddGrupo ("Piso","" );//Cria a Raiz do Modelo
    AddModelo("C:/William/Desenvolvimento/INS3D/world/Modelos/Piso.obj",NULL);//Cria o Modelo na Raiz
    AddModelo("C:/William/Desenvolvimento/INS3D/world/Modelos/Rua.obj" ,NULL);//Cria o Modelo na Raiz

    AddGrupo ("Casas","Piso"  );//Cria grupo abaixo do Piso
    AddModelo("C:/William/Desenvolvimento/INS3D/world/Modelos/Casa01.obj","Casas");//Cria o Modelo na Raiz
    AddModelo("C:/William/Desenvolvimento/INS3D/world/Modelos/Casa02.obj","Casas");//Cria o Modelo na Raiz
    AddModelo("C:/William/Desenvolvimento/INS3D/world/Modelos/Casa03.obj","Casas");//Cria o Modelo na Raiz
    AddModelo("C:/William/Desenvolvimento/INS3D/world/Modelos/Casa04.obj","Casas");//Cria o Modelo na Raiz

}
