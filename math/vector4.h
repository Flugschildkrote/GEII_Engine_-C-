#if !defined(VECTOR4_H)
#define VECTOR4_H

#include <math.h>

/// Macro definition, don't use these functions
#define Vec4Copy(v1,v2) {v1[0]=v2[0]; v1[1]=v2[1]; v1[2]=v2[2]; v1[3]=v2[3];}
#define Vec4IsEqual(v1,v2) (v1[0]==v2[0] && v1[1]==v2[1] && v1[3]==v2[3] && v1[3]==v2[3])

/// ///////////////////////////
///Vector of size 4, type float
/// ///////////////////////////
typedef float vec4f[4];

#define Vec4fCopy(v1,v2) Vec4Copy(v1,v2)
#define Vec4fIsEqual(v1,v2) Vec4IsEqual(v1,v2)

void Vec4fAdd(vec4f v1, vec4f v2);
void Vec4fAdd2(vec4f v, vec4f v1, vec4f v2);
void Vec4fAddC(vec4f v, float c);
void Vec4fAddC2(vec4f v, vec4f v1, float c);

void Vec4fSub(vec4f v1, vec4f v2);
void Vec4fSub2(vec4f v, vec4f v1, vec4f v2);
void Vec4fSubC(vec4f v, float c);
void Vec4fSubC2(vec4f v, vec4f v1, float c);

void Vec4fMul(vec4f v1, vec4f v2);
void Vec4fMul2(vec4f v, vec4f v1, vec4f v2);
void Vec4fMulC(vec4f v, float c);
void Vec4fMulC2(vec4f v, vec4f v1, float c);

void Vec4fDiv(vec4f v1, vec4f v2);
void Vec4fDiv2(vec4f v, vec4f v1, vec4f v2);
void Vec4fDivC(vec4f v, float c);
void Vec4fDivC2(vec4f v, vec4f v1, float c);

void Vec4fNormalize(vec4f v);
float Vec4fDot(vec4f v1, vec4f v2);

/// ///////////////////////////
///Vector of size 4, type int
/// ///////////////////////////

typedef int vec4i[4];

#define Vec4iCopy(v1,v2) Vec4Copy(v1,v2)
#define Vec4iIsEqual(v1,v2) Vec4IsEqual(v1,v2)

void Vec4iAdd(vec4i v1, vec4i v2);
void Vec4iAdd2(vec4i v, vec4i v1, vec4i v2);
void Vec4iAddC(vec4i v, float c);
void Vec4iAddC2(vec4i v, vec4i v1, float c);

void Vec4iSub(vec4i v1, vec4i v2);
void Vec4iSub2(vec4i v, vec4i v1, vec4i v2);
void Vec4iSubC(vec4i v, float c);
void Vec4iSubC2(vec4i v, vec4i v1, float c);

void Vec4iMul(vec4i v1, vec4i v4);
void Vec4iMul2(vec4i v, vec4i v1, vec4i v2);
void Vec4iMulC(vec4i v, float c);
void Vec4iMulC2(vec4i v, vec4i v1, float c);

void Vec4iDiv(vec4i v1, vec4i v2);
void Vec4iDiv2(vec4i v, vec4i v1, vec4i v2);
void Vec4iDivC(vec4i v, float c);
void Vec4iDivC2(vec4i v, vec4i v1, float c);

void Vec4iNormalize(vec4i v);
int Vec4iDot(vec4i v1, vec4i v2);

#endif //VECTOR4_H
