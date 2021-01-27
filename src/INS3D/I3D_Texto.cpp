#include "I3D_Texto.h"


CI3DTexto::CI3DTexto(CI3DFonte *pFonte, int nLinhas, int nColunas):
    CI3DPainel()
{
   cFonte       = pFonte;

   //Atribui o material da Fonte para a realização da Renderização
   I3D_Mesh->I3D_Material = cFonte->I3D_Mesh->I3D_Material;

   if(nColunas>0){iQtdColunas  = nColunas;}
   else{iQtdColunas  = 1;}

   if(nLinhas>0){ iQtdLinhas   = nLinhas ;}
   else{iQtdLinhas   = 1;}

   iQtdCaracter = iQtdLinhas * iQtdColunas;

   iTamCaracter = 1;

}

CI3DTexto::CI3DTexto(CI3DFonte *pFonte, QString pTexto, int iTamChar):
    CI3DPainel()
{
   cFonte       = pFonte;

   //Atribui o material da Fonte para a realização da Renderização
   I3D_Mesh->I3D_Material = cFonte->I3D_Mesh->I3D_Material;

   if(pTexto.size()>0){iQtdColunas  = pTexto.size();}
   else{iQtdColunas  = 1;}

   iQtdLinhas   = 1;

   iQtdCaracter = iQtdLinhas * iQtdColunas;

   iTamCaracter = iTamChar;

   Build();
   int i;
   for(i=0 ; i< pTexto.size();i++)
   {
      int id = cFonte->PegaIndiceChar(pTexto.at(i).toLatin1());
      iTexto.push_back(id);
   }

   for(i=0 ; i< iTexto.size();i++)
   {
      I3D_Mesh->Faces[i]->Vertices[0].I3D_CoordTexturaU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[0].I3D_CoordTexturaU;
      I3D_Mesh->Faces[i]->Vertices[0].I3D_CoordTexturaV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[0].I3D_CoordTexturaV;
      I3D_Mesh->Faces[i]->Vertices[0].I3D_CoordDetTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[0].I3D_CoordDetTextU;
      I3D_Mesh->Faces[i]->Vertices[0].I3D_CoordDetTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[0].I3D_CoordDetTextV;
      I3D_Mesh->Faces[i]->Vertices[0].I3D_CoordLtmTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[0].I3D_CoordLtmTextU;
      I3D_Mesh->Faces[i]->Vertices[0].I3D_CoordLtmTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[0].I3D_CoordLtmTextV;

      I3D_Mesh->Faces[i]->Vertices[1].I3D_CoordTexturaU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[1].I3D_CoordTexturaU;
      I3D_Mesh->Faces[i]->Vertices[1].I3D_CoordTexturaV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[1].I3D_CoordTexturaV;
      I3D_Mesh->Faces[i]->Vertices[1].I3D_CoordDetTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[1].I3D_CoordDetTextU;
      I3D_Mesh->Faces[i]->Vertices[1].I3D_CoordDetTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[1].I3D_CoordDetTextV;
      I3D_Mesh->Faces[i]->Vertices[1].I3D_CoordLtmTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[1].I3D_CoordLtmTextU;
      I3D_Mesh->Faces[i]->Vertices[1].I3D_CoordLtmTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[1].I3D_CoordLtmTextV;

      I3D_Mesh->Faces[i]->Vertices[2].I3D_CoordTexturaU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[2].I3D_CoordTexturaU;
      I3D_Mesh->Faces[i]->Vertices[2].I3D_CoordTexturaV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[2].I3D_CoordTexturaV;
      I3D_Mesh->Faces[i]->Vertices[2].I3D_CoordDetTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[2].I3D_CoordDetTextU;
      I3D_Mesh->Faces[i]->Vertices[2].I3D_CoordDetTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[2].I3D_CoordDetTextV;
      I3D_Mesh->Faces[i]->Vertices[2].I3D_CoordLtmTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[2].I3D_CoordLtmTextU;
      I3D_Mesh->Faces[i]->Vertices[2].I3D_CoordLtmTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[2].I3D_CoordLtmTextV;

      I3D_Mesh->Faces[i]->Vertices[3].I3D_CoordTexturaU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[3].I3D_CoordTexturaU;
      I3D_Mesh->Faces[i]->Vertices[3].I3D_CoordTexturaV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[3].I3D_CoordTexturaV;
      I3D_Mesh->Faces[i]->Vertices[3].I3D_CoordDetTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[3].I3D_CoordDetTextU;
      I3D_Mesh->Faces[i]->Vertices[3].I3D_CoordDetTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[3].I3D_CoordDetTextV;
      I3D_Mesh->Faces[i]->Vertices[3].I3D_CoordLtmTextU = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[3].I3D_CoordLtmTextU;
      I3D_Mesh->Faces[i]->Vertices[3].I3D_CoordLtmTextV = cFonte->I3D_Mesh->Faces[iTexto[i]]->Vertices[3].I3D_CoordLtmTextV;
   }

   I3D_Mesh->SetaShader         (I3D_Shader                          );
   I3D_Mesh->CalculaBorda       (                                    );
   I3D_Mesh->CalculaNrml        (I3D_Mesh->I3D_BordaMesh.PegaCentro());

   if(iTpPainel == IGL_PAINEL_DEFAULT)
   {
      I3D_Mesh->ConstroiBuffersSH  (                          );
   }

   I3D_Pos = I3D_Mesh->I3D_BordaMesh.PegaCentro();

}

