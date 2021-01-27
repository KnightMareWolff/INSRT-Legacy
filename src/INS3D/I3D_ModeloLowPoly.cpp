#include "I3D_ModeloLowPoly.h"


CI3DModeloLowPoly::CI3DModeloLowPoly()
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON   ;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;

    mBsp = new CI3DArvoreBsp;
    mBsp->I3D_TpArvore            = BSP_TYPE_SPLIT;
    mBsp->I3D_AcumuladorDivisores = 60;
    mBsp->I3D_HeuristicaDivisao   = 3.0f;
    mBsp->I3D_RemoveFolhasIlegais = true;

    mHSR = new CI3DProcessadorHSR;
}

CI3DModeloLowPoly::CI3DModeloLowPoly(QString   pNomeArquivo)
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON   ;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;

    mBsp = new CI3DArvoreBsp;
    mBsp->I3D_TpArvore            = BSP_TYPE_SPLIT;
    mBsp->I3D_AcumuladorDivisores = 60;
    mBsp->I3D_HeuristicaDivisao   = 3.0f;
    mBsp->I3D_RemoveFolhasIlegais = true;

    mHSR = new CI3DProcessadorHSR;
}
CI3DModeloLowPoly::CI3DModeloLowPoly(CIMTVetor pPos)
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON   ;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;

    mBsp = new CI3DArvoreBsp;
    mBsp->I3D_TpArvore            = BSP_TYPE_SPLIT;
    mBsp->I3D_AcumuladorDivisores = 60;
    mBsp->I3D_HeuristicaDivisao   = 3.0f;
    mBsp->I3D_RemoveFolhasIlegais = true;

    mHSR = new CI3DProcessadorHSR;
}
CI3DModeloLowPoly::CI3DModeloLowPoly(CIMTVetor pPos,QString mNomeMaterial)
{
    I3D_Mesh->PolygonMode =IGL_RENDER_POLYGON   ;
    I3D_Mesh->ShadingMode =IGL_SHADING_MODE_FLAT;
    I3D_Mesh->MeshType    =IGL_MESH_SKINNED     ;
    I3D_Mesh->RenderMode  =IGL_MODE_RENDER;

    mBsp = new CI3DArvoreBsp;
    mBsp->I3D_TpArvore            = BSP_TYPE_SPLIT;
    mBsp->I3D_AcumuladorDivisores = 60;
    mBsp->I3D_HeuristicaDivisao   = 3.0f;
    mBsp->I3D_RemoveFolhasIlegais = true;

    mHSR = new CI3DProcessadorHSR;
}

bool CI3DModeloLowPoly::AddGeometria(CI3DModeloHierarquico pModelo)
{
    /*******************************************************/
    /*Carrega Modelo Hierarquico diretamente na BSP        */
    /*******************************************************/
    /*
    int IndiceMatAtu=0;
    for(int i=0 ; i< pModelo->PegaQtdGrupos();i++)
    {
        for(int j=0;j<pModelo->BuscaGrupo(i)->PegaQtdModelos();j++)
        {
           mMateriaisLowPoly.push_back(pModelo->BuscaGrupo(i)->PegaModelo(j)->pMat);

           IndiceMatAtu = mMateriaisLowPoly.size()-1;

           for(int k=0;k<pModelo->BuscaGrupo(i)->PegaModelo(j)->I3D_QtdFaces;k++)
           {
               pModelo->BuscaGrupo(i)->PegaModelo(j)->Faces[k]->I3D_IndiceMaterial = IndiceMatAtu;
           }

           mBsp->AdicionaFaces(pModelo->BuscaGrupo(i)->PegaModelo(j)->Faces,
                               pModelo->BuscaGrupo(i)->PegaModelo(j)->I3D_QtdFaces);
        }
    }
    */
    /*******************************************************/
    /*Carrega Modelo Hierarquico na Lista de Primitivos    */
    /*******************************************************/
    int IndiceMatAtu=0;
    int QtdMod=0;
    int IdMat=0;
    for(int i=0 ; i< pModelo.PegaQtdModelos();i++)
    {
        QtdMod++;
        mMateriaisLowPoly.push_back(pModelo.BuscaModeloIndice(i)->I3D_Mesh->I3D_Material);

        IndiceMatAtu = mMateriaisLowPoly.size()-1;

        for(int k=0;k<pModelo.BuscaModeloIndice(i)->I3D_Mesh->I3D_QtdFaces;k++)
        {
            IdMat = mMateriaisLowPoly[IndiceMatAtu];
            pModelo.BuscaModeloIndice(i)->I3D_Mesh->Faces[k]->I3D_IndiceMaterial = IdMat;
        }

        mGeometriaLowPoly.push_back(pModelo.BuscaModeloIndice(i));
    }
    return true;
}

