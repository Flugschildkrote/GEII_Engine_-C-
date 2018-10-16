#include "Render.h"


/// ////////////////////
/// PROGRAM SHADER
/// ////////////////////
static const char* FSSrcPhong = { // Fragment Shader
    "#version 330 core\n\
    \n\
    layout (location = 0) out vec4 color;\n\
    \n\
    in vec3 vs_worldpos;\n\
    in vec3 vs_normal;\n\
    in vec2 vs_texcoord;\n\
    \n\
    uniform vec3 color_Kd = vec3(0.9,0.0,0.0);\n\
    uniform vec3 color_Ks = vec3(0.0,0.0,0.0);\n\
    uniform float color_Ns = 1.0f;\n\
    uniform float color_Alpha = 1.0f;\n\
    uniform sampler2D texture_sampler;\n\
    \n\
    uniform vec3 worldlight_pos = vec3(10.0,20.0,10.0);\n\
    uniform vec3 light_power = vec3(1.0,1.0,1.0);\n\
    uniform vec3 light_ambient = vec3(0.2,0.2,0.2);\n\
    \n\
    uniform vec3 worldeye_pos = vec3(1.0,0.0,0.0);\n\
    \n\
    void main(void)\n\
    {\n\
        vec3 light_direction=normalize(worldlight_pos-vs_worldpos);\n\
        vec3 normal=normalize(vs_normal);\n\
        vec3 eye=worldeye_pos;\n\
        vec3 half_vector=normalize(-reflect(light_direction,normal));\n\
        float diffuse = max(0.0, dot(normal, light_direction));\n\
        float specular = pow(max(0.0, dot(half_vector,eye)), color_Ns);\n\
        vec4 tex=texture(texture_sampler,vs_texcoord);\n\
        vec4 colorambient=tex*vec4(color_Kd*light_ambient,color_Alpha);\n\
        vec4 colorlight=tex*vec4((diffuse * color_Kd + specular * color_Ks)*light_power,color_Alpha);\n\
        color = colorambient+colorlight;\n\
    }\n\
    "};

static const char* VSSrcPhong = { // Vertex Shader
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
        vs_normal = (model_matrix*vec4(normal,0.0)).xyz; //only without scale factor!\n\
        vs_texcoord = texture;\n\
    }\n\
    "};

