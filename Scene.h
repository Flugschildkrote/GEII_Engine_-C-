#if !defined(SCENE_H)
#define SCENE_H

#include "shape\VBOShape.h"
#include "Material.h"
#include "Texture.h"
#include "GeometricPrimitive.h"

#define SCENE_GET_DATA_ERROR ((unsigned int)(-1))

///La liste des formes
typedef struct
{
    TVBOShape *m_pShape;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TSceneShape;

///La liste des materiaux
typedef struct
{
    TMaterial *m_pMaterial;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TSceneMaterial;

///La liste des textures
typedef struct
{
    TTexture *m_pTexture;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TSceneTexture;

///La liste de primitive
typedef struct
{
    TGeometricPrimitive *m_pPrimitive;
    unsigned int m_NumberMax;
    unsigned int m_Number;
}TSceneGeometricPrimitive;

///Le contenu de la scene
typedef struct
{
    TSceneShape                 m_Shape;
    TSceneMaterial              m_Material;
    TSceneTexture               m_Texture;
    TSceneGeometricPrimitive    m_Primitive;
}TScene;

int SceneCreate(TScene *pScene,
                unsigned int nshape, unsigned int nmaterial, unsigned int ntexture, unsigned int nprimitive);

void SceneDelete(TScene *pScene);

unsigned int SceneGetNewShape(TScene *pScene, TVBOShape **pshape);
unsigned int SceneGetNewMaterial(TScene *pScene, TMaterial **pmaterial);
unsigned int SceneGetNewTexture(TScene *pScene, TTexture **ptexture);
unsigned int SceneGetNewGeometricPrimitive(TScene *pScene, TGeometricPrimitive **pprimitive);

int SceneGetShape(TScene *pScene, TVBOShape **pshape, unsigned int id);
int SceneGetMaterial(TScene *pScene, TMaterial **pmaterial, unsigned int id);
int SceneGetTexture(TScene *pScene, TTexture **ptexture, unsigned int id);
int SceneGetGeometricPrimitive(TScene *pScene, TGeometricPrimitive **pprimitive, unsigned int id);
int SceneGetGeometricPrimitiveByPickingID(TScene *pScene, TGeometricPrimitive **pprimitive, unsigned int id);

unsigned int SceneGetShapeNumber(TScene *pScene);
unsigned int SceneGetMaterialNumber(TScene *pScene);
unsigned int SceneGetTextureNumber(TScene *pScene);
unsigned int SceneGetGeometricPrimitiveNumber(TScene *pScene);

void SceneSortTransparentGeometricPrimitive(TScene *pScene);
unsigned int SceneGetTranparentGeometricPrimitiveNumber(TScene *pScene);

void SceneSwapGeometricPrimitive(TScene *pScene, unsigned int p0, unsigned int p1);

unsigned int SceneGetGeometricPrimitiveTriangleNumber(TScene *pScene, unsigned int p);

/// ////////////////////
/// INTERNAL FUNCTIONS
/// ////////////////////
int SceneResizeShapeList(TScene *pScene, unsigned int nshape);
int SceneResizeMaterialList(TScene *pScene, unsigned int nmaterial);
int SceneResizeTextureList(TScene *pScene, unsigned int ntexture);
int SceneResizeGeometricPrimitiveList(TScene *pScene, unsigned int nprimitive);

#endif //SCENE_H
