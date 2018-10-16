#include "Scene.h"

int SceneCreate(TScene *pScene,
                unsigned int nshape, unsigned int nmaterial, unsigned int ntexture, unsigned int nprimitive)
{
    //Initialise les parametres de la scene
    pScene->m_Material.m_NumberMax=0;
    pScene->m_Material.m_Number=0;
    pScene->m_Material.m_pMaterial=NULL;
    if(!SceneResizeMaterialList(pScene,nmaterial))
    {
        printf("#Error SceneCreate : can not initialize material list.\n");
        return 0;
    }

    pScene->m_Primitive.m_NumberMax=0;
    pScene->m_Primitive.m_Number=0;
    pScene->m_Primitive.m_pPrimitive=NULL;
    if(!SceneResizeGeometricPrimitiveList(pScene,nprimitive))
    {
        printf("#Error SceneCreate : can not initialize primitive list.\n");
        return 0;
    }

    pScene->m_Shape.m_NumberMax=0;
    pScene->m_Shape.m_Number=0;
    pScene->m_Shape.m_pShape=NULL;
    if(!SceneResizeShapeList(pScene,nshape))
    {
        printf("#Error SceneCreate : can not initialize shape list.\n");
        return 0;
    }

    pScene->m_Texture.m_NumberMax=0;
    pScene->m_Texture.m_Number=0;
    pScene->m_Texture.m_pTexture=NULL;
    if(!SceneResizeTextureList(pScene,ntexture))
    {
        printf("#Error SceneCreate : can not initialize texture list.\n");
        return 0;
    }

    return 1;
}

void SceneDelete(TScene *pScene){
    unsigned int i;
    for(i=0; i<pScene->m_Material.m_Number; i++)
        MaterialDelete(&pScene->m_Material.m_pMaterial[i]);
    free(pScene->m_Material.m_pMaterial);

    for(i=0; i<pScene->m_Primitive.m_Number; i++)
        GeometricPrimitiveDelete(&pScene->m_Primitive.m_pPrimitive[i]);
    free(pScene->m_Primitive.m_pPrimitive);

    for(i=0; i<pScene->m_Shape.m_Number; i++)
        VBOShapeDelete(&pScene->m_Shape.m_pShape[i]);
    free(pScene->m_Shape.m_pShape);

    for(i=0; i<pScene->m_Texture.m_Number; i++)
        TextureDelete(&pScene->m_Texture.m_pTexture[i]);
    free(pScene->m_Texture.m_pTexture);
}

unsigned int SceneGetNewShape(TScene *pScene, TVBOShape **pshape){
    if(pScene==NULL)
    {
        printf("#Error SceneGetNewShape : pScene=NULL.\n");
        return SCENE_GET_DATA_ERROR;
    }
    if(pScene->m_Shape.m_Number==pScene->m_Shape.m_NumberMax &&
       !SceneResizeShapeList(pScene,pScene->m_Shape.m_NumberMax*2))
    {
        printf("#Error SceneGetNewShape : can not resize shape list.\n");
        return SCENE_GET_DATA_ERROR;
    }
    unsigned int id=pScene->m_Shape.m_Number;
    *pshape=&pScene->m_Shape.m_pShape[id];
    pScene->m_Shape.m_Number++;
    return id;
}

unsigned int SceneGetNewMaterial(TScene *pScene, TMaterial **pmaterial){
    if(pScene==NULL)
    {
        printf("#Error SceneGetNewMaterial : pScene=NULL.\n");
        return SCENE_GET_DATA_ERROR;
    }
    if(pScene->m_Material.m_Number==pScene->m_Material.m_NumberMax &&
       !SceneResizeMaterialList(pScene,pScene->m_Material.m_NumberMax*2))
    {
        printf("#Error SceneGetNewMaterial : can not resize material list.\n");
        return SCENE_GET_DATA_ERROR;
    }
    unsigned int id=pScene->m_Material.m_Number;
    *pmaterial=&pScene->m_Material.m_pMaterial[id];
    pScene->m_Material.m_Number++;
    return id;
}

unsigned int SceneGetNewTexture(TScene *pScene, TTexture **ptexture){
    if(pScene==NULL)
    {
        printf("#Error SceneGetNewTexture : pScene=NULL.\n");
        return SCENE_GET_DATA_ERROR;
    }
    if(pScene->m_Texture.m_Number==pScene->m_Texture.m_NumberMax &&
       !SceneResizeTextureList(pScene,pScene->m_Texture.m_NumberMax*2))
    {
        printf("#Error SceneGetNewTexture : can not resize texture list.\n");
        return SCENE_GET_DATA_ERROR;
    }
    unsigned int id=pScene->m_Texture.m_Number;
    *ptexture=&pScene->m_Texture.m_pTexture[id];
    pScene->m_Texture.m_Number++;
    return id;
}

