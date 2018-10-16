#include "OGLShader.h"

/// ////////////////////
/// SHADER DATA & FUNCTIONS
/// ////////////////////
void OGLShaderCreate(TShaderData* pshader, GLenum type)
{
//Init. les valeurs
    pshader->m_ShaderSource=0;
    pshader->m_Object=0;
    pshader->m_Type=type;
}

void OGLShaderDelete(TShaderData* pshader)
{
    if(pshader && pshader->m_ShaderSource)
    {
        free(pshader->m_ShaderSource);
        if(pshader->m_Object)
            glDeleteShader(pshader->m_Object);
    }
}

int OGLShaderLoadFromFile(TShaderData *pshader, const char* sfilename)
{
    if(pshader==NULL)
    {
         printf("#Error OGLShaderLoadFromFile: no pshader.\n");
         return 0;
    }
    if(pshader->m_ShaderSource)
    {
        free(pshader->m_ShaderSource);
        if(pshader->m_Object)
            glDeleteShader(pshader->m_Object);
    }
    FILE *shaderfile=NULL;
    shaderfile=fopen(sfilename,"rb");
    if(shaderfile==NULL) ///No file
    {
        printf("#Error OGLShaderLoadFromFile: no file.\n");
        return 0;
    }
    fseek(shaderfile,0,SEEK_END);
    size_t size=ftell(shaderfile);
    if(size==0)          ///Empty file
    {
        printf("#Error OGLShaderLoadFromFile: file empty.\n");
        return 0;
    }
    fseek(shaderfile,0,SEEK_SET);
    pshader->m_ShaderSource=malloc((size+1)*sizeof(char));
    fread(pshader->m_ShaderSource,size,1,shaderfile);
    fclose(shaderfile);
    pshader->m_ShaderSource[size]='\0';
    return 1;
}

int OGLShaderLoadFromMemory(TShaderData *pshader, const char* sprogram)
{
    if(pshader==NULL)
    {
         printf("#Error OGLShaderLoadFromFile: no pshader.\n");
         return 0;
    }
    if(pshader->m_ShaderSource)
    {
        free(pshader->m_ShaderSource);
        if(pshader->m_Object)
            glDeleteShader(pshader->m_Object);
    }
    size_t size=strlen(sprogram);
    pshader->m_ShaderSource=malloc((size+1)*sizeof(char));
    memcpy(pshader->m_ShaderSource,sprogram,size);
    pshader->m_ShaderSource[size]='\0';
    return 1;
}

int OGLShaderCreateAndCompile(TShaderData* pshader)
{
    if(pshader==NULL)
    {
         printf("#Error OGLShaderCompile: no pshader.\n");
         return 0;
    }
    //Creation du shader
    pshader->m_Object = glCreateShader(pshader->m_Type);
    if(!pshader->m_Object)
    {
        printf("#Error OGLShaderCompile: can't create shader.\n");
        return 0;
    }
    glShaderSource(pshader->m_Object,1,(const GLchar**)&pshader->m_ShaderSource,NULL);
    glCompileShader(pshader->m_Object);
    GLint compiled=0;
    glGetShaderiv(pshader->m_Object,GL_COMPILE_STATUS,&compiled);
    if(!compiled)
    {
        char stmp[256] = "";
        glGetShaderInfoLog(pshader->m_Object,256,NULL,stmp);
        printf("#Error OGLShaderCompile: can't compile shader.\n%s\n",stmp);
        return 0;
    }
    return 1;
}

/// ////////////////////
/// PROGRAM SHADER FUNCTIONS
/// ////////////////////

///PROGRAM
inline int OGLShaderProgramCreate(TShaderProgram *pprog)
{
    *pprog = glCreateProgram();
    if(!(*pprog))
    {
        printf("#Error OGLShaderProgramCreate : can't create program shader.\n");
        return 0;
    }
    return 1;
}

inline void OGLShaderProgramDelete(TShaderProgram *program)
{
    glDeleteProgram(*program);
}

int OGLShaderProgramAttachVertexAndFragmentShader(TShaderProgram *program, TShaderData* pvertex, TShaderData *pfragment)
{
    if(!pvertex || !pfragment)
    {
        printf("#Error OGLShaderProgramAttachVertexAndFragmentShader: no shader.\n");
        return 0;
    }
    glAttachShader(*program,pvertex->m_Object);
    glAttachShader(*program,pfragment->m_Object);
    return 1;
}

int OGLShaderProgramLink(TShaderProgram *program)
{
    GLint linked;
    glLinkProgram(*program);
    glGetProgramiv(*program,GL_LINK_STATUS,&linked);
    if(!linked)
    {
        printf("#Error OGLShaderProgramAttachVertexAndFragmentShader: can't link.\n");
        return 0;
    }
    return 1;
}

inline void OGLShaderProgramBind(TShaderProgram *program)
{
    glUseProgram(*program);
}

inline void OGLShaderProgramUnBind()
{
    glUseProgram(0);
}

///DATA
inline GLint OGLShaderProgramGetUniformLocation(TShaderProgram *program, const char* sname)
{
    return glGetUniformLocation(*program,sname);
}

inline void OGLShaderProgramSetMatrix4fv(GLint id, TMatrix4x4f m)
{
    glUniformMatrix4fv(id,1,GL_FALSE,m);
}

inline void OGLShaderProgramSetVec3fv(GLint id, vec3f vec)
{
    glUniform3fv(id,1,vec);
}

inline void OGLShaderProgramSetVec4fv(GLint id, vec4f vec)
{
    glUniform4fv(id,1,vec);
}

inline void OGLShaderProgramSet1f(GLint id, float val)
{
    glUniform1f(id,val);
}

inline void OGLShaderProgramSetTextureUnit(GLint id, GLint unit)
{
    glUniform1i(id,unit);
}
