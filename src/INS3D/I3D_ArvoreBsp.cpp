/*********************************************************************************/
/*Projeto             :Insane RT Framework
/*Descricao           :
/*Data de Criação     :
/*
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados
/**********************************************************************************/
#include "I3D_ArvoreBsp.h"

CI3DArvoreBsp::CI3DArvoreBsp()
{
    I3D_ListaFaces          = NULL;
    I3D_NumFacesAtivas      = 0;
    I3D_TpArvore            = BSP_TYPE_NONSPLIT/*BSP_TYPE_SPLIT*/;
    I3D_HeuristicaDivisao   = 3.0f;
    I3D_AcumuladorDivisores = 60;
    I3D_RemoveFolhasIlegais = true;
    I3D_AddPoligonosBorda   = false;
}

CI3DArvoreBsp::~CI3DArvoreBsp()
{
    LimpaArvore();
}

void CI3DArvoreBsp::LimpaArvore()
{
    unsigned long i;

    for ( i = 0; i < PegaQtdFaces()  ; i++ ) if ( PegaFace  (i) ) delete PegaFace  (i);
    for ( i = 0; i < PegaQtdNos()    ; i++ ) if ( PegaNo    (i) ) delete PegaNo    (i);
    for ( i = 0; i < PegaQtdFolhas() ; i++ ) if ( PegaFolha (i) ) delete PegaFolha (i);
    for ( i = 0; i < PegaQtdPlanos() ; i++ ) if ( PegaPlano (i) ) delete PegaPlano (i);

    for ( i = 0; i < I3D_VetorLixo.size(); i++ )
    {
        if ( I3D_VetorLixo[i] ) delete I3D_VetorLixo[i];
    }

    for ( i = 0; i < I3D_VetorFacesRemovidas.size(); i++ )
    {
        if ( I3D_VetorFacesRemovidas[i] ) delete I3D_VetorFacesRemovidas[i];
    }

    I3D_VetorNos    .clear();
    I3D_VetorPlanos .clear();
    I3D_VetorFolhas .clear();
    I3D_VetorFaces  .clear();
    I3D_VetorLixo   .clear();

    I3D_ListaFaces     = NULL;
    I3D_NumFacesAtivas = 0;
}

//-----------------------------------------------------------------------------
// Name : LimpaArvore ()
// Desc : Releases all memory allocated by the BSP Tree
//-----------------------------------------------------------------------------
void CI3DArvoreBsp::Inverte()
{
    int			Counter	= 1;
    long        QtdFaces;
    CI3DVertice *TVerts = NULL;

    QtdFaces=PegaQtdFaces();

    for ( int i = 0; i < QtdFaces; i++ )
    {
        if (PegaFace(i)->Deleted) continue;
        // Cria vetor de vertices temporario
        TVerts = new CI3DVertice[PegaFace(i)->I3D_QtdVertices];
        // copia vertice 0 no vetor
        TVerts[0] = PegaFace(i)->Vertices[0];
        Counter = 1;
        // copia os vertices em ordem reversa no vetor
        for ( int k = PegaFace(i)->I3D_QtdVertices; k > 1; k--, Counter++ )
        {
            TVerts[Counter] = PegaFace(i)->Vertices[k - 1];
        }
        // Copia os vertices novamente no vetor de vertices.
        for ( int l = 0;l<PegaFace(i)->I3D_QtdVertices;l++)
        {
            PegaFace(i)->Vertices[l]=TVerts[l];
        }
        memcpy( PegaFace(i)->Vertices[0], &TVerts[0], PegaFace(i)->I3D_QtdVertices * sizeof(CI3DVertice));
        delete []TVerts;

        // Inverte as normais
        PegaFace(i)->I3D_NormalFace = -PegaFace(i)->I3D_NormalFace;

        // Copia a normal para as normais de vertices.
        for ( int k = 0; k < PegaFace(i)->I3D_QtdVertices; k++ )
        {
            PegaFace(i)->Vertices[k].I3D_PlanarNormal = PegaFace(i)->I3D_NormalFace;
        }

        //triangulariza o poligono
        PegaFace(i)->Triangulariza();

    }
}

void CI3DArvoreBsp::CompilaArvore( )
{
    // Calcula o vetor de Planos
    ConstroiVetorPlanos();
    // Aloca o No Raiz
    IncrementaNos();
    // Compila a Arvore BSP
    Constroi(0, I3D_ListaFaces);
    // Calcula a Borda Geral
    CalculaBorda();
}

bool CI3DArvoreBsp::AdicionaFaces(CI3DFace ** ppFaces, unsigned long pQtdFaces, bool pSalvaOrigem)
{
    CI3DFaceBsp *NovaFace = NULL;

    // Limpa conteudo previo
    if (!I3D_ListaFaces) LimpaArvore();

    // Não podemos salvar os originais em uma arvore tipo Divisao
    if ( I3D_TpArvore == BSP_TYPE_SPLIT )
    {
        pSalvaOrigem = false;
    }

    for ( unsigned long i = 0; i < pQtdFaces; i++ )
    {
        if (ppFaces[i])
        {
            NovaFace = AlocaFaceBsp( ppFaces[i] ) ;

            NovaFace->IndiceOriginal = I3D_NumFacesAtivas;
            I3D_NumFacesAtivas++;

            NovaFace->Proximo = I3D_ListaFaces;

            I3D_ListaFaces    = NovaFace;

            if (pSalvaOrigem)
            {
                if (!IncrementaFaces())
                {
                    LimpaArvore();
                    return false;
                }

                NovaFace = AlocaFaceBsp( ppFaces[i] );
                SetaFace( PegaQtdFaces() - 1, NovaFace );
            }
        }
    }

    return true;
}

