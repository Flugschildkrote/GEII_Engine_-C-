#include "OGLExt.h"

#ifdef _WIN32
PFNGLGENBUFFERSPROC                 pglGenBuffers=NULL;
PFNGLBINDBUFFERPROC                 pglBindBuffer=NULL;
PFNGLBUFFERDATAPROC                 pglBufferData=NULL;
PFNGLBUFFERSUBDATAPROC              pglBufferSubData=NULL;
PFNGLDELETEBUFFERSPROC              pglDeleteBuffers=NULL;
PFNGLGETBUFFERPARAMETERIVPROC       pglGetBufferParameteriv=NULL;
PFNGLMAPBUFFERPROC                  pglMapBuffer=NULL;
PFNGLUNMAPBUFFERPROC                pglUnmapBuffer=NULL;
PFNGLVERTEXATTRIBPOINTERPROC        pglVertexAttribPointer=NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC    pglEnableVertexAttribArray=NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC   pglDisableVertexAttribArray=NULL;

PFNGLGENFRAMEBUFFERSEXTPROC         pglGenFrameBuffers=NULL;
PFNGLBINDFRAMEBUFFEREXTPROC         pglBindFramebuffer=NULL;
PFNGLFRAMEBUFFERTEXTURE2DEXTPROC    pglFramebufferTexture2D=NULL;
PFNGLDELETEFRAMEBUFFERSEXTPROC      pglDeleteFramebuffers=NULL;

PFNGLDELETEOBJECTARBPROC            pglDeleteObject=NULL;
PFNGLGETHANDLEARBPROC               pglGetHandle=NULL;
PFNGLDETACHOBJECTARBPROC            pglDetachObject=NULL;
PFNGLCREATESHADEROBJECTARBPROC      pglCreateShaderObject=NULL;
PFNGLSHADERSOURCEARBPROC            pglShaderSource=NULL;
PFNGLCOMPILESHADERARBPROC           pglCompileShader=NULL;
PFNGLCREATEPROGRAMOBJECTARBPROC     pglCreateProgramObject=NULL;
PFNGLATTACHOBJECTARBPROC            pglAttachObject=NULL;
PFNGLLINKPROGRAMARBPROC             pglLinkProgram=NULL;
PFNGLUSEPROGRAMOBJECTARBPROC        pglUseProgramObject=NULL;
PFNGLVALIDATEPROGRAMARBPROC         pglValidateProgram=NULL;
PFNGLDELETEPROGRAMPROC              pglDeleteProgram=NULL;
PFNGLATTACHSHADERPROC               pglAttachShader=NULL;
PFNGLDELETESHADERPROC               pglDeleteShader=NULL;
PFNGLCREATESHADEROBJECTARBPROC      pglCreateShader=NULL;
PFNGLGETSHADERIVPROC                pglGetShaderiv=NULL;
PFNGLGETSHADERINFOLOGPROC           pglGetShaderInfoLog=NULL;
PFNGLCREATEPROGRAMPROC              pglCreateProgram=NULL;
PFNGLGETPROGRAMIVPROC               pglGetProgramiv=NULL;
PFNGLUSEPROGRAMPROC                 pglUseProgram=NULL;
PFNGLACTIVETEXTUREPROC              pglActiveTexture=NULL;
PFNGLGETOBJECTPARAMETERFVARBPROC    pglGetObjectParameterfv=NULL;
PFNGLGETOBJECTPARAMETERIVARBPROC    pglGetObjectParameteriv=NULL;
PFNGLGETINFOLOGARBPROC              pglGetInfoLog=NULL;
PFNGLGETATTACHEDOBJECTSARBPROC      pglGetAttachedObjects=NULL;
PFNGLGETUNIFORMLOCATIONARBPROC      pglGetUniformLocation=NULL;
PFNGLGETACTIVEUNIFORMARBPROC        pglGetActiveUniform=NULL;
PFNGLGETUNIFORMFVARBPROC            pglGetUniformfv=NULL;
PFNGLGETUNIFORMIVARBPROC            pglGetUniformiv=NULL;
PFNGLGETSHADERSOURCEARBPROC         pglGetShaderSource=NULL;

