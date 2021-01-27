#include "IGL_FunctionsPCv45.h"
#ifdef Q_OS_WIN

CIGLFunctionsPCv45::CIGLFunctionsPCv45(QOpenGLContext *pContext, int iVersao, int iMajor, int iMinor)
{
    iIGLVersion      = iVersao;
    iIGLMinorVersion = iMajor ;
    iIGLMajorVersion = iMinor ;

    pGL = pContext->versionFunctions<QOpenGLFunctions_4_5_Core>();
    if (!pGL)
    {
       qWarning() << "Não foi possivel Obter Contexto de Função para esta versão da OpenGL.";
       exit(1);
    }

    if(!bIGLContextoInicializado)
    {
       if(!pGL->initializeOpenGLFunctions())
       {
          qWarning() << "Não foi possivel Inicializar as Funções OpenGL para este contexto.";
          exit(1);
       }
       else
       {
          bIGLContextoInicializado = true;
       }
    }
}

bool CIGLFunctionsPCv45::iglEnableStates()
{
    pGL->glEnable     (GL_DEPTH_TEST    );
    pGL->glEnable     (GL_BLEND         );
    pGL->glEnable     (GL_CULL_FACE     );
    pGL->glEnable     (GL_TEXTURE_2D    );

    pGL->glClear     ( GL_COLOR_BUFFER_BIT  |
                       GL_DEPTH_BUFFER_BIT  |
                       GL_ACCUM_BUFFER_BIT  |
                       GL_STENCIL_BUFFER_BIT);

    pGL->glPolygonMode(GL_FRONT,GL_FILL );
    pGL->glCullFace   (GL_BACK          );
    pGL->glDepthFunc  (GL_LESS          );
    //pGL->glDepthMask  (GL_TRUE          );

    return true;
}

bool CIGLFunctionsPCv45::iglDisableStates()
{
    pGL->glDisable     (GL_DEPTH_TEST   );
    pGL->glDisable     (GL_CULL_FACE    );
    pGL->glDisable     (GL_TEXTURE_2D   );
    pGL->glDisable     (GL_BLEND        );
    //pGL->glDepthMask   (GL_FALSE        );
    return true;
}

bool CIGLFunctionsPCv45::iglFenceSync(GLsync &pIGL_Sync)
{
   pIGL_Sync = pGL->glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE,0);
   return true;
}

bool CIGLFunctionsPCv45::iglWaitSync(GLsync pIGL_Sync)
{
   pGL->glWaitSync(pIGL_Sync,0,0);
   return true;
}

bool CIGLFunctionsPCv45::iglFinish()
{
   pGL->glFinish();
   return true;
}


bool CIGLFunctionsPCv45::iglActiveTexture(unsigned int estado)
{
    pGL->glActiveTexture( estado );
    return true;
}

bool CIGLFunctionsPCv45::iglEnable(unsigned int estado)
{
    pGL->glEnable( estado );
    return true;
}

bool CIGLFunctionsPCv45::iglDisable(unsigned int estado)
{
    pGL->glDisable( estado );
    return true;
}

bool CIGLFunctionsPCv45::iglDeleteTextures(int vlr, GLuint *Id)
{
    pGL->glDeleteTextures(vlr,Id);
    return true;
}

bool CIGLFunctionsPCv45::iglDeleteBuffers(int vlr, GLuint *Id)
{
    pGL->glDeleteBuffers(vlr,Id);
    return true;
}

bool CIGLFunctionsPCv45::iglRenderBuffers(int            vlr           ,
                                          long           QtdVertices   ,
                                          long           QtdIndices    ,
                                          GLuint         ProgramId     ,
                                          GLuint        *Id            ,
                                          bool           FeedBack      ,
                                          FeedBackData  *FeedbackBuffer)
{
    if(FeedBack)
    {
        //seta a subrotina shader a ser usada para coleta do feedback
        GLuint updateSub = pGL->glGetSubroutineIndex(ProgramId, GL_VERTEX_SHADER, "update");
        pGL->glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &updateSub);
        //habilita descarte de renderização
        pGL->glEnable(GL_RASTERIZER_DISCARD);
        //Faz o Bind dos Buffers Utilizados
        BindBuffers(ProgramId,Id);
        //Realiza a Renderizacao "Fake" para a coleta do resultado
        TransfFeedback(QtdVertices ,QtdIndices, FeedbackBuffer );
        //desabilita descarte de renderização
        pGL->glDisable(GL_RASTERIZER_DISCARD);
    }
    else
    {
        //seta a subrotina shader a ser usada para a renderizacao
        GLuint renderSub = pGL->glGetSubroutineIndex(ProgramId, GL_VERTEX_SHADER, "render");
        pGL->glUniformSubroutinesuiv(GL_VERTEX_SHADER, 1, &renderSub);
        //Faz o Bind dos Buffers atuais
        BindBuffers(ProgramId,Id);
        //Renderiza os Buffers atuais
        RenderBuffers(vlr,QtdIndices);
    }
    return true;
}