bool CI3DArvoreBsp::AdicionaBordasPoligonos(bool pSalvaOrigem)
{
    CI3DFaceBsp *pIterator;
    CIMTBorda    Borda;
    unsigned long     i, j;

    if ( I3D_TpArvore == BSP_TYPE_SPLIT ) pSalvaOrigem = false;

    Borda.Limpa();
    for ( pIterator = I3D_ListaFaces; pIterator; pIterator = pIterator->Proximo )
    {
        Borda.CalculaBordaMesh( pIterator->Vertices       ,
                                pIterator->I3D_QtdVertices,
                                sizeof(CI3DVertice)       ,
                                false                     );
    }


    Borda.IMT_MaxVetorBorda += CIMTVetor( 10.0f, 10.0f, 10.0f );
    Borda.IMT_MinVetorBorda -= CIMTVetor( 10.0f, 10.0f, 10.0f );

    CIMTVetor Size   = Borda.PegaDimensao() / 2.0f;
    CIMTVetor Centre = Borda.PegaCentro();

    for ( i = 0; i < 6; i++ )
    {
        CI3DFaceBsp * pFace = AlocaFaceBsp();

        pFace->AdicionaVertices( 4 , IGL_RENDER_TRIANGLES );

        pFace->IndiceOriginal = I3D_NumFacesAtivas;
        I3D_NumFacesAtivas++;

        switch ( i )
        {
            case 0:
            {
                // Topo

                CIMTVetor Vertice01,
                          Vertice02,
                          Vertice03,
                          Vertice04;

                Vertice01 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                          Size.y,
                                                         -Size.z));
                Vertice02 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                          Size.y,
                                                         -Size.z));
                Vertice03 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                          Size.y,
                                                          Size.z));
                Vertice04 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                          Size.y,
                                                          Size.z));
                pFace->Vertices[0].x=Vertice01.x;
                pFace->Vertices[0].y=Vertice01.y;
                pFace->Vertices[0].z=Vertice01.z;

                pFace->Vertices[1].x=Vertice02.x;
                pFace->Vertices[1].y=Vertice02.y;
                pFace->Vertices[1].z=Vertice02.z;

                pFace->Vertices[2].x=Vertice03.x;
                pFace->Vertices[2].y=Vertice03.y;
                pFace->Vertices[2].z=Vertice03.z;

                pFace->Vertices[3].x=Vertice04.x;
                pFace->Vertices[3].y=Vertice04.y;
                pFace->Vertices[3].z=Vertice04.z;

                pFace->I3D_NormalFace=CIMTVetor( 0.0f, -1.0f, 0.0f );

                pFace->Triangulariza();

            }break;

            case 1:
            {
                // Embaixo

                CIMTVetor Vertice01,
                          Vertice02,
                          Vertice03,
                          Vertice04;

                Vertice01 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         -Size.y,
                                                          Size.z));
                Vertice02 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                         -Size.y,
                                                          Size.z));
                Vertice03 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                         -Size.y,
                                                         -Size.z));
                Vertice04 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         -Size.y,
                                                         -Size.z));
                pFace->Vertices[0].x=Vertice01.x;
                pFace->Vertices[0].y=Vertice01.y;
                pFace->Vertices[0].z=Vertice01.z;
                pFace->Vertices[1].x=Vertice02.x;
                pFace->Vertices[1].y=Vertice02.y;
                pFace->Vertices[1].z=Vertice02.z;
                pFace->Vertices[2].x=Vertice03.x;
                pFace->Vertices[2].y=Vertice03.y;
                pFace->Vertices[2].z=Vertice03.z;
                pFace->Vertices[3].x=Vertice04.x;
                pFace->Vertices[3].y=Vertice04.y;
                pFace->Vertices[3].z=Vertice04.z;

                pFace->I3D_NormalFace=CIMTVetor( 0.0f, 1.0f, 0.0f );

                pFace->Triangulariza();

            }break;

            case 2:
            {
                // Esquerda
                CIMTVetor Vertice01,
                          Vertice02,
                          Vertice03,
                          Vertice04;

                Vertice01 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         Size.y,
                                                        -Size.z));
                Vertice02 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         Size.y,
                                                         Size.z));
                Vertice03 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         -Size.y,
                                                          Size.z));
                Vertice04 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         -Size.y,
                                                         -Size.z));
                pFace->Vertices[0].x=Vertice01.x;
                pFace->Vertices[0].y=Vertice01.y;
                pFace->Vertices[0].z=Vertice01.z;
                pFace->Vertices[1].x=Vertice02.x;
                pFace->Vertices[1].y=Vertice02.y;
                pFace->Vertices[1].z=Vertice02.z;
                pFace->Vertices[2].x=Vertice03.x;
                pFace->Vertices[2].y=Vertice03.y;
                pFace->Vertices[2].z=Vertice03.z;
                pFace->Vertices[3].x=Vertice04.x;
                pFace->Vertices[3].y=Vertice04.y;
                pFace->Vertices[3].z=Vertice04.z;

                pFace->I3D_NormalFace=CIMTVetor( 1.0f, 0.0f, 0.0f );

                pFace->Triangulariza();

            }break;

            case 3:
            {
                // Direita

            CIMTVetor Vertice01,
                      Vertice02,
                      Vertice03,
                      Vertice04;

            Vertice01 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                      Size.y,
                                                      Size.z));
            Vertice02 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                      Size.y,
                                                     -Size.z));
            Vertice03 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                      -Size.y,
                                                      -Size.z));
            Vertice04 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                      -Size.y,
                                                       Size.z));
            pFace->Vertices[0].x=Vertice01.x;
            pFace->Vertices[0].y=Vertice01.y;
            pFace->Vertices[0].z=Vertice01.z;
            pFace->Vertices[1].x=Vertice02.x;
            pFace->Vertices[1].y=Vertice02.y;
            pFace->Vertices[1].z=Vertice02.z;
            pFace->Vertices[2].x=Vertice03.x;
            pFace->Vertices[2].y=Vertice03.y;
            pFace->Vertices[2].z=Vertice03.z;
            pFace->Vertices[3].x=Vertice04.x;
            pFace->Vertices[3].y=Vertice04.y;
            pFace->Vertices[3].z=Vertice04.z;

                pFace->I3D_NormalFace=CIMTVetor( -1.0f, 0.0f, 0.0f );

                pFace->Triangulariza();

            }break;

            case 4:
            {
                // Frente

                CIMTVetor Vertice01,
                          Vertice02,
                          Vertice03,
                          Vertice04;

                Vertice01 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                          Size.y,
                                                         -Size.z));
                Vertice02 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         Size.y,
                                                        -Size.z));
                Vertice03 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         -Size.y,
                                                         -Size.z));
                Vertice04 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                         -Size.y,
                                                         -Size.z));
                pFace->Vertices[0].x=Vertice01.x;
                pFace->Vertices[0].y=Vertice01.y;
                pFace->Vertices[0].z=Vertice01.z;
                pFace->Vertices[1].x=Vertice02.x;
                pFace->Vertices[1].y=Vertice02.y;
                pFace->Vertices[1].z=Vertice02.z;
                pFace->Vertices[2].x=Vertice03.x;
                pFace->Vertices[2].y=Vertice03.y;
                pFace->Vertices[2].z=Vertice03.z;
                pFace->Vertices[3].x=Vertice04.x;
                pFace->Vertices[3].y=Vertice04.y;
                pFace->Vertices[3].z=Vertice04.z;

                pFace->I3D_NormalFace=CIMTVetor( 0.0f, 0.0f, 1.0f );

                pFace->Triangulariza();

            }break;

            case 5:
            {
                // Atras

            CIMTVetor Vertice01,
                      Vertice02,
                      Vertice03,
                      Vertice04;

                Vertice01 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                          Size.y,
                                                          Size.z));
                Vertice02 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                          Size.y,
                                                          Size.z));
                Vertice03 = CIMTVetor(Centre + CIMTVetor( Size.x,
                                                         -Size.y,
                                                          Size.z));
                Vertice04 = CIMTVetor(Centre + CIMTVetor(-Size.x,
                                                         -Size.y,
                                                          Size.z));
                pFace->Vertices[0].x=Vertice01.x;
                pFace->Vertices[0].y=Vertice01.y;
                pFace->Vertices[0].z=Vertice01.z;
                pFace->Vertices[1].x=Vertice02.x;
                pFace->Vertices[1].y=Vertice02.y;
                pFace->Vertices[1].z=Vertice02.z;
                pFace->Vertices[2].x=Vertice03.x;
                pFace->Vertices[2].y=Vertice03.y;
                pFace->Vertices[2].z=Vertice03.z;
                pFace->Vertices[3].x=Vertice04.x;
                pFace->Vertices[3].y=Vertice04.y;
                pFace->Vertices[3].z=Vertice04.z;

                pFace->I3D_NormalFace=CIMTVetor( 0.0f, 0.0f, -1.0f );

                pFace->Triangulariza();

            }break;

        }

        for ( j = 0; j < 4; j++ ) pFace->Vertices[j].I3D_PlanarNormal=pFace->I3D_NormalFace;

        pFace->Proximo = I3D_ListaFaces;
        I3D_ListaFaces = pFace;

        if (pSalvaOrigem)
        {
            CI3DFaceBsp * NewFace = NULL;

            if (!IncrementaFaces())
            {
                LimpaArvore();
                return false;
            }

            if (!(NewFace = AlocaFaceBsp( pFace )))
            {
                LimpaArvore();
                return false;
            }

            SetaFace( PegaQtdFaces() - 1, NewFace );

        }

    }

    return true;
}

