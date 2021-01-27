/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IUT_CarregadorArquivos.h"

CIUTCarregadorArquivos::CIUTCarregadorArquivos()
{

}

bool CIUTCarregadorArquivos::Importar(QString pNomeArq, bool pIUT_LeftHanded)
{
//  scene = importer.ReadFile( "C:/William/Desenvolvimento/INS3D/world/Modelos/FuseModel.fbx",
//    scene = importer.ReadFile( pNomeArq.toStdString() ,
//            aiProcess_Triangulate             |
//            aiProcess_SortByPType             |
//            aiProcess_RemoveRedundantMaterials|
//            aiProcess_FixInfacingNormals      |
//            aiProcess_FindInvalidData         |
//            aiProcess_GenUVCoords             |
//            aiProcess_TransformUVCoords       |
//            aiProcess_FlipUVs);

    if(pIUT_LeftHanded)
    {
        scene = importer.ReadFile( pNomeArq.toStdString() ,
                                   aiProcess_MakeLeftHanded          |
                                   aiProcess_Triangulate             |
                                   aiProcess_SortByPType             |
                                   aiProcess_RemoveRedundantMaterials|
                                   aiProcess_FixInfacingNormals      |
                                   aiProcess_FindInvalidData         |
                                   aiProcess_GenUVCoords             |
                                   aiProcess_TransformUVCoords       |
                                   aiProcess_FlipUVs                 |
                                   aiProcess_CalcTangentSpace);
    }
    else
    {
        scene = importer.ReadFile( pNomeArq.toStdString() ,
                                   aiProcess_Triangulate             |
                                   aiProcess_SortByPType             |
                                   aiProcess_RemoveRedundantMaterials|
                                   aiProcess_FixInfacingNormals      |
                                   aiProcess_FindInvalidData         |
                                   aiProcess_GenUVCoords             |
                                   aiProcess_TransformUVCoords       |
                                   aiProcess_FlipUVs                 |
                                   aiProcess_CalcTangentSpace);
    }
    // If the import failed, report it
    if( !scene)
    {
      return false;
    }

    return true;
}