bool CI3DModeloLowPoly::AddBorda(bool bTrue)
{
    return mBsp->AdicionaBordasPoligonos(bTrue);
}

void CI3DModeloLowPoly::Compila()
{
    //Adiciona Geometria no Processador HSR
    for(int i=0;i<mGeometriaLowPoly.size();i++)
    {
       mHSR->AddPrimitivo(mGeometriaLowPoly[i]);
    }

    mHSR->Processa();

    mPrimitivoResultante = mHSR->PegaPrimitivoResultante();

    mBsp->AdicionaFaces(mPrimitivoResultante->I3D_Mesh->Faces,
                        mPrimitivoResultante->I3D_Mesh->I3D_QtdFaces);

    mBsp->CompilaArvore();
}

void CI3DModeloLowPoly::CalculaBorda()
{
    mBsp->CalculaBorda();
    I3D_Pos = mBsp->PegaBorda().PegaCentro();
}

void CI3DModeloLowPoly::Render      (CIMTVetor pPos         ,
                                     int       pRenderMode  ,
                                     int       pPolygonMode ,
                                     int       pMaterialMode,
                                     int       pShadingMode ,
                                     int       pGeometryMode)
{
    long  IndiceFolha;

    I3D_Mesh->PolygonMode  = pPolygonMode;
    I3D_Mesh->ShadingMode  = pShadingMode;
    I3D_Mesh->RenderMode   = pRenderMode;
    I3D_Mesh->GeometryMode = pGeometryMode;

    /******************************************/
    /*Atualiza Matrizes de Transformação      */
    /******************************************/
    Update();

    IndiceFolha = mBsp->ProcuraFolha( pPos );

    //Se Não encontrou uma Folha Renderiza todo mundo
    if ( IndiceFolha < 0 )
    {

       long lQtdFolhas = mBsp->PegaQtdFolhas();
       for ( long i = 0; i < lQtdFolhas ; i++ )
       {
           int iQtdFaces = mBsp->PegaFolha(i)->I3D_FaceCount;

           for(long j=0;j<iQtdFaces;j++)
           {
              long lIndiceFace = mBsp->PegaFolha(i)->I3D_FaceIndices[j];
              int  iIndiceMat  = mBsp->PegaFace(lIndiceFace)->I3D_IndiceMaterial;
              int  QtdMat = pINSMAMaterialManager->PegaQtdMateriais();

              pINSMAMaterialManager->Prepara(I3D_Shader,iIndiceMat);

              mBsp->PegaFace(lIndiceFace)->Renderiza(pRenderMode ,pPolygonMode, pShadingMode,pGeometryMode);
           }
       }

    }
    else
    {
        int iQtdFaces = mBsp->PegaFolha(IndiceFolha)->I3D_FaceCount;

        for(long j=0;j<iQtdFaces;j++)
        {
           long lIndiceFace = mBsp->PegaFolha(IndiceFolha)->I3D_FaceIndices[j];
           int  iIndiceMat  = mBsp->PegaFace(lIndiceFace)->I3D_IndiceMaterial;

           pINSMAMaterialManager->Prepara(I3D_Shader,iIndiceMat);

           mBsp->PegaFace(lIndiceFace)->Renderiza(pRenderMode ,pPolygonMode, pShadingMode,pGeometryMode);
        }
    }
}
