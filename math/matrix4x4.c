#include "matrix4x4.h"

void Matrix4x4fZero(TMatrix4x4f m)
{
    memset(m,0,sizeof(float)*16);
}

void Matrix4x4fIdentity(TMatrix4x4f m)
{
    m[0]=1.0f;  m[4]=0.0f;  m[8]=0.0f;  m[12]=0.0f;
    m[1]=0.0f;  m[5]=1.0f;  m[9]=0.0f;  m[13]=0.0f;
    m[2]=0.0f;  m[6]=0.0f;  m[10]=1.0f;  m[14]=0.0f;
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f;  m[15]=1.0f;
}

void Matrix4x4fCopy(TMatrix4x4f m, TMatrix4x4f m1)
{
   m[0] = m1[0]; m[4] = m1[4]; m[8] = m1[8];   m[12] = m1[12];
   m[1] = m1[1]; m[5] = m1[5]; m[9] = m1[9];   m[13] = m1[13];
   m[2] = m1[2]; m[6] = m1[6]; m[10] = m1[10]; m[14] = m1[14];
   m[3] = m1[3]; m[7] = m1[7]; m[11] = m1[11]; m[15] = m1[15];
}

void Matrix4x4fPrint(TMatrix4x4f m)
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
            printf("%.2f  ", m[j*4+i]);
        printf("\n");
    }
}

///Arithmetic operations

//Macro for fast coding
#define MATRIX4X4_MACRO_FUNC(op,m1,m2)      \
    {                                       \
        m1[0] = m1[0] op m2[0];             \
        m1[1] = m1[1] op m2[1];             \
        m1[2] = m1[2] op m2[2];             \
        m1[3] = m1[3] op m2[3];             \
                                            \
        m1[4] = m1[4] op m2[4];             \
        m1[5] = m1[5] op m2[5];             \
        m1[6] = m1[6] op m2[6];             \
        m1[7] = m1[7] op m2[7];             \
                                            \
        m1[8] = m1[8] op m2[8];             \
        m1[9] = m1[9] op m2[9];             \
        m1[10] = m1[10] op m2[10];          \
        m1[11] = m1[11] op m2[11];          \
                                            \
        m1[12] = m1[12] op m2[12];          \
        m1[13] = m1[13] op m2[13];          \
        m1[14] = m1[14] op m2[14];          \
        m1[15] = m1[15] op m2[15];          \
    }

#define MATRIX4X4_MACRO_FUNC2(op,m,m1,m2)   \
    {                                       \
        m[0] = m1[0] op m2[0];              \
        m[1] = m1[1] op m2[1];              \
        m[2] = m1[2] op m2[2];              \
        m[3] = m1[3] op m2[3];              \
                                            \
        m[4] = m1[4] op m2[4];              \
        m[5] = m1[5] op m2[5];              \
        m[6] = m1[6] op m2[6];              \
        m[7] = m1[7] op m2[7];              \
                                            \
        m[8] = m1[8] op m2[8];              \
        m[9] = m1[9] op m2[9];              \
        m[10] = m1[10] op m2[10];           \
        m[11] = m1[11] op m2[11];           \
                                            \
        m[12] = m1[12] op m2[12];           \
        m[13] = m1[13] op m2[13];           \
        m[14] = m1[14] op m2[14];           \
        m[15] = m1[15] op m2[15];           \
    }

#define MATRIX4X4_MACRO_FUNCC(op,m1,c)      \
    {                                       \
        m1[0] = m1[0] op c;                 \
        m1[1] = m1[1] op c;                 \
        m1[2] = m1[2] op c;                 \
        m1[3] = m1[3] op c;                 \
                                            \
        m1[4] = m1[4] op c;                 \
        m1[5] = m1[5] op c;                 \
        m1[6] = m1[6] op c;                 \
        m1[7] = m1[7] op c;                 \
                                            \
        m1[8] = m1[8] op c;                 \
        m1[9] = m1[9] op c;                 \
        m1[10] = m1[10] op c;               \
        m1[11] = m1[11] op c;               \
                                            \
        m1[12] = m1[12] op c;               \
        m1[13] = m1[13] op c;               \
        m1[14] = m1[14] op c;               \
        m1[15] = m1[15] op c;               \
    }

