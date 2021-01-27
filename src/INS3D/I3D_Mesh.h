/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef I3D_MESH_H
#define I3D_MESH_H

#include "I3D_Face.h"
#include "I3D_ArvoreBsp.h"

/************************************************************/
/************************************************************/
class CI3DMesh : public INSGL , public INSMA , public INSCLInterface
{

public:

    long            I3D_QtdFaces          ;
    CIMTBorda       I3D_BordaMesh         ;
    CI3DFace        **Faces               ;

    /***************************************************/
    /*Parametros de Materiais aplicados no Mesh        */
    /***************************************************/
    int             I3D_Material        ;
    int             I3D_MeshProgramId   ;
    bool            bMultiTexture       ;//Sinaliza que a renderização é Multitexturizada
    bool            I3D_MultipleTextures;
    bool            I3D_Multitexture    ;

    /***************************************************/
    /*Parametros de construção/Renderização do Mesh    */
    /***************************************************/
    int             Status                ;
    int             PolygonMode           ;
    int             ShadingMode           ;
    int             GeometryMode          ;
    int             WindingMode           ;
    int             ProjectionMode        ;
    int             MeshType              ;
    int             RenderMode            ;
    int             ConstructionMode      ;
    int             iIdMesh               ;//Id de atribuição temporario para picking

    /*********************************/
    /*Atributos para Shaders         */
    /*********************************/
    IGLVertexBuffer   *I3D_SkinVertexBuffer   ;
    GLuint            *I3D_SkinVertexIndices  ;
    GLuint             I3D_SkinVboIds[3]      ;
    GLuint             I3D_QtdVerticesSkin    ;
    GLuint             I3D_QtdIndicesSkin     ;
    GLuint             I3D_QtdFacesSkin       ;
    GLuint             I3D_QtdFdkVertsSkin    ;
    FeedBackData      *I3D_SkinFeedbackBuffer ;

public:
                    CI3DMesh(                        );
                    CI3DMesh(int I3D_ProgramId       );
//                    CI3DMesh(const CI3DMesh &i3dMesh );
                   ~CI3DMesh(                        );


    void             LimpaFaces        (                                                  );
    const CIMTBorda& CalculaBorda      (                                                  );
    void             CalculaNrml       (CIMTVetor smooth                                  );
    void             CalculaPlnrNrml   (                                                  );
    void             CalculaSmthNrml   (CIMTVetor centro                                  );
    void             InverteNormais    (                                                  );
    void             CalculaTgns       (                                                  );
    void             ConstroiBuffersSH (                                                  );
    void             PreencheSkin      (                                                  );
    void             PreencheSkinModel (                                                  );
    void             TriangularizaSkin (                                                  );
    void             AlocaSkinBuffer   (int i3dQtdVertices, int i3dQtdIndices             );
    void             IniSkinBuffer     (                                                  );
    void             InverteWindingMode(                                                  );
    void             SetaWindingMode   (int iWindingMode                                  );
    void             Render            (int pRenderMode ,int pPolygonMode,int pShadingMode);
    void             RenderizaFaces    (                                                  );
    void             RenderizaFace     (int i3dIndice                                     );
    void             RenderizaSkin     (                                                  );
    void             AdicionaFaces     (int i3dQtd                                        );
    void             SetaMaterial      (int pI3D_IndiceMaterial                           );
    void             SetaMaterialFace  (int pI3D_IndiceMaterial,int pI3D_IndiceFace       );
    void             SetaShader        (int pI3D_ShaderId                                 );
    void             SetaShaderFace    (int pI3D_ShaderId      ,int pI3D_IndiceFace       );
    void             SetaNormalFace    (int pI3D_IndiceFace    ,CIMTVetor pI3D_Normal     );
    void             SetaTexturaFace   (int pI3D_IndiceTextura ,int pI3D_IndiceFace       );
    void             ProcessaFeedback  (                                                  );
    void             SetaGeometryMode  (int pGeometryMode                                 );
    void             UpdateVertices    (CIMTMatriz pIMT_Matrix                            );
    bool             ConstroiBSP       (const CI3DArvoreBsp * pTree, bool pReset          );
};

#endif // I3D_MESH_H