void CI3DArvoreBsp::ConstroiVetorPlanos()
{
    CI3DFaceBsp * Iterator = NULL;
    CIMTPlano     Plano,* PlanoTeste;
    CIMTVetor     Normal, PtoCentral;
    int           i, ContPlano;
    float         Distancia;


    // Para Cada Face
    for ( Iterator = I3D_ListaFaces; Iterator; Iterator = Iterator->Proximo )
    {
        // Calcula o Ponto Central
        PtoCentral = Iterator->Vertices[0];
        for ( i = 1; i < Iterator->I3D_QtdVertices; i++ )
        {
            PtoCentral += Iterator->Vertices[i];
        }

        PtoCentral /= Iterator->I3D_QtdVertices;

        // Calcula o Plano do Poligono
        Plano = CIMTPlano( Iterator->I3D_NormalFace, PtoCentral );

        // Procura na Lista de Planos para ver se ja existe
        ContPlano = PegaQtdPlanos();
        for ( i = 0; i < ContPlano; i++ )
        {
            // Recupera os dados do Plano
            PlanoTeste = PegaPlano(i);

            // Compara com o da Lista
            if ( fabsf(PlanoTeste->IMT_DistanciaPlano  - Plano.IMT_DistanciaPlano) < 1e-5f &&
                 Plano.IMT_NormalPlano.Compara(PlanoTeste->IMT_NormalPlano, 1e-5f )) break;

        } // Proximo Plano

        // Adiciona o Plano se Não encontrou ninguem
        if ( i == ContPlano )
        {
             IncrementaPlanos();
            *PegaPlano( ContPlano ) = Plano;
        }

        // Armazena o indice do plano
        Iterator->Plano = i;

        // Recupera os dados do Plano
        Normal    = PegaPlano(i)->IMT_NormalPlano;
        Distancia = PegaPlano(i)->IMT_DistanciaPlano;

        // Certifica que todos os vertices estao no mesmo plano
        for ( int v = 0; v < Iterator->I3D_QtdVertices; v++ )
        {
            float Resultado = Iterator->Vertices[v].ProdutoEscalar(Normal) - Distancia;
            Iterator->Vertices[v]+=(Normal * -Resultado);
        }

    }
}

