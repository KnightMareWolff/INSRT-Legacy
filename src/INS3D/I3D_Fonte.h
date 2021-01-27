/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_FONTE_H
#define I3D_FONTE_H

#include "I3D_Painel.h"

class CI3DFonte: public CI3DPainel , public INSMA
{
public:
    CI3DFonte();

    bool AddFont       (QString pI3D_ImgFonte,QString pI3D_NomeFonte);
    int  PegaIndiceChar(char    pChar   );

protected:
    void Build              (    );
    void BuildTextureCoord  (    );
private:
    char   *pTabelaCaracteres;
    QString I3D_NomeFonte;
};

#endif // I3D_FONTE_H