bool CIGLFunctionsPCv45::iglSetaMaterial(GLuint     ProgramId        ,
                                         CIMTVetor4 CorDifusa        ,
                                         CIMTVetor4 CorAmbiente      ,
                                         CIMTVetor4 CorEmissiva      ,
                                         CIMTVetor4 CorSpecular      ,
                                         CIMTVetor4 CorAlpha         ,
                                         bool       bRejeitaAlphabits,
                                         float      opacidade        ,
                                         float      brilho           ,
                                         float      reflexao         ,
                                         float      IndiceRefracao   )
{
    iglSetaUniformVec4 (ProgramId,"cor_diffusa_mat"  ,CorDifusa  );
    iglSetaUniformVec4 (ProgramId,"cor_ambiente_mat" ,CorAmbiente);
    iglSetaUniformVec4 (ProgramId,"cor_emissiva_mat" ,CorEmissiva);
    iglSetaUniformVec4 (ProgramId,"cor_specular_mat" ,CorSpecular);
    iglSetaUniformVec4 (ProgramId,"color_reject"     ,CorAlpha   );

    //habilita/desabilita rejeição de Pixel
    if(bRejeitaAlphabits)
    {
        iglSetaUniformInt(ProgramId,"pixeloper",1);
    }
    else
    {
        iglSetaUniformInt(ProgramId,"pixeloper",0);
    }

    iglSetaUniformFloat(ProgramId,"opacidade_mat"    ,opacidade        );
    iglSetaUniformFloat(ProgramId,"brilho_mat"       ,brilho           );
    iglSetaUniformFloat(ProgramId,"reflexao_mat"     ,reflexao         );
    iglSetaUniformFloat(ProgramId,"indice_refracao"  ,IndiceRefracao   );
    return true;
}