PFNGLUNIFORM1FPROC                  pglUniform1f=NULL;
PFNGLUNIFORM2FPROC                  pglUniform2f=NULL;
PFNGLUNIFORM3FPROC                  pglUniform3f=NULL;
PFNGLUNIFORM4FPROC                  pglUniform4f=NULL;
PFNGLUNIFORM1IPROC                  pglUniform1i=NULL;
PFNGLUNIFORM2IPROC                  pglUniform2i=NULL;
PFNGLUNIFORM3IPROC                  pglUniform3i=NULL;
PFNGLUNIFORM4IPROC                  pglUniform4i=NULL;
PFNGLUNIFORM1FVPROC                 pglUniform1fv=NULL;
PFNGLUNIFORM2FVPROC                 pglUniform2fv=NULL;
PFNGLUNIFORM3FVPROC                 pglUniform3fv=NULL;
PFNGLUNIFORM4FVPROC                 pglUniform4fv=NULL;
PFNGLUNIFORM1IVPROC                 pglUniform1iv=NULL;
PFNGLUNIFORM2IVPROC                 pglUniform2iv=NULL;
PFNGLUNIFORM3IVPROC                 pglUniform3iv=NULL;
PFNGLUNIFORM4IVPROC                 pglUniform4iv=NULL;
PFNGLUNIFORMMATRIX2FVPROC           pglUniformMatrix2fv=NULL;
PFNGLUNIFORMMATRIX3FVPROC           pglUniformMatrix3fv=NULL;
PFNGLUNIFORMMATRIX4FVPROC           pglUniformMatrix4fv=NULL;

//Macro for fast coding
#define OGL_EXT_INIT_MACRO_FUNC(pointer,type,name)                                      \
{                                                                                       \
    pointer = (type)wglGetProcAddress(name);                                            \
    if(!pointer)                                                                        \
    {                                                                                   \
        printf("#Error OGLExtInitialize: shader function %s is not supported.\n",name); \
        return 0;                                                                       \
    }                                                                                   \
}
#endif //_WIN32



