#include "RenderPicking.h"

/// ////////////////////
/// PROGRAM SHADER
/// ////////////////////
static const char* FSSrcColor = { // Fragment Shader
    "#version 330 core\n\
    \n\
    layout (location = 0) out vec4 color;\n\
    \n\
    uniform vec3 color_Kd = vec3(0.9,0.0,0.0);\n\
    uniform sampler2D texture_sampler;\n\
    \n\
    void main(void)\n\
    {\n\
        color = vec4(color_Kd, 1.0);\n\
    }\n\
    "};

static const char* VSSrcColor = { // Vertex Shader
    "\n\
    #version 330 core\n\
    \n\
    uniform mat4 model_matrix;\n\
    uniform mat4 mvp_matrix;\n\
    //uniform mat4 normal_matrix;\n\
    \n\
    layout (location = 0) in vec3 position;\n\
    layout (location = 1) in vec3 normal;\n\
    layout (location = 2) in vec2 texture;\n\
    \n\
    out vec3 vs_worldpos;\n\
    out vec3 vs_normal;\n\
    out vec2 vs_texcoord;\n\
    \n\
    void main(void)\n\
    {\n\
        gl_Position = mvp_matrix * vec4(position,1.0);\n\
        vs_worldpos = (model_matrix*vec4(position,1.0)).xyz;\n\
        vs_texcoord = texture;\n\
    }\n\
    "};

/// ////////////////////
/// RENDER FUNCTIONS
/// ////////////////////
int RenderPickingInitialize(TRenderPicking *prender, TScene *pscene){
//Cree un shader program pour le rendu
    //Fragment shader
    TShaderData pfs;
    OGLShaderCreate(&pfs,GL_FRAGMENT_SHADER);
    if(!OGLShaderLoadFromMemory(&pfs,FSSrcColor)){
        printf("#Error RenderInitialize : can't create fragment shader.\n");
        return 0;
    }
    if(!OGLShaderCreateAndCompile(&pfs)){
        printf("#Error RenderInitialize : can't compile fragment shader.\n");
        return 0;
    }
    //vertex shader
    TShaderData pvs;
    OGLShaderCreate(&pvs,GL_VERTEX_SHADER);
    if(!OGLShaderLoadFromMemory(&pvs,VSSrcColor)){
        printf("#Error RenderInitialize : can't create vertex shader.\n");
        return 0;
    }
    if(!OGLShaderCreateAndCompile(&pvs)){
        printf("#Error RenderInitialize : can't compile vertex shader.\n");
        return 0;
    }
    //Creation du program shader
    if(!OGLShaderProgramCreate(&prender->m_ProgramShader))
    {
        printf("#Error RenderInitialize: can't create program shader.\n");
        return 0;
    }
    if(!OGLShaderProgramAttachVertexAndFragmentShader(&prender->m_ProgramShader,&pvs,&pfs))
    {
        printf("#Error RenderInitialize : can't attach shader to program.\n");
        return 0;
    }
    if(!OGLShaderProgramLink(&prender->m_ProgramShader))
    {
        printf("#Error RenderInitialize : can't link program shader.\n");
        return 0;
    }
    //Supprime les shaders
    OGLShaderDelete(&pvs);
    OGLShaderDelete(&pfs);
    //Initialise les variables du program shader
    if(!RenderPickingInitializeUniforms(prender))
    {
        printf("#Error RenderPickingInitialize : can't initialize uniforms for program shader.\n");
        return 0;
    }
//Creation de la texture blanche
    TTexture *pTex;
    prender->m_IDWhiteTexture=SceneGetNewTexture(pscene,&pTex);
    if(prender->m_IDWhiteTexture==SCENE_GET_DATA_ERROR)
    {
        printf("#Error RenderInitialize: can't get a new texture from scene.\n");
        return 0;
    }
    if(!TextureCreateWhite(pTex))
    {
        printf("#Error RenderInitialize: can't create a white texture.\n");
        return 0;
    }
//Creation de la lampe
    return 1;
}

void RenderPickingDelete(TRenderPicking *prender){
    OGLShaderProgramDelete(&prender->m_ProgramShader);
}

