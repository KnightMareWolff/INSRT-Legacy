/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_NoBsp.h"


CI3DNoBsp::CI3DNoBsp()
{
    Plano     =-1;
    I3D_Atras =-1;
    I3D_Frente=-1;
}

CI3DNoBsp::~CI3DNoBsp()
{
    Plano     =-1;
    I3D_Atras =-1;
    I3D_Frente=-1;
}

void CI3DNoBsp::CalculaBordaNo(CI3DFaceBsp *ListaFaces,bool kbcPermiteAcumulo)
{
    CI3DFaceBsp *Iterator = ListaFaces;
    while ( Iterator )
    {
        I3D_Borda.CalculaBordaMesh( Iterator->Vertices,Iterator->I3D_QtdVertices,sizeof(CI3DVertice), kbcPermiteAcumulo );
        kbcPermiteAcumulo = false;
        Iterator = Iterator->Proximo;
    }
}