void CI3DTexto::Build()
{
    int   Index          = 0;

    float x,y,z;

    CI3DVertice vertice1,
                vertice2,
                vertice3,
                vertice4;


    I3D_Mesh->AdicionaFaces(iQtdCaracter);
    /****************************************/
    /*Adiciona o Total de Vertices do Painel*/
    /****************************************/
    for ( int Y = 0; Y < (iQtdLinhas*iTamCaracter); Y +=iTamCaracter )
    {
       for ( int X = 0;  X < (iQtdColunas*iTamCaracter); X +=iTamCaracter )
       {
           I3D_Mesh->Faces[Index]->AdicionaVertices(4,I3D_Mesh->PolygonMode);

           // Embaixo e Esquerda
           x = X;
           y = 0;
           z = Y;

           vertice1                   = CI3DVertice(x, y, z);
           vertice1.I3D_CoordTexturaU = 0.0f;
           vertice1.I3D_CoordTexturaV = 0.0f;
           vertice1.I3D_CoordDetTextU = 0.0f;
           vertice1.I3D_CoordDetTextU = 0.0f;
           vertice1.I3D_CoordLtmTextU = 0.0f;
           vertice1.I3D_CoordLtmTextU = 0.0f;

           // Acima e Esquerda
           x = X;
           y = 0;
           z = Y + iTamCaracter ;

           vertice2                   = CI3DVertice(x, y, z);
           vertice2.I3D_CoordTexturaU = 1.0f;
           vertice2.I3D_CoordTexturaV = 0.0f;
           vertice2.I3D_CoordDetTextU = 1.0f;
           vertice2.I3D_CoordDetTextV = 0.0f;
           vertice2.I3D_CoordLtmTextU = 1.0f;
           vertice2.I3D_CoordLtmTextV = 0.0f;

           // Acima e Direita
           x = X + iTamCaracter;
           y = 0;
           z = Y + iTamCaracter ;

           vertice3                   = CI3DVertice(x, y, z);
           vertice3.I3D_CoordTexturaU = 1.0f;
           vertice3.I3D_CoordTexturaV = 1.0f;
           vertice3.I3D_CoordDetTextU = 1.0f;
           vertice3.I3D_CoordDetTextV = 1.0f;
           vertice3.I3D_CoordLtmTextU = 1.0f;
           vertice3.I3D_CoordLtmTextV = 1.0f;

           // Embaixo e Direita
           x = X + iTamCaracter;
           y = 0;
           z = Y;

           vertice4                   = CI3DVertice(x, y, z);
           vertice4.I3D_CoordTexturaU = 0.0f;
           vertice4.I3D_CoordTexturaV = 1.0f;
           vertice4.I3D_CoordDetTextU = 0.0f;
           vertice4.I3D_CoordDetTextV = 1.0f;
           vertice4.I3D_CoordLtmTextU = 0.0f;
           vertice4.I3D_CoordLtmTextV = 1.0f;

           if(I3D_Mesh->WindingMode==IGL_WINMODE_CW)
           {
               //Preenchemos o vetor de vertices
               I3D_Mesh->Faces[Index]->Vertices[0]     = vertice1;
               I3D_Mesh->Faces[Index]->Vertices[1]     = vertice2;
               I3D_Mesh->Faces[Index]->Vertices[2]     = vertice3;
               I3D_Mesh->Faces[Index]->Vertices[3]     = vertice4;
           }
           else
           {
               //Preenchemos o vetor de vertices
               I3D_Mesh->Faces[Index]->Vertices[0]     = vertice4;
               I3D_Mesh->Faces[Index]->Vertices[1]     = vertice3;
               I3D_Mesh->Faces[Index]->Vertices[2]     = vertice2;
               I3D_Mesh->Faces[Index]->Vertices[3]     = vertice1;
           }


           I3D_Mesh->Faces[Index]->Triangulariza();
           I3D_Mesh->Faces[Index]->CalculaNormal(true);
           I3D_Mesh->Faces[Index]->CalculaBordaFace();
           Index++;
       }
    }
}
