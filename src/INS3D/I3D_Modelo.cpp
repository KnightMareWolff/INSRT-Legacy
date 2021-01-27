/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_Modelo.h"


CI3DModelo::~CI3DModelo()
{
    delete importador;
}

CI3DModelo::CI3DModelo():
    CI3DPrimitivo()
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;
}

CI3DModelo::CI3DModelo(QString   pI3D_NomeArquivo, QString pI3D_NomeModelo, bool pI3D_MakeLeftHand):
    CI3DPrimitivo()
{
    int iQtdMeshs    ,
        iQtdTexturas ,
        iQtdMateriais,
        iQtdAnimacoes,
        iQtdLuzes    ,
        iQtdCameras  ,
        iQtdFaces    ,
        iQtdVertices ;

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


    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;

    importador = new CIUTCarregadorArquivos;

    importador->Importar(pI3D_NomeArquivo,pI3D_MakeLeftHand);

    mNomeModelo = pI3D_NomeModelo;

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
           if(importador->scene->mMeshes[i]->HasFaces())
           {
               iQtdFaces = importador->scene->mMeshes[i]->mNumFaces;
               I3D_Mesh->AdicionaFaces(iQtdFaces);
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

                   I3D_Mesh->Faces[j]->AdicionaVertices(3,IGL_RENDER_TRIANGLES);

                   I3D_Mesh->Faces[j]->Vertices[0] = CI3DVertice(vertice0);
                   I3D_Mesh->Faces[j]->Vertices[1] = CI3DVertice(vertice1);
                   I3D_Mesh->Faces[j]->Vertices[2] = CI3DVertice(vertice2);

                   //Criado no Poligono original Indices para reconstrução da Skin
                   I3D_Mesh->Faces[j]->I3D_IndicesSkin[0] = iIndice01;
                   I3D_Mesh->Faces[j]->I3D_IndicesSkin[1] = iIndice02;
                   I3D_Mesh->Faces[j]->I3D_IndicesSkin[2] = iIndice03;

                   if(importador->scene->mMeshes[i]->HasTextureCoords(0))
                   {
                       fPosU = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice01].x;
                       fPosV = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice01].y;

                       I3D_Mesh->Faces[j]->Vertices[0].I3D_CoordTexturaU = fPosU;
                       I3D_Mesh->Faces[j]->Vertices[0].I3D_CoordTexturaV = fPosV;

                       fPosU = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice02].x;
                       fPosV = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice02].y;

                       I3D_Mesh->Faces[j]->Vertices[1].I3D_CoordTexturaU = fPosU;
                       I3D_Mesh->Faces[j]->Vertices[1].I3D_CoordTexturaV = fPosV;

                       fPosU = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice03].x;
                       fPosV = importador->scene->mMeshes[i]->mTextureCoords[0][iIndice03].y;

                       I3D_Mesh->Faces[j]->Vertices[2].I3D_CoordTexturaU = fPosU;
                       I3D_Mesh->Faces[j]->Vertices[2].I3D_CoordTexturaV = fPosV;
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

                       I3D_Mesh->Faces[j]->Vertices[0].I3D_Tangente   = tangent0;
                       I3D_Mesh->Faces[j]->Vertices[0].I3D_BiTangente = bitangt0;

                       I3D_Mesh->Faces[j]->Vertices[1].I3D_Tangente   = tangent1;
                       I3D_Mesh->Faces[j]->Vertices[1].I3D_BiTangente = bitangt1;

                       I3D_Mesh->Faces[j]->Vertices[2].I3D_Tangente   = tangent2;
                       I3D_Mesh->Faces[j]->Vertices[2].I3D_BiTangente = bitangt2;
                   }

                   I3D_Mesh->Faces[j]->Triangulariza();

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


               I3D_Mesh->SetaMaterial(pINSMAMaterialManager->AddMaterial(mNomeModelo,IGL_MATERIAL_NORMALMAP));

               pINSMAMaterialManager->SetaMaterial(I3D_Mesh->I3D_Material   ,
                                                   CIMACor(difusa  .r,difusa  .g,difusa  .b,opacidade) ,
                                                   CIMACor(ambiente.r,ambiente.g,ambiente.b,opacidade)       ,
                                                   CIMACor(emissiva.r,emissiva.g,emissiva.b,opacidade)       ,
                                                   CIMACor(specular.r,specular.g,specular.b,opacidade)       ,
                                                   opacidade      ,
                                                   /*brilho*/ 0.5f         );

               pINSMAMaterialManager->SetaRejeicaoCor(I3D_Mesh->I3D_Material,false,CIMACor(0.0f,0.0f,0.0f,1.0f));


               if (mat->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
               {
                   int IdTextura=0;
                   NomeTextura         = Path.C_Str();
                   NomePath            = CIUTGerenciadorPath::IUT_PathWorld + "Texturas/";
                   //NomeArquivo         = NomePath + NomeTextura;
                   NomeArquivo           = NomePath + "ogre_diffuse.bmp";
                   IdTextura=pINSMAMaterialManager->AddTextura(I3D_Mesh->I3D_Material,NomeArquivo,IGL_TEXTURE_LINEAR);

                   //Inclui os Layers de txtura somente já que a textura Base foi carregada e o material criado
                   pINSMAMaterialManager->AddLayerTex(I3D_Mesh->I3D_Material,
                                                      IdTextura,
                                                      CIUTGerenciadorPath::IUT_PathWorld + "Texturas/ogre_detail.bmp",
                                                      IMA_LAYER_CHN_DETAIL);

                   pINSMAMaterialManager->AddLayerTex(I3D_Mesh->I3D_Material,
                                                      IdTextura,
                                                      CIUTGerenciadorPath::IUT_PathWorld + "Texturas/ogre_normalmap.bmp",
                                                      IMA_LAYER_CHN_NMAP);
               }

           }
           I3D_Mesh->SetaShader       (I3D_Shader                          );
           I3D_Mesh->CalculaBorda     (                                    ); //Calcula a Borda do Cubo
           I3D_Mesh->CalculaNrml      (I3D_Mesh->I3D_BordaMesh.PegaCentro()); //Calcula as Normais do Cubo(Planares e Smooth)

           /************************************************************************/
           /*Atualmente o calculo de tangentes esta sendo realizado pelo importador*/
           /*O calculo de tangentes não está correto ainda e em fase de testes     */
           /************************************************************************/
           //CalculaTgns      (                          ); //Calcula as Tangentes do Cubo(Tangente e BiTangente)

           I3D_Mesh->ConstroiBuffersSH(                          ); //Aloca os Buffers na GPU da Placa de Video

           I3D_Pos = I3D_Mesh->I3D_BordaMesh.PegaCentro(); //Seta a Posição do Objeto
       }
    }

    delete importador;
    importador=NULL;
}
