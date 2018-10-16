#include "MainApp.h"

///FORCE L'UTILISATION DE LA CARTE NVIDIA A LA PLACE DE L'INTEL
#ifdef __cplusplus
extern "C" {
#endif
//    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
#ifdef __cplusplus
}
#endif

//Definition de la structure du programme principal
TMainApp g_mainapp;


#define ID_CUBE 1
#define ID_SPHERE 36587
#define ID_VOID 0

int MainAppInitialize(){
    //Initialise le mode de dessin
    //                    2 buffers   RGB          profondeur
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //Initialise la taille de la fenetre
    g_mainapp.m_windowsize_x=g_mainapp.m_windowsize_y=600;
    glutInitWindowSize(g_mainapp.m_windowsize_x,g_mainapp.m_windowsize_y);
    //Creation de la fenetre
    g_mainapp.m_window=glutCreateWindow("Engine3DGEII");

    //Initialise les ext. OpenGL
    TOGLInfo oglinfo;
    OGLInfoGet(&oglinfo);
    if(!OGLExtInitialize(&oglinfo))
    {
        printf("#Error MainAppInitialize : can not initialize OpenGL extensions.\n");
        return 0;
    }
    OGLInfoPrint(&oglinfo);
    OGLInfoDelete(&oglinfo);

    //La fonction pour dessiner
    glutDisplayFunc(MainAppDisplayCallback);

    //Active le buffer de pronfondeur
    glEnable(GL_DEPTH_TEST);

    //Initialise la souris
    MouseManagerInitialize(&g_mainapp.m_mouse);
    MouseManagerSetMotionFunction(MainAppMouseMotionCallback,&g_mainapp);
    MouseManaferSetButtonFunction(MainAppMouseButtonCallback,&g_mainapp);

    //Initialise le clavier
    KeyboardManagerInitialize(&g_mainapp.m_keyboard);
    KeyboardManagerSetKeyFunction(MainAppKeyboardKeyCallback,&g_mainapp);
    KeyboardManagerSetSpecialKeyFunction(MainAppKeyboardSpecialKeyCallback,&g_mainapp);

    //Initialise la camera
    vec3f eye={0.0f,0.0f,10.0f},
          center={0.0f,0.0f,0.0f},
          up={0.0f,1.0f,0.0f};
    CameraInitialize(&g_mainapp.m_camera3D,CAMERA_PERSPECTIVE,
                     g_mainapp.m_windowsize_x, g_mainapp.m_windowsize_y,
                     eye,center,up,
                     45.0f,1.0f,0.1f,200.0f);

    //Initialise la scene (fixe le nombre d'objet disponible)
    if(!SceneCreate(&g_mainapp.m_Scene,20,10,10,10))
    {
        printf("#Error MainAppInitialize : can not initialize scene.\n");
        return 0;
    }
    //Initialise le render
    if(!RenderInitialize(&g_mainapp.m_Render, &g_mainapp.m_Scene))
    {
        printf("#Error MainAppInitialize : can not initialize render.\n");
        return 0;
    }

    if(!RenderPickingInitialize(&g_mainapp.m_RenderPicking, &g_mainapp.m_Scene))
    {
        printf("#Error MainAppInitialize : can not initialize render picking.\n");
        return 0;
    }
    //Initialise la lumiere
    vec3f lamb={0.1f,0.1f,0.1f};
    vec3f lpower={0.8f,0.9f,0.7f};
    vec3f lpos={0.0f,10.0f,10.0f};
    if(!LightCreate(&g_mainapp.m_Render.m_Light,lamb,lpower,lpos))
    {
        printf("#Error MainAppInitialize : can not initialize light.\n");
        return 0;
    }
/// //////////////
///TEST POUR DEBUG
/// //////////////
//*/
///Ajouter une cube rouge dans la scene
   ///Creation d'un VBO pour la forme (stockage generique dans la carte graphique)
   //Le pointeur sur le conteneur
    TVBOShape *pshape;
    //Demande au gestionnaire de la scene un ID et une zone memoire
    unsigned int idshape=SceneGetNewShape(&g_mainapp.m_Scene,&pshape);
    //Test la validite de ID
    if(idshape==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new shape from scene.\n");
        return 0;
    }
    //Creation de la forme cube de taille 0.5
    if(!CubeCreate(pshape,0.5f))
    {
        printf("#Error MainAppInitialize : can not create a cube.\n");
        return 0;
    }
    ///Creation d'un materiau pour le cube
    //Le pointeur
    TMaterial *pmat;
    //Demande au gestionnaire de la scene un ID et une zone memoire
    unsigned int idmat=SceneGetNewMaterial(&g_mainapp.m_Scene,&pmat);
    if(idmat==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new material from scene.\n");
        return 0;
    }
    //Les parametres du materiau
    vec3f kd={1.0f,0.0f,0.0f};  //Le diffus
    vec3f ks={0.0f,1.0f,0.0f};  //Le brillant
    float ns=50.0f;             //La puissance du brillant
    //Initialise le materiau (sans texture)
    if(!MaterialCreate(pmat,kd,ks,ns,MATERIAL_NOT_TEXTURE))
    {
        printf("#Error MainAppInitialize : can not create a material.\n");
        return 0;
    }
    //Fixe la transparence du materiau
    MaterialSetTransparency(pmat,0.9f);
    ///Creation d'une primitive (forme + materiau + transformation geometrique)
    //Le pointeur
    TGeometricPrimitive *pprim;
    //Demande au gestionnaire de la scene un ID et une zone memoire
    unsigned int idprim=SceneGetNewGeometricPrimitive(&g_mainapp.m_Scene,&pprim);
    if(idprim==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new primitive from scene.\n");
        return 0;
    }
    //Creation d'une matrice de transformation pour la primitive
    //ici une translation sur l'axe X
    Matrix4x4fTranslate(pprim->m_OtoW,2.0f,0.0f,0.0f);
    //Fixe les parametres de la primitive
    pprim->m_IdShape=idshape;
    pprim->m_IdMaterial=idmat;
    pprim->m_IDPicking = ID_CUBE;

///Ajoute une sphere avec une texture
    idshape=SceneGetNewShape(&g_mainapp.m_Scene,&pshape);
    if(idshape==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new shape from scene.\n");
        return 0;
    }
    if(!SphereCreate(pshape,50,50,0.5f))
    {
        printf("#Error MainAppInitialize : can not create a sphere.\n");
        return 0;
    }
    //Ajoute un nouveau materiau
    idmat=SceneGetNewMaterial(&g_mainapp.m_Scene,&pmat);
    if(idmat==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new material from scene.\n");
        return 0;
    }
    //Une texture
    TTexture *ptex;
    unsigned int idtex=SceneGetNewTexture(&g_mainapp.m_Scene,&ptex);
    if(idtex==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new texture from scene.\n");
        return 0;
    }
    if(!TextureCreateFromFile(ptex,"./Data/earth.bmp",1024))
    {
        printf("#Error MainAppInitialize : can not create a texture.\n");
        return 0;
    }
    kd[0]=1.0;kd[1]=1.0;kd[2]=1.0;
    if(!MaterialCreate(pmat,kd,ks,ns,idtex))
    {
        printf("#Error MainAppInitialize : can not create a material.\n");
        return 0;
    }
    //Ajoute une nouvelle primitive
    idprim=SceneGetNewGeometricPrimitive(&g_mainapp.m_Scene,&pprim);
    if(idprim==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MainAppInitialize : can not get new primitive from scene.\n");
        return 0;
    }
    Matrix4x4fTranslate(pprim->m_OtoW,0.0f,0.0f,0);
    pprim->m_IdShape=idshape;
    pprim->m_IdMaterial=idmat;
    pprim->m_IDPicking = ID_SPHERE;

/*/ ///Ouverture d'un fichier Obj pour la scene
    //if(!ObjParserOpenScene("./Data/citroen_ds3/Citroen_DS3.obj",&g_mainapp.m_Scene))
    if(!ObjParserOpenScene("./Data/dabrovic-sponza/sponza.obj",&g_mainapp.m_Scene))
    {
        printf("#Error MainAppInitialize : can not open obj file.\n");
        return 0;
    }
    printf("#Info: Obj scene:\n");
    printf("\t - Shape number : %d\n",SceneGetShapeNumber(&g_mainapp.m_Scene));
    printf("\t - Material number : %d\n",SceneGetMaterialNumber(&g_mainapp.m_Scene));
    printf("\t - Texture number : %d\n",SceneGetTextureNumber(&g_mainapp.m_Scene));
    printf("\t - Primitive number : %d\n",SceneGetGeometricPrimitiveNumber(&g_mainapp.m_Scene));
    unsigned int trinum=0;
    unsigned int i;
    for(i=0; i<SceneGetGeometricPrimitiveNumber(&g_mainapp.m_Scene); i++)
        trinum+=SceneGetGeometricPrimitiveTriangleNumber(&g_mainapp.m_Scene,i);
    printf("\t - Triangle number : %d\n",trinum);
//*/
//Classe la liste des primitives pour la transparence
    SceneSortTransparentGeometricPrimitive(&g_mainapp.m_Scene);

    /// UPDATED
    g_mainapp.mPickingGeomPrimitive = NULL;
/// //////////////
///TEST POUR DEBUG
/// //////////////
    return 1;
}

