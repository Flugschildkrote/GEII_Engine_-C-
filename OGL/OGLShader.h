#if !defined(OGLSHADER_H)
#define OGLSHADER_H

#include <stdlib.h>
#include <stdio.h>

#include <GL\gl.h>
#include "OGLExt.h"

#include "../math/matrix4x4.h"

/// ////////////////////
/// SHADER DATA & FUNCTIONS
/// ////////////////////
typedef struct{
    char *m_ShaderSource;       //Le programme source.
    GLuint m_Object;            //L'objet shader (l'index).
    GLenum m_Type;              //Le type de shader.
}TShaderData;

void OGLShaderCreate(TShaderData* pshader, GLenum type);
void OGLShaderDelete(TShaderData* pshader);
int OGLShaderLoadFromFile(TShaderData *pshader, const char* sfilename);
int OGLShaderLoadFromMemory(TShaderData *pshader, const char* sprogram);

int OGLShaderCreateAndCompile(TShaderData* pshader);

/// ////////////////////
/// PROGRAM SHADER DATA & FUNCTIONS
/// ////////////////////

///PROGRAM
typedef GLuint TShaderProgram;

int OGLShaderProgramCreate(TShaderProgram *pprog);
void OGLShaderProgramDelete(TShaderProgram *program);
int OGLShaderProgramAttachVertexAndFragmentShader(TShaderProgram *program, TShaderData* pvertex, TShaderData *pfragment);
int OGLShaderProgramLink(TShaderProgram *program);
void OGLShaderProgramBind(TShaderProgram *program);
void OGLShaderProgramUnBind();

///DATA
GLint OGLShaderProgramGetUniformLocation(TShaderProgram *program, const char* sname);
void OGLShaderProgramSetMatrix4fv(GLint id, TMatrix4x4f m);
void OGLShaderProgramSetVec3fv(GLint id, vec3f vec);
void OGLShaderProgramSetVec4fv(GLint id, vec4f vec);
void OGLShaderProgramSet1f(GLint id, float val);

void OGLShaderProgramSetTextureUnit(GLint id, GLint unit);

#endif //OGLSHADER_H
