#if !defined(RENDER_H)
#define RENDER_H

#include "OGL\OGLShader.h"
#include "Scene.h"
#include "Camera.h"
#include "Light.h"

typedef struct
{
    GLint m_IDModelMatrix;
    GLint m_IDMVPMatrix;
    GLint m_IDKd;
    GLint m_IDKs;
    GLint m_IDNs;
    GLint m_IDAlpha;
    GLint m_IDTexture;
    GLint m_IDLightPosition;
    GLint m_IDLightPower;
    GLint m_IDLightAmbient;
    GLint m_IDEyePosition;
}TRenderUniforms;

typedef struct
{
    TShaderProgram m_ProgramShader;     //Vertex et fragment shader pour faire le rendu.
    unsigned int  m_IDWhiteTexture;            //La texture pour les primitives sans texture
    TRenderUniforms m_ShaderUniforms;   //Les variables pour le shader
    TLight m_Light;
}TRender;

int RenderInitialize(TRender *prender, TScene *pscene);

void RenderDelete(TRender *prender);

int RenderDraw(TRender *prender, TScene *pScene, TCamera *pcamera);

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int RenderInitializeUniforms(TRender *prender);

#endif //RENDER_H