#define MATRIX4X4_MACRO_FUNCC2(op,m,m1,c)   \
    {                                       \
        m[0] = m1[0] op c;                  \
        m[1] = m1[1] op c;                  \
        m[2] = m1[2] op c;                  \
        m[3] = m1[3] op c;                  \
                                            \
        m[4] = m1[4] op c;                  \
        m[5] = m1[5] op c;                  \
        m[6] = m1[6] op c;                  \
        m[7] = m1[7] op c;                  \
                                            \
        m[8] = m1[8] op c;                  \
        m[9] = m1[9] op c;                  \
        m[10] = m1[10] op c;                \
        m[11] = m1[11] op c;                \
                                            \
        m[12] = m1[12] op c;                \
        m[13] = m1[13] op c;                \
        m[14] = m1[14] op c;                \
        m[15] = m1[15] op c;                \
    }


void Matrix4x4fAdd(TMatrix4x4f m1, TMatrix4x4f m2)                  MATRIX4X4_MACRO_FUNC(+,m1,m2)
void Matrix4x4fAdd2(TMatrix4x4f m, TMatrix4x4f m1, TMatrix4x4f m2)  MATRIX4X4_MACRO_FUNC2(+,m,m1,m2)
void Matrix4x4fAddC(TMatrix4x4f m, float c)                         MATRIX4X4_MACRO_FUNCC(+,m,c)
void Matrix4x4fAddC2(TMatrix4x4f m, TMatrix4x4f m1, float c)        MATRIX4X4_MACRO_FUNCC2(+,m,m1,c)

void Matrix4x4fSub(TMatrix4x4f m1, TMatrix4x4f m2)                  MATRIX4X4_MACRO_FUNC(-,m1,m2)
void Matrix4x4fSub2(TMatrix4x4f m, TMatrix4x4f m1, TMatrix4x4f m2)  MATRIX4X4_MACRO_FUNC2(-,m,m1,m2)
void Matrix4x4fSubC(TMatrix4x4f m, float c)                         MATRIX4X4_MACRO_FUNCC(-,m,c)
void Matrix4x4fSubC2(TMatrix4x4f m, TMatrix4x4f m1, float c)        MATRIX4X4_MACRO_FUNCC2(-,m,m1,c)

void Matrix4x4fMul2(TMatrix4x4f m, TMatrix4x4f m1, TMatrix4x4f m2)
{
    m[0] = m1[0]*m2[0]+m1[4]*m2[1]+m1[8]*m2[2]+m1[12]*m2[3];
    m[1] = m1[1]*m2[0]+m1[5]*m2[1]+m1[9]*m2[2]+m1[13]*m2[3];
    m[2] = m1[2]*m2[0]+m1[6]*m2[1]+m1[10]*m2[2]+m1[14]*m2[3];
    m[3] = m1[3]*m2[0]+m1[7]*m2[1]+m1[11]*m2[2]+m1[15]*m2[3];

    m[4] = m1[0]*m2[4]+m1[4]*m2[5]+m1[8]*m2[6]+m1[12]*m2[7];
    m[5] = m1[1]*m2[4]+m1[5]*m2[5]+m1[9]*m2[6]+m1[13]*m2[7];
    m[6] = m1[2]*m2[4]+m1[6]*m2[5]+m1[10]*m2[6]+m1[14]*m2[7];
    m[7] = m1[3]*m2[4]+m1[7]*m2[5]+m1[11]*m2[6]+m1[15]*m2[7];

    m[8] = m1[0]*m2[8]+m1[4]*m2[9]+m1[8]*m2[10]+m1[12]*m2[11];
    m[9] = m1[1]*m2[8]+m1[5]*m2[9]+m1[9]*m2[10]+m1[13]*m2[11];
    m[10] = m1[2]*m2[8]+m1[6]*m2[9]+m1[10]*m2[10]+m1[14]*m2[11];
    m[11] = m1[3]*m2[8]+m1[7]*m2[9]+m1[11]*m2[10]+m1[15]*m2[11];

    m[12] = m1[0]*m2[12]+m1[4]*m2[13]+m1[8]*m2[14]+m1[12]*m2[15];
    m[13] = m1[1]*m2[12]+m1[5]*m2[13]+m1[9]*m2[14]+m1[13]*m2[15];
    m[14] = m1[2]*m2[12]+m1[6]*m2[13]+m1[10]*m2[14]+m1[14]*m2[15];
    m[15] = m1[3]*m2[12]+m1[7]*m2[13]+m1[11]*m2[14]+m1[15]*m2[15];
}
void Matrix4x4fMulC(TMatrix4x4f m, float c)                         MATRIX4X4_MACRO_FUNCC(*,m,c)
void Matrix4x4fMulC2(TMatrix4x4f m, TMatrix4x4f m1, float c)        MATRIX4X4_MACRO_FUNCC2(*,m,m1,c)

