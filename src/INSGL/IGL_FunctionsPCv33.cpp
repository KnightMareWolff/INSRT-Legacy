#include "IGL_FunctionsPCv33.h"

#ifdef Q_OS_WIN

CIGLFunctionsPCv33::CIGLFunctionsPCv33(QOpenGLContext *pContext, int iVersao, int iMajor, int iMinor)
{
    iIGLVersion      = iVersao;
    iIGLMinorVersion = iMajor ;
    iIGLMajorVersion = iMinor ;

    bIGLSuportaFeedback = false;

    bIGLSuportaShaders       = false;
    bIGLSuportaVertexShader  = false;
    bIGLSuportaFragmentShader= false;
    bIGLSuportaTessCtrlShader= false;
    bIGLSuportaTessEvalShader= false;
    bIGLSuportaGeometryShader= false;
    bIGLSuportaComputeShader = false;

    pGL = pContext->versionFunctions<QOpenGLFunctions_3_3_Compatibility>();
    if (!pGL)
    {
       qWarning() << "Não foi possivel Obter Contexto de Função para esta versão da OpenGL.";
       exit(1);
    }
    if(!pGL->initializeOpenGLFunctions())
    {
       qWarning() << "Não foi possivel Inicializar as Funções OpenGL para este contexto.";
       exit(1);
    }
}

bool CIGLFunctionsPCv33::iglEnableStates()
{
    bool gouraudshade=false;
    pGL->glMatrixMode(GL_MODELVIEW);
    pGL->glLoadIdentity();
    pGL->glClearDepth( 1.0f                 );
    pGL->glClear     ( GL_COLOR_BUFFER_BIT  |
                       GL_DEPTH_BUFFER_BIT  |
                       GL_ACCUM_BUFFER_BIT  );
    pGL->glEnable     (GL_DEPTH_TEST    );
    pGL->glFrontFace  (GL_CCW           );
    pGL->glEnable     (GL_CULL_FACE     );
    pGL->glEnable     (GL_LIGHTING      );
    pGL->glEnable     (GL_TEXTURE_2D    );
    if(!gouraudshade)
    {
       pGL->glShadeModel (GL_FLAT);
    }
    else
    {
       pGL->glShadeModel (GL_SMOOTH);
    }
    pGL->glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    pGL->glLightModeli(GL_LIGHT_MODEL_TWO_SIDE    , GL_TRUE);
    return true;
}

bool CIGLFunctionsPCv33::iglDisableStates()
{
    pGL->glDisable     (GL_DEPTH_TEST   );
    pGL->glDisable     (GL_CULL_FACE    );
    pGL->glDisable     (GL_TEXTURE_2D   );
    pGL->glDisable     (GL_BLEND        );
    pGL->glDepthMask   (GL_TRUE         );
    return true;
}

bool CIGLFunctionsPCv33::iglActiveTexture(unsigned int estado)
{
    qWarning() << "Função iglActiveTexture Não é utilizada em versoes anteriores a 1.3.";
    return false;
}

bool CIGLFunctionsPCv33::iglBegin(unsigned int estado)
{
    pGL->glBegin( estado );
    return true;
}

bool CIGLFunctionsPCv33::iglEnd()
{
    pGL->glEnd();
    return true;
}

bool CIGLFunctionsPCv33::iglEnable(unsigned int estado)
{
    pGL->glEnable( estado );
    return true;
}

bool CIGLFunctionsPCv33::iglDisable(unsigned int estado)
{
    pGL->glDisable( estado );
    return true;
}

bool CIGLFunctionsPCv33::iglDeleteTextures(int vlr, GLuint *Id)
{
    pGL->glDeleteTextures(vlr,Id);
    return true;
}

bool CIGLFunctionsPCv33::iglDeleteBuffers(int vlr, GLuint *Id)
{
    qWarning() << "Função iglDeleteBuffers Não é utilizada em versoes anteriores a 1.5.";
    return false;
}

bool CIGLFunctionsPCv33::iglRenderBuffers(int            vlr           ,
                                          long           QtdVertices   ,
                                          long           QtdIndices    ,
                                          GLuint        *Id            ,
                                          GLuint        *FbId          ,
                                          GLuint        *QryId         ,
                                          bool           FeedBack      ,
                                          FeedBackData  *FeedbackBuffer)
{
    qWarning() << "Função iglRenderBuffers Não é utilizada em versoes anteriores a 1.5.";
    return false;
}

