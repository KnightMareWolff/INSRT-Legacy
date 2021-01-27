#ifndef CIGOMUNDO_H
#define CIGOMUNDO_H

#include "IGO_GlobalDef.h"
#include "IGO_Nivel.h"

class CIGOMundo
{
public:
    CIGOMundo();

    void Render();

private:
    CIUTGrafo<CIGONivel>    IGO_Mundo ;
    CIUTGrafo<CIGONivel>   *pGrafo01  ;
    CIUTGrafo<CIGONivel>   *pGrafo02  ;
    CIGONivel              *pNivel01  ,
                           *pNivel02  ,
                           *pNivel03  ;

};

#endif // CIGOWORLD_H
