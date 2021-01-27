/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IUT_CARREGADORARQUIVOS_H
#define IUT_CARREGADORARQUIVOS_H

#include "IUT_GlobalDef.h"

class CIUTCarregadorArquivos
{
public:
    CIUTCarregadorArquivos();

    bool Importar(QString pNomeArq,bool pIUT_LeftHanded);

//Cria Instancia do importador e Objeto com a Cena
      Assimp::Importer importer;
const aiScene*         scene;
};

#endif // CIUTCARREGADORARQUIVOS_H
