#if !defined(OGLEXT_H)
#define OGLEXT_H

#include <GL\gl.h>

#include "glext.h"

#include "OGLInfo.h"

///Function pointers for OpenGL extensions
#ifdef _WIN32
#include <windows.h>
///For VBO functions
extern PFNGLGENBUFFERSPROC                  pglGenBuffers;              // generate buffer object names
extern PFNGLBINDBUFFERPROC                  pglBindBuffer;              // bind a named buffer object
extern PFNGLBUFFERDATAPROC                  pglBufferData;              // creates and initializes a buffer object's data store
extern PFNGLBUFFERSUBDATAPROC               pglBufferSubData;           // updates a subset of a buffer object's data store
extern PFNGLDELETEBUFFERSPROC               pglDeleteBuffers;           // delete named buffer objects
extern PFNGLGETBUFFERPARAMETERIVPROC        pglGetBufferParameteriv;    // return parameters of a buffer object
extern PFNGLMAPBUFFERPROC                   pglMapBuffer;               // map a buffer object's data store
extern PFNGLUNMAPBUFFERPROC                 pglUnmapBuffer;             // unmap a buffer object's data store
extern PFNGLVERTEXATTRIBPOINTERPROC         pglVertexAttribPointer;     // define an array of generic vertex attribute data
extern PFNGLENABLEVERTEXATTRIBARRAYPROC     pglEnableVertexAttribArray; // enable a generic vertex attribute array
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC    pglDisableVertexAttribArray;// disable a generic vertex attribute array

#define glGenBuffers                pglGenBuffers
#define glBindBuffer                pglBindBuffer
#define glBufferData                pglBufferData
#define glBufferSubData             pglBufferSubData
#define glDeleteBuffers             pglDeleteBuffers
#define glGetBufferParameteriv      pglGetBufferParameteriv
#define glMapBuffer                 pglMapBuffer
#define glUnmapBuffer               pglUnmapBuffer
#define glVertexAttribPointer       pglVertexAttribPointer
#define glEnableVertexAttribArray   pglEnableVertexAttribArray
#define glDisableVertexAttribArray  pglDisableVertexAttribArray

///For FBO functions
extern PFNGLGENFRAMEBUFFERSEXTPROC  pglGenFrameBuffers;                 // generate framebuffer object names
extern PFNGLBINDFRAMEBUFFEREXTPROC  pglBindFramebuffer;                 // bind a framebuffer to a framebuffer target
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC pglFramebufferTexture2D;        // attach a texture image to a framebuffer object
extern PFNGLDELETEFRAMEBUFFERSEXTPROC pglDeleteFramebuffers;            // delete named framebuffer objects

#define glGenFrameBuffers           pglGenFrameBuffers
#define glBindFramebuffer           pglBindFramebuffer
#define glFramebufferTexture2D      pglFramebufferTexture2D
#define glDeleteFramebuffers        pglDeleteFramebuffers

///For shader functions
extern PFNGLDELETEOBJECTARBPROC            pglDeleteObject;             // deletes an object
extern PFNGLGETHANDLEARBPROC               pglGetHandle;                // returns the handle of the current program object
extern PFNGLDETACHOBJECTARBPROC            pglDetachObject;             // detaches a shader object from a program object
extern PFNGLCREATESHADEROBJECTARBPROC      pglCreateShaderObject;       // creates a shader object
extern PFNGLSHADERSOURCEARBPROC            pglShaderSource;             // replaces  the  source  code  strings for a shader object
extern PFNGLCOMPILESHADERARBPROC           pglCompileShader;            // compiles a shader object
extern PFNGLCREATEPROGRAMOBJECTARBPROC     pglCreateProgramObject;      // creates a program object
extern PFNGLATTACHOBJECTARBPROC            pglAttachObject;             // attacheds a shader object to a program object
extern PFNGLLINKPROGRAMARBPROC             pglLinkProgram;              // links a program object
extern PFNGLUSEPROGRAMOBJECTARBPROC        pglUseProgramObject;         // make a program object part of the current rendering state
extern PFNGLVALIDATEPROGRAMARBPROC         pglValidateProgram;          // validates a program object
extern PFNGLATTACHSHADERPROC               pglAttachShader;             // attaches a shader object to a program object
extern PFNGLDELETESHADERPROC               pglDeleteShader;             // deletes a shader object
extern PFNGLCREATESHADEROBJECTARBPROC      pglCreateShader;             // creates a shader object
extern PFNGLGETSHADERIVPROC                pglGetShaderiv;              // return a parameter from a shader object
extern PFNGLGETSHADERINFOLOGPROC           pglGetShaderInfoLog;         // returns the information log for a shader object
extern PFNGLCREATEPROGRAMPROC              pglCreateProgram;            // creates a program object
extern PFNGLGETPROGRAMIVPROC               pglGetProgramiv;             // returns a parameter from a program object
extern PFNGLUSEPROGRAMPROC                 pglUseProgram;               // installs a program object as part of current rendering state
extern PFNGLACTIVETEXTUREPROC              pglActiveTexture;            // select active texture unit
extern PFNGLDELETEPROGRAMPROC              pglDeleteProgram;            // deletes a program object
extern PFNGLGETOBJECTPARAMETERFVARBPROC    pglGetObjectParameterfv;
extern PFNGLGETOBJECTPARAMETERIVARBPROC    pglGetObjectParameteriv;
extern PFNGLGETINFOLOGARBPROC              pglGetInfoLog;               // returns the information log for an object
extern PFNGLGETATTACHEDOBJECTSARBPROC      pglGetAttachedObjects;       // returns  an	array of handles attached to a program object
extern PFNGLGETUNIFORMLOCATIONARBPROC      pglGetUniformLocation;       // returns the location of a uniform variable
extern PFNGLGETACTIVEUNIFORMARBPROC        pglGetActiveUniform;         // returns information about active uniform variable
extern PFNGLGETUNIFORMFVARBPROC            pglGetUniformfv;             // returns the value of a uniform
extern PFNGLGETUNIFORMIVARBPROC            pglGetUniformiv;             // returns the value of a uniform
extern PFNGLGETSHADERSOURCEARBPROC         pglGetShaderSource;          // returns the source code string for a shader object.


