#include "OGLInfo.h"

// WGL specific extensions for v3.0+ //////////////////////////////////////////
#ifdef _WIN32
    #include <windows.h>
    #ifndef WGLGETEXTENSIONSSTRING_DEF
        #define WGLGETEXTENSIONSSTRING_DEF
        typedef const char* (WINAPI * PFNWGLGETEXTENSIONSSTRINGPROC)(HDC hdc);
        PFNWGLGETEXTENSIONSSTRINGPROC    pwglGetExtensionsString = 0;
        #define wglGetExtensionsString  pwglGetExtensionsString
    #endif //WGLGETEXTENSIONSSTRING_DEF
#endif //_WIN32

// version 2.0 or greater
#define GL_SHADING_LANGUAGE_VERSION       0x8B8C

void OGLInfoGet(TOGLInfo* pinfo)
{
    if(pinfo==0)
    {
        printf("#Error OGLGetInfo: pinfo=NULL\n");
        return;
    }

    const char *str;
    char *str2, *tok;
    unsigned int sizestr, sizeext, i;
///VENDOR
    str = (const char*)(glGetString(GL_VENDOR));
    if(str)
    {
        sizestr=strlen(str)+1;
        pinfo->m_Vendor=(char*)malloc(sizeof(char)*sizestr);
        strcpy(pinfo->m_Vendor,str);
    }
    else
        pinfo->m_Vendor=0;
///RENDERER
    str = (const char*)(glGetString(GL_RENDERER));
    if(str)
    {
        sizestr=strlen(str)+1;
        pinfo->m_Renderer=(char*)malloc(sizeof(char)*sizestr);
        strcpy(pinfo->m_Renderer,str);
    }
    else
        pinfo->m_Renderer=0;
///VERSION
    str = (const char*)(glGetString(GL_VERSION));
    if(str)
    {
        sizestr=strlen(str)+1;
        pinfo->m_Version=(char*)malloc(sizeof(char)*sizestr);
        strcpy(pinfo->m_Version,str);
    }
    else
        pinfo->m_Version=0;
///EXTENSIONS
    str = (const char*)(glGetString(GL_EXTENSIONS));
    if(str)
    {
        sizestr=strlen(str)+1;
        str2=(char*)malloc(sizeof(char)*sizestr);
        strcpy(str2,str);
        tok=strtok(str2," ");
        sizeext=0;
        while(tok)
        {
            sizeext++;
            tok=strtok(0," ");
        }
        pinfo->m_Extensions=(char**)malloc(sizeof(char*)*sizeext);
        pinfo->m_SizeExtensions=sizeext;
        strcpy(str2,str);
        tok=strtok(str2," ");
        i=0;
        while(tok)
        {
            sizestr=strlen(tok)+1;
            pinfo->m_Extensions[i]=(char*)malloc(sizeof(char)*sizestr);
            strcpy(pinfo->m_Extensions[i],tok);
            tok=strtok(0," ");
            i++;
        }
        free(str2);
    }
    else
        pinfo->m_Extensions=0;

#ifdef _WIN32
    wglGetExtensionsString = (PFNWGLGETEXTENSIONSSTRINGPROC)wglGetProcAddress("wglGetExtensionsString");
    if(wglGetExtensionsString)
    {
        str = (const char*)wglGetExtensionsString(wglGetCurrentDC());
        if(str)
        {
            sizestr=strlen(str)+1;
            str2=(char*)malloc(sizeof(char)*sizestr);
            strcpy(str2,str);
            tok=strtok(str2," ");
            sizeext=0;
            while(tok)
            {
                sizeext++;
                tok=strtok(0," ");
            }
            i=pinfo->m_SizeExtensions;
            pinfo->m_SizeExtensions+=sizeext;
            pinfo->m_Extensions=(char**)realloc(pinfo->m_Extensions,sizeof(char*)*pinfo->m_SizeExtensions);
            strcpy(str2,str);
            tok=strtok(str2," ");
            while(tok)
            {
                sizestr=strlen(tok)+1;
                pinfo->m_Extensions[i]=(char*)malloc(sizeof(char)*sizestr);
                strcpy(pinfo->m_Extensions[i],tok);
                tok=strtok(0," ");
                i++;
            }
            free(str2);
        }
    }
#endif //_WIN32
///GLSL VERSION
   str = (const char*)(glGetString(GL_SHADING_LANGUAGE_VERSION));
    if(str!=0)
    {
        sizestr=strlen(str)+1;
        pinfo->m_GlslVersion=(char*)malloc(sizeof(char)*sizestr);
        strcpy(pinfo->m_GlslVersion,str);
    }
    else
    {
        if(OGLInfoIsExtensionSupported(pinfo,"GL_ARB_shading_language_100"))
        {
            sizestr=strlen("GL_shading_language_100")+1;
            pinfo->m_GlslVersion=(char*)malloc(sizeof(char)*sizestr);
            strcpy(pinfo->m_GlslVersion,"GL_shading_language_100");
        }
        else
        {
            sizestr=strlen("no_shading_language")+1;
            pinfo->m_GlslVersion=(char*)malloc(sizeof(char)*sizestr);
            strcpy(pinfo->m_GlslVersion,"no_shading_language");
        }
    }
///COLOR BITS
    glGetIntegerv(GL_RED_BITS, &pinfo->m_RedBits);
    glGetIntegerv(GL_GREEN_BITS, &pinfo->m_GreenBits);
    glGetIntegerv(GL_BLUE_BITS, &pinfo->m_BlueBits);
    glGetIntegerv(GL_ALPHA_BITS, &pinfo->m_AlphaBits);
///DEPTH BITS
    glGetIntegerv(GL_DEPTH_BITS, &pinfo->m_DepthBits);
///STECIL BITS
    glGetIntegerv(GL_STENCIL_BITS, &pinfo->m_StencilBits);
///MAX NUMBER OF LIGHTS ALLOWED
    glGetIntegerv(GL_MAX_LIGHTS, &pinfo->m_MaxLights);
///MAX TEXTURE RESOLUTION
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &pinfo->m_MaxTextureSize);
///MAX NUMBER OF CLIPPING PLANES
    glGetIntegerv(GL_MAX_CLIP_PLANES, &pinfo->m_MaxClipPlanes);
