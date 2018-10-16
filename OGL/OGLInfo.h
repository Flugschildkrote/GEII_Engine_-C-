#if !defined(OGLINFO_H)
#define OGLINFO_H

#include <GL\gl.h>

#include <stdio.h>

//Test des erreurs avec openGL
#define OPENGL_CHECK_ERROR(str)                                    \
{                                                                  \
    GLenum error;                                                  \
    if((error = glGetError()) != GL_NO_ERROR)                      \
       printf("GL Error: %s (%s)\n", gluErrorString(error), str);  \
}

typedef struct{
    char*   m_Vendor;
    char*   m_Renderer;
    char*   m_Version;
    char*   m_GlslVersion;
    char**  m_Extensions;
    unsigned int m_SizeExtensions;
    int     m_RedBits;
    int     m_GreenBits;
    int     m_BlueBits;
    int     m_AlphaBits;
    int     m_DepthBits;
    int     m_StencilBits;
    int     m_MaxTextureSize;
    int     m_MaxLights;
    int     m_MaxAttribStacks;
    int     m_MaxModelViewStacks;
    int     m_MaxProjectionStacks;
    int     m_MaxClipPlanes;
    int     m_MaxTextureStacks;
}TOGLInfo;

void OGLInfoGet(TOGLInfo* pinfo);

void OGLInfoDelete(TOGLInfo* pinfo);

void OGLInfoPrint(TOGLInfo* pinfo);

int OGLInfoIsExtensionSupported(TOGLInfo* pinfo, const char* sext);
int OGLInfoGetShaderVersion(TOGLInfo* pinfo);

#endif //OGLINFO_H