void MainAppDelete(){
    RenderDelete(&g_mainapp.m_Render);
    RenderPickingDelete(&g_mainapp.m_RenderPicking);
    SceneDelete(&g_mainapp.m_Scene);
    glFinish();//Force l'exe de toutes les commandes opengl avant la fin
}


void MainAppDisplayCallback(){
//La couleur par defaut
    glClearColor(0.0f,0.0f,0.0f,1.0f);

//Efface le buffer de dessin
  //  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

///RENDU IMMEDIAT OPENGL 1.0
    //Initialise le mode de projection
    //Choix de la matrice a modifier
    glMatrixMode(GL_PROJECTION);
    //Charge une matrice identitee
    glLoadIdentity();
    TMatrix4x4f mp;
    CameraGetProjectionMatrix(&g_mainapp.m_camera3D,mp);
//    Matrix4x4fPrint(mp);
    glMultMatrixf(mp);

    //La position de visualisation
    glMatrixMode(GL_MODELVIEW);
    //Charge une matrice identitee
    glLoadIdentity();
    TMatrix4x4f mv;
    CameraGetModelViewMatrix(&g_mainapp.m_camera3D,mv);
//    Matrix4x4fPrint(mv);
    glMultMatrixf(mv);
    vec3f pos;
    Vec3fCopy(pos,g_mainapp.m_camera3D.m_PCenter);
    vec4f xcol={1.0f,0.0f,0.0f,1.0f};
    vec4f ycol={0.0f,1.0f,0.0f,1.0f};
    vec4f zcol={0.0f,0.0f,1.0f,1.0f};
    OGLDrawImmediateOrthonormal(pos,1.0f,xcol,ycol,zcol,4.0f);


    GLfloat pointsize;
    glGetFloatv(GL_POINT_SIZE,&pointsize);
    glPointSize(pointsize*8.0f);
    vec4f lcolor;
    Vec3fToVec4f(lcolor,g_mainapp.m_Render.m_Light.m_Power,1.0f);
    OGLDrawImmediatePoint(g_mainapp.m_Render.m_Light.m_Position,lcolor);
    glPointSize(pointsize);
///RENDU SHADER OPENGL >3.0
//Affiche la scene
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //RenderPickingDraw(&g_mainapp.m_RenderPicking, &g_mainapp.m_Scene, &g_mainapp.m_camera3D);
    RenderDraw(&g_mainapp.m_Render, &g_mainapp.m_Scene, &g_mainapp.m_camera3D);

//Charge le nouveau dessin
   glutSwapBuffers();


   OPENGL_CHECK_ERROR("#Error in MainAppDisplayCallback !");
   //glutPostRedisplay(); //Rendu en continu
}