int RenderPickingDraw(TRenderPicking *prender, TScene *pScene, TCamera *pcamera){
    TShaderProgram *pshader=&prender->m_ProgramShader;
    TRenderPickingUniforms *puniforms=&prender->m_ShaderUniforms;
//Selectionne le program shader
    OGLShaderProgramBind(pshader);
//Les matrices view, projection
    TMatrix4x4f mproj, mview, mpv;
    CameraGetProjectionMatrix(pcamera,mproj);
    CameraGetModelViewMatrix(pcamera,mview);
    Matrix4x4fMul2(mpv,mproj,mview);

/// //////////////
///TEST POUR DEBUG
/// //////////////
//    printf("mproj : \n");
//    Matrix4x4fPrint(mproj);
//    printf("mview : \n");
//    Matrix4x4fPrint(mview);
//    printf("mpv : \n");
//    Matrix4x4fPrint(mpv);
/// //////////////
///TEST POUR DEBUG
/// //////////////

//Le point de vue
    vec3f eye;
    Vec3fCopy(eye,pcamera->m_PEye);
    Vec3fNormalize(eye);
//Fixe l'unitee de texture
//La texture blanche
//Pour chaque primitive
    int nbprim=SceneGetGeometricPrimitiveNumber(pScene);
    int nbtprim=SceneGetTranparentGeometricPrimitiveNumber(pScene);
    TSceneGeometricPrimitive *plistprim=&pScene->m_Primitive;
    TSceneShape *plistshape=&pScene->m_Shape;
    TSceneMaterial *plistmat=&pScene->m_Material;
    TSceneTexture *plisttex=&pScene->m_Texture;
    TGeometricPrimitive *pprim;
    TVBOShape *pshape;
    TMaterial *pmat;
    TMatrix4x4f mmvp;
//Les primitives non transparentes
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    while(nbprim > 0)
    {


        nbprim--;
        pprim=&plistprim->m_pPrimitive[nbprim];
        uint32_t primID = pprim->m_IDPicking;

        uint8_t rouge = (primID & 0x0000FF) ;
        uint8_t bleu = (primID & 0x00FF00) >> 8;
        uint8_t vert = (primID & 0xFF0000) >> 16;

        printf("ID_Picking : %d = %d ; %d ; %d\n", primID, rouge, vert, bleu);

        // 24 bits

        //Fixe la matrice mvp
        Matrix4x4fMul2(mmvp,mpv,pprim->m_OtoW);
        OGLShaderProgramSetMatrix4fv(puniforms->m_IDMVPMatrix,mmvp);
        OGLShaderProgramSetMatrix4fv(puniforms->m_IDModelMatrix,pprim->m_OtoW);
        //Fixe les parametres du materiau
        pmat=&plistmat->m_pMaterial[pprim->m_IdMaterial];
        vec3f vecteur3;
        vecteur3[0] = (float) rouge/255.0f;
        vecteur3[1] = (float) vert/255.0f;
        vecteur3[2] = (float) bleu/255.0f;

       // vecteur3[0] = (float) 1.0f;
       // vecteur3[1] = (float) 0.5f;
        //vecteur3[2] = (float) 0.2f;

        OGLShaderProgramSetVec3fv(puniforms->m_IDKd,vecteur3);
        /*if(pmat->m_IdTexture==MATERIAL_NOT_TEXTURE)
            glBindTexture(GL_TEXTURE_2D,*pTexWhite);
        else
            glBindTexture(GL_TEXTURE_2D,plisttex->m_pTexture[pmat->m_IdTexture]);*/
        //Dessine la forme
        pshape=&plistshape->m_pShape[pprim->m_IdShape];
        VBOShapeDraw(pshape);
    }


//Fin de l'utilisation du program shader
    OGLShaderProgramUnBind();
    return 1;
}

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int RenderPickingInitializeUniforms(TRenderPicking *prender){
    TRenderPickingUniforms *puniforms=&prender->m_ShaderUniforms;
    TShaderProgram *pprog=&prender->m_ProgramShader;
    puniforms->m_IDModelMatrix=OGLShaderProgramGetUniformLocation(pprog,"model_matrix");
    if(puniforms->m_IDModelMatrix==-1)
    {
        printf("#Error RenderPickingInitializeUniforms : model_matrix not found.\n");
        return 0;
    }
    puniforms->m_IDMVPMatrix=OGLShaderProgramGetUniformLocation(pprog,"mvp_matrix");
    if(puniforms->m_IDMVPMatrix==-1)
    {
        printf("#Error RenderPickingInitializeUniforms : mvp_matrix not found.\n");
        return 0;
    }
    puniforms->m_IDKd=OGLShaderProgramGetUniformLocation(pprog,"color_Kd");
    if(puniforms->m_IDKd==-1)
    {
        printf("#Error RenderPickingInitializeUniforms : color_Kd not found.\n");
        return 0;
    }
   /* puniforms->m_IDTexture=OGLShaderProgramGetUniformLocation(pprog,"texture_sampler");
    if(puniforms->m_IDTexture==-1)
    {
        printf("#Error RenderPickingInitializeUniforms : texture_sampler not found.\n");
        return 0;
    }*/
    return 1;
}

