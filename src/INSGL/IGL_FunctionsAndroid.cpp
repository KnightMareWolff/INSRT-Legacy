#include "IGL_FunctionsAndroid.h"

#ifdef Q_OS_ANDROID

CIGLFunctionsAndroid::CIGLFunctionsAndroid(QOpenGLContext *pContext, int iVersao, int iMajor, int iMinor)
{
    iIGLVersion      = iVersao;
    iIGLMinorVersion = iMajor ;
    iIGLMajorVersion = iMinor ;

    bIGLSuportaFeedback = false;

    pShaderControl  = new INSSH();


    bIGLSuportaShaders = pShaderControl->SupportShaders(bIGLSuportaVertexShader  ,
                                                        bIGLSuportaFragmentShader,
                                                        bIGLSuportaTessCtrlShader,
                                                        bIGLSuportaTessEvalShader,
                                                        bIGLSuportaGeometryShader,
                                                        bIGLSuportaComputeShader );

    if(bIGLSuportaShaders)
    {
       pShader = new CISHProgram();
    }

    /**********************************************************/
    /*Para OpenGL ES Usamos a Classe Base e não a via template*/
    /**********************************************************/
    if(pContext->isValid())
    {
       pGL = pContext->versionFunctions<QOpenGLFunctions_ES2>();
       if (!pGL)
       {
          qWarning() << "Não foi possivel Obter Contexto de Função para esta versão da OpenGL.";
          QMessageBox::information(0, "Insane RT Framework",
                                      "Não foi possivel Obter Contexto de Função para esta versão da OpenGL.");
          exit(0);
       }
       if(!pGL->initializeOpenGLFunctions())
       {
          qWarning() << "Não foi possivel Inicializar as Funções OpenGL para este contexto.";
          QMessageBox::information(0, "Insane RT Framework",
                                      "Não foi possivel Inicializar as Funções OpenGL para este contexto.");
          exit(0);
       }
    }
}

bool CIGLFunctionsAndroid::iglEnableStates()
{
    pGL->glClearDepthf(1.0f                  );

    /********************************************/
    /*OpenGL ES Nao suporta GL_ACCUM_BUFFER_BIT */
    /********************************************/
    pGL->glClear      ( GL_COLOR_BUFFER_BIT  |
                        GL_DEPTH_BUFFER_BIT  );

    /********************************************/
    /*OpenGL ES Nao suporta GL_LIGHTING ...     */
    /********************************************/
    pGL->glEnable     (GL_DEPTH_TEST    );
    pGL->glFrontFace  (GL_CCW           );
    pGL->glEnable     (GL_CULL_FACE     );
    pGL->glEnable     (GL_TEXTURE_2D    );
    return true;
}

bool CIGLFunctionsAndroid::iglDisableStates()
{
    pGL->glDisable     (GL_DEPTH_TEST   );
    pGL->glDisable     (GL_CULL_FACE    );
    pGL->glDisable     (GL_TEXTURE_2D   );
    pGL->glDisable     (GL_BLEND        );
    pGL->glDepthMask   (GL_TRUE         );
    return true;
}

bool CIGLFunctionsAndroid::iglActiveTexture(unsigned int estado)
{
    pGL->glActiveTexture( estado );
    return true;
}