void CI3DArvoreBsp::Constroi( unsigned long No, CI3DFaceBsp * pListaFaces )
{
    CI3DFaceBsp     *FaceTeste	   = NULL, *ProximaFace	= NULL;
    CI3DFaceBsp     *ListaFrente   = NULL, *ListaAtras	= NULL;
    CI3DFaceBsp     *DivisorFrente = NULL, *DivisorAtras= NULL;
    CI3DFaceBsp     *Divisor       = NULL;
    CLASSIFICACAO    Resultado;

    int v;

    // Seleciona o Melhor Divisor da Lista
    Divisor = CriterioSelecao( pListaFaces,I3D_HeuristicaDivisao,I3D_AcumuladorDivisores);
    if (!Divisor)
    {
        goto BuildError;
    }

    Divisor->Divisor = true;

    PegaNo(No)->Plano=Divisor->Plano;

    // Para cada passo setamos a face de nivel acima.
    for ( FaceTeste = pListaFaces; FaceTeste != NULL; FaceTeste = ProximaFace, pListaFaces = ProximaFace )
    {
        // Armazena plano para acesso facil
        CIMTPlano * pPlano = PegaPlano( FaceTeste->Plano );

        // Armazena a proxima face(pode ser eliminada durante o processo)
        ProximaFace = FaceTeste->Proximo;

        // Classifica o Poligono
        if ( FaceTeste->Plano == Divisor->Plano )
        {
            Resultado = COPLANAR;

        }
        else
        {
            Resultado = PegaPlano(Divisor->Plano)->ClassificaPoligono( FaceTeste->Vertices, FaceTeste->I3D_QtdVertices,sizeof(CI3DVertice));
        }

        // Processa o Resultado
        switch ( Resultado )
        {
            case COPLANAR:

                // Testa a Direcao da face contra o Plano.
                if ( PegaPlano(Divisor->Plano)->MesmoLado( pPlano->IMT_NormalPlano))
                {
                    #if ( BSP_SHARENODES )

                        // Marca planos coincidentes como usados(Acuracidade pode ser reduzida)
                        if (!FaceTeste->Divisor)
                        {
                            FaceTeste->Divisor = true;

                        }

                    #endif // BSP_SHARENODES

                    FaceTeste->Proximo	= ListaFrente;
                    ListaFrente		    = FaceTeste;
                }
                else
                {
                    FaceTeste->Proximo	= ListaAtras;
                    ListaAtras	    	= FaceTeste;
                }
                break;

                case FRENTE:
                // Passa a Face para a lista da Frente.
                FaceTeste->Proximo		= ListaFrente;
                ListaFrente			    = FaceTeste;
                break;

                case ATRAS:
                // Passa a Face para a lista Atras.
                FaceTeste->Proximo		= ListaAtras;
                ListaAtras			= FaceTeste;
                break;

            case CRUZANDO:
                // Para certificar que é uma acao valida
                if ( FaceTeste == Divisor )
                {
                    goto BuildError;
                }

                DivisorFrente           = AlocaFaceBsp();
                DivisorFrente->Proximo	= ListaFrente;
                ListaFrente			    = DivisorFrente;

                DivisorAtras            = AlocaFaceBsp();
                DivisorAtras->Proximo   = ListaAtras;
                ListaAtras			    = DivisorAtras;

                FaceTeste->Divide(*PegaPlano(Divisor->Plano),DivisorFrente,DivisorAtras);

                // Certifica que todos os vertices estao no mesmo plano original
                for ( v = 0; v < DivisorFrente->I3D_QtdVertices; v++ )
                {
                    float Resultado1 = DivisorFrente->Vertices[v].ProdutoEscalar(pPlano->IMT_NormalPlano) - pPlano->IMT_DistanciaPlano;
                    DivisorFrente->Vertices[v] += (pPlano->IMT_NormalPlano * -Resultado1);
                }

                // Certifica que todos os vertices estao no mesmo plano original
                for ( v = 0; v < DivisorAtras->I3D_QtdVertices; v++ )
                {
                    float Resultado2 = DivisorAtras->Vertices[v].ProdutoEscalar(pPlano->IMT_NormalPlano) - pPlano->IMT_DistanciaPlano;
                    DivisorAtras->Vertices[v] += (pPlano->IMT_NormalPlano * -Resultado2);
                }

                #if ( BSP_NEWSPLITNODES )
                    // Permite Faces divididas gerarem seu proprio No(Acuracidade pode ser aumentada)
                    DivisorFrente->Divisor = false;
                    DivisorAtras->Divisor  = false;
                #endif
                // + 2 Fragmentos - 1 Original
                I3D_NumFacesAtivas++;

                delete FaceTeste;
                break;
        }
    }

    if ( I3D_RemoveFolhasIlegais )
    {
       if ( ListaAtras && ContaDivisores( ListaAtras ) == 0 )
       {
           // Move Faces Ilegais para uma Lista temporaria Para exibicão caso desejado.
           for ( FaceTeste = ListaAtras; FaceTeste; FaceTeste = FaceTeste->Proximo )
           {
               I3D_VetorFacesRemovidas.push_back( FaceTeste );
               I3D_NumFacesAtivas--;
           }
           ListaAtras = NULL;
       }
    }

    // Calcula BBox do No
    PegaNo(No)->CalculaBordaNo(ListaFrente, true   );
    PegaNo(No)->CalculaBordaNo(ListaAtras , false  );

    // Se a Lista Frente esta vazia esta e uma folha vazia caso contrario
    // incluimos a Lista frente neste no e preenchemos a folha
    if ( ContaDivisores( ListaFrente ) == 0 )
    {
        // Adiciona uma nova folha e armazena as faces resultantes
        IncrementaFolhas();
        PegaNo(No)->I3D_Frente = -PegaQtdFolhas(); // Igual a -(Indice Folha + 1)

        ProcessaFacesFolha(PegaFolha(PegaQtdFolhas() - 1),ListaFrente);
    }
    else
    {
        // Aloca Novo No e segue em frente.
        IncrementaNos();
        PegaNo(No)->I3D_Frente = PegaQtdNos() - 1;
        Constroi( PegaNo(No)->I3D_Frente, ListaFrente );

    }

    // Lista de Frente Ja foi processada e não a possuimos mais
    ListaFrente = NULL;

    // Se a Lista Atras é vazia isto é um Objeto Solido, caso contrario
    // Enviamos a Lista Atras seguindo em frente com o No
    if ( !ListaAtras )
    {
        // Seta como uma Folha de Objeto Solido
        PegaNo(No)->I3D_Atras = -1;
    }
    else
    {
        // Aloca Novo No e segue em frente.
        if ( ContaDivisores( ListaAtras ) == 0 )
        {
           // Adiciona uma nova folha e armazena as faces resultantes
           IncrementaFolhas();
           PegaNo(No)->I3D_Atras = -PegaQtdFolhas(); // Equates to -(Leaf Index + 1)
           ProcessaFacesFolha(PegaFolha(PegaQtdFolhas() - 1),ListaAtras);
        }
        else
        {
           IncrementaNos();
           PegaNo(No)->I3D_Atras = PegaQtdNos() - 1;
           Constroi( PegaNo(No)->I3D_Atras, ListaAtras);
        }

    }

    // Lista Atras Ja foi processada e não a possuimos mais
    ListaAtras = NULL;

BuildError:
    // Adiciona Todas as faces processadas na Lixeira...
    Lixeira( pListaFaces );
    Lixeira( ListaFrente );
    Lixeira( ListaAtras  );

}