bool CIGLFunctionsPCv33::iglRenderVertice(CIMTVetor vertice,
                                          CIMTVetor normal ,
                                          bool Autotexture ,
                                          bool Multitextura,
                                          float tu         ,
                                          float tv         )
{
    //Render normal
    pGL->glNormal3f(normal.x,normal.y,normal.z);
    //Coordenada de textura
    if(!Autotexture)
    {
        pGL->glTexCoord2f(tu,tv);
    }
    //Render vertice
    pGL->glVertex3f(vertice.x,vertice.y,vertice.z);
    return true;
}

bool CIGLFunctionsPCv33::iglAutoTexture(float S[], float T[])
{
    pGL->glTexGeni ( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    pGL->glTexGenfv( GL_S, GL_OBJECT_PLANE, S );
    pGL->glTexGeni ( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR );
    pGL->glTexGenfv( GL_T, GL_OBJECT_PLANE, T );
    pGL->glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    pGL->glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL    );
    return true;
}

bool CIGLFunctionsPCv33::iglMultiTexture(float S[], float T[])
{
    pGL->glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE );
    pGL->glTexEnvi ( GL_TEXTURE_ENV, GL_RGB_SCALE, 2);
    return true;
}

bool CIGLFunctionsPCv33::iglSetaMaterial(CIMTVetor4 CorDifusa  ,
                                         CIMTVetor4 CorAmbiente,
                                         CIMTVetor4 CorEmissiva,
                                         CIMTVetor4 CorSpecular,
                                         float      opacidade  ,
                                         float      brilho     )
{
    pGL->glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    pGL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    pGL->glDepthMask(GL_FALSE);
    if (opacidade < 1.0f)
    {
        pGL->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        pGL->glDepthMask(GL_FALSE);
    }
    else
    {
        pGL->glDisable(GL_BLEND);
        pGL->glDepthMask(GL_TRUE);
    }
    pGL->glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT  , CorAmbiente);
    pGL->glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE  , CorDifusa  );
    pGL->glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , CorSpecular);
    pGL->glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION , CorEmissiva);
    pGL->glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, brilho);
    pGL->glColor4f(CorDifusa.x,
                   CorDifusa.y,
                   CorDifusa.z,
                   opacidade);

    return true;
}

