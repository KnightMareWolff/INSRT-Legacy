/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef ISH_PROGRAM_H
#define ISH_PROGRAM_H

#include "ISH_VertexShader.h"
#include "ISH_FragmentShader.h"
#include "ISH_GeometryShader.h"
#include "ISH_TessCtrlShader.h"
#include "ISH_TessEvalShader.h"
#include "ISH_ComputeShader.h"

class CISHProgram : public QOpenGLShaderProgram
{
public:
    CISHProgram();
    void AddShader  (QString pPath  , int pShaderType );
    void AddFeedBack(bool bFeedBack                   );

    QString ISH_NomeProgram;//Nome Chave de Identificação do programa
    bool    ISH_Feedback   ;//Informa se devemos incluir feedback ou não
};

#endif // ISH_PROGRAM_H