void CI3DArvoreBsp::ProcessaFacesFolha( CI3DFolhaBsp * pFolha, CI3DFaceBsp * pListaFaces )
{
    // Dependendo do tipo de arvore temos que armazenar as faces resultantes
    if (I3D_TpArvore == BSP_TYPE_NONSPLIT )
    {
        // Adiciona as faces na Folha
        pFolha->ConstroiIndicesFaces( pListaFaces );

        // Libera as Faces enviadas
        LimpaListaFaces( pListaFaces );

    }
    else
    {
        // Para arvore de Divisao precisamos armazenar os ponteiros das faces.
        CI3DFaceBsp * Iterator = pListaFaces;
        while ( Iterator != NULL )
        {
            IncrementaFaces();

            SetaFace( PegaQtdFaces() - 1, Iterator );
            Iterator->IndiceOriginal = PegaQtdFaces() - 1;
            Iterator = Iterator->Proximo;

        }

        // Adiciona as Faces na Folha
        pFolha->ConstroiIndicesFaces( pListaFaces );
    }
}


unsigned long CI3DArvoreBsp::ContaDivisores( CI3DFaceBsp * pListaFaces ) const
{
    unsigned long    ContDivisores = 0;
    CI3DFaceBsp     *Iterator      = pListaFaces;

    // Conta o Numero de Divisores
    while ( Iterator != NULL )
    {
        if ( !Iterator->Divisor ) ContDivisores++;
        Iterator = Iterator->Proximo;

    }

    // Retorna o Numero de Divisores restando...
    return ContDivisores;
}

CI3DFaceBsp * CI3DArvoreBsp::CriterioSelecao( CI3DFaceBsp * pListaFaces,float pHeuristica,unsigned long pAcumuladorDiv)
{
    unsigned long Score, Splits, FacesAtras, FacesFrente;
    unsigned long MelhorScore = 10000000, ContDivisores = 0;
    CI3DFaceBsp *Divisor = pListaFaces, *FaceAtual = NULL, *FaceSelecionada = NULL;

    // Percorre a Lista Linkada de Faces
    while ( Divisor != NULL )
    {
        // Se não é um Divisor
        if ( !Divisor->Divisor )
        {
            // Cria o Plano de Divisão
            CIMTPlano PlanoDivisor( Divisor->I3D_NormalFace, Divisor->Vertices[0]);

            // Testa em relação aos outros poligonos e pega o score.
            FaceAtual    = pListaFaces;
            Score = Splits = FacesAtras = FacesFrente = 0;
            while ( FaceAtual != NULL )
            {
                CLASSIFICACAO Resultado = PlanoDivisor.ClassificaPoligono( FaceAtual->Vertices, FaceAtual->I3D_QtdVertices,sizeof(CI3DVertice));
                switch ( Resultado )
                {
                    case FRENTE:
                        FacesFrente++;
                        break;

                    case ATRAS:
                        FacesAtras++;
                        break;

                    case CRUZANDO:
                        Splits++;
                        break;

                    default:
                        break;

                }
                FaceAtual = FaceAtual->Proximo;
            }

            Score = (unsigned long)abs((long)( FacesFrente - FacesAtras + (Splits * pHeuristica)));

            // Este é o Melhor Score ?
            if ( Score < MelhorScore)
            {
                MelhorScore	    = Score;
                FaceSelecionada = Divisor;
            }

            ContDivisores++;
        }

        Divisor = Divisor->Proximo;

        // Interrompe se chegamos no limite de acumuladores de Divisao.
        if (pAcumuladorDiv != 0 && ContDivisores >= pAcumuladorDiv && FaceSelecionada) break;
    }

    // Isto será NULL Se não restar nenhuma face para ser usada
    return FaceSelecionada;
}

