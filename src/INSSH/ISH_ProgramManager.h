/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef CISHPROGRAMMANAGER_H
#define CISHPROGRAMMANAGER_H

#include "ISH_GlobalDef.h"
#include "ISH_Program.h"

class CISHProgramManager
{
public:
    CISHProgramManager(                      );
    CISHProgramManager(INSGL *pISHGLPlat     );

    int  AddProgram (QString pISH_NomeProgram);
    void AddShader  (QString pISH_NomeProgram,QString pISH_NomeShader,int pISH_TpShader);
    void AddShader  (int     pISH_Indice     ,QString pISH_NomeShader,int pISH_TpShader);
    void Compile    (                        );
    uint ProgramId  (QString pISH_NomeProgram);
private:
    /******************************/
    /*Metodos Privados de Acesso  */
    /******************************/
    bool ChecaDuplicado(QString pISH_NomeProgram,int &pISH_IndiceExistente);
    bool ChecaExistente(QString pISH_NomeProgram                          );
    bool ChecaExistente(int     pISH_Indice                               );
    int  PegaIndice    (QString pISH_NomeProgram                          );

    /********************************/
    /*Atributos Privados de Acesso  */
    /********************************/
    int                  ISH_QtdProgramas;
    vector<CISHProgram*> ISH_Programas;
    INSGL             * pISHGLPlatInterface;//Interface com a placa de Video - OpenGL
};

#endif // CISHPROGRAMMANAGER_H