bool CIGLFunctionsAndroid::iglBegin(unsigned int estado)
{
    qWarning() << "Função glBegin Não é utilizada em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função glBegin Não é utilizada em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglEnd()
{
    qWarning() << "Função glEnd Não é utilizada em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função glEnd Não é utilizada em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglEnable(unsigned int estado)
{
    pGL->glEnable( estado );
    return true;
}

bool CIGLFunctionsAndroid::iglDisable(unsigned int estado)
{
    pGL->glDisable( estado );
    return true;
}

bool CIGLFunctionsAndroid::iglDeleteTextures(int vlr, GLuint *Id)
{
    pGL->glDeleteTextures(vlr,Id);
    return true;
}

bool CIGLFunctionsAndroid::iglDeleteBuffers(int vlr, GLuint *Id)
{
    pGL->glDeleteBuffers(vlr,Id);
    return true;
}

bool CIGLFunctionsAndroid::iglRenderBuffers(int          vlr           ,
                                          long           QtdVertices   ,
                                          long           QtdIndices    ,
                                          GLuint        *Id            ,
                                          GLuint        *FbId          ,
                                          GLuint        *QryId         ,
                                          bool           FeedBack      ,
                                          FeedBackData  *FeedbackBuffer)
{
    if(FeedBack)
    {
        qWarning() << "OpenGL ES Não suporta Transformation Feedback e nem Subrotinas Shader...";
        QMessageBox::information(0, "Insane RT Framework",
                                    "OpenGL ES Não suporta Transformation Feedback e nem Subrotinas Shader...");
        exit(0);
        return false;
    }
    else
    {
        /****************************************************************/
        /*Como a OpenGL ES não suporta subrotinas apenas fazemos o bind */
        /*dos buffers suportados e renderizamos com um shader preparado */
        /*para renderização OpenGL ES e não OpenGL PC                   */
        /****************************************************************/
        //Faz o Bind dos Buffers atuais
        BindBuffers(Id);
        //Renderiza os Buffers atuais
        RenderBuffers(vlr,QtdIndices);
    }
    return true;
}

bool CIGLFunctionsAndroid::iglRenderVertice(CIMTVetor vertice,
                                          CIMTVetor normal ,
                                          bool Autotexture ,
                                          bool Multitextura,
                                          float tu         ,
                                          float tv         )
{
    qWarning() << "Função glRenderVertice Não é utilizada em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função glRenderVertice Não é utilizada em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglAutoTexture(float S[], float T[])
{
    qWarning() << "Função iglAutoTexture Não é utilizada em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglAutoTexture Não é utilizada em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglMultiTexture(float S[], float T[])
{
    qWarning() << "Função iglMultiTexture Não é utilizada em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglMultiTexture Não é utilizada em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglSetaMaterial(CIMTVetor4 CorDifusa  ,
                                         CIMTVetor4 CorAmbiente,
                                         CIMTVetor4 CorEmissiva,
                                         CIMTVetor4 CorSpecular,
                                         float      opacidade  ,
                                         float      brilho     )
{
    qWarning() << "Função iglSetaMaterial Não implementada em shaders ainda.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglSetaMaterial Não implementada em shaders ainda.");
    //exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglSetaLuzPonto     (unsigned int Id ,
                                                CIMTVetor4   pos,
                                                CIMTVetor4   dir,
                                                CIMTVetor4   CorDifusa,
                                                CIMTVetor4   CorAmbiente,
                                                CIMTVetor4   CorSpecular,
                                                float        Expoente   ,
                                                float        CutOff     ,
                                                float        AtenuacaoConstante,
                                                float        AtenuacaoLinear   ,
                                                float        AtenuacaoQuadratica)
{
    qWarning() << "Função iglSetaLuzPonto Não implementada em shaders ainda.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglSetaLuzPonto Não implementada em shaders ainda.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglSetaLuzDirecional  (unsigned int Id,
                                                CIMTVetor4 pos ,
                                                CIMTVetor4 dir,
                                                CIMTVetor4 CorDifusa,
                                                CIMTVetor4 CorAmbiente,
                                                CIMTVetor4 CorSpecular,
                                                float Expoente,
                                                float CutOff,
                                                float AtenuacaoConstante,
                                                float AtenuacaoLinear,
                                                float AtenuacaoQuadratica)
{
    qWarning() << "Função iglSetaLuzDirecional Não implementada em shaders ainda.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglSetaLuzDirecional Não implementada em shaders ainda.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglSetaLuzSpot        (unsigned int Id,
                                                CIMTVetor4  pos,
                                                CIMTVetor4 dir,
                                                CIMTVetor4 CorDifusa,
                                                CIMTVetor4 CorAmbiente,
                                                CIMTVetor4 CorSpecular,
                                                float Expoente,
                                                float CutOff,
                                                float AtenuacaoConstante,
                                                float AtenuacaoLinear,
                                                float AtenuacaoQuadratica)
{
    qWarning() << "Função iglSetaLuzSpot Não implementada em shaders ainda.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglSetaLuzSpot Não implementada em shaders ainda.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglSetaVisPerspectiva(float ValorProx   ,
                                               float ValorDist   ,
                                               int   ValorAltura ,
                                               int   ValorLargura,
                                               float FOV         )
{
    int proj_location;

    GLfloat Aspecto = (GLfloat)ValorAltura/(GLfloat)ValorLargura;

    pGL->glViewport(0, 0, ValorAltura, ValorLargura);

    mIGLProjectionMatrix.SetPerspectiveFovRH(FOV/2,Aspecto,ValorProx,ValorDist);

    proj_location=pGL->glGetUniformLocation(pShader->programId(),"proj_matrix");

    pGL->glUniformMatrix4fv(proj_location, 1, GL_FALSE, mIGLProjectionMatrix);
    return true;
}

bool CIGLFunctionsAndroid::iglSetaVisOrtogonal(float ValorProx,
                                             float ValorDist,
                                             int   ValorAltura,
                                             int   ValorLargura)
{
    int proj_location;

    pGL->glViewport(0, 0, ValorAltura, ValorLargura);

    mIGLProjectionMatrix.SetOrthoRH((GLfloat)ValorAltura,(GLfloat)ValorLargura,ValorProx,ValorDist);

    proj_location=pGL->glGetUniformLocation(pShader->programId(),"proj_matrix");

    pGL->glUniformMatrix4fv(proj_location, 1, GL_FALSE, mIGLProjectionMatrix);
    return true;
}

bool CIGLFunctionsAndroid::iglSetaLookAt(CIMTVetor Pos, CIMTVetor View, CIMTVetor Up)
{
    int view_location;

    mIGLViewMatrix.SetLookAtRH(Pos,View,Up);

    view_location=pGL->glGetUniformLocation(pShader->programId(),"view_matrix");

    pGL->glUniformMatrix4fv(view_location, 1, GL_FALSE, mIGLViewMatrix);
    return true;
}

bool CIGLFunctionsAndroid::iglSetaUniformInt(GLchar *nome,int vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(pShader->programId(),nome);
    pGL->glUniform1i(uniform_location,vlr);
    return true;
}

bool CIGLFunctionsAndroid::iglSetaUniformVec3(GLchar *nome,CIMTVetor vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(pShader->programId(),nome);
    pGL->glUniform3fv(uniform_location,1,vlr);
    return true;
}

bool CIGLFunctionsAndroid::iglSetaUniformVec4(GLchar *nome,CIMTVetor4 vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(pShader->programId(),nome);
    pGL->glUniform4fv(uniform_location,1,vlr);
    return true;
}

bool CIGLFunctionsAndroid::iglSetaUniformMatrix(CIMTMatriz mtx)
{
    int model_location;
    model_location=pGL->glGetUniformLocation(pShader->programId(),"modl_matrix");
    pGL->glUniformMatrix4fv(model_location, 1, GL_FALSE,mtx);
    return true;
}

bool CIGLFunctionsAndroid::iglCalculaPVMMatrix(CIMTMatriz mtx,CIMTMatriz &resmtx)
{
    mIGLPVMMatrix = mIGLProjectionMatrix * mIGLViewMatrix * mtx;
    resmtx = mIGLPVMMatrix;
    return true;
}

bool CIGLFunctionsAndroid::iglPegaPVMMatrix(CIMTMatriz &resmtx)
{
    resmtx = mIGLPVMMatrix;
    return true;
}

bool CIGLFunctionsAndroid::iglInitBuffers( VertexData   *VertexBuffer  ,
                                           GLuint       *VertexIndices ,
                                           long          QtdVertices   ,
                                           long          QtdIndices    ,
                                           GLuint        vboIds[]      ,
                                           GLuint        qryIds[]      )
{
    /*********************************************************************/
    /*Garação de Queries OpenGL Não suportada também Haaaaa!!!!          */
    /*Aliás também não é suportado GL_STATIC_READ usado em Feedback no PC*/
    /*********************************************************************/
    // Gera 2 VBO´s uma para os vertices e outra para os indices
    pGL->glGenBuffers(2, vboIds);

    // Transfere o vetor de VERTICES para a VBO 0
    pGL->glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    pGL->glBufferData(GL_ARRAY_BUFFER,
                      QtdVertices * sizeof(VertexData),
                      VertexBuffer,
                      GL_STATIC_DRAW);

    // Transfere o vetor de INDICES para a VBO 1
    pGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    pGL->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      QtdIndices * sizeof(GLuint),
                      VertexIndices,
                      GL_STATIC_DRAW);

    return true;
}

/*************************************/
/*Metodos Privados da Classe         */
/*************************************/
void CIGLFunctionsAndroid::BindBuffers(GLuint *Id)
{
    /****************************************************************/
    /*OpenGL ES Não suporta GL_TRANSFORM_FEEDBACK_BUFFER HuuHuuuu!  */
    /****************************************************************/
    // Informa Quais VBOs utilizar
    pGL->glBindBuffer(GL_ARRAY_BUFFER, Id[0]);
    pGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id[1]);
    // Offset de memoria para informar o intervalo de memoria entre um
    // dado e outro do buffer
    quintptr offset = 0;
    // Informa para a OpenGL como localizar a VBO de vertices
    // neste caso no inicio da estrutura VertexData
    int vertexLocation = pShader->attributeLocation("a_position");
    pShader->enableAttributeArray(vertexLocation);
    pGL->glVertexAttribPointer(vertexLocation       ,
                                3                    ,
                                GL_FLOAT             ,
                                GL_FALSE             ,
                                sizeof(VertexData)   ,
                                (const void *)offset);

    // Desloca o Offset O TAMANHO de um Vetor3D desta forma a OpenGL
    // encontra o Vetor2D contendo as coordenadas de textura
    offset += sizeof(CIMTVetor);
    // Informa para a OpenGL como localizar a VBO de coord. de textura
    int texcoordLocation = pShader->attributeLocation("a_texcoord");
    pShader->enableAttributeArray(texcoordLocation);
    pGL->glVertexAttribPointer(texcoordLocation,
                               2               ,
                               GL_FLOAT        ,
                               GL_FALSE        ,
                               sizeof(VertexData),
                               (const void *)offset);
    // Desloca o Offset O TAMANHO de um Vetor2D desta forma a OpenGL
    // encontra o Vetor2D contendo as normais
    offset += sizeof(CIMTVetor2);
    // Informa para a OpenGL como localizar a VBO de normais
    int normalcoordLocation = pShader->attributeLocation("a_normal");
    pShader->enableAttributeArray(normalcoordLocation);
    pGL->glVertexAttribPointer(normalcoordLocation,
                                3                  ,
                                GL_FLOAT           ,
                                GL_FALSE           ,
                                sizeof(VertexData) ,
                                (const void *)offset);
}

void CIGLFunctionsAndroid::TransfFeedback(long           QtdVertices    ,
                                          long           QtdIndices     ,
                                          FeedBackData  *FeedbackBuffer )
{
    /*************************************************************************/
    /*Apenas mantive esta função aqui para que possamos enxergar as          */
    /*limitações contidas na OpenGL ES comparadas a versao PC da OpenGL, oK? */
    /*************************************************************************/
    qWarning() << "OpenGL ES Não suportA Transformation Feedback...";
    QMessageBox::information(0, "Insane RT Framework",
                                "OpenGL ES Não suportA Transformation Feedback...");
    exit(0);
}

void CIGLFunctionsAndroid::RenderBuffers(int TpPoligono, long QtdIndices)
{
    switch(TpPoligono)
    {
       // Desenha de acordo com o Modo Informado na variavel TpPoligono
       case IGL_RENDER_TRIANGLE_STRIP:
       {
          pGL->glDrawElements(GL_TRIANGLE_STRIP,QtdIndices, GL_UNSIGNED_INT, 0);
       }break;
       case IGL_RENDER_TRIANGLE_FAN:
       {
          pGL->glDrawElements(GL_TRIANGLE_FAN,QtdIndices, GL_UNSIGNED_INT, 0);
       }break;
       case IGL_RENDER_TRIANGLES:
       {
          pGL->glDrawElements(GL_TRIANGLES,QtdIndices, GL_UNSIGNED_INT, 0);
       }break;
       case IGL_RENDER_TRIANGLE_STRIP_ARRAY:
       {
          pGL->glDrawArrays(GL_TRIANGLE_STRIP,0, 0);
       }break;
       case IGL_RENDER_TRIANGLE_FAN_ARRAY:
       {
          pGL->glDrawArrays(GL_TRIANGLE_STRIP,0, 0);
       }break;
       case IGL_RENDER_TRIANGLES_ARRAY:
       {
          pGL->glDrawArrays(GL_TRIANGLE_STRIP,0, 0);
       }break;
       case IGL_RENDER_POINTS:
       {
          pGL->glDrawElements(GL_POINTS,QtdIndices,GL_UNSIGNED_INT, 0);
       }break;
       default:
       {
          qWarning() << "Função RenderBuffers sendo utilizada em primitivo nao suportado.";
          QMessageBox::information(0, "Insane RT Framework",
                                      "Função RenderBuffers sendo utilizada em primitivo nao suportado.");
          exit(0);
       }break;
    }
}

bool CIGLFunctionsAndroid::iglSuportaShaders()
{
   return bIGLSuportaShaders;
}

bool CIGLFunctionsAndroid::iglSuportaFeedback()
{
   return bIGLSuportaFeedback;
}

bool CIGLFunctionsAndroid::iglAddShader(QString pi3dNomeShader, int pShaderType)
{
   pShader->AddPgm(pi3dNomeShader,pShaderType);
   return true;
}

bool CIGLFunctionsAndroid::iglCompile()
{
   /*******************************************************/
   /*aFFF....Não suporta GL_INTERLEAVED_ATTRIBS Também!!! */
   /*glTransformFeedbackVaryings nao existe também        */
   /*******************************************************/
   pShader->link();
   pShader->bind();
   return true;
}

bool CIGLFunctionsAndroid::iglPegaIdLuz(GLenum       &ThisGLLight    ,
                                        int           IdLuz          ,
                                        bool          bHabilita      )
{
    qWarning() << "Função iglPegaIdLuz Não implementada em shaders ainda.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglPegaIdLuz Não implementada em shaders ainda.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglColormaterial(bool bHabilita)
{
    qWarning() << "Função iglColormaterial Não suportado em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglColormaterial Não suportado em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglTextureST(bool bHabilita)
{
    qWarning() << "Função iglTextureST Não suportado em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglTextureST Não suportado em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglQuads()
{
    qWarning() << "Função iglQuads Não suportado em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglQuads Não suportado em shaders.");
    exit(0);
    return false;
}

bool CIGLFunctionsAndroid::iglPolygons()
{
    qWarning() << "Função iglPolygons Não suportado em shaders.";
    QMessageBox::information(0, "Insane RT Framework",
                                "Função iglPolygons Não suportado em shaders.");
    exit(0);
    return false;
}

#endif
