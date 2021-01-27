#include "I3D_Fonte.h"


CI3DFonte::CI3DFonte():
    CI3DPainel()
{
   pTabelaCaracteres = new char[16*16];
   pTabelaCaracteres[0]  = ' ';
   pTabelaCaracteres[1]  = '!';
   pTabelaCaracteres[2]  = '\"';
   pTabelaCaracteres[3]  = '#';
   pTabelaCaracteres[4]  = '$';
   pTabelaCaracteres[5]  = '%';
   pTabelaCaracteres[6]  = '&';
   pTabelaCaracteres[7]  = '\'';
   pTabelaCaracteres[8]  = '(';
   pTabelaCaracteres[9]  = ')';
   pTabelaCaracteres[10] = '*';
   pTabelaCaracteres[11] = '+';
   pTabelaCaracteres[12] = ',';
   pTabelaCaracteres[13] = '-';
   pTabelaCaracteres[14] = '.';
   pTabelaCaracteres[15] = '/';
   pTabelaCaracteres[16] = '0';
   pTabelaCaracteres[17] = '1';
   pTabelaCaracteres[18] = '2';
   pTabelaCaracteres[19] = '3';
   pTabelaCaracteres[20] = '4';
   pTabelaCaracteres[21] = '5';
   pTabelaCaracteres[22] = '6';
   pTabelaCaracteres[23] = '7';
   pTabelaCaracteres[24] = '8';
   pTabelaCaracteres[25] = '9';
   pTabelaCaracteres[26] = ':';
   pTabelaCaracteres[27] = ';';
   pTabelaCaracteres[28] = '<';
   pTabelaCaracteres[29] = '_';
   pTabelaCaracteres[30] = '>';
   pTabelaCaracteres[31] = '?';
   pTabelaCaracteres[32] = '@';
   pTabelaCaracteres[33] = 'A';
   pTabelaCaracteres[34] = 'B';
   pTabelaCaracteres[35] = 'C';
   pTabelaCaracteres[36] = 'D';
   pTabelaCaracteres[37] = 'E';
   pTabelaCaracteres[38] = 'F';
   pTabelaCaracteres[39] = 'G';
   pTabelaCaracteres[40] = 'H';
   pTabelaCaracteres[41] = 'I';
   pTabelaCaracteres[42] = 'J';
   pTabelaCaracteres[43] = 'K';
   pTabelaCaracteres[44] = 'L';
   pTabelaCaracteres[45] = 'M';
   pTabelaCaracteres[46] = 'N';
   pTabelaCaracteres[47] = 'O';
   pTabelaCaracteres[48] = 'P';
   pTabelaCaracteres[49] = 'Q';
   pTabelaCaracteres[50] = 'R';
   pTabelaCaracteres[51] = 'S';
   pTabelaCaracteres[52] = 'T';
   pTabelaCaracteres[53] = 'U';
   pTabelaCaracteres[54] = 'V';
   pTabelaCaracteres[55] = 'W';
   pTabelaCaracteres[56] = 'X';
   pTabelaCaracteres[57] = 'Y';
   pTabelaCaracteres[58] = 'Z';
   pTabelaCaracteres[59] = '[';
   pTabelaCaracteres[60] = '\\';
   pTabelaCaracteres[61] = ']';
   pTabelaCaracteres[62] = '^';
   pTabelaCaracteres[63] = '_';
   pTabelaCaracteres[64] = '\'';
   pTabelaCaracteres[65] = 'a';
   pTabelaCaracteres[66] = 'b';
   pTabelaCaracteres[67] = 'c';
   pTabelaCaracteres[68] = 'd';
   pTabelaCaracteres[69] = 'e';
   pTabelaCaracteres[70] = 'f';
   pTabelaCaracteres[71] = 'g';
   pTabelaCaracteres[72] = 'h';
   pTabelaCaracteres[73] = 'i';
   pTabelaCaracteres[74] = 'j';
   pTabelaCaracteres[75] = 'k';
   pTabelaCaracteres[76] = 'l';
   pTabelaCaracteres[77] = 'm';
   pTabelaCaracteres[78] = 'n';
   pTabelaCaracteres[79] = 'o';
   pTabelaCaracteres[80] = 'p';
   pTabelaCaracteres[81] = 'q';
   pTabelaCaracteres[82] = 'r';
   pTabelaCaracteres[83] = 's';
   pTabelaCaracteres[84] = 't';
   pTabelaCaracteres[85] = 'u';
   pTabelaCaracteres[86] = 'v';
   pTabelaCaracteres[87] = 'w';
   pTabelaCaracteres[88] = 'x';
   pTabelaCaracteres[89] = 'y';
   pTabelaCaracteres[90] = 'z';
   pTabelaCaracteres[91] = '{';
   pTabelaCaracteres[92] = '|';
   pTabelaCaracteres[93] = '}';
   pTabelaCaracteres[94] = ' ';
   pTabelaCaracteres[95] = ' ';
   pTabelaCaracteres[96] = ' ';
   pTabelaCaracteres[97] = 'u';
   pTabelaCaracteres[98] = 'e';
   pTabelaCaracteres[99] = 'a';
   pTabelaCaracteres[100] = 'a';
   pTabelaCaracteres[101] = 'a';
   pTabelaCaracteres[102] = 'a';
   pTabelaCaracteres[103] = ' ';
   pTabelaCaracteres[104] = 'e';
   pTabelaCaracteres[105] = 'e';
   pTabelaCaracteres[106] = 'e';
   pTabelaCaracteres[107] = '|';
   pTabelaCaracteres[108] = '|';
   pTabelaCaracteres[109] = '|';
   pTabelaCaracteres[110] = 'A';
   pTabelaCaracteres[111] = 'A';
   pTabelaCaracteres[112] = 'E';
   pTabelaCaracteres[113] = 'A';
   pTabelaCaracteres[114] = 'A';
   pTabelaCaracteres[115] = 'o';
   pTabelaCaracteres[116] = 'o';
   pTabelaCaracteres[117] = 'o';
   pTabelaCaracteres[118] = 'u';
   pTabelaCaracteres[119] = 'u';
   pTabelaCaracteres[120] = 'y';
   pTabelaCaracteres[121] = 'O';
   pTabelaCaracteres[122] = 'U';
   pTabelaCaracteres[123] = '0';
   pTabelaCaracteres[124] = '$';
   pTabelaCaracteres[125] = '0';
   pTabelaCaracteres[126] = 'x';
   pTabelaCaracteres[127] = 'f';

   //Caracteres em Bold
   pTabelaCaracteres[128]  = ' ';
   pTabelaCaracteres[129]  = '!';
   pTabelaCaracteres[130]  = '\"';
   pTabelaCaracteres[131]  = '#';
   pTabelaCaracteres[132]  = '$';
   pTabelaCaracteres[133]  = '%';
   pTabelaCaracteres[134]  = '&';
   pTabelaCaracteres[135]  = '\'';
   pTabelaCaracteres[136]  = '(';
   pTabelaCaracteres[137]  = ')';
   pTabelaCaracteres[138]  = '*';
   pTabelaCaracteres[139]  = '+';
   pTabelaCaracteres[140]  = ',';
   pTabelaCaracteres[141]  = '-';
   pTabelaCaracteres[142]  = '.';
   pTabelaCaracteres[143]  = '/';
   pTabelaCaracteres[144]  = '0';
   pTabelaCaracteres[145]  = '1';
   pTabelaCaracteres[146]  = '2';
   pTabelaCaracteres[147]  = '3';
   pTabelaCaracteres[148]  = '4';
   pTabelaCaracteres[149]  = '5';
   pTabelaCaracteres[150]  = '6';
   pTabelaCaracteres[151]  = '7';
   pTabelaCaracteres[152]  = '8';
   pTabelaCaracteres[153]  = '9';
   pTabelaCaracteres[154]  = ':';
   pTabelaCaracteres[155]  = ';';
   pTabelaCaracteres[156]  = '<';
   pTabelaCaracteres[157]  = '_';
   pTabelaCaracteres[158]  = '>';
   pTabelaCaracteres[159]  = '?';
   pTabelaCaracteres[160]  = '@';
   pTabelaCaracteres[161]  = 'A';
   pTabelaCaracteres[162]  = 'B';
   pTabelaCaracteres[163]  = 'C';
   pTabelaCaracteres[164]  = 'D';
   pTabelaCaracteres[165]  = 'E';
   pTabelaCaracteres[166]  = 'F';
   pTabelaCaracteres[167]  = 'G';
   pTabelaCaracteres[168]  = 'H';
   pTabelaCaracteres[169]  = 'I';
   pTabelaCaracteres[170]  = 'J';
   pTabelaCaracteres[171]  = 'K';
   pTabelaCaracteres[172]  = 'L';
   pTabelaCaracteres[173]  = 'M';
   pTabelaCaracteres[174]  = 'N';
   pTabelaCaracteres[175]  = 'O';
   pTabelaCaracteres[176]  = 'P';
   pTabelaCaracteres[177]  = 'Q';
   pTabelaCaracteres[178]  = 'R';
   pTabelaCaracteres[179]  = 'S';
   pTabelaCaracteres[180]  = 'T';
   pTabelaCaracteres[181]  = 'U';
   pTabelaCaracteres[182]  = 'V';
   pTabelaCaracteres[183]  = 'W';
   pTabelaCaracteres[184]  = 'X';
   pTabelaCaracteres[185]  = 'Y';
   pTabelaCaracteres[186]  = 'Z';
   pTabelaCaracteres[187]  = '[';
   pTabelaCaracteres[188]  = '\\';
   pTabelaCaracteres[189]  = ']';
   pTabelaCaracteres[190]  = '^';
   pTabelaCaracteres[191]  = '_';
   pTabelaCaracteres[192]  = '\'';
   pTabelaCaracteres[193]  = 'a';
   pTabelaCaracteres[194]  = 'b';
   pTabelaCaracteres[195]  = 'c';
   pTabelaCaracteres[196]  = 'd';
   pTabelaCaracteres[197]  = 'e';
   pTabelaCaracteres[198]  = 'f';
   pTabelaCaracteres[199]  = 'g';
   pTabelaCaracteres[200]  = 'h';
   pTabelaCaracteres[201]  = 'i';
   pTabelaCaracteres[202]  = 'j';
   pTabelaCaracteres[203]  = 'k';
   pTabelaCaracteres[204]  = 'l';
   pTabelaCaracteres[205]  = 'm';
   pTabelaCaracteres[206]  = 'n';
   pTabelaCaracteres[207]  = 'o';
   pTabelaCaracteres[208]  = 'p';
   pTabelaCaracteres[209]  = 'q';
   pTabelaCaracteres[210]  = 'r';
   pTabelaCaracteres[211]  = 's';
   pTabelaCaracteres[212]  = 't';
   pTabelaCaracteres[213]  = 'u';
   pTabelaCaracteres[214]  = 'v';
   pTabelaCaracteres[215]  = 'w';
   pTabelaCaracteres[216]  = 'x';
   pTabelaCaracteres[217]  = 'y';
   pTabelaCaracteres[218]  = 'z';
   pTabelaCaracteres[219]  = '{';
   pTabelaCaracteres[220]  = '|';
   pTabelaCaracteres[221]  = '}';
   pTabelaCaracteres[222]  = ' ';
   pTabelaCaracteres[223]  = ' ';
   pTabelaCaracteres[224]  = ' ';
   pTabelaCaracteres[225]  = 'u';
   pTabelaCaracteres[226]  = 'e';
   pTabelaCaracteres[227]  = 'a';
   pTabelaCaracteres[228]  = 'a';
   pTabelaCaracteres[229]  = 'a';
   pTabelaCaracteres[230]  = 'a';
   pTabelaCaracteres[231]  = ' ';
   pTabelaCaracteres[232]  = 'e';
   pTabelaCaracteres[233]  = 'e';
   pTabelaCaracteres[234]  = 'e';
   pTabelaCaracteres[235]  = '|';
   pTabelaCaracteres[236]  = '|';
   pTabelaCaracteres[237]  = '|';
   pTabelaCaracteres[238]  = 'A';
   pTabelaCaracteres[239]  = 'A';
   pTabelaCaracteres[240]  = 'E';
   pTabelaCaracteres[241]  = 'A';
   pTabelaCaracteres[242]  = 'A';
   pTabelaCaracteres[243]  = 'o';
   pTabelaCaracteres[244]  = 'o';
   pTabelaCaracteres[245]  = 'o';
   pTabelaCaracteres[246]  = 'u';
   pTabelaCaracteres[247]  = 'u';
   pTabelaCaracteres[248]  = 'y';
   pTabelaCaracteres[249]  = 'O';
   pTabelaCaracteres[250]  = 'U';
   pTabelaCaracteres[251]  = '0';
   pTabelaCaracteres[252]  = '$';
   pTabelaCaracteres[253]  = '0';
   pTabelaCaracteres[254]  = 'x';
   pTabelaCaracteres[255]  = 'f';

}

