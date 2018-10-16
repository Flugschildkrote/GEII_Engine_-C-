#if !defined(OGLVBO_H)
#define OGLVBO_H

#include <GL\gl.h>
#include "OGLExt.h"

typedef struct{
    GLuint m_id;                //Identifiant du vbo
    unsigned int m_sizedata;    //La taille des donnees
}TVBOData;

GLuint OGLVBOCreate(const void* data, int datasize, GLenum target, GLenum usage);
void OGLVBODelete(const GLuint id);

void OGLVBOCopy(TVBOData *pdest, TVBOData *psrc);
#endif //OGLVBO_H