int OGLExtInitialize(TOGLInfo* pinfo)
{
#ifdef _WIN32
///VBO extensions
    if(!OGLInfoIsExtensionSupported(pinfo,"GL_ARB_vertex_buffer_object"))
    {
        printf("#Error OGLExtInitialize: vertex buffer object is not supported.\n");
        return 0;
    }
    OGL_EXT_INIT_MACRO_FUNC(glGenBuffers,PFNGLGENBUFFERSPROC,"glGenBuffers");
    OGL_EXT_INIT_MACRO_FUNC(glBindBuffer,PFNGLBINDBUFFERPROC,"glBindBuffer");
    OGL_EXT_INIT_MACRO_FUNC(glBufferData,PFNGLBUFFERDATAPROC,"glBufferData");
    OGL_EXT_INIT_MACRO_FUNC(glBufferSubData,PFNGLBUFFERSUBDATAPROC,"glBufferSubData");
    OGL_EXT_INIT_MACRO_FUNC(glDeleteBuffers,PFNGLDELETEBUFFERSPROC,"glDeleteBuffers");
    OGL_EXT_INIT_MACRO_FUNC(glGetBufferParameteriv,PFNGLGETBUFFERPARAMETERIVPROC,"glGetBufferParameteriv");
    OGL_EXT_INIT_MACRO_FUNC(glMapBuffer,PFNGLMAPBUFFERPROC,"glMapBuffer");
    OGL_EXT_INIT_MACRO_FUNC(glUnmapBuffer,PFNGLUNMAPBUFFERPROC,"glUnmapBuffer");
    OGL_EXT_INIT_MACRO_FUNC(glVertexAttribPointer,PFNGLVERTEXATTRIBPOINTERPROC,"glVertexAttribPointer");
    OGL_EXT_INIT_MACRO_FUNC(glEnableVertexAttribArray,PFNGLENABLEVERTEXATTRIBARRAYPROC,"glEnableVertexAttribArray");
    OGL_EXT_INIT_MACRO_FUNC(glDisableVertexAttribArray,PFNGLDISABLEVERTEXATTRIBARRAYPROC,"glDisableVertexAttribArray");
///FBO extensions
    OGL_EXT_INIT_MACRO_FUNC(glGenFrameBuffers,PFNGLGENFRAMEBUFFERSEXTPROC,"glGenFramebuffersEXT");
    OGL_EXT_INIT_MACRO_FUNC(glBindFramebuffer,PFNGLBINDFRAMEBUFFEREXTPROC,"glBindFramebufferEXT");
    OGL_EXT_INIT_MACRO_FUNC(glFramebufferTexture2D,PFNGLFRAMEBUFFERTEXTURE2DEXTPROC,"glFramebufferTexture2DEXT");
    OGL_EXT_INIT_MACRO_FUNC(glDeleteFramebuffers,PFNGLDELETEFRAMEBUFFERSEXTPROC,"glDeleteFramebuffersEXT");
///Shader extensions
    if(!OGLInfoIsExtensionSupported(pinfo,"GL_ARB_shading_language_100")
       || OGLInfoGetShaderVersion(pinfo)<330)
    {
        printf("#Error OGLExtInitialize: shader is not supported.\n");
        return 0;
    }
    OGL_EXT_INIT_MACRO_FUNC(glDeleteObject,PFNGLDELETEOBJECTARBPROC,"glDeleteObjectARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetHandle,PFNGLGETHANDLEARBPROC,"glGetHandleARB");
    OGL_EXT_INIT_MACRO_FUNC(glDetachObject,PFNGLDETACHOBJECTARBPROC,"glDetachObjectARB");
    OGL_EXT_INIT_MACRO_FUNC(glCreateShaderObject,PFNGLCREATESHADEROBJECTARBPROC,"glCreateShaderObjectARB");
    OGL_EXT_INIT_MACRO_FUNC(glShaderSource,PFNGLSHADERSOURCEARBPROC,"glShaderSourceARB");
    OGL_EXT_INIT_MACRO_FUNC(glCompileShader,PFNGLCOMPILESHADERARBPROC,"glCompileShaderARB");
    OGL_EXT_INIT_MACRO_FUNC(glCreateProgramObject,PFNGLCREATEPROGRAMOBJECTARBPROC,"glCreateProgramObjectARB");
    OGL_EXT_INIT_MACRO_FUNC(glAttachObject,PFNGLATTACHOBJECTARBPROC,"glAttachObjectARB");
    OGL_EXT_INIT_MACRO_FUNC(glLinkProgram,PFNGLLINKPROGRAMARBPROC,"glLinkProgramARB");
    OGL_EXT_INIT_MACRO_FUNC(glUseProgramObject,PFNGLUSEPROGRAMOBJECTARBPROC,"glUseProgramObjectARB");
    OGL_EXT_INIT_MACRO_FUNC(glValidateProgram,PFNGLVALIDATEPROGRAMARBPROC,"glValidateProgramARB");

    OGL_EXT_INIT_MACRO_FUNC(glAttachShader,PFNGLATTACHSHADERPROC,"glAttachShader");
    OGL_EXT_INIT_MACRO_FUNC(glDeleteShader,PFNGLDELETESHADERPROC,"glDeleteShader");
    OGL_EXT_INIT_MACRO_FUNC(glCreateShader,PFNGLCREATESHADEROBJECTARBPROC,"glCreateShader");
    OGL_EXT_INIT_MACRO_FUNC(glGetShaderiv,PFNGLGETSHADERIVPROC,"glGetShaderiv");
    OGL_EXT_INIT_MACRO_FUNC(glGetShaderInfoLog,PFNGLGETSHADERINFOLOGPROC,"glGetShaderInfoLog");
    OGL_EXT_INIT_MACRO_FUNC(glCreateProgram,PFNGLCREATEPROGRAMPROC,"glCreateProgram");
    OGL_EXT_INIT_MACRO_FUNC(glGetProgramiv,PFNGLGETPROGRAMIVPROC,"glGetProgramiv");
    OGL_EXT_INIT_MACRO_FUNC(glUseProgram,PFNGLUSEPROGRAMPROC,"glUseProgram");
    OGL_EXT_INIT_MACRO_FUNC(glActiveTexture,PFNGLACTIVETEXTUREPROC,"glActiveTexture");
    OGL_EXT_INIT_MACRO_FUNC(glDeleteProgram,PFNGLDELETEPROGRAMPROC,"glDeleteProgram");

    OGL_EXT_INIT_MACRO_FUNC(glGetObjectParameterfv,PFNGLGETOBJECTPARAMETERFVARBPROC,"glGetObjectParameterfvARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetObjectParameteriv,PFNGLGETOBJECTPARAMETERIVARBPROC,"glGetObjectParameterivARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetInfoLog,PFNGLGETINFOLOGARBPROC,"glGetInfoLogARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetAttachedObjects,PFNGLGETATTACHEDOBJECTSARBPROC,"glGetAttachedObjectsARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetUniformLocation,PFNGLGETUNIFORMLOCATIONARBPROC,"glGetUniformLocationARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetActiveUniform,PFNGLGETACTIVEUNIFORMARBPROC,"glGetActiveUniformARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetUniformfv,PFNGLGETUNIFORMFVARBPROC,"glGetUniformfvARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetUniformiv,PFNGLGETUNIFORMIVARBPROC,"glGetUniformivARB");
    OGL_EXT_INIT_MACRO_FUNC(glGetShaderSource,PFNGLGETSHADERSOURCEARBPROC,"glGetShaderSourceARB");

    OGL_EXT_INIT_MACRO_FUNC(glUniform1f,PFNGLUNIFORM1FPROC,"glUniform1f");
    OGL_EXT_INIT_MACRO_FUNC(glUniform2f,PFNGLUNIFORM2FPROC,"glUniform2f");
    OGL_EXT_INIT_MACRO_FUNC(glUniform3f,PFNGLUNIFORM3FPROC,"glUniform3f");
    OGL_EXT_INIT_MACRO_FUNC(glUniform4f,PFNGLUNIFORM4FPROC,"glUniform4f");
    OGL_EXT_INIT_MACRO_FUNC(glUniform1i,PFNGLUNIFORM1IPROC,"glUniform1i");
    OGL_EXT_INIT_MACRO_FUNC(glUniform2i,PFNGLUNIFORM2IPROC,"glUniform2i");
    OGL_EXT_INIT_MACRO_FUNC(glUniform3i,PFNGLUNIFORM3IPROC,"glUniform3i");
    OGL_EXT_INIT_MACRO_FUNC(glUniform4i,PFNGLUNIFORM4IPROC,"glUniform4i");
    OGL_EXT_INIT_MACRO_FUNC(glUniform1fv,PFNGLUNIFORM1FVPROC,"glUniform1fv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform2fv,PFNGLUNIFORM2FVPROC,"glUniform2fv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform3fv,PFNGLUNIFORM3FVPROC,"glUniform3fv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform4fv,PFNGLUNIFORM4FVPROC,"glUniform4fv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform1iv,PFNGLUNIFORM1IVPROC,"glUniform1iv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform2iv,PFNGLUNIFORM2IVPROC,"glUniform2iv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform3iv,PFNGLUNIFORM3IVPROC,"glUniform3iv");
    OGL_EXT_INIT_MACRO_FUNC(glUniform4iv,PFNGLUNIFORM4IVPROC,"glUniform4iv");
    OGL_EXT_INIT_MACRO_FUNC(glUniformMatrix2fv,PFNGLUNIFORMMATRIX2FVPROC,"glUniformMatrix2fv");
    OGL_EXT_INIT_MACRO_FUNC(glUniformMatrix3fv,PFNGLUNIFORMMATRIX3FVPROC,"glUniformMatrix3fv");
    OGL_EXT_INIT_MACRO_FUNC(glUniformMatrix4fv,PFNGLUNIFORMMATRIX4FVPROC,"glUniformMatrix4fv");
#endif // _WIN32
    return 1;
}