unsigned int SceneGetNewGeometricPrimitive(TScene *pScene, TGeometricPrimitive **pprimitive){
    if(pScene==NULL)
    {
        printf("#Error SceneGetNewGeometricPrimitive : pScene=NULL.\n");
        return SCENE_GET_DATA_ERROR;
    }
    if(pScene->m_Primitive.m_Number==pScene->m_Primitive.m_NumberMax &&
       !SceneResizeGeometricPrimitiveList(pScene,pScene->m_Primitive.m_NumberMax*2))
    {
        printf("#Error SceneGetNewGeometricPrimitive : can not resize primitive list.\n");
        return SCENE_GET_DATA_ERROR;
    }
    unsigned int id=pScene->m_Primitive.m_Number;
    *pprimitive=&pScene->m_Primitive.m_pPrimitive[id];
    pScene->m_Primitive.m_Number++;
    return id;
}

int SceneGetShape(TScene *pScene, TVBOShape **pshape, unsigned int id){
    if(pScene->m_Shape.m_Number<=id)
    {
        printf("#Error SceneGetShape : shape not exist.\n");
        return 0;
    }
    *pshape=&pScene->m_Shape.m_pShape[id];
    return 1;
}

int SceneGetMaterial(TScene *pScene, TMaterial **pmaterial, unsigned int id){
    if(pScene->m_Material.m_Number<=id)
    {
        printf("#Error SceneGetMaterial : material not exist.\n");
        return 0;
    }
    *pmaterial=&pScene->m_Material.m_pMaterial[id];
    return 1;
}

int SceneGetTexture(TScene *pScene, TTexture **ptexture, unsigned int id){
    if(pScene->m_Texture.m_Number<=id)
    {
        printf("#Error SceneGetTexture : texture not exist.\n");
        return 0;
    }
    *ptexture=&pScene->m_Texture.m_pTexture[id];
    return 1;
}

int SceneGetGeometricPrimitive(TScene *pScene, TGeometricPrimitive **pprimitive, unsigned int id){
    if(pScene->m_Primitive.m_Number<=id)
    {
        printf("#Error SceneGetGeometricPrimitive : primitive not exist.\n");
        return 0;
    }
    *pprimitive=&pScene->m_Primitive.m_pPrimitive[id];
    return 1;
}

int SceneGetGeometricPrimitiveByPickingID(TScene *pScene, TGeometricPrimitive **pprimitive, unsigned int id){
    int primId;
    for(primId = 0; primId < pScene->m_Primitive.m_Number; primId++){
        if(pScene->m_Primitive.m_pPrimitive[primId].m_IDPicking == id){
            *pprimitive = &pScene->m_Primitive.m_pPrimitive[primId];
            return 0;
        }
    }
    printf("#Error SceneGetGeometricPrimitive : failed to find primitive with ID %d.\n", id);
    return 1;
}


inline unsigned int SceneGetShapeNumber(TScene *pScene){
    return pScene->m_Shape.m_Number;
}

inline unsigned int SceneGetMaterialNumber(TScene *pScene){
    return pScene->m_Material.m_Number;
}

inline unsigned int SceneGetTextureNumber(TScene *pScene){
    return pScene->m_Texture.m_Number;
}

inline unsigned int SceneGetGeometricPrimitiveNumber(TScene *pScene){
    return pScene->m_Primitive.m_Number;
}

void SceneSortTransparentGeometricPrimitive(TScene *pScene){
    unsigned int nbprim=pScene->m_Primitive.m_Number;
    if(!nbprim)
        return;
    unsigned int lasttranparent=0;
    TSceneMaterial *plistmat=&pScene->m_Material;
    TMaterial *pmat=plistmat->m_pMaterial;
    TSceneGeometricPrimitive *plistprim=&pScene->m_Primitive;
    TGeometricPrimitive *pprim=plistprim->m_pPrimitive;
    //Cherche la premiere primitive non transparente
    while(lasttranparent<nbprim &&
          MaterialIsTransparent(pmat+pprim[lasttranparent].m_IdMaterial))
    {
        lasttranparent++;
    }
    //Place toutes les primitives transparentes au debut de la liste
    //(inverse du rendu)
    while(nbprim>lasttranparent)
    {
        nbprim--;
        if(MaterialIsTransparent(pmat+pprim[nbprim].m_IdMaterial))//SWAP
        {
            SceneSwapGeometricPrimitive(pScene,nbprim,lasttranparent);
            lasttranparent++;
        }
    }
}

inline unsigned int SceneGetTranparentGeometricPrimitiveNumber(TScene *pScene){
    unsigned int nbprim=pScene->m_Primitive.m_Number;
    if(!nbprim)
        return 0;
    unsigned int lasttranparent=0;
    TSceneMaterial *plistmat=&pScene->m_Material;
    TMaterial *pmat=plistmat->m_pMaterial;
    TSceneGeometricPrimitive *plistprim=&pScene->m_Primitive;
    TGeometricPrimitive *pprim=plistprim->m_pPrimitive;
    while(lasttranparent<nbprim &&
          MaterialIsTransparent(pmat+pprim[lasttranparent].m_IdMaterial))
    {
        lasttranparent++;
    }
    return lasttranparent;
}