long CI3DArvoreBsp::ProcuraFolha(const CIMTVetor& pPosicao ) const
{
    long  No = 0;
    float distancia;
    long  pPlano;

    for (;;)
    {
        CI3DNoBsp * pNo = PegaNo( No );

        //se isto acontecer é que estamos em "Solid Space"
        //if(pNo->I3D_Frente == -1 && pNo->I3D_Atras==-1)
        //{
        //    No++;
        //    continue;
        //}

        pPlano = pNo->Plano;

        switch ( PegaPlano( pPlano )->ClassificaPonto(pPosicao ,&distancia))
        {
            case COPLANAR:
            case FRENTE:

                // Se é uma Folha
                if ( pNo->I3D_Frente < 0 )
                {
                    return abs( pNo->I3D_Frente + 1 );
                }
                // Se é um No
                else
                {
                    No = pNo->I3D_Frente;
                }
                break;

            case ATRAS:
                // Se é uma Folha
                if ( pNo->I3D_Atras < 0 )
                {
                    return -1;
                }
                // Se é um No
                else
                {
                    No = pNo->I3D_Atras;
                }
                break;
        }
    }
    // Nunca deve acontecer....Ooops..Ei! ;)
    return -1;
}

//-----------------------------------------------------------------------------
// Nome : SetaPVS ()
// Desc : Aloca e armazena os dados de visão desta Arvore.
//-----------------------------------------------------------------------------
bool CI3DArvoreBsp::SetaPVS( UCHAR m_PVSData[], unsigned long PVSSize, bool pPVSCompressed )
{
    //Libera alocação previa
    if (I3D_PVSData) delete[] I3D_PVSData;

    try
    {
        //Aloca novo dado de visão
        I3D_PVSData = new UCHAR[ PVSSize ];
        if (!I3D_PVSData) throw std::bad_alloc();

        //Copia os dados de visão fornecidos
        memcpy( I3D_PVSData, m_PVSData , PVSSize );
    }

    catch ( std::bad_alloc )
    {
        return false;
    }

    //Repassa dados de tamanho e compressão do PVS
    I3D_PVSDataSize   = PVSSize;
    I3D_PVSCompressed = pPVSCompressed;

    //Sucesso!
    return true;
}

void CI3DArvoreBsp::LimpaListaFaces( CI3DFaceBsp * pListaFaces )
{
    CI3DFaceBsp * FaceTeste = pListaFaces, *ProximaFace = NULL;
    while ( FaceTeste != NULL )
    {
        ProximaFace = FaceTeste->Proximo;
        delete FaceTeste;
        I3D_NumFacesAtivas--;
        FaceTeste = ProximaFace;
    }
}

void CI3DArvoreBsp::Lixeira( CI3DFaceBsp * pListaFaces )
{
    CI3DFaceBsp * Iterator = pListaFaces;

    while ( Iterator != NULL )
    {
        if (std::find(I3D_VetorLixo.begin(), I3D_VetorLixo.end(), Iterator) == I3D_VetorLixo.end())
        {
            try
            {
                if (I3D_VetorLixo.size() >= (I3D_VetorLixo.capacity() - 1))
                {
                    I3D_VetorLixo.reserve( I3D_VetorLixo.size() + BLOCO_MEMORIA );
                }
                I3D_VetorLixo.push_back(Iterator);
            }
            catch (std::exception&) { return; }
        }
        Iterator = Iterator->Proximo;
    }
}

bool CI3DArvoreBsp::IncrementaNos()
{
    CI3DNoBsp *NovoNo = NULL;
    try
    {
        if (I3D_VetorNos.size() >= (I3D_VetorNos.capacity() - 1))
        {
            I3D_VetorNos.reserve( I3D_VetorNos.size() + BLOCO_MEMORIA );
        }
        if (!(NovoNo = new CI3DNoBsp())) throw std::bad_alloc();
        I3D_VetorNos.push_back(NovoNo);
    }

    catch (std::bad_alloc)
    {
        return false;
    }
    catch (...)
    {
        if (NovoNo) delete NovoNo;
        return false;
    }
    return true;
}

bool CI3DArvoreBsp::IncrementaFolhas()
{
    CI3DFolhaBsp *NovaFolha = NULL;
    try
    {
        if (I3D_VetorFolhas.size() >= (I3D_VetorFolhas.capacity() - 1))
        {
            I3D_VetorFolhas.reserve( I3D_VetorFolhas.size() + BLOCO_MEMORIA );
        }
        if (!(NovaFolha = new CI3DFolhaBsp)) throw std::bad_alloc();
        I3D_VetorFolhas.push_back(NovaFolha);
    }
    catch (std::bad_alloc)
    {
        return false;
    }
    catch (...)
    {
        if (NovaFolha) delete NovaFolha;
        return false;
    }
    return true;
}

bool CI3DArvoreBsp::IncrementaPlanos()
{
    CIMTPlano *NovoPlano = NULL;
    try
    {
        if (I3D_VetorPlanos.size() >= (I3D_VetorPlanos.capacity() - 1))
        {
            I3D_VetorPlanos.reserve( I3D_VetorPlanos.size() + BLOCO_MEMORIA );
        }
        if (!(NovoPlano = new CIMTPlano())) throw std::bad_alloc();
        I3D_VetorPlanos.push_back(NovoPlano);
    }

    catch (std::bad_alloc)
    {
        return false;
    }
    catch (...)
    {
        if (NovoPlano) delete NovoPlano;
        return false;
    }
    return true;
}

bool CI3DArvoreBsp::IncrementaFaces()
{
    try
    {
        if (I3D_VetorFaces.size() >= (I3D_VetorFaces.capacity() - 1))
        {
            I3D_VetorFaces.reserve( I3D_VetorFaces.size() + BLOCO_MEMORIA );

        }
        I3D_VetorFaces.push_back( NULL );
    }

    catch (...)
    {
        return false;
    }
    return true;
}

bool CI3DArvoreBsp::IncrementaPortais()
{
    try
    {
        if (I3D_VetorPortais.size() >= (I3D_VetorPortais.capacity() - 1))
        {
            I3D_VetorPortais.reserve( I3D_VetorPortais.size() + BLOCO_MEMORIA );

        }
        I3D_VetorPortais.push_back( NULL );
    }

    catch (...)
    {
        return false;
    }
    return true;
}

