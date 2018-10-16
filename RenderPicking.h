#ifndef RENDERPICKING_H
#define RENDERPICKING_H

#include "OGL\OGLShader.h"
#include "Scene.h"
#include "Camera.h"

typedef struct
{
    GLint m_IDModelMatrix; // Position de l'objet
    GLint m_IDMVPMatrix; // Projection*Vue*Position de l'objet
    GLint m_IDKd; // Couleur diffuse
}TRenderPickingUniforms;

typedef struct
{
    TShaderProgram m_ProgramShader;     //Vertex et fragment shader pour faire le rendu.
    unsigned int  m_IDWhiteTexture;            //La texture pour les primitives sans texture
    TRenderPickingUniforms m_ShaderUniforms;   //Les variables pour le shader
}TRenderPicking;

int RenderPickingInitialize(TRenderPicking *prender, TScene *pscene);

void RenderPickingDelete(TRenderPicking *prender);

int RenderPickingDraw(TRenderPicking *prender, TScene *pScene, TCamera *pcamera);

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int RenderPickingInitializeUniforms(TRenderPicking *prender);

#endif // RENDERPICKING_H