bool CIGLFunctionsPCv45::iglSetaLuzPonto       (GLuint       ProgramId          ,
                                                unsigned int Id                 ,
                                                CIMTVetor4   pos                ,
                                                CIMTVetor4   dir                ,
                                                CIMTVetor4   CorDifusa          ,
                                                CIMTVetor4   CorAmbiente        ,
                                                CIMTVetor4   CorSpecular        ,
                                                float        Expoente           ,
                                                float        CutOff             ,
                                                float        AtenuacaoConstante ,
                                                float        AtenuacaoLinear    ,
                                                float        AtenuacaoQuadratica)
{
    char nome[60];

    sprintf(nome, "Luzes[%d].cor_ambiente_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorAmbiente);

    sprintf(nome, "Luzes[%d].cor_diffusa_luz" , Id);
    iglSetaUniformVec4 (ProgramId,nome,CorDifusa  );

    sprintf(nome, "Luzes[%d].cor_specular_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorSpecular);

    sprintf(nome, "Luzes[%d].posicao_luz", Id);
    iglSetaUniformVec3 (ProgramId,nome,CIMTVetor(pos.x,pos.y,pos.z));

    sprintf(nome, "Luzes[%d].direcao_luz", Id);
    iglSetaUniformVec3 (ProgramId,nome,CIMTVetor(dir.x,dir.y,dir.z));

    sprintf(nome, "Luzes[%d].expoente_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,Expoente);

    sprintf(nome, "Luzes[%d].cutoff_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,CutOff);

    sprintf(nome, "Luzes[%d].atenuacaoconstante_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoConstante);

    sprintf(nome, "Luzes[%d].atenuacaolinear_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoLinear);

    sprintf(nome, "Luzes[%d].atenuacaoquadratica_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoQuadratica);

    //qWarning() << "Função iglSetaLuzPonto Não implementada em shaders ainda.";
    return true;
}

bool CIGLFunctionsPCv45::iglSetaLuzDirecional  (GLuint ProgramId         ,
                                                unsigned int Id          ,
                                                CIMTVetor4 pos           ,
                                                CIMTVetor4 dir           ,
                                                CIMTVetor4 CorDifusa     ,
                                                CIMTVetor4 CorAmbiente   ,
                                                CIMTVetor4 CorSpecular   ,
                                                float Expoente           ,
                                                float CutOff             ,
                                                float AtenuacaoConstante ,
                                                float AtenuacaoLinear    ,
                                                float AtenuacaoQuadratica)
{
    char nome[60];

    sprintf(nome, "Luzes[%d].cor_ambiente_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorAmbiente);

    sprintf(nome, "Luzes[%d].cor_diffusa_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorDifusa  );

    sprintf(nome, "Luzes[%d].cor_specular_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorSpecular);

    sprintf(nome, "Luzes[%d].posicao_luz", Id);
    iglSetaUniformVec3 (ProgramId,nome,CIMTVetor(pos.x,pos.y,pos.z));

    sprintf(nome, "Luzes[%d].direcao_luz", Id);
    iglSetaUniformVec3 (ProgramId,nome,CIMTVetor(dir.x,dir.y,dir.z));

    sprintf(nome, "Luzes[%d].expoente_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,Expoente);

    sprintf(nome, "Luzes[%d].cutoff_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,CutOff);

    sprintf(nome, "Luzes[%d].atenuacaoconstante_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoConstante);

    sprintf(nome, "Luzes[%d].atenuacaolinear_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoLinear);

    sprintf(nome, "Luzes[%d].atenuacaoquadratica_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoQuadratica);

    //qWarning() << "Função iglSetaLuzDirecional Não implementada em shaders ainda.";
    return true;
}

bool CIGLFunctionsPCv45::iglSetaLuzSpot        (GLuint ProgramId,
                                                unsigned int Id         ,
                                                CIMTVetor4  pos         ,
                                                CIMTVetor4 dir          ,
                                                CIMTVetor4 CorDifusa    ,
                                                CIMTVetor4 CorAmbiente  ,
                                                CIMTVetor4 CorSpecular  ,
                                                float Expoente          ,
                                                float CutOff            ,
                                                float AtenuacaoConstante,
                                                float AtenuacaoLinear   ,
                                                float AtenuacaoQuadratica)
{
    char nome[60];

    sprintf(nome, "Luzes[%d].cor_ambiente_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorAmbiente);

    sprintf(nome, "Luzes[%d].cor_diffusa_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorDifusa  );

    sprintf(nome, "Luzes[%d].cor_specular_luz", Id);
    iglSetaUniformVec4 (ProgramId,nome,CorSpecular);

    sprintf(nome, "Luzes[%d].posicao_luz", Id);
    iglSetaUniformVec3 (ProgramId,nome,CIMTVetor(pos.x,pos.y,pos.z));

    sprintf(nome, "Luzes[%d].direcao_luz", Id);
    iglSetaUniformVec3 (ProgramId,nome,CIMTVetor(dir.x,dir.y,dir.z));

    sprintf(nome, "Luzes[%d].expoente_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,Expoente);

    sprintf(nome, "Luzes[%d].cutoff_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,CutOff);

    sprintf(nome, "Luzes[%d].atenuacaoconstante_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoConstante);

    sprintf(nome, "Luzes[%d].atenuacaolinear_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoLinear);

    sprintf(nome, "Luzes[%d].atenuacaoquadratica_luz", Id);
    iglSetaUniformFloat(ProgramId,nome,AtenuacaoQuadratica);

    return true;
}

bool CIGLFunctionsPCv45::iglSetaVisPerspectiva(GLuint ProgramId   ,
                                               float  ValorProx   ,
                                               float  ValorDist   ,
                                               int    ValorAltura ,
                                               int    ValorLargura,
                                               float  FOV         )
{
    int proj_location;

    GLfloat Aspecto = (GLfloat)ValorAltura/(GLfloat)ValorLargura;

    pGL->glViewport(0, 0, ValorAltura, ValorLargura);

    mIGLProjectionMatrix.SetPerspectiveFovRH(FOV/2,Aspecto,ValorProx,ValorDist);

    proj_location=pGL->glGetUniformLocation(ProgramId,"proj_matrix");

    pGL->glUniformMatrix4fv(proj_location, 1, GL_FALSE, mIGLProjectionMatrix);
    return true;
}

bool CIGLFunctionsPCv45::iglSetaVisOrtogonal(GLuint ProgramId,
                                             float ValorProx,
                                             float ValorDist,
                                             int   ValorAltura,
                                             int   ValorLargura)
{
    int proj_location;

    pGL->glViewport(0, 0, ValorAltura, ValorLargura);

    mIGLProjectionMatrix.SetOrthoRH((GLfloat)ValorAltura,(GLfloat)ValorLargura,ValorProx,ValorDist);

    proj_location=pGL->glGetUniformLocation(ProgramId,"proj_matrix");

    pGL->glUniformMatrix4fv(proj_location, 1, GL_FALSE, mIGLProjectionMatrix);
    return true;
}

bool CIGLFunctionsPCv45::iglSetaLookAt(GLuint ProgramId,CIMTVetor Pos, CIMTVetor View, CIMTVetor Up)
{
    int view_location;

    mIGLViewMatrix.SetLookAtRH(Pos,View,Up);

    view_location=pGL->glGetUniformLocation(ProgramId,"view_matrix");

    pGL->glUniformMatrix4fv(view_location, 1, GL_FALSE, mIGLViewMatrix);

    //Atualiza a posição da camera no Shader
    iglSetaUniformVec3 (ProgramId,"posicao_camera",Pos);
    iglSetaUniformVec3 (ProgramId,"view_camera",View);
    iglSetaUniformVec3 (ProgramId,"up_camera",Up);

    return true;
}

bool CIGLFunctionsPCv45::iglSetaUniformInt(GLuint ProgramId,const GLchar *nome,int vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(ProgramId,nome);
    pGL->glUniform1i(uniform_location,vlr);
    return true;
}

bool CIGLFunctionsPCv45::iglSetaUniformFloat(GLuint ProgramId,const GLchar *nome,float vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(ProgramId,nome);
    pGL->glUniform1f(uniform_location,vlr);
    return true;
}

bool CIGLFunctionsPCv45::iglSetaUniformVec3(GLuint ProgramId,const GLchar *nome,CIMTVetor  vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(ProgramId,nome);
    pGL->glUniform3fv(uniform_location,1,vlr);
    return true;
}

bool CIGLFunctionsPCv45::iglSetaUniformVec4(GLuint ProgramId,const GLchar *nome,CIMTVetor4  vlr)
{
    int uniform_location;
    uniform_location=pGL->glGetUniformLocation(ProgramId,nome);
    pGL->glUniform4fv(uniform_location,1,vlr);
    return true;
}

bool CIGLFunctionsPCv45::iglSetaUniformMatrix(GLuint ProgramId,CIMTMatriz mtx)
{
    int model_location;
    model_location=pGL->glGetUniformLocation(ProgramId,"modl_matrix");
    pGL->glUniformMatrix4fv(model_location, 1, GL_FALSE,mtx);
    return true;
}

bool CIGLFunctionsPCv45::iglCalculaPVMMatrix(CIMTMatriz mtx,CIMTMatriz &resmtx)
{
    mIGLPVMMatrix = mIGLProjectionMatrix * mIGLViewMatrix * mtx;
    resmtx = mIGLPVMMatrix;
    return true;
}

bool CIGLFunctionsPCv45::iglPegaPVMMatrix(CIMTMatriz &resmtx)
{
    resmtx = mIGLPVMMatrix;
    return true;
}

bool CIGLFunctionsPCv45::iglInitBuffers(IGLVertexBuffer *IGL_VertexBuffer  ,
                                         GLuint       *IGL_VertexIndices ,
                                         long          IGL_QtdVertices   ,
                                         long          IGL_QtdIndices    ,
                                         GLuint        IGL_VboIds[]      )
{
    // Gera 2 VBO´s uma para os vertices e outra para os indices
    pGL->glGenBuffers(3, IGL_VboIds);

    // Transfere o vetor de VERTICES para a VBO 0
    pGL->glBindBuffer(GL_ARRAY_BUFFER, IGL_VboIds[0]);
    pGL->glBufferData(GL_ARRAY_BUFFER,
                      IGL_QtdVertices * sizeof(IGLVertexBuffer),
                      IGL_VertexBuffer,
                      GL_STATIC_DRAW);

    // Transfere o vetor de INDICES para a VBO 1
    pGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IGL_VboIds[1]);
    pGL->glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                      IGL_QtdIndices * sizeof(GLuint),
                      IGL_VertexIndices,
                      GL_STATIC_DRAW);

    //Inicializa Feedback Buffer VBO 2
    pGL->glBindBuffer(GL_ARRAY_BUFFER, IGL_VboIds[2]);
    pGL->glBufferData(GL_ARRAY_BUFFER,
                      IGL_QtdVertices * sizeof(FeedBackData),
                      NULL,
                      GL_STATIC_READ);

    return true;
}

/*************************************/
/*Metodos Privados da Classe         */
/*************************************/
void CIGLFunctionsPCv45::BindBuffers(GLuint ProgramId,GLuint *Id)
{
    // Informa Quais VBOs utilizar
    pGL->glBindBuffer(GL_ARRAY_BUFFER, Id[0]);
    pGL->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id[1]);
    // Offset de memoria para informar o intervalo de memoria entre um
    // dado e outro do buffer
    quintptr offset = 0;
    // Informa para a OpenGL como localizar a VBO de vertices
    // neste caso no inicio da estrutura VertexData
    int vertexLocation = pGL->glGetAttribLocation(ProgramId,"a_position");

    pGL->glEnableVertexAttribArray(vertexLocation);
    pGL->glVertexAttribPointer(vertexLocation       ,
                                3                    ,
                                GL_FLOAT             ,
                                GL_FALSE             ,
                                sizeof(IGLVertexBuffer)   ,
                                (const void *)offset);

    // Desloca o Offset O TAMANHO de um Vetor3D desta forma a OpenGL
    // encontra o Vetor2D contendo as coordenadas de textura
    offset += sizeof(CIMTVetor);
    // Informa para a OpenGL como localizar a VBO de coord. de textura
    int texcoordLocation = pGL->glGetAttribLocation(ProgramId,"a_texcoord");
    pGL->glEnableVertexAttribArray(texcoordLocation);
    pGL->glVertexAttribPointer(texcoordLocation,
                               2               ,
                               GL_FLOAT        ,
                               GL_FALSE        ,
                               sizeof(IGLVertexBuffer),
                               (const void *)offset);
    // Desloca o Offset O TAMANHO de um Vetor2D desta forma a OpenGL
    // encontra o Vetor2D contendo as normais
    offset += sizeof(CIMTVetor2);
    // Informa para a OpenGL como localizar a VBO de normais
    int normalcoordLocation = pGL->glGetAttribLocation(ProgramId,"a_normal");
    pGL->glEnableVertexAttribArray(normalcoordLocation);
    pGL->glVertexAttribPointer(normalcoordLocation,
                                3                  ,
                                GL_FLOAT           ,
                                GL_FALSE           ,
                                sizeof(IGLVertexBuffer) ,
                                (const void *)offset);
    // Desloca o Offset O TAMANHO de um Vetor desta forma a OpenGL
    // encontra o Vetor2D contendo as normais
    offset += sizeof(CIMTVetor);
    // Informa para a OpenGL como localizar a VBO de normais
    int smoothcoordLocation = pGL->glGetAttribLocation(ProgramId,"a_smooth");
    pGL->glEnableVertexAttribArray(smoothcoordLocation);
    pGL->glVertexAttribPointer(smoothcoordLocation,
                                3                  ,
                                GL_FLOAT           ,
                                GL_FALSE           ,
                                sizeof(IGLVertexBuffer) ,
                                (const void *)offset);

    // Desloca o Offset O TAMANHO de um Vetor desta forma a OpenGL
    // encontra o Vetor2D contendo as normais
    offset += sizeof(CIMTVetor);
    // Informa para a OpenGL como localizar a VBO de normais
    int tancoordLocation = pGL->glGetAttribLocation(ProgramId,"a_tangente");
    pGL->glEnableVertexAttribArray(tancoordLocation);
    pGL->glVertexAttribPointer(tancoordLocation,
                                3                  ,
                                GL_FLOAT           ,
                                GL_FALSE           ,
                                sizeof(IGLVertexBuffer) ,
                                (const void *)offset);

    // Desloca o Offset O TAMANHO de um Vetor desta forma a OpenGL
    // encontra o Vetor2D contendo as normais
    offset += sizeof(CIMTVetor);
    // Informa para a OpenGL como localizar a VBO de normais
    int bitancoordLocation = pGL->glGetAttribLocation(ProgramId,"a_bitangente");
    pGL->glEnableVertexAttribArray(bitancoordLocation);
    pGL->glVertexAttribPointer(bitancoordLocation,
                                3                  ,
                                GL_FLOAT           ,
                                GL_FALSE           ,
                                sizeof(IGLVertexBuffer) ,
                                (const void *)offset);

    //pGL->glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0,Id[2]);
}

void CIGLFunctionsPCv45::TransfFeedback(long           QtdVertices    ,
                                        long           QtdIndices     ,
                                        FeedBackData  *FeedbackBuffer )
{
    pGL->glBeginTransformFeedback(GL_POINTS);
    RenderBuffers(IGL_RENDER_POINTS,QtdIndices);
    pGL->glEndTransformFeedback();
    pGL->glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER,
                            0,
                            QtdVertices * sizeof(FeedBackData),
                            FeedbackBuffer);
}

void CIGLFunctionsPCv45::RenderBuffers(int TpPoligono, long QtdIndices)
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
       }break;
    }
}


bool CIGLFunctionsPCv45::iglColormaterial(GLuint ProgramId,bool bHabilita)
{
    /*****************************************************************************/
    /*Em Shaders Não temos a Limitação de ColorMaterial mutuamente exclusiva com */
    /*As Luzes e Materiais                                                       */
    /*Porem, para fazer a manutenção de Shaders onde os materiais usados tem ou  */
    /*não texturas utilizamos a mesma logica para setar o calculo da cor final do*/
    /*fragmento, ou seja, não são mutuamente exclusivos, porem quando setarmos   */
    /*ColorMaterial a renderização irá ignorar as texturas e aplicar somente     */
    /*Calculos no fragmento da Iluminação e Materiais e quando for solicitado    */
    /*renderização por textura, sem nenhuma textura setada                       */
    /*****************************************************************************/
    if(bHabilita)
    {
        //coloca o modo de material apenas para cores e iluminação
        iglSetaUniformInt(ProgramId,"modo_material",0);
    }
    else
    {
        //coloca o modo de material para considerar as texturas também
        iglSetaUniformInt(ProgramId,"modo_material",1);
    }
    return true;
}

bool CIGLFunctionsPCv45::iglMaterialMode(GLuint ProgramId, int iMode)
{
    /*****************************************************************************/
    /*Em Shaders Não temos a Limitação de ColorMaterial mutuamente exclusiva com */
    /*As Luzes e Materiais                                                       */
    /*Porem, para fazer a manutenção de Shaders onde os materiais usados tem ou  */
    /*não texturas utilizamos a mesma logica para setar o calculo da cor final do*/
    /*fragmento, ou seja, não são mutuamente exclusivos, porem quando setarmos   */
    /*ColorMaterial a renderização irá ignorar as texturas e aplicar somente     */
    /*Calculos no fragmento da Iluminação e Materiais e quando for solicitado    */
    /*renderização por textura, sem nenhuma textura setada                       */
    /*****************************************************************************/
    switch(iMode)
    {
       //coloca o modo de material apenas para cores e iluminação
       case IGL_SH_COLORMATERIAL   :{iglSetaUniformInt(ProgramId,"modo_material",0);}break;
       case IGL_SH_TEXTUREDMATERIAL:{iglSetaUniformInt(ProgramId,"modo_material",1);}break;
       case IGL_SH_MIXEDMATERIAL   :{iglSetaUniformInt(ProgramId,"modo_material",2);}break;
       case IGL_SH_NMAPMATERIAL    :{iglSetaUniformInt(ProgramId,"modo_material",3);}break;
       case IGL_SH_REFLMATERIAL    :{iglSetaUniformInt(ProgramId,"modo_material",4);}break;
       case IGL_SH_REFRMATERIAL    :{iglSetaUniformInt(ProgramId,"modo_material",5);}break;
       case IGL_SH_CUBEMAPMATERIAL :{iglSetaUniformInt(ProgramId,"modo_material",6);}break;
    }
    return true;
}


bool CIGLFunctionsPCv45::iglReadPixels(int x, int y, GLchar *res)
{
    GLint viewport[4];
    pGL->glGetIntegerv(GL_VIEWPORT, viewport);
    pGL->glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, res);
    return true;
}

bool CIGLFunctionsPCv45::iglFrontFace(int iMode)
{
    pGL->glFrontFace(iMode);
    return true;
}

int CIGLFunctionsPCv45::iglGetVersion()
{
    if(bIGLContextoInicializado)
    {
        return iIGLVersion;
    }
    else
    {
        return 99;
    }
}

bool CIGLFunctionsPCv45::iglCreateTexture(GLuint        &IGL_TextureId     ,
                                          GLubyte       *IGL_TextureData   ,
                                          GLuint         IGL_TextureWidth  ,
                                          GLuint         IGL_TextureHeight ,
                                          GLuint         IGL_TextureFormat ,
                                          GLuint         IGL_TextureMipmaps)
{
    Q_UNUSED(IGL_TextureFormat );//Como OpenCV converte pixels fixamos
    Q_UNUSED(IGL_TextureMipmaps);//Futuramente suporte a Mipmaps

    pGL->glGenTextures (1, &IGL_TextureId);
    pGL->glBindTexture (GL_TEXTURE_2D, IGL_TextureId);

    pGL->glTexImage2D(GL_TEXTURE_2D    ,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureData  ); // The actual image data itself

    return true;
}

bool CIGLFunctionsPCv45::iglCreateCubeMap  (GLuint        &IGL_TextureId     ,
                                            GLubyte       *IGL_TextureRight  ,
                                            GLubyte       *IGL_TextureLeft   ,
                                            GLubyte       *IGL_TextureTop    ,
                                            GLubyte       *IGL_TextureBottom ,
                                            GLubyte       *IGL_TextureBack   ,
                                            GLubyte       *IGL_TextureFront  ,
                                            GLuint         IGL_TextureWidth  ,
                                            GLuint         IGL_TextureHeight ,
                                            GLuint         IGL_TextureFormat ,
                                            GLuint         IGL_TextureMipmaps)
{
    Q_UNUSED(IGL_TextureFormat );//Como OpenCV converte pixels fixamos
    Q_UNUSED(IGL_TextureMipmaps);//Futuramente suporte a Mipmaps

    pGL->glGenTextures (1, &IGL_TextureId);
    pGL->glBindTexture (GL_TEXTURE_CUBE_MAP, IGL_TextureId);

    pGL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X ,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureRight  ); // The actual image data itself

    pGL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureLeft  ); // The actual image data itself

    pGL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureTop  ); // The actual image data itself

    pGL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureBottom  ); // The actual image data itself

    pGL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureBack  ); // The actual image data itself

    pGL->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5,  // Type of texture
                      0                ,  // Pyramid level (for mip-mapping) - 0 is the top level
                      GL_RGB           ,  // Internal colour format to convert to
                      IGL_TextureWidth ,  // Image width  i.e. 640 for Kinect in standard mode
                      IGL_TextureHeight,  // Image height i.e. 480 for Kinect in standard mode
                      0                ,  // Border width in pixels (can either be 1 or 0)
                      GL_BGR           ,  // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                      GL_UNSIGNED_BYTE ,  // Image data type
                      IGL_TextureFront ); // The actual image data itself

    return true;
}

bool CIGLFunctionsPCv45::iglPreparaTextura(GLuint     IGL_TextureId     ,
                                           GLuint     IGL_TextureMode   ,
                                           GLboolean  IGL_TextureUpdate ,
                                           GLubyte   *IGL_TextureData   ,
                                           GLuint     IGL_TextureWidth  ,
                                           GLuint     IGL_TextureHeight ,
                                           GLuint     IGL_TextureFormat )
{
    Q_UNUSED(IGL_TextureFormat);

    switch(IGL_TextureMode)
    {
       case IGL_TEXTURE_CLAMP:
       {
           pGL->glBindTexture(GL_TEXTURE_2D, IGL_TextureId);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
       }break;
       case IGL_TEXTURE_LINEAR:
       {
           pGL->glBindTexture(GL_TEXTURE_2D, IGL_TextureId);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       }break;
       case IGL_TEXTURE_GEN_ST:
       {
           pGL->glBindTexture(GL_TEXTURE_2D, IGL_TextureId);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
       }break;
       case IGL_TEXTURE_CUBEMAP:
       {
           pGL->glBindTexture(GL_TEXTURE_CUBE_MAP, IGL_TextureId);
           pGL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
           pGL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
           pGL->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

       }break;
       case IGL_TEXTURE_RENDER:
       {
           pGL->glBindTexture(GL_TEXTURE_2D, IGL_TextureId);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
           pGL->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
       }break;
       default:
       {
          qWarning() << "Atenção! Modo de Preparação de textura inexistente!.";
       }break;
    }

    if(IGL_TextureUpdate)
    {
        pGL->glTexSubImage2D(GL_TEXTURE_2D,0,0,0,
                             IGL_TextureWidth,
                             IGL_TextureHeight,
                             GL_BGR,
                             GL_UNSIGNED_BYTE,
                             IGL_TextureData);
    }

    return true;
}

bool CIGLFunctionsPCv45::iglTransformFeedback(GLuint IGL_ProgramId)
{
    pGL->glTransformFeedbackVaryings(IGL_ProgramId,1, tf_varyings, GL_INTERLEAVED_ATTRIBS);
    return true;
}

bool CIGLFunctionsPCv45::iglTransformBuffer(GLuint IGL_ProgramId, GLuint IGL_VboId, GLuint IGL_QtdVertices, CIMTMatriz IGL_TransfMtx, IGLVertexBuffer *IGL_VertexData)
{
    IGLVertexBuffer *pVertex   = 0;
    CIMTVetor   vet;

    pGL->glBindBuffer(GL_ARRAY_BUFFER, IGL_VboId);

    IGL_VertexData = static_cast<IGLVertexBuffer *>(pGL->glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));

    if (!IGL_VertexData)
    {
        pGL->glBindBuffer(GL_ARRAY_BUFFER, 0);
        return false;
    }

    for (uint i = 0; i < IGL_QtdVertices; i++)
    {
        pVertex = &IGL_VertexData[i];

        vet.x=pVertex->position.x;
        vet.y=pVertex->position.y;
        vet.z=pVertex->position.z;

        vet = vet * IGL_TransfMtx;

        pVertex->position.x = vet.x;
        pVertex->position.y = vet.y;
        pVertex->position.z = vet.z;

    }

    pGL->glUnmapBuffer(GL_ARRAY_BUFFER);
    pGL->glBindBuffer(GL_ARRAY_BUFFER, 0);

    return true;
}

IGLVertexBuffer * CIGLFunctionsPCv45::iglMapBuffer(GLuint  IGL_ProgramId,
                                                   GLuint  IGL_VboId    )
{
    IGLVertexBuffer *pVertex   = 0;

    pGL->glBindBuffer(GL_ARRAY_BUFFER, IGL_VboId);

    pVertex = static_cast<IGLVertexBuffer *>(pGL->glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE));

    if (!pVertex)
    {
        pGL->glBindBuffer(GL_ARRAY_BUFFER, 0);
        return false;
    }

    return pVertex;
}

bool CIGLFunctionsPCv45::iglUnMapBuffer(GLuint           IGL_ProgramId,
                                        GLuint           IGL_VboId    ,
                                        IGLVertexBuffer *IGL_VertexData)
{
    Q_UNUSED(IGL_ProgramId);
    Q_UNUSED(IGL_VboId);
    Q_UNUSED(IGL_VertexData);
    pGL->glUnmapBuffer(GL_ARRAY_BUFFER);
    pGL->glBindBuffer(GL_ARRAY_BUFFER, 0);
    return true;
}

QString CIGLFunctionsPCv45::iglGetString(GLuint           IGL_StringId)
{
    return QString((const char*)pGL->glGetString(IGL_StringId));
}

#endif