void MainAppMouseButtonCallback(void* pdata){
    TMainApp *pmain=(TMainApp*)pdata;
    TMouseManager *pmouse=&pmain->m_mouse;
    int startx,starty;
    startx=pmouse->m_start_x;
    starty=pmouse->m_start_y;
    printf("Button clicked (%s), position : %d ; %d\n"  ,(pmouse->m_action==MOUSE_MANAGER_ACTION_NONE ? "Up" : "Down")
                                                        ,startx,starty);

    if(pmouse->m_action!=MOUSE_MANAGER_ACTION_NONE){
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        RenderPickingDraw(&g_mainapp.m_RenderPicking, &g_mainapp.m_Scene, &g_mainapp.m_camera3D);
        glReadPixels(startx, g_mainapp.m_windowsize_y-starty, 1,1, GL_RGBA, GL_UNSIGNED_BYTE, g_mainapp.m_pickingPixels);
        uint32_t pickingID = (g_mainapp.m_pickingPixels[0] & 0xFF) | ((g_mainapp.m_pickingPixels[2] & 0xFF) << 8) | ((g_mainapp.m_pickingPixels[1] & 0xFF) << 16);

        TGeometricPrimitive *pprim;
        if(SceneGetGeometricPrimitiveByPickingID(&g_mainapp.m_Scene, &pprim, pickingID) == 0){
            printf("Found\n");
            g_mainapp.mPickingGeomPrimitive = pprim;
        }
        else{
            printf("Not Found\n");
            g_mainapp.mPickingGeomPrimitive = NULL;
        }

        if(pickingID == ID_VOID){
            printf("Du vide\n");
        }else if(pickingID == ID_CUBE){
            printf("Click Cube\n");
        }else if(pickingID == ID_SPHERE){
            printf("Click Sphere\n");
        }
     //   printf("Pixels : %d ; %d ; %d ; %d = ID %d\n", pixels[0],pixels[1],pixels[2],pixels[3], pickingID);
    }



}