CI3DFaceBsp * CI3DArvoreBsp::AlocaFaceBsp( const CI3DFace * I3D_Replica )
{
    CI3DFaceBsp * NovaFace = NULL;
    try
    {
        if (I3D_Replica != NULL)
        {
            NovaFace = new CI3DFaceBsp( I3D_Replica );
        }
        else
        {
            NovaFace = new CI3DFaceBsp();
        }
        if (!NovaFace) throw std::bad_alloc();
    }
    catch (...) { return NULL; }

    return NovaFace;
}

CI3DPortal * CI3DArvoreBsp::AlocaPortalBsp( )
{
    CI3DPortal * NovoPortal = NULL;
    try
    {
        NovoPortal = new CI3DPortal();
        if (!NovoPortal)
        {
            throw std::bad_alloc();
        }
    }

    catch (...)
    {
        return NULL;
    }

    return NovoPortal;
}

/************************************************************/
/*Nome do Método      : InicializaVetores()
/*
/*Objetivo            : Aloca Espaço inicial para compilacao.
/************************************************************/
void CI3DArvoreBsp::InicializaPVS()
{
    /*******************************************************/
    /*Inicializa PVS                                       */
    /*******************************************************/
    I3D_PVSDataSize	= PegaQtdFolhas() * ((PegaQtdFolhas() + 7) / 8);
    I3D_PVSData		= (BYTE *)malloc (I3D_PVSDataSize);
    memset(I3D_PVSData,255,I3D_PVSDataSize);
}

void CI3DArvoreBsp::CalculaBorda()
{
    I3D_BordaTotal.Limpa();
    for ( unsigned long i = 0; i < PegaQtdFaces(); i++ )
    {
        I3D_BordaTotal.CalculaBordaMesh( PegaFace(i)->Vertices        ,
                                         PegaFace(i)->I3D_QtdVertices ,
                                         sizeof(CI3DVertice)          ,
                                         false                       );
    }
}

bool CI3DArvoreBsp::ClipTree( CI3DArvoreBsp * pTree           ,
                              bool            ClipSolid       ,
                              bool            RemoveCoPlanar  ,
                              unsigned long   CurrentNode     ,
                              CI3DFaceBsp *   pFaceList       )
{
    CI3DFaceBsp     *TestFace	 = NULL, *NextFace	= NULL;
    CI3DFaceBsp     *FrontList	 = NULL, *BackList	= NULL;
    CI3DFaceBsp     *FrontSplit = NULL, *BackSplit	= NULL;
    unsigned long Plane      = 0;

    if (!pTree) return false;

    // Alguem mandou uma arvore invalida?
    if (pTree->PegaQtdFaces() < 1 || PegaQtdFaces() < 1 ) return false;

    //Se é a primeira chamada precisamos construir as listas
    if ( pFaceList == NULL )
    {
        unsigned int i;
        // Constroi a lista linkada de Faces
        for ( i = 0; i < pTree->PegaQtdFaces(); i++ )
        {
            pTree->PegaFace(i)->ChildSplit[0]= -1;
            pTree->PegaFace(i)->ChildSplit[1]= -1;
            if ( i > 0 ) pTree->PegaFace(i - 1)->Proximo = pTree->PegaFace(i);
        }
        // Reseta a ultima face (só para ter certeza...)
        pTree->PegaFace(i - 1)->Proximo = NULL;
        pFaceList = pTree->PegaFace(0);
    }

    // Todos os poligonos estao agora linkados em uma lista com o ultimo item apontando para NULL
    // Agora percorremos esta lista enviando-a para a arvore.
    Plane = PegaNo( CurrentNode )->Plano;

    for ( TestFace = pFaceList; TestFace; TestFace = NextFace )
    {
        // Armazena Proxima Face(pode ser modificada/deletada)
        NextFace = TestFace->Proximo;

        // Pula se foi deletado por outro processo
        if ( TestFace->Deleted ) continue;

        // Classifica o Poligono em relação com o Plano
        switch ( PegaPlano(Plane)->ClassificaPoligono( TestFace->Vertices, TestFace->I3D_QtdVertices,sizeof(CI3DVertice)) )
        {
            case COPLANAR:
                if ( PegaPlano(Plane)->MesmoLado( TestFace->I3D_NormalFace ) )
                {
                    if ( RemoveCoPlanar ) { TestFace->Proximo = BackList;  BackList  = TestFace; }
                    else                  { TestFace->Proximo = FrontList; FrontList = TestFace; }
                }
                else
                {
                    TestFace->Proximo	= BackList;
                    BackList		= TestFace;
                }
                break;

            case FRENTE:
                TestFace->Proximo		= FrontList;
                FrontList			    = TestFace;
                break;

            case ATRAS:
                TestFace->Proximo		= BackList;
                BackList			    = TestFace;
                break;

            case CRUZANDO:
                if (!(FrontSplit = AlocaFaceBsp())) { goto ClipError; }
                if (!pTree->IncrementaFaces())      { goto ClipError; }
                pTree->SetaFace( pTree->PegaQtdFaces() - 1, FrontSplit );

                if (!(BackSplit	= AlocaFaceBsp())) { goto ClipError; }
                if (!pTree->IncrementaFaces())     { goto ClipError; }
                pTree->SetaFace( pTree->PegaQtdFaces() - 1, BackSplit );

                // Divide o Poligono
                TestFace->Divide(*PegaPlano(Plane), FrontSplit, BackSplit);

                //if(!(TestFace->Divide(*PegaPlano(Plane), FrontSplit, BackSplit)))
                //{
                //    goto ClipError;
                //}


                //Como é um pre-processamento em uma "Mini-bsp" nao precisamos armazenar os
                //poligonos resultantes
                TestFace->Deleted    = true;
                TestFace->ChildSplit[0] = pTree->PegaQtdFaces() - 2;
                TestFace->ChildSplit[1] = pTree->PegaQtdFaces() - 1;

                // Adiciona no Head da Recursividade
                FrontSplit->Proximo = FrontList;
                FrontList           = FrontSplit;
                BackSplit->Proximo  = BackList;
                BackList            = BackSplit;
                break;
        }
    }
    // Agora realizamos o Clipping propriamente dito
    if ( ClipSolid )
    {
        //Se é um solido
        if ( PegaNo(CurrentNode)->I3D_Atras < 0 )
        {
            // Sinaliza poligonos atras como deletados
            for ( TestFace = BackList; TestFace; TestFace = TestFace->Proximo ) TestFace->Deleted = true;
            // Lista Atras Vazia
            BackList = NULL;
        }
    }
    else
    {
        if ( PegaNo(CurrentNode)->I3D_Frente < 0 )
        {
            // Sinaliza lista frente como deletada
            for ( TestFace = FrontList; TestFace; TestFace = TestFace->Proximo ) TestFace->Deleted = true;
            // Lista Frente Vazia
            FrontList = NULL;
        }
    }
    // Recursividade Listra Frente
    if ( FrontList && PegaNo(CurrentNode)->I3D_Frente >= 0 )
    {
        if(!ClipTree( pTree, ClipSolid, RemoveCoPlanar, PegaNo(CurrentNode)->I3D_Frente, FrontList))
        {
            goto ClipError;
        }
    }

    // Recursividade Listra Atras
    if ( BackList && PegaNo(CurrentNode)->I3D_Atras >= 0 )
    {
        if(!ClipTree( pTree, ClipSolid, RemoveCoPlanar, PegaNo(CurrentNode)->I3D_Atras, BackList))
        {
            goto ClipError;
        }
    }
    // Sucesso!
    return true;

ClipError:
    //Falhou
    return false;
}

