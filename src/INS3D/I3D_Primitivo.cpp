/******************************************************************************************/
/*Projeto             :Insane RT Framework                                                   */
/*Descricao           :Classe responsavel pelos controles e processos de um primitivo gene*/
/*                     rico(Primitivo = Mesh + Dados de Controle(Posição,Direção e etc...)*/
/*Data de Criação     :01/08/2014                                                         */
/*                                                                                        */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                          */
/******************************************************************************************/
/*25-02-2016 - Retirado rotinas de transformação para pipeline Fixa(Acho que apos 15 anos)*/
/*             Se precisarmos usar isto significa que a maquina é ultravelha portanto     */
/*             penalizamos com a necessidade de que se desenvolva novamente isto...       */
/******************************************************************************************/
#include "I3D_Primitivo.h"


CI3DPrimitivo::CI3DPrimitivo()
{
    I3D_View  =CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Up    =CIMTVetor( 0.0f, 1.0f, 0.0f);
    I3D_Pos   =CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_RefPos=CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Rot   =CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_RefRot=CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Scl   =CIMTVetor( 1.0f, 1.0f, 1.0f);
    I3D_RefScl=CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Dim   =CIMTVetor( 5.0f, 5.0f, 5.0f);

    I3D_Pickable    =false;
    I3D_Selecionado =false;

    //Como o programa CoreRender ja existe e é a base da plataforma retorna o indice apenas
    I3D_Shader   =  INSSH::pISHProgramManager->ProgramId("CoreRender");

    //Cria o Mesh Base e atribui Programa
    I3D_Mesh     =  new CI3DMesh(I3D_Shader);

}

CI3DPrimitivo::CI3DPrimitivo(CIMTVetor pI3D_Pos)
{
    I3D_View  =CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Up    =CIMTVetor( 0.0f, 1.0f, 0.0f);

    I3D_Pos   = pI3D_Pos;

    I3D_RefPos=CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Rot   =CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_RefRot=CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Scl   =CIMTVetor( 1.0f, 1.0f, 1.0f);
    I3D_RefScl=CIMTVetor( 0.0f, 0.0f, 0.0f);
    I3D_Dim   =CIMTVetor( 5.0f, 5.0f, 5.0f);

    I3D_Pickable    =false;
    I3D_Selecionado =false;

    //Como o programa CoreRender ja existe e é a base da plataforma retorna o indice apenas
    I3D_Shader   =  INSSH::pISHProgramManager->ProgramId("CoreRender");

    I3D_Mesh     =  new CI3DMesh(I3D_Shader);
}

CI3DPrimitivo::~CI3DPrimitivo()
{

}

void CI3DPrimitivo::Render(int pRenderMode, int pPolygonMode, int pShadingMode)
{
    /****************************************************/
    /*Na renderização de seleção o Id de identificação  */
    /*É usado como pixel de identificação no Framebuffer*/
    /****************************************************/
    if(pRenderMode==IGL_MODE_SELECTION_PRIMI)
    {
        execGL(IGL_SH_UNIINT,I3D_Shader,"color_pick",I3D_IdPrimitivo);
    }
    /******************************************************/
    /*Não é uma maravilha trabalhar com matrizes? ;)      */
    /*Escala,rotação e Translação tudo numa paulada só... */
    /******************************************************/
    switch(I3D_Mesh->GeometryMode)
    {
       case IGL_GEOMETRY_DINAMIC:
       {
          I3D_MtxTransf.Translate(I3D_RefPos.x,I3D_RefPos.y,I3D_RefPos.z,true);
          I3D_MtxTransf.RotateX  (DEG2RAD(I3D_Rot.x),I3D_RefRot,false);
          I3D_MtxTransf.RotateY  (DEG2RAD(I3D_Rot.y),I3D_RefRot,false);
          I3D_MtxTransf.RotateZ  (DEG2RAD(I3D_Rot.z),I3D_RefRot,false);
          I3D_MtxTransf.Scale    (I3D_Scl.x,I3D_Scl.y,I3D_Scl.z,I3D_RefScl,false);
       }break;
       case IGL_GEOMETRY_STATIC:
       {
          I3D_MtxTransf.Identity();
       }break;
       case IGL_GEOMETRY_PHYSICS:
       {
          I3D_MtxTransf.Identity();
       }break;
    }

    //Atualiza a Matriz Model na OpenGL
    execGL(IGL_SH_MODELMTX,I3D_Shader,I3D_MtxTransf);
    /******************************************/
    /*Desenha o Objeto Já Inicializado        */
    /******************************************/
    I3D_Mesh->Render(pRenderMode,pPolygonMode,pShadingMode);
}

void CI3DPrimitivo::Update()
{
    switch(I3D_Mesh->GeometryMode)
    {
       case IGL_GEOMETRY_PHYSICS:
       {
          //Como o buffer é atualizado no momento da transfomação
          float dimensao = I3D_Mesh->I3D_BordaMesh.PegaDimensao().x/2;
          I3D_Mesh->I3D_BordaMesh.CalculaBordaPonto(I3D_Pos,dimensao);

       }break;
       case IGL_GEOMETRY_DINAMIC:
       {
          //Para dinamicos nao e garantido a mesma posicao devido a thread OGL
          float dimensao = I3D_Mesh->I3D_BordaMesh.PegaDimensao().x/2;
          I3D_Pos *= I3D_MtxTransf;
          I3D_Mesh->I3D_BordaMesh.CalculaBordaPonto(I3D_Pos,dimensao);
       }break;
       case IGL_GEOMETRY_STATIC:
       {
          //pOR ENQUANTO NAO HA NADA PARA ESTATICOS
       }break;
    default:{}break;
    }
}