bool CI3DFonte::AddFont(QString pI3D_ImgFonte, QString pI3D_NomeFonte)
{
    if(bPainelInicializado)
    {
        qWarning() << "Tentativa de inicialização de painel já construido.";
        return false;
    }

    /**************************************************************/
    /*Cria o Material e atribui a textura de Fonte                */
    /**************************************************************/
    I3D_Mesh->I3D_Material = pINSMAMaterialManager->AddMaterial(pI3D_NomeFonte,IGL_MATERIAL_TEXTURE);

    pINSMAMaterialManager->AddTextura     (I3D_Mesh->I3D_Material,pI3D_ImgFonte,IGL_TEXTURE_GEN_ST);
    pINSMAMaterialManager->SetaRejeicaoCor(I3D_Mesh->I3D_Material,true,CIMACor(0.0f,0.0f,0.0f,1.0f));

    I3D_Altura      = 256;
    I3D_Largura     = 256;
    Build();
    bPainelInicializado = true;
    return true;
}

void CI3DFonte::Build()
{
    int   TamanhoQuad    = 16;
    int   NumeroFaces    = ((I3D_Altura)/TamanhoQuad) * ((I3D_Largura)/TamanhoQuad);
    int   Index          = 0;

    float x,y,z;

    CI3DVertice vertice1,
                vertice2,
                vertice3,
                vertice4;


    I3D_Mesh->AdicionaFaces(NumeroFaces);
    /****************************************/
    /*Adiciona o Total de Vertices do Painel*/
    /****************************************/
    for ( int Y = 0; Y < (I3D_Largura); Y +=TamanhoQuad )
    {
       for ( int X = 0;  X < (I3D_Altura); X +=TamanhoQuad )
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
           z = Y + TamanhoQuad ;

           vertice2                   = CI3DVertice(x, y, z);
           vertice2.I3D_CoordTexturaU = 1.0f;
           vertice2.I3D_CoordTexturaV = 0.0f;
           vertice2.I3D_CoordDetTextU = 1.0f;
           vertice2.I3D_CoordDetTextV = 0.0f;
           vertice2.I3D_CoordLtmTextU = 1.0f;
           vertice2.I3D_CoordLtmTextV = 0.0f;

           // Acima e Direita
           x = X + TamanhoQuad;
           y = 0;
           z = Y + TamanhoQuad ;

           vertice3                   = CI3DVertice(x, y, z);
           vertice3.I3D_CoordTexturaU = 1.0f;
           vertice3.I3D_CoordTexturaV = 1.0f;
           vertice3.I3D_CoordDetTextU = 1.0f;
           vertice3.I3D_CoordDetTextV = 1.0f;
           vertice3.I3D_CoordLtmTextU = 1.0f;
           vertice3.I3D_CoordLtmTextV = 1.0f;

           // Embaixo e Direita
           x = X + TamanhoQuad;
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

    I3D_Mesh->SetaShader         (I3D_Shader                          );
    I3D_Mesh->CalculaBorda       (                                    );
    I3D_Mesh->CalculaNrml        (I3D_Mesh->I3D_BordaMesh.PegaCentro());
    BuildTextureCoordSH          (                                    );

    if(iTpPainel == IGL_PAINEL_DEFAULT)
    {
       I3D_Mesh->ConstroiBuffersSH  (                          );
    }

    I3D_Pos = I3D_Mesh->I3D_BordaMesh.PegaCentro();
}

void CI3DFonte::BuildTextureCoord()
{

}

int CI3DFonte::PegaIndiceChar(char pChar)
{
    for(int i=0;i<256;i++)
    {
        if(pChar == pTabelaCaracteres[i])
        {
            return i;
        }
    }
    return 0;
}