bool CIGLFunctionsPCv33::iglSetaLuzPonto       (unsigned int Id ,
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
    CIMTVetor4 Pos;
    Pos.x = pos.x;
    Pos.y = pos.y;
    Pos.z = pos.z;
    Pos.w = 1.0f;
    pGL->glLightfv(Id, GL_AMBIENT              , CorAmbiente);
    pGL->glLightfv(Id, GL_DIFFUSE              , CorDifusa  );
    pGL->glLightfv(Id, GL_SPECULAR             , CorSpecular);
    pGL->glLightfv(Id, GL_POSITION             , Pos);
    pGL->glLightf (Id, GL_SPOT_CUTOFF          , 180.0f);
    pGL->glLightf (Id, GL_CONSTANT_ATTENUATION , AtenuacaoConstante);
    pGL->glLightf (Id, GL_LINEAR_ATTENUATION   , AtenuacaoLinear);
    pGL->glLightf (Id, GL_QUADRATIC_ATTENUATION, AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctionsPCv33::iglSetaLuzDirecional  (unsigned int Id,
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
    CIMTVetor4 Dir;

    Dir.x = -dir.x;
    Dir.y = -dir.y;
    Dir.z = -dir.z;
    Dir.w = 0.0f;

    pGL->glLightfv(Id, GL_AMBIENT , CorAmbiente);
    pGL->glLightfv(Id, GL_DIFFUSE , CorDifusa  );
    pGL->glLightfv(Id, GL_SPECULAR, CorSpecular);
    pGL->glLightfv(Id, GL_POSITION, Dir);
    return true;
}

bool CIGLFunctionsPCv33::iglSetaLuzSpot        (unsigned int Id,
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
    if(CutOff!=180.0f)
    {
       CutOff=180.0f;
    }
    pGL->glLightfv(Id, GL_AMBIENT              , CorAmbiente);
    pGL->glLightfv(Id, GL_DIFFUSE              , CorDifusa  );
    pGL->glLightfv(Id, GL_SPECULAR             , CorSpecular);
    pGL->glLightfv(Id, GL_POSITION             , pos);
    pGL->glLightfv(Id, GL_SPOT_DIRECTION       , dir);
    pGL->glLightf (Id, GL_SPOT_EXPONENT        , Expoente);
    pGL->glLightf (Id, GL_SPOT_CUTOFF          , CutOff);
    pGL->glLightf (Id, GL_CONSTANT_ATTENUATION , AtenuacaoConstante );
    pGL->glLightf (Id, GL_LINEAR_ATTENUATION   , AtenuacaoLinear    );
    pGL->glLightf (Id, GL_QUADRATIC_ATTENUATION, AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctionsPCv33::iglSetaVisPerspectiva(float ValorProx   ,
                                               float ValorDist   ,
                                               int   ValorAltura ,
                                               int   ValorLargura,
                                               float FOV         )
{
    CIMTMatriz Look;
    GLfloat Aspecto = (GLfloat)ValorAltura/(GLfloat)ValorLargura;

    pGL->glViewport(0, 0, ValorAltura, ValorLargura);
    pGL->glMatrixMode(GL_PROJECTION);
    pGL->glLoadIdentity();

    Look.SetPerspectiveFovRH(FOV/2,Aspecto,ValorProx,ValorDist);

    pGL->glMatrixMode(GL_MODELVIEW);
    pGL->glLoadIdentity();
    return true;
}

bool CIGLFunctionsPCv33::iglSetaVisOrtogonal(float ValorProx,
                                             float ValorDist,
                                             int   ValorAltura,
                                             int   ValorLargura)
{
    qWarning() << "Função iglSetaVisOrtogonal Não Implementada em versoes anteriores a 4.0.";
    return false;
}

bool CIGLFunctionsPCv33::iglSetaLookAt(CIMTVetor Pos, CIMTVetor View, CIMTVetor Up)
{
    CIMTMatriz Look;
    Look.SetLookAtRH(Pos,View,Up);
    pGL->glLoadMatrixf(Look);
    return true;
}

bool CIGLFunctionsPCv33::iglSetaUniformInt(GLchar *nome,int vlr)
{
    qWarning() << "Função iglSetaUniformInt Não Suportado por versoes anteriores a 3.1.";
    return false;
}

bool CIGLFunctionsPCv33::iglSetaUniformMatrix(CIMTMatriz mtx)
{
    qWarning() << "Função iglSetaUniformMatrix Não Suportado por versoes anteriores a 2.0.";
    return false;
}

bool CIGLFunctionsPCv33::iglCalculaPVMMatrix(CIMTMatriz mtx,CIMTMatriz &resmtx)
{
    mIGLPVMMatrix = mIGLProjectionMatrix * mIGLViewMatrix * mtx;
    resmtx = mIGLPVMMatrix;
    return true;
}

bool CIGLFunctionsPCv33::iglPegaPVMMatrix(CIMTMatriz &resmtx)
{
    resmtx = mIGLPVMMatrix;
    return true;
}

bool CIGLFunctionsPCv33::iglInitBuffers( VertexData   *VertexBuffer  ,
                                         GLuint       *VertexIndices ,
                                         long          QtdVertices   ,
                                         long          QtdIndices    ,
                                         GLuint        vboIds[]      ,
                                         GLuint        qryIds[]      )
{
    qWarning() << "Função iglInitBuffers Não Suportado por versoes anteriores a 1.5.";
    return false;
}

bool CIGLFunctionsPCv33::iglSuportaShaders()
{
   return bIGLSuportaShaders;
}

bool CIGLFunctionsPCv33::iglSuportaFeedback()
{
   return bIGLSuportaFeedback;
}

bool CIGLFunctionsPCv33::iglAddShader(QString pi3dNomeShader, int pShaderType)
{
   return false;
}

bool CIGLFunctionsPCv33::iglCompile()
{
   return false;
}

bool CIGLFunctionsPCv33::iglPegaIdLuz(GLenum       &ThisGLLight    ,
                                      int           IdLuz          ,
                                      bool          bHabilita      )
{
    ThisGLLight = GL_LIGHT0 + IdLuz;

    if(bHabilita)
    {
       iglEnable(ThisGLLight);
    }
    return true;
}

bool CIGLFunctionsPCv33::iglColormaterial(bool bHabilita)
{
    if(bHabilita)
    {
       iglEnable(GL_COLOR_MATERIAL);
    }
    else
    {
       iglDisable(GL_COLOR_MATERIAL);
    }
    return true;
}

bool CIGLFunctionsPCv33::iglTextureST(bool bHabilita)
{
    if(bHabilita)
    {
       iglEnable(GL_TEXTURE_GEN_S);
       iglEnable(GL_TEXTURE_GEN_T);
    }
    else
    {
       iglDisable(GL_TEXTURE_GEN_S);
       iglDisable(GL_TEXTURE_GEN_T);
    }
    return true;
}

bool CIGLFunctionsPCv33::iglQuads()
{
    iglBegin(GL_QUADS);
    return true;
}

bool CIGLFunctionsPCv33::iglPolygons()
{
    iglBegin(GL_POLYGON);
    return true;
}

#endif