bool CI3DArvoreBsp::CruzamentoArvore( const CI3DArvoreBsp * pTree ) const
{
    for ( unsigned long i = 0; i < pTree->PegaQtdFaces(); i++ )
    {
        if ( CruzamentoFace( pTree->PegaFace(i) ) ) return true;
    }
    return false;
}

bool CI3DArvoreBsp::CruzamentoFace(const CI3DFace * pFace, unsigned long Node /* = 0 */ ) const
{
    if (!pFace || Node < 0 || Node >= PegaQtdNos() ) return false;

    CI3DNoBsp* NoTemp = NULL;

    NoTemp = PegaNo( Node );

    int NodeFront = NoTemp->I3D_Frente;
    int NodeBack  = NoTemp->I3D_Atras;

    switch ( PegaPlano(NoTemp->Plano)->ClassificaPoligono( pFace->Vertices, pFace->I3D_QtdVertices,sizeof(CI3DVertice)))
    {
        case CRUZANDO:
        case COPLANAR:
            // Folha Solido
            if (NodeBack  <  0 ) return true;
            // Passa a Frente
            if (NodeFront >= 0 ) { if ( CruzamentoFace( pFace, NodeFront ) ) return true; }
            // Passa Atras
            if (NodeBack  >= 0 ) { if ( CruzamentoFace( pFace, NodeBack  ) ) return true; }
            break;

        case FRENTE:
            // Passa a Frente
            if (NodeFront >= 0 ) { if ( CruzamentoFace( pFace, NodeFront ) ) return true; }
            break;

        case ATRAS:
            // Folha Solido
            if (NodeBack  <  0 ) return true;
            // Passa Atras
            if (NodeBack  >= 0 ) { if ( CruzamentoFace( pFace, NodeBack  ) ) return true; }
            break;
    }
    return false;
}

bool CI3DArvoreBsp::CruzamentoEsfera(const CIMTVetor& SphereCenter,
                                            float      SphereRadius,
                                            unsigned long Node        ) const
{
    CI3DNoBsp * pNode     = PegaNo   ( Node         );
    CIMTPlano * pPlane    = PegaPlano( pNode->Plano );

    // Pega a distancia da Esfera ate o No(ao longo da normal do plano)
    float      fDistance = fabsf(SphereCenter.DistanciaPlano(*pPlane ));

    switch ( pPlane->ClassificaPonto( SphereCenter ))
    {
        case COPLANAR:
        case FRENTE:
            if ( pNode->I3D_Frente >= 0 )
            {
                if (CruzamentoEsfera( SphereCenter, SphereRadius, pNode->I3D_Frente ) ) return true;
            }
            if ( fDistance < SphereRadius )
            {
                if ( pNode->I3D_Atras < 0 )
                {
                    return true;
                }
                else
                {
                    if ( CruzamentoEsfera( SphereCenter, SphereRadius, pNode->I3D_Atras) ) return true;
                }
            }
            break;
        case ATRAS:
            if ( pNode->I3D_Atras < 0 )
            {
                return true;
            }
            else
            {
                if ( CruzamentoEsfera( SphereCenter, SphereRadius, pNode->I3D_Atras) ) return true;
            }
            if ( fDistance < SphereRadius )
            {
                if ( pNode->I3D_Frente >= 0 )
                {
                    if ( CruzamentoEsfera( SphereCenter, SphereRadius, pNode->I3D_Frente) ) return true;
                }
            }
            break;
    }
    return false;
}

void CI3DArvoreBsp::ReparaDivisao()
{
    for ( int i = PegaQtdFaces() - 1; i >= 0; i--)
    {
        if ( PegaFace(i)->ChildSplit[0] != -1)
        {
            if ( !PegaFace( PegaFace(i)->ChildSplit[0] )->Deleted && !PegaFace( PegaFace(i)->ChildSplit[1] )->Deleted )
            {
                PegaFace( i )->Deleted = false;
                PegaFace( PegaFace(i)->ChildSplit[0] )->Deleted = true;
                PegaFace( PegaFace(i)->ChildSplit[1] )->Deleted = true;
            }
        }
    }
}