void CI3DPrimitivo::Build()
{
    //Método Build deve ser contruido de acordo com os primitivos herdados!
}

bool CI3DPrimitivo::Collision(CI3DPrimitivo *pI3D_Primitivo,float pI3D_TimeElapsed)
{
    if(I3D_Mesh->I3D_BordaMesh.CruzamentoEsfera(pI3D_Primitivo->I3D_Mesh->I3D_BordaMesh,pI3D_TimeElapsed))
    {
        return true;
    }

    return false;
}

void CI3DPrimitivo::SetaSelecao(bool pFlagSelecionavel)
{
    I3D_Pickable = pFlagSelecionavel;
}

void CI3DPrimitivo::SetaIdSelecao(int pIdSelecao)
{
    I3D_IdPrimitivo = pIdSelecao;
}

void CI3DPrimitivo::SetaSelecionado(bool pFlagSelecionado)
{
    I3D_Selecionado = pFlagSelecionado;
}

void CI3DPrimitivo::Translate(CIMTVetor pTransf, bool Incremento)
{
    /*********************************************************************/
    /*Se é geometria estática não há necessidade de transformação        */
    /*isto será incluido durante topicos avançados como ações simples    */
    /*que podem trazer ganhos de performance significativos para a engine*/
    /*********************************************************************/
    if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_STATIC) return;

    if(Incremento)
    {
       I3D_RefPos.x = I3D_Pos.x + pTransf.x;
       I3D_RefPos.y = I3D_Pos.y + pTransf.y;
       I3D_RefPos.z = I3D_Pos.z + pTransf.z;
    }
    else
    {
       I3D_RefPos   = pTransf - I3D_Pos;
    }

    if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_PHYSICS)
    {
       I3D_MtxTransf.Translate(I3D_RefPos.x,I3D_RefPos.y,I3D_RefPos.z,true);
       I3D_Mesh->UpdateVertices(I3D_MtxTransf);
       I3D_Pos *= I3D_MtxTransf;
       I3D_MtxTransf.Identity();
    }
}

void CI3DPrimitivo::Rotate(bool pControlPoint,CIMTVetor  pTransf,CIMTVetor  pControl)
{
    if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_STATIC) return;

    if(!pControlPoint)
    {
       if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_DINAMIC)
       {
           I3D_Rot.x += pTransf.x;
           I3D_Rot.y += pTransf.y;
           I3D_Rot.z += pTransf.z;
       }
       else
       {
          I3D_Rot.x = pTransf.x;
          I3D_Rot.y = pTransf.y;
          I3D_Rot.z = pTransf.z;
       }
       /*************************************/
       /*Verificamos se chegamos a 360 graus*/
       /*Somente acontece com Dinamico      */
       /*************************************/
       if(fabs(I3D_Rot.x)==360.0f){I3D_Rot.x=0.0f;}
       if(fabs(I3D_Rot.y)==360.0f){I3D_Rot.y=0.0f;}
       if(fabs(I3D_Rot.z)==360.0f){I3D_Rot.z=0.0f;}

       I3D_RefRot = I3D_Pos;
    }
    else
    {
        if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_DINAMIC)
        {
           I3D_Rot.x += pTransf.x;
           I3D_Rot.y += pTransf.y;
           I3D_Rot.z += pTransf.z;
        }
        else
        {
           I3D_Rot.x = pTransf.x;
           I3D_Rot.y = pTransf.y;
           I3D_Rot.z = pTransf.z;
        }
       /*************/
       /*IDEM ACIMA */
       /*************/
       if(fabs(I3D_Rot.x)==360.0f){I3D_Rot.x=0.0f;}
       if(fabs(I3D_Rot.y)==360.0f){I3D_Rot.y=0.0f;}
       if(fabs(I3D_Rot.z)==360.0f){I3D_Rot.z=0.0f;}

       I3D_RefRot = pControl;
    }

    if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_PHYSICS)
    {
       I3D_MtxTransf.RotateX  (DEG2RAD(I3D_Rot.x),I3D_RefRot,true );
       I3D_MtxTransf.RotateY  (DEG2RAD(I3D_Rot.y),I3D_RefRot,false);
       I3D_MtxTransf.RotateZ  (DEG2RAD(I3D_Rot.z),I3D_RefRot,false);

       I3D_Mesh->UpdateVertices(I3D_MtxTransf);
       I3D_Pos *= I3D_MtxTransf;
       I3D_MtxTransf.Identity();
    }
}

void CI3DPrimitivo::Scale(bool pControlPoint,CIMTVetor  pTransf,CIMTVetor  pControl)
{
    /*********************************************************************/
    /*Se é geometria estática não há necessidade de transformação        */
    /*isto será incluido durante topicos avançados como ações simples    */
    /*que podem trazer ganhos de performance significativos para a engine*/
    /*********************************************************************/
    if(I3D_Mesh->GeometryMode==IGL_GEOMETRY_STATIC) return;

    if(!pControlPoint)
    {
       I3D_Scl    = pTransf;
       I3D_RefScl = I3D_Pos;
    }
    else
    {
       I3D_Scl    = pTransf;
       I3D_RefScl = pControl;
    }
}