void Matrix4x4fDivC(TMatrix4x4f m, float c)                         MATRIX4X4_MACRO_FUNCC(/,m,c)
void Matrix4x4fDivC2(TMatrix4x4f m, TMatrix4x4f m1, float c)        MATRIX4X4_MACRO_FUNCC2(/,m,m1,c)

int Matrix4x4fInvert(TMatrix4x4f mi, TMatrix4x4f m)
{
    //pre-compute 2x2 dets for last two rows
    //when computing cofactors of first two rows
    float d12 = m[2]*m[7]  - m[3]*m[6];
    float d13 = m[2]*m[11] - m[3]*m[10];
    float d23 = m[6]*m[11] - m[7]*m[10];
    float d24 = m[6]*m[15] - m[7]*m[14];
    float d34 = m[10]*m[15]- m[11]*m[14];
    float d41 = m[14]*m[3] - m[15]*m[2];

    mi[0] =  (m[5]*d34 - m[9]*d24 + m[13]*d23);
    mi[1] = -(m[1]*d34 + m[9]*d41 + m[13]*d13);
    mi[2] =  (m[1]*d24 + m[5]*d41 + m[13]*d12);
    mi[3] = -(m[1]*d23 - m[5]*d13 + m[9]*d12);

    //Compute det
    float det = m[0]*mi[0] + m[4]*mi[1] + m[8]*mi[2] + m[12]*mi[3];
    if(det==0.0f)//singularity test
        return 0;
    float idet=1.0f/det;
    mi[0] *= idet;
    mi[1] *= idet;
    mi[2] *= idet;
    mi[3] *= idet;

    mi[4] = -(m[4]*d34 - m[8]*d24 + m[12]*d23) * idet;
    mi[5] =  (m[0]*d34 + m[8]*d41 + m[12]*d13) * idet;
    mi[6] = -(m[0]*d24 + m[4]*d41 + m[12]*d12) * idet;
    mi[7] =  (m[0]*d23 - m[4]*d13 + m[8]*d12)  * idet;

    d12 = m[0]*m[5]  - m[1]*m[4];
    d13 = m[0]*m[9]  - m[1]*m[8];
    d23 = m[4]*m[9]  - m[5]*m[8];
    d24 = m[4]*m[13] - m[5]*m[12];
    d34 = m[8]*m[13] - m[9]*m[12];
    d41 = m[12]*m[1] - m[13]*m[0];

    mi[8]  =  (m[7]*d34 - m[11]*d24 + m[15]*d23) * idet;
    mi[9]  = -(m[3]*d34 + m[11]*d41 + m[15]*d13) * idet;
    mi[10] =  (m[3]*d24 + m[7]*d41  + m[15]*d12) * idet;
    mi[11] = -(m[3]*d23 - m[7]*d13  + m[11]*d12) * idet;
    mi[12] = -(m[6]*d34 - m[10]*d24 + m[14]*d23) * idet;
    mi[13] =  (m[2]*d34 + m[10]*d41 + m[14]*d13) * idet;
    mi[14] = -(m[2]*d24 + m[6]*d41  + m[14]*d12) * idet;
    mi[15] =  (m[2]*d23 - m[6]*d13  + m[10]*d12) * idet;
    return 1;
}

void Matrix4x4fTranspose(TMatrix4x4f mt, TMatrix4x4f m)
{
    float tmp;
    tmp=m[1]; m[1]=m[4];  m[4]=tmp;
    tmp=m[2]; m[2]=m[8];  m[8]=tmp;
    tmp=m[3]; m[3]=m[12]; m[12]=tmp;

    tmp=m[6]; m[6]=m[9];  m[9]=tmp;
    tmp=m[7]; m[7]=m[13]; m[13]=tmp;

    tmp=m[11]; m[11]=m[14]; m[14]=tmp;
}

///Geometric operations
void Matrix4x4fTranslate(TMatrix4x4f m, float x, float y, float z)
{
    m[0]=1.0f;  m[4]=0.0f;  m[8]=0.0f;  m[12]=x;
    m[1]=0.0f;  m[5]=1.0f;  m[9]=0.0f;  m[13]=y;
    m[2]=0.0f;  m[6]=0.0f;  m[10]=1.0f; m[14]=z;
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f; m[15]=1.0f;
}