void SceneSwapGeometricPrimitive(TScene *pScene, unsigned int p0, unsigned int p1){
    TSceneGeometricPrimitive *plistprim=&pScene->m_Primitive;
    TGeometricPrimitive *pprim=plistprim->m_pPrimitive;
    TGeometricPrimitive ptmp;
    GeometricPrimitiveCopy(&ptmp,pprim+p0);
    GeometricPrimitiveCopy(pprim+p0,pprim+p1);
    GeometricPrimitiveCopy(pprim+p1,&ptmp);
}

unsigned int SceneGetGeometricPrimitiveTriangleNumber(TScene *pScene, unsigned int p){
    TSceneGeometricPrimitive *plistprim=&pScene->m_Primitive;
    TGeometricPrimitive *pprim=plistprim->m_pPrimitive+p;
    TVBOShape *pshape=pScene->m_Shape.m_pShape+pprim->m_IdShape;
    return VBOShapeGetTriangleNumber(pshape);
}

/// ////////////////////
/// INTERNAL FUNCTIONS
/// ////////////////////
int SceneResizeShapeList(TScene *pScene, unsigned int nshape){
    TSceneShape olddata=pScene->m_Shape;
    //Allocation des donnees
    pScene->m_Shape.m_NumberMax=nshape;
    pScene->m_Shape.m_pShape=malloc(nshape*sizeof(TVBOShape));
    if(pScene->m_Shape.m_pShape==NULL)
    {
        printf("#Error SceneResizeShapeList : can not allocate new list.\n");
        pScene->m_Shape.m_NumberMax=0;
        return 0;
    }
    if(olddata.m_NumberMax==0)//Nouvelle allocation
        pScene->m_Shape.m_Number=0;
    else    //Changement de taille
    {
        pScene->m_Shape.m_Number=olddata.m_Number;
        //Recopie des anciennes valeurs
        unsigned int i;
        for(i=0; i<olddata.m_Number; i++)
            VBOShapeCopy(&pScene->m_Shape.m_pShape[i],&olddata.m_pShape[i]);
        //Supprime l'ancienne allocation
        free(olddata.m_pShape);
    }
    return 1;
}

int SceneResizeMaterialList(TScene *pScene, unsigned int nmaterial){
    TSceneMaterial olddata=pScene->m_Material;
    //Allocation des donnees
    pScene->m_Material.m_NumberMax=nmaterial;
    pScene->m_Material.m_pMaterial=malloc(nmaterial*sizeof(TMaterial));
    if(pScene->m_Material.m_pMaterial==NULL)
    {
        printf("#Error SceneResizeMaterialList : can not allocate new list.\n");
        pScene->m_Material.m_NumberMax=0;
        return 0;
    }
    if(olddata.m_NumberMax==0)
        pScene->m_Material.m_Number=0;
    else
    {
        pScene->m_Material.m_Number=olddata.m_Number;
        unsigned int i;
        for(i=0; i<olddata.m_Number; i++)
            MaterialCopy(&pScene->m_Material.m_pMaterial[i],&olddata.m_pMaterial[i]);
        free(olddata.m_pMaterial);
    }
    return 1;
}

int SceneResizeTextureList(TScene *pScene, unsigned int ntexture){
    TSceneTexture olddata=pScene->m_Texture;
    //Allocation des donnees
    pScene->m_Texture.m_NumberMax=ntexture;
    pScene->m_Texture.m_pTexture=malloc(ntexture*sizeof(TTexture));
    if(pScene->m_Texture.m_pTexture==NULL)
    {
        printf("#Error SceneResizeTextureList : can not allocate new list.\n");
        pScene->m_Texture.m_NumberMax=0;
        return 0;
    }
    if(olddata.m_NumberMax==0)
        pScene->m_Texture.m_Number=0;
    else
    {
        pScene->m_Texture.m_Number=olddata.m_Number;
        unsigned int i;
        for(i=0; i<olddata.m_Number; i++)
            TextureCopy(&pScene->m_Texture.m_pTexture[i],&olddata.m_pTexture[i]);
        free(olddata.m_pTexture);
    }
    return 1;
}

int SceneResizeGeometricPrimitiveList(TScene *pScene, unsigned int nprimitive){
    TSceneGeometricPrimitive olddata=pScene->m_Primitive;
    //Allocation des donnees
    pScene->m_Primitive.m_NumberMax=nprimitive;
    pScene->m_Primitive.m_pPrimitive=malloc(nprimitive*sizeof(TGeometricPrimitive));
    if(pScene->m_Primitive.m_pPrimitive==NULL)
    {
        printf("#Error SceneResizeGeometricPrimitiveList : can not allocate new list.\n");
        pScene->m_Primitive.m_NumberMax=0;
        return 0;
    }
    if(olddata.m_NumberMax==0)
        pScene->m_Primitive.m_Number=0;
    else
    {
        pScene->m_Primitive.m_Number=olddata.m_Number;
        unsigned int i;
        for(i=0; i<olddata.m_Number; i++)
            GeometricPrimitiveCopy(&pScene->m_Primitive.m_pPrimitive[i],&olddata.m_pPrimitive[i]);
        free(olddata.m_pPrimitive);
    }
    return 1;
}