/// ////////////////////
/// RENDER FUNCTIONS
/// ////////////////////
int RenderInitialize(TRender *prender, TScene *pscene){
//Cree un shader program pour le rendu
    //Fragment shader
    TShaderData pfs;
    OGLShaderCreate(&pfs,GL_FRAGMENT_SHADER);
    if(!OGLShaderLoadFromMemory(&pfs,FSSrcPhong))
    {
        printf("#Error RenderInitialize : can't create fragment shader.\n");
        return 0;
    }
    if(!OGLShaderCreateAndCompile(&pfs))
    {
        printf("#Error RenderInitialize : can't compile fragment shader.\n");
        return 0;
    }
    //vertex shader
    TShaderData pvs;
    OGLShaderCreate(&pvs,GL_VERTEX_SHADER);
    if(!OGLShaderLoadFromMemory(&pvs,VSSrcPhong))
    {
        printf("#Error RenderInitialize : can't create vertex shader.\n");
        return 0;
    }
    if(!OGLShaderCreateAndCompile(&pvs))
    {
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
    if(!RenderInitializeUniforms(prender))
    {
        printf("#Error RenderInitialize : can't initialize uniforms for program shader.\n");
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
    vec3f lamb={0.1f,0.1f,0.1f};
    vec3f lpower={0.8f,0.9f,0.7f};
    vec3f lpos={0.0f,0.0f,0.0f};
    if(!LightCreate(&prender->m_Light,lamb,lpower,lpos))
    {
        printf("#Error RenderInitialize: can not create a light.\n");
        return 0;
    }
    return 1;
}

void RenderDelete(TRender *prender){
    OGLShaderProgramDelete(&prender->m_ProgramShader);
}

int RenderDraw(TRender *prender, TScene *pScene, TCamera *pcamera){
    TShaderProgram *pshader=&prender->m_ProgramShader;
    TRenderUniforms *puniforms=&prender->m_ShaderUniforms;
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

//Gestion de la lumiere
    OGLShaderProgramSetVec3fv(puniforms->m_IDLightPosition,prender->m_Light.m_Position);
    OGLShaderProgramSetVec3fv(puniforms->m_IDLightPower,prender->m_Light.m_Power);
    OGLShaderProgramSetVec3fv(puniforms->m_IDLightAmbient,prender->m_Light.m_Ambient);
//Le point de vue
    vec3f eye;
    Vec3fCopy(eye,pcamera->m_PEye);
    Vec3fNormalize(eye);
    OGLShaderProgramSetVec3fv(puniforms->m_IDEyePosition,eye);
//Fixe l'unitee de texture
    OGLShaderProgramSetTextureUnit(puniforms->m_IDTexture,0);
    glActiveTexture(GL_TEXTURE0);
//La texture blanche
    TTexture *pTexWhite;
    SceneGetTexture(pScene,&pTexWhite,prender->m_IDWhiteTexture);
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
    OGLShaderProgramSet1f(puniforms->m_IDAlpha,1.0f);
    while(nbprim>nbtprim)
    {
        nbprim--;
        pprim=&plistprim->m_pPrimitive[nbprim];
        //Fixe la matrice mvp
        Matrix4x4fMul2(mmvp,mpv,pprim->m_OtoW);
        OGLShaderProgramSetMatrix4fv(puniforms->m_IDMVPMatrix,mmvp);
        OGLShaderProgramSetMatrix4fv(puniforms->m_IDModelMatrix,pprim->m_OtoW);
        //Fixe les parametres du materiau
        pmat=&plistmat->m_pMaterial[pprim->m_IdMaterial];
        OGLShaderProgramSetVec3fv(puniforms->m_IDKd,pmat->m_Kd);
        OGLShaderProgramSetVec3fv(puniforms->m_IDKs,pmat->m_Ks);
        OGLShaderProgramSet1f(puniforms->m_IDNs,pmat->m_Ns);
        if(pmat->m_IdTexture==MATERIAL_NOT_TEXTURE)
            glBindTexture(GL_TEXTURE_2D,*pTexWhite);
        else
            glBindTexture(GL_TEXTURE_2D,plisttex->m_pTexture[pmat->m_IdTexture]);
        //Dessine la forme
        pshape=&plistshape->m_pShape[pprim->m_IdShape];
        VBOShapeDraw(pshape);
    }
//Les primitives transparentes
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    while(nbtprim--)
    {
        pprim=&plistprim->m_pPrimitive[nbtprim];
        //Fixe la matrice mvp
        Matrix4x4fMul2(mmvp,mpv,pprim->m_OtoW);
        OGLShaderProgramSetMatrix4fv(puniforms->m_IDMVPMatrix,mmvp);
        OGLShaderProgramSetMatrix4fv(puniforms->m_IDModelMatrix,pprim->m_OtoW);
        //Fixe les parametres du materiau
        pmat=&plistmat->m_pMaterial[pprim->m_IdMaterial];
        OGLShaderProgramSetVec3fv(puniforms->m_IDKd,pmat->m_Kd);
        OGLShaderProgramSetVec3fv(puniforms->m_IDKs,pmat->m_Ks);
        OGLShaderProgramSet1f(puniforms->m_IDNs,pmat->m_Ns);
        OGLShaderProgramSet1f(puniforms->m_IDAlpha,pmat->m_Alpha);
        if(pmat->m_IdTexture==MATERIAL_NOT_TEXTURE)
            glBindTexture(GL_TEXTURE_2D,*pTexWhite);
        else
            glBindTexture(GL_TEXTURE_2D,plisttex->m_pTexture[pmat->m_IdTexture]);
        //Dessine la forme
        pshape=&plistshape->m_pShape[pprim->m_IdShape];
        VBOShapeDraw(pshape);
    }
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
//Fin de l'utilisation du program shader
    OGLShaderProgramUnBind();
    return 1;
}

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int RenderInitializeUniforms(TRender *prender){
    TRenderUniforms *puniforms=&prender->m_ShaderUniforms;
    TShaderProgram *pprog=&prender->m_ProgramShader;
    puniforms->m_IDModelMatrix=OGLShaderProgramGetUniformLocation(pprog,"model_matrix");
    if(puniforms->m_IDModelMatrix==-1)
    {
        printf("#Error RenderInitializeUniforms : model_matrix not found.\n");
        return 0;
    }
    puniforms->m_IDMVPMatrix=OGLShaderProgramGetUniformLocation(pprog,"mvp_matrix");
    if(puniforms->m_IDMVPMatrix==-1)
    {
        printf("#Error RenderInitializeUniforms : mvp_matrix not found.\n");
        return 0;
    }
    puniforms->m_IDKd=OGLShaderProgramGetUniformLocation(pprog,"color_Kd");
    if(puniforms->m_IDKd==-1)
    {
        printf("#Error RenderInitializeUniforms : color_Kd not found.\n");
        return 0;
    }
    puniforms->m_IDKs=OGLShaderProgramGetUniformLocation(pprog,"color_Ks");
    if(puniforms->m_IDKs==-1)
    {
        printf("#Error RenderInitializeUniforms : color_Ks not found.\n");
        return 0;
    }
    puniforms->m_IDNs=OGLShaderProgramGetUniformLocation(pprog,"color_Ns");
    if(puniforms->m_IDNs==-1)
    {
        printf("#Error RenderInitializeUniforms : color_Ns not found.\n");
        return 0;
    }
    puniforms->m_IDAlpha=OGLShaderProgramGetUniformLocation(pprog,"color_Alpha");
    if(puniforms->m_IDAlpha==-1)
    {
        printf("#Error RenderInitializeUniforms : color_Alpha not found.\n");
        return 0;
    }
    puniforms->m_IDTexture=OGLShaderProgramGetUniformLocation(pprog,"texture_sampler");
    if(puniforms->m_IDTexture==-1)
    {
        printf("#Error RenderInitializeUniforms : texture_sampler not found.\n");
        return 0;
    }
    puniforms->m_IDLightPosition=OGLShaderProgramGetUniformLocation(pprog,"worldlight_pos");
    if(puniforms->m_IDLightPosition==-1)
    {
        printf("#Error RenderInitializeUniforms : worldlight_pos not found.\n");
        return 0;
    }
    puniforms->m_IDLightPower=OGLShaderProgramGetUniformLocation(pprog,"light_power");
    if(puniforms->m_IDLightPower==-1)
    {
        printf("#Error RenderInitializeUniforms : light_power not found.\n");
        return 0;
    }
    puniforms->m_IDLightAmbient=OGLShaderProgramGetUniformLocation(pprog,"light_ambient");
    if(puniforms->m_IDLightAmbient==-1)
    {
        printf("#Error RenderInitializeUniforms : light_ambient not found.\n");
        return 0;
    }
    puniforms->m_IDEyePosition=OGLShaderProgramGetUniformLocation(pprog,"worldeye_pos");
    if(puniforms->m_IDEyePosition==-1)
    {
        printf("#Error RenderInitializeUniforms : worldeye_pos not found.\n");
        return 0;
    }
    return 1;
}

