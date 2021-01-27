/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_FOLHABSP_H
#define I3D_FOLHABSP_H

#include "I3D_GlobalDef.h"
#include "I3D_FaceBsp.h"

class CI3DFolhaBsp
{

public:

    CIMTBorda   I3D_Borda;

    long		I3D_IndicePVS ;

    std::vector<long>   I3D_FaceIndices;
    std::vector<long>   PortalIndices;
    std::vector<long>   ObjectIndices;
    std::vector<long>   RefLogIndices;

    unsigned long       I3D_FaceCount  ;// Numero de faces na Folha
    unsigned long       PortalCount    ;// Numero de portals na Folha
    unsigned long       ObjectCount    ;// Numero de obj dinâmicos/detalhados na Folha
    unsigned long       RefLogCount    ;// Numero de Ref Logicas na Folha

public:
    ~CI3DFolhaBsp();
     CI3DFolhaBsp();

     bool ConstroiIndicesFaces( CI3DFaceBsp * pListaFaces );
     bool AdicionaPortal      ( unsigned long IndicePortal);
     bool AdicionaRefLogica   ( unsigned long IndiceRefLog);
     bool AdicionaObjDetalhado( unsigned long IndiceObjDet);

};

#endif // I3D_FOLHABSP_H
