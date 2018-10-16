#if !defined(VECTOR3_H)
#define VECTOR3_H

#include <math.h>

/// Macro definition, don't use these functions
#define Vec3Copy(v1,v2) {v1[0]=v2[0]; v1[1]=v2[1]; v1[2]=v2[2];}
#define Vec3IsEqual(v1,v2) (v1[0]==v2[0] && v1[1]==v2[1] && v1[2]==v2[2])

/// ///////////////////////////
///Vector of size 3, type float
/// ///////////////////////////
typedef float vec3f[3];

#define Vec3fCopy(v1,v2) Vec3Copy(v1,v2)
#define Vec3fIsEqual(v1,v2) Vec3IsEqual(v1,v2)

void Vec3fAdd(vec3f v1, vec3f v2);
void Vec3fAdd2(vec3f v, vec3f v1, vec3f v2);
void Vec3fAddC(vec3f v, float c);
void Vec3fAddC2(vec3f v, vec3f v1, float c);

void Vec3fSub(vec3f v1, vec3f v2);
void Vec3fSub2(vec3f v, vec3f v1, vec3f v2);
void Vec3fSubC(vec3f v, float c);
void Vec3fSubC2(vec3f v, vec3f v1, float c);

void Vec3fMul(vec3f v1, vec3f v2);
void Vec3fMul2(vec3f v, vec3f v1, vec3f v2);
void Vec3fMulC(vec3f v, float c);
void Vec3fMulC2(vec3f v, vec3f v1, float c);

void Vec3fDiv(vec3f v1, vec3f v2);
void Vec3fDiv2(vec3f v, vec3f v1, vec3f v2);
void Vec3fDivC(vec3f v, float c);
void Vec3fDivC2(vec3f v, vec3f v1, float c);

void Vec3fNormalize(vec3f v);
float Vec3fLength(vec3f v);
void Vec3fCross(vec3f v, vec3f v1, vec3f v2);
float Vec3fDot(vec3f v1, vec3f v2);

/// ///////////////////////////
///Vector of size 3, type int
/// ///////////////////////////

typedef int vec3i[3];

#define Vec3iCopy(v1,v2) Vec3Copy(v1,v2)
#define Vec3iIsEqual(v1,v2) Vec3IsEqual(v1,v2)

void Vec3iAdd(vec3i v1, vec3i v2);
void Vec3iAdd2(vec3i v, vec3i v1, vec3i v2);
void Vec3iAddC(vec3i v, float c);
void Vec3iAddC2(vec3i v, vec3i v1, float c);

void Vec3iSub(vec3i v1, vec3i v2);
void Vec3iSub2(vec3i v, vec3i v1, vec3i v2);
void Vec3iSubC(vec3i v, float c);
void Vec3iSubC2(vec3i v, vec3i v1, float c);

void Vec3iMul(vec3i v1, vec3i v3);
void Vec3iMul2(vec3i v, vec3i v1, vec3i v2);
void Vec3iMulC(vec3i v, float c);
void Vec3iMulC2(vec3i v, vec3i v1, float c);

void Vec3iDiv(vec3i v1, vec3i v2);
void Vec3iDiv2(vec3i v, vec3i v1, vec3i v2);
void Vec3iDivC(vec3i v, float c);
void Vec3iDivC2(vec3i v, vec3i v1, float c);

void Vec3iNormalize(vec3i v);
void Vec3iCross(vec3i v, vec3i v1, vec3i v2);
int Vec3iDot(vec3i v1, vec3i v2);

/// ///////////////////////////
///Vector of size 3, type unsigned int
/// ///////////////////////////

typedef int vec3ui[3];

#define Vec3uiCopy(v1,v2) Vec3Copy(v1,v2)
#define Vec3uiIsEqual(v1,v2) Vec3IsEqual(v1,v2)

void Vec3uiAdd(vec3ui v1, vec3ui v2);
void Vec3uiAdd2(vec3ui v, vec3ui v1, vec3ui v2);
void Vec3uiAddC(vec3ui v, float c);
void Vec3uiAddC2(vec3ui v, vec3ui v1, float c);

void Vec3uiSub(vec3ui v1, vec3ui v2);
void Vec3uiSub2(vec3ui v, vec3ui v1, vec3ui v2);
void Vec3uiSubC(vec3ui v, float c);
void Vec3uiSubC2(vec3ui v, vec3ui v1, float c);

void Vec3uiMul(vec3ui v1, vec3ui v3);
void Vec3uiMul2(vec3ui v, vec3ui v1, vec3ui v2);
void Vec3uiMulC(vec3ui v, float c);
void Vec3uiMulC2(vec3ui v, vec3ui v1, float c);

void Vec3uiDiv(vec3ui v1, vec3ui v2);
void Vec3uiDiv2(vec3ui v, vec3ui v1, vec3ui v2);
void Vec3uiDivC(vec3ui v, float c);
void Vec3uiDivC2(vec3ui v, vec3ui v1, float c);

void Vec3uiNormalize(vec3ui v);
void Vec3uiCross(vec3ui v, vec3ui v1, vec3ui v2);
unsigned int Vec3uiDot(vec3ui v1, vec3ui v2);

#endif //VECTOR3_H
