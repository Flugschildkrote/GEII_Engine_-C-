#include "OGLVBO.h"

GLuint OGLVBOCreate(const void* data, int datasize, GLenum target, GLenum usage)
{
    GLuint id=0;
    glGenBuffers(1,&id);
    glBindBuffer(target, id);
    glBufferData(target, datasize, data, usage);

    int buffersize=0;
    glGetBufferParameteriv(target,GL_BUFFER_SIZE, &buffersize);
    if(datasize != buffersize)
    {
        glDeleteBuffers(1,&id);
        id=0;
        printf("#Error OGLCreateVBO: can't create VBO.\n");
    }
    return id;
}

void OGLVBODelete(const GLuint id)
{
    glDeleteBuffers(1,&id);
}

void OGLVBOCopy(TVBOData *pdest, TVBOData *psrc)
{
    pdest->m_id=psrc->m_id;
    pdest->m_sizedata=psrc->m_sizedata;
}