#define glDeleteObject          pglDeleteObject
#define glGetHandle             pglGetHandle
#define glDetachObject          pglDetachObject
#define glCreateShaderObject    pglCreateShaderObject
#define glShaderSource          pglShaderSource
#define glCompileShader         pglCompileShader
#define glCreateProgramObject   pglCreateProgramObject
#define glAttachObject          pglAttachObject
#define glLinkProgram           pglLinkProgram
#define glUseProgramObject      pglUseProgramObject
#define glValidateProgram       pglValidateProgram
#define glAttachShader          pglAttachShader
#define glDeleteShader          pglDeleteShader
#define glCreateShader          pglCreateShader
#define glGetShaderiv           pglGetShaderiv
#define glGetShaderInfoLog      pglGetShaderInfoLog
#define glCreateProgram         pglCreateProgram
#define glGetProgramiv          pglGetProgramiv
#define glUseProgram            pglUseProgram
#define glActiveTexture         pglActiveTexture
#define glDeleteProgram         pglDeleteProgram
#define glGetObjectParameterfv  pglGetObjectParameterfv
#define glGetObjectParameteriv  pglGetObjectParameteriv
#define glGetInfoLog            pglGetInfoLog
#define glGetAttachedObjects    pglGetAttachedObjects
#define glGetUniformLocation    pglGetUniformLocation
#define glGetActiveUniform      pglGetActiveUniform
#define glGetUniformfv          pglGetUniformfv
#define glGetUniformiv          pglGetUniformiv
#define glGetShaderSource       pglGetShaderSource

extern PFNGLUNIFORM1FPROC                   pglUniform1f;
extern PFNGLUNIFORM2FPROC                   pglUniform2f;
extern PFNGLUNIFORM3FPROC                   pglUniform3f;
extern PFNGLUNIFORM4FPROC                   pglUniform4f;
extern PFNGLUNIFORM1IPROC                   pglUniform1i;
extern PFNGLUNIFORM2IPROC                   pglUniform2i;
extern PFNGLUNIFORM3IPROC                   pglUniform3i;
extern PFNGLUNIFORM4IPROC                   pglUniform4i;
extern PFNGLUNIFORM1FVPROC                  pglUniform1fv;
extern PFNGLUNIFORM2FVPROC                  pglUniform2fv;
extern PFNGLUNIFORM3FVPROC                  pglUniform3fv;
extern PFNGLUNIFORM4FVPROC                  pglUniform4fv;
extern PFNGLUNIFORM1IVPROC                  pglUniform1iv;
extern PFNGLUNIFORM2IVPROC                  pglUniform2iv;
extern PFNGLUNIFORM3IVPROC                  pglUniform3iv;
extern PFNGLUNIFORM4IVPROC                  pglUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC            pglUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC            pglUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC            pglUniformMatrix4fv;

#define glUniform1f               pglUniform1f
#define glUniform2f               pglUniform2f
#define glUniform3f               pglUniform3f
#define glUniform4f               pglUniform4f
#define glUniform1i               pglUniform1i
#define glUniform2i               pglUniform2i
#define glUniform3i               pglUniform3i
#define glUniform4i               pglUniform4i
#define glUniform1fv              pglUniform1fv
#define glUniform2fv              pglUniform2fv
#define glUniform3fv              pglUniform3fv
#define glUniform4fv              pglUniform4fv
#define glUniform1iv              pglUniform1iv
#define glUniform2iv              pglUniform2iv
#define glUniform3iv              pglUniform3iv
#define glUniform4iv              pglUniform4iv
#define glUniformMatrix2fv        pglUniformMatrix2fv
#define glUniformMatrix3fv        pglUniformMatrix3fv
#define glUniformMatrix4fv        pglUniformMatrix4fv
#endif //_WIN32

int OGLExtInitialize(TOGLInfo* pinfo);

#endif //OGLEXT_H
