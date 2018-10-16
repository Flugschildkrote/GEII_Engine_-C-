#if !defined(MATRIX4X4_H)
#define MATRIX4X4_H

#include <string.h>
#include <math.h>
#include <stdio.h>

#include "vector.h"
#include "mathutil.h"

/// Definition of a matrix of size 4x4, type float
// OpenGL matrices are column major.
//  | a0    a4      a8      a12|
//  | a1    a5      a9      a13|
//  | a2    a6      a10     a14|
//  | a3    a7      a11     a15|
typedef float TMatrix4x4f[16];

void Matrix4x4fZero(TMatrix4x4f m);
void Matrix4x4fIdentity(TMatrix4x4f m);

void Matrix4x4fCopy(TMatrix4x4f m, TMatrix4x4f m1);

void Matrix4x4fPrint(TMatrix4x4f m);

///Arithmetic operations
void Matrix4x4fAdd(TMatrix4x4f m1, TMatrix4x4f m2);
void Matrix4x4fAdd2(TMatrix4x4f m, TMatrix4x4f m1, TMatrix4x4f m2);
void Matrix4x4fAddC(TMatrix4x4f m, float c);
void Matrix4x4fAddC2(TMatrix4x4f m, TMatrix4x4f m1, float c);

void Matrix4x4fSub(TMatrix4x4f m1, TMatrix4x4f m2);
void Matrix4x4fSub2(TMatrix4x4f m, TMatrix4x4f m1, TMatrix4x4f m2);
void Matrix4x4fSubC(TMatrix4x4f m, float c);
void Matrix4x4fSubC2(TMatrix4x4f m, TMatrix4x4f m1, float c);

void Matrix4x4fMul2(TMatrix4x4f m, TMatrix4x4f m1, TMatrix4x4f m2);
void Matrix4x4fMulC(TMatrix4x4f m, float c);
void Matrix4x4fMulC2(TMatrix4x4f m, TMatrix4x4f m1, float c);

void Matrix4x4fDivC(TMatrix4x4f m, float c);
void Matrix4x4fDivC2(TMatrix4x4f m, TMatrix4x4f m1, float c);

int Matrix4x4fInvert(TMatrix4x4f mi, TMatrix4x4f m);
void Matrix4x4fTranspose(TMatrix4x4f mt, TMatrix4x4f m);

///Geometric operations
void Matrix4x4fTranslate(TMatrix4x4f m, float x, float y, float z);

void Matrix4x4fRotateX(TMatrix4x4f m, float arad);
void Matrix4x4fRotateY(TMatrix4x4f m, float arad);
void Matrix4x4fRotateZ(TMatrix4x4f m, float arad);

void Matrix4x4fScale(TMatrix4x4f m, float x, float y, float z);

void Matrix4x4fFrustum(TMatrix4x4f m, float left, float right, float bottom, float top, float near, float far);
void Matrix4x4fPerspective(TMatrix4x4f m, float fov, float aspect, float near, float far);
void Matrix4x4fOrthographic(TMatrix4x4f m, float left, float right, float bottom, float top, float near, float far);
void Matrix4x4fLookAt(TMatrix4x4f m, vec3f eye, vec3f center, vec3f up);

#endif //MATRIX4X4_H