///MAX MODELVIEW AND PROJECTIOn MATRIX STACKS
    glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH, &pinfo->m_MaxModelViewStacks);
    glGetIntegerv(GL_MAX_PROJECTION_STACK_DEPTH, &pinfo->m_MaxProjectionStacks);
    glGetIntegerv(GL_MAX_ATTRIB_STACK_DEPTH, &pinfo->m_MaxAttribStacks);
///MAX TEXTURE STACKS
    glGetIntegerv(GL_MAX_TEXTURE_STACK_DEPTH, &pinfo->m_MaxTextureStacks);
}

void OGLInfoDelete(TOGLInfo* pinfo)
{
    unsigned int i;
    if(pinfo==0)
    {
        printf("#Error OGLDeleteInfo: pinfo=NULL\n");
        return;
    }
    if(pinfo->m_Vendor)
        free(pinfo->m_Vendor);
    if(pinfo->m_Renderer)
        free(pinfo->m_Renderer);
    if(pinfo->m_Version)
        free(pinfo->m_Version);
    if(pinfo->m_Extensions)
    {
        for(i=0; i<pinfo->m_SizeExtensions; i++)
            free(pinfo->m_Extensions[i]);
        free(pinfo->m_Extensions);
    }
    if(pinfo->m_GlslVersion)
        free(pinfo->m_GlslVersion);
}

void OGLInfoPrint(TOGLInfo* pinfo)
{
    unsigned int i;
    if(pinfo==0)
    {
        printf("#Error OGLPrintInfo: pinfo=NULL\n");
        return;
    }
    printf("Vendor: %s\n",pinfo->m_Vendor);
    printf("Renderer: %s\n",pinfo->m_Renderer);
    printf("Version: %s\n",pinfo->m_Version);
    printf("glsl version: %s\n",pinfo->m_GlslVersion);
    printf("Number of Extensions: %d\n",pinfo->m_SizeExtensions);
    for(i=0; i<pinfo->m_SizeExtensions; i++)
        printf("\t%d : %s\n",i, pinfo->m_Extensions[i]);
    printf("Number of color bits: %d; %d; %d; %d\n",pinfo->m_RedBits,
                                                    pinfo->m_GreenBits,
                                                    pinfo->m_BlueBits,
                                                    pinfo->m_AlphaBits);
    printf("Depth Bits: %d\n", pinfo->m_DepthBits);
    printf("Stencil Bits: %d\n", pinfo->m_StencilBits);
    printf("Max Texture Size: %dx%d\n", pinfo->m_MaxTextureSize, pinfo->m_MaxTextureSize);
    printf("Max Lights: %d\n", pinfo->m_MaxLights);
    printf("Max Clip Planes: %d\n", pinfo->m_MaxClipPlanes);
    printf("Max Modelview Matrix Stacks: %d\n", pinfo->m_MaxModelViewStacks);
    printf("Max Projection Matrix Stacks: %d\n", pinfo->m_MaxProjectionStacks);
    printf("Max Attribute Stacks: %d\n", pinfo->m_MaxAttribStacks);
    printf("Max Texture Stacks: %d\n", pinfo->m_MaxTextureStacks);
}

int OGLInfoIsExtensionSupported(TOGLInfo* pinfo, const char* sext)
{
    unsigned int i;
    for(i=0; i<pinfo->m_SizeExtensions; i++)
    {
        if(strcmp(pinfo->m_Extensions[i],sext)==0)
            return 1;
    }
    return 0;
}

int OGLInfoGetShaderVersion(TOGLInfo* pinfo)
{
    if(strncmp(pinfo->m_Version,"2.0.0",5)==0)
        return 110;
    else if(strncmp(pinfo->m_Version,"2.1.0",5)==0)
        return 120;
    else if(strncmp(pinfo->m_Version,"3.0.0",5)==0)
        return 130;
    else if(strncmp(pinfo->m_Version,"3.1.0",5)==0)
        return 140;
    else if(strncmp(pinfo->m_Version,"3.2.0",5)==0)
        return 150;
    else if(strncmp(pinfo->m_Version,"3.3.0",5)==0)
        return 330;
    else if(strncmp(pinfo->m_Version,"4.0.0",5)==0)
        return 400;
    else if(strncmp(pinfo->m_Version,"4.1.0",5)==0)
        return 410;
    else if(strncmp(pinfo->m_Version,"4.2.0",5)==0)
        return 420;
    else if(strncmp(pinfo->m_Version,"4.3.0",5)==0)
        return 430;
    else if(strncmp(pinfo->m_Version,"4.4.0",5)==0)
        return 440;
    else if(strncmp(pinfo->m_Version,"4.5.0",5)==0)
        return 450;
    return 0;
}