void Matrix4x4fRotateX(TMatrix4x4f m, float arad)
{
    float sin_t = sin(arad);
    float cos_t = cos(arad);
    m[0]=1.0f;  m[4]=0.0f;   m[8]=0.0f;   m[12]=0.0f;
    m[1]=0.0f;  m[5]=cos_t;  m[9]=-sin_t; m[13]=0.0f;
    m[2]=0.0f;  m[6]=sin_t;  m[10]=cos_t; m[14]=0.0f;
    m[3]=0.0f;  m[7]=0.0f;   m[11]=0.0f;  m[15]=1.0f;
}
void Matrix4x4fRotateY(TMatrix4x4f m, float arad)
{
    float sin_t = sin(arad);
    float cos_t = cos(arad);
    m[0]=cos_t;  m[4]=0.0f;  m[8]=sin_t;  m[12]=0.0f;
    m[1]=0.0f;   m[5]=1.0f;  m[9]=0.0f;   m[13]=0.0f;
    m[2]=-sin_t; m[6]=0.0f;  m[10]=cos_t; m[14]=0.0f;
    m[3]=0.0f;   m[7]=0.0f;  m[11]=0.0f;  m[15]=1.0f;
}
void Matrix4x4fRotateZ(TMatrix4x4f m, float arad)
{
    float sin_t = sin(arad);
    float cos_t = cos(arad);
    m[0]=cos_t;  m[4]=-sin_t; m[8]=0.0;   m[12]=0.0f;
    m[1]=sin_t;  m[5]=cos_t;  m[9]=0.0f;  m[13]=0.0f;
    m[2]=0.0f;   m[6]=0.0f;   m[10]=1.0f; m[14]=0.0f;
    m[3]=0.0f;   m[7]=0.0f;   m[11]=0.0f; m[15]=1.0f;
}

void Matrix4x4fScale(TMatrix4x4f m, float x, float y, float z)
{
    m[0]=1.0f/x;   m[4]=0.0f;    m[8]=0.0;       m[12]=0.0f;
    m[1]=0.0f;     m[5]=1.0f/y;  m[9]=0.0f;      m[13]=0.0f;
    m[2]=0.0f;     m[6]=0.0f;    m[10]=1.0f/z;   m[14]=0.0f;
    m[3]=0.0f;     m[7]=0.0f;    m[11]=0.0f;     m[15]=1.0f;
}

void Matrix4x4fFrustum(TMatrix4x4f m,
                            float left, float right,
                            float bottom, float top,
                            float near, float far)
{
    Matrix4x4fIdentity(m);
    if((right==left) || (top==bottom)
     || (near==far) || (near<0.0f) || (far<0.0f))
        return;
    m[0]=(2.0f*near)/(right-left);

    m[5]=(2.0f*near)/(top-bottom);

    m[8]=(right+left)/(right-left);
    m[9]=(top+bottom)/(top-bottom);
    m[10]=-(far+near)/(far-near);
    m[11]=-1.0f;

    m[14]=-(2.0f*far*near)/(far-near);
    m[15]=0.0f;
}

void Matrix4x4fPerspective(TMatrix4x4f m,
                                float fov, float aspect,
                                float near, float far)
{
    float top=near*tan(radian(0.5f*fov));
    float right=top*aspect;
    Matrix4x4fFrustum(m,-right,right,-top,top,near,far);
}

void Matrix4x4fOrthographic(TMatrix4x4f m,
                                 float left, float right,
                                 float bottom, float top,
                                 float near, float far)
{
    float rl=right-left;
    float tb=top-bottom;
    float fn=far-near;
    m[0]=2.0f/rl;   m[4]=0.0f;      m[8]=0.0f;      m[12]=-(right+left)/rl;
    m[1]=0.0f;      m[5]=2.0f/tb;   m[9]=0.0f;      m[13]=-(top+bottom)/tb;
    m[2]=0.0f;      m[6]=0.0f;      m[10]=-2.0f/fn; m[14]=-(far+near)/fn;
    m[3]=0.0f;      m[7]=0.0f;      m[11]=0.0f;     m[15]=1.0f;
}

void Matrix4x4fLookAt(TMatrix4x4f m, vec3f eye, vec3f center, vec3f up)
{
    vec3f f,s,u;
    Vec3fSub2(f,center,eye);
    Vec3fNormalize(f);
    Vec3fCross(s,f,up);
    Vec3fNormalize(s);
    Vec3fCross(u,s,f);
    m[0]=s[0];  m[4]=s[1];  m[8]=s[2];   m[12]=-Vec3fDot(s,eye);
    m[1]=u[0];  m[5]=u[1];  m[9]=u[2];   m[13]=-Vec3fDot(u,eye);
    m[2]=-f[0]; m[6]=-f[1]; m[10]=-f[2]; m[14]=Vec3fDot(f,eye);
    m[3]=0.0f;  m[7]=0.0f;  m[11]=0.0f;  m[15]=1.0f;
}

