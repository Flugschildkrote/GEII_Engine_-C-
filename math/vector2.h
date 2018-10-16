#if !defined(VECTOR2_H)
#define VECTOR2_H

#include <math.h>

/// Macro definition, don't use these functions
#define Vec2Copy(v1,v2) {v1[0]=v2[0]; v1[1]=v2[1];}
#define Vec2IsEqual(v1,v2) (v1[0]==v2[0] && v1[1]==v2[1])

/// ///////////////////////////
///Vector of size 2, type float
/// ///////////////////////////
typedef float vec2f[2];

#define Vec2fCopy(v1,v2) Vec2Copy(v1,v2)
#define Vec2fIsEqual(v1,v2) Vec2IsEqual(v1,v2)

void Vec2fAdd(vec2f v1, vec2f v2);
void Vec2fAdd2(vec2f v, vec2f v1, vec2f v2);
void Vec2fAddC(vec2f v, float c);
void Vec2fAddC2(vec2f v, vec2f v1, float c);

void Vec2fSub(vec2f v1, vec2f v2);
void Vec2fSub2(vec2f v, vec2f v1, vec2f v2);
void Vec2fSubC(vec2f v, float c);
void Vec2fSubC2(vec2f v, vec2f v1, float c);

void Vec2fMul(vec2f v1, vec2f v2);
void Vec2fMul2(vec2f v, vec2f v1, vec2f v2);
void Vec2fMulC(vec2f v, float c);
void Vec2fMulC2(vec2f v, vec2f v1, float c);

void Vec2fDiv(vec2f v1, vec2f v2);
void Vec2fDiv2(vec2f v, vec2f v1, vec2f v2);
void Vec2fDivC(vec2f v, float c);
void Vec2fDivC2(vec2f v, vec2f v1, float c);

void Vec2fNormalize(vec2f v);
float Vec2fDot(vec2f v1, vec2f v2);

/// ///////////////////////////
///Vector of size 2, type int
/// ///////////////////////////

typedef int vec2i[2];

#define Vec2iCopy(v1,v2) Vec2Copy(v1,v2)
#define Vec2iIsEqual(v1,v2) Vec2IsEqual(v1,v2)

void Vec2iAdd(vec2i v1, vec2i v2);
void Vec2iAdd2(vec2i v, vec2i v1, vec2i v2);
void Vec2iAddC(vec2i v, float c);
void Vec2iAddC2(vec2i v, vec2i v1, float c);

void Vec2iSub(vec2i v1, vec2i v2);
void Vec2iSub2(vec2i v, vec2i v1, vec2i v2);
void Vec2iSubC(vec2i v, float c);
void Vec2iSubC2(vec2i v, vec2i v1, float c);

void Vec2iMul(vec2i v1, vec2i v2);
void Vec2iMul2(vec2i v, vec2i v1, vec2i v2);
void Vec2iMulC(vec2i v, float c);
void Vec2iMulC2(vec2i v, vec2i v1, float c);

void Vec2iDiv(vec2i v1, vec2i v2);
void Vec2iDiv2(vec2i v, vec2i v1, vec2i v2);
void Vec2iDivC(vec2i v, float c);
void Vec2iDivC2(vec2i v, vec2i v1, float c);

void Vec2iNormalize(vec2i v);
int Vec2iDot(vec2i v1, vec2i v2);
#endif //VECTOR2_H