void MainAppMouseMotionCallback(void* pdata){
    TMainApp *pmain=(TMainApp*)pdata;
    TMouseManager *pmouse=&pmain->m_mouse;
    int deltax,deltay;
    deltax=pmouse->m_move_x-pmouse->m_start_x;
    deltay=pmouse->m_move_y-pmouse->m_start_y;
    if(pmouse->m_action==MOUSE_MANAGER_ACTION_LEFT)
    {
        CameraRotateTheta(&pmain->m_camera3D,((double)deltay),1.0f,179.0f);
        pmouse->m_start_y=pmouse->m_move_y;
        CameraRotatePhi(&pmain->m_camera3D,((double)deltax),-179.0f,179.0f);
        pmouse->m_start_x=pmouse->m_move_x;
    }
    else if(pmouse->m_action==MOUSE_MANAGER_ACTION_RIGHT)
    {
        CameraForwardEye(&pmain->m_camera3D,((double)deltay)/4.0f,0.5f);
        pmouse->m_start_y=pmouse->m_move_y;

    }
    else if(pmouse->m_action==MOUSE_MANAGER_ACTION_MIDDLE)
    {

    }
}

void MainAppKeyboardKeyCallback(void* pdata){
    TMainApp *pmain=(TMainApp*)pdata;
    TKeyboardManager *pkeyboard=&pmain->m_keyboard;
}

void MainAppKeyboardSpecialKeyCallback(void* pdata){
    TMainApp *pmain=(TMainApp*)pdata;
    TKeyboardManager *pkeyboard=&pmain->m_keyboard;
//Deplacement de la lampe
    TGeometricPrimitive *pprim = g_mainapp.mPickingGeomPrimitive;
    if(pprim != NULL){
        switch(pkeyboard->m_special_key){
        case GLUT_KEY_UP :
            Matrix4x4fTranslate(pprim->m_OtoW,pprim->m_OtoW[12],pprim->m_OtoW[13]+0.1f,pprim->m_OtoW[14]);
            break;
        case GLUT_KEY_DOWN :
            Matrix4x4fTranslate(pprim->m_OtoW,pprim->m_OtoW[12],pprim->m_OtoW[13]-0.1f,pprim->m_OtoW[14]);
            break;
        case GLUT_KEY_LEFT :
            Matrix4x4fTranslate(pprim->m_OtoW,pprim->m_OtoW[12]-0.1f,pprim->m_OtoW[13],pprim->m_OtoW[14]);
            break;
        case GLUT_KEY_RIGHT :
            Matrix4x4fTranslate(pprim->m_OtoW,pprim->m_OtoW[12]+0.1f,pprim->m_OtoW[13],pprim->m_OtoW[14]);
            break;
        }
    }


    if(pkeyboard->m_special_key==GLUT_KEY_UP)
    {
        if(pkeyboard->m_modifiers&KEYBOARD_MANAGER_MODIFIER_CTRL)
            CameraForward(&pmain->m_camera3D,0.2f);
        else if(pkeyboard->m_modifiers&KEYBOARD_MANAGER_MODIFIER_SHIFT)
            pmain->m_Render.m_Light.m_Position[2]+=0.2f;
        else
            pmain->m_Render.m_Light.m_Position[1]+=0.2f;

    }
    else if(pkeyboard->m_special_key==GLUT_KEY_DOWN)
    {
        if(pkeyboard->m_modifiers&KEYBOARD_MANAGER_MODIFIER_CTRL)
            CameraBackward(&pmain->m_camera3D,0.2f);
        else if(pkeyboard->m_modifiers&KEYBOARD_MANAGER_MODIFIER_SHIFT)
            pmain->m_Render.m_Light.m_Position[2]-=0.2f;
        else
            pmain->m_Render.m_Light.m_Position[1]-=0.2f;
    }
    else if(pkeyboard->m_special_key==GLUT_KEY_LEFT)
    {
        pmain->m_Render.m_Light.m_Position[0]-=0.2f;
    }
    else if(pkeyboard->m_special_key==GLUT_KEY_RIGHT)
    {
        pmain->m_Render.m_Light.m_Position[0]+=0.2f;
    }
}
