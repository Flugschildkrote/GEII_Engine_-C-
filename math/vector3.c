#include "vector3.h"

//Macro for fast coding
#define VEC3_MACRO_FUNC(op,v1,v2)       \
    {                                   \
        v1[0] = v1[0] op v2[0];         \
        v1[1] = v1[1] op v2[1];         \
        v1[2] = v1[2] op v2[2];         \
    }

#define VEC3_MACRO_FUNC2(op,v,v1,v2)    \
    {                                   \
        v[0] = v1[0] op v2[0];          \
        v[1] = v1[1] op v2[1];          \
        v[2] = v1[2] op v2[2];          \
    }

#define VEC3_MACRO_FUNCC(op,v,c)        \
    {                                   \
        v[0] = v[0] op c;               \
        v[1] = v[1] op c;               \
        v[2] = v[2] op c;               \
    }

#define VEC3_MACRO_FUNCC2(op,v,v1,c)    \
    {                                   \
        v[0] = v1[0] op c;              \
        v[1] = v1[1] op c;              \
        v[2] = v1[2] op c;              \
    }

/// ///////////////////////////
///Vector of size 3, type float
/// ///////////////////////////

inline void Vec3fAdd(vec3f v1, vec3f v2)           VEC3_MACRO_FUNC(+,v1,v2)
inline void Vec3fAdd2(vec3f v, vec3f v1, vec3f v2) VEC3_MACRO_FUNC2(+,v,v1,v2)
inline void Vec3fAddC(vec3f v, float c)            VEC3_MACRO_FUNCC(+,v,c)
inline void Vec3fAddC2(vec3f v, vec3f v1, float c) VEC3_MACRO_FUNCC2(+,v,v1,c)

inline void Vec3fSub(vec3f v1, vec3f v2)           VEC3_MACRO_FUNC(-,v1,v2)
inline void Vec3fSub2(vec3f v, vec3f v1, vec3f v2) VEC3_MACRO_FUNC2(-,v,v1,v2)
inline void Vec3fSubC(vec3f v, float c)            VEC3_MACRO_FUNCC(-,v,c)
inline void Vec3fSubC2(vec3f v, vec3f v1, float c) VEC3_MACRO_FUNCC2(-,v,v1,c)

inline void Vec3fMul(vec3f v1, vec3f v2)           VEC3_MACRO_FUNC(*,v1,v2)
inline void Vec3fMul2(vec3f v, vec3f v1, vec3f v2) VEC3_MACRO_FUNC2(*,v,v1,v2)
inline void Vec3fMulC(vec3f v, float c)            VEC3_MACRO_FUNCC(*,v,c)
inline void Vec3fMulC2(vec3f v, vec3f v1, float c) VEC3_MACRO_FUNCC2(*,v,v1,c)

inline void Vec3fDiv(vec3f v1, vec3f v2)           VEC3_MACRO_FUNC(/,v1,v2)
inline void Vec3fDiv2(vec3f v, vec3f v1, vec3f v2) VEC3_MACRO_FUNC2(/,v,v1,v2)
inline void Vec3fDivC(vec3f v, float c)            VEC3_MACRO_FUNCC(/,v,c)
inline void Vec3fDivC2(vec3f v, vec3f v1, float c) VEC3_MACRO_FUNCC2(/,v,v1,c)

inline void Vec3fNormalize(vec3f v)
{
    float l=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    VEC3_MACRO_FUNCC(/,v,l);
}

inline float Vec3fLength(vec3f v)
{
    return sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

inline void Vec3fCross(vec3f v, vec3f v1, vec3f v2)
{
    v[0]=v1[1]*v2[2]-v1[2]*v2[1];
    v[1]=v1[2]*v2[0]-v1[0]*v2[2];
    v[2]=v1[0]*v2[1]-v1[1]*v2[0];
}

inline float Vec3fDot(vec3f v1, vec3f v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
}

/// ///////////////////////////
///Vector of size 3, type int
/// ///////////////////////////

inline void Vec3iAdd(vec3i v1, vec3i v2)           VEC3_MACRO_FUNC(+,v1,v2)
inline void Vec3iAdd2(vec3i v, vec3i v1, vec3i v2) VEC3_MACRO_FUNC2(+,v,v1,v2)
inline void Vec3iAddC(vec3i v, float c)            VEC3_MACRO_FUNCC(+,v,c)
inline void Vec3iAddC2(vec3i v, vec3i v1, float c) VEC3_MACRO_FUNCC2(+,v,v1,c)

inline void Vec3iSub(vec3i v1, vec3i v2)           VEC3_MACRO_FUNC(-,v1,v2)
inline void Vec3iSub2(vec3i v, vec3i v1, vec3i v2) VEC3_MACRO_FUNC2(-,v,v1,v2)
inline void Vec3iSubC(vec3i v, float c)            VEC3_MACRO_FUNCC(-,v,c)
inline void Vec3iSubC2(vec3i v, vec3i v1, float c) VEC3_MACRO_FUNCC2(-,v,v1,c)

inline void Vec3iMul(vec3i v1, vec3i v2)           VEC3_MACRO_FUNC(*,v1,v2)
inline void Vec3iMul2(vec3i v, vec3i v1, vec3i v2) VEC3_MACRO_FUNC2(*,v,v1,v2)
inline void Vec3iMulC(vec3i v, float c)            VEC3_MACRO_FUNCC(*,v,c)
inline void Vec3iMulC2(vec3i v, vec3i v1, float c) VEC3_MACRO_FUNCC2(*,v,v1,c)

inline void Vec3iDiv(vec3i v1, vec3i v2)           VEC3_MACRO_FUNC(/,v1,v2)
inline void Vec3iDiv2(vec3i v, vec3i v1, vec3i v2) VEC3_MACRO_FUNC2(/,v,v1,v2)
inline void Vec3iDivC(vec3i v, float c)            VEC3_MACRO_FUNCC(/,v,c)
inline void Vec3iDivC2(vec3i v, vec3i v1, float c) VEC3_MACRO_FUNCC2(/,v,v1,c)

inline void Vec3iNormalize(vec3i v)
{
    int l=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    VEC3_MACRO_FUNCC(/,v,l);
}

inline void Vec3iCross(vec3i v, vec3i v1, vec3i v2)
{
    v[0]=v1[1]*v2[2]-v1[2]*v2[1];
    v[1]=v1[2]*v2[0]-v1[0]*v2[2];
    v[2]=v1[0]*v2[1]-v1[1]*v2[0];
}

inline int Vec3iDot(vec3i v1, vec3i v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
}

/// ///////////////////////////
///Vector of size 3, type unsigned int
/// ///////////////////////////

inline void Vec3uiAdd(vec3ui v1, vec3ui v2)             VEC3_MACRO_FUNC(+,v1,v2)
inline void Vec3uiAdd2(vec3ui v, vec3ui v1, vec3ui v2)  VEC3_MACRO_FUNC2(+,v,v1,v2)
inline void Vec3uiAddC(vec3ui v, float c)               VEC3_MACRO_FUNCC(+,v,c)
inline void Vec3uiAddC2(vec3ui v, vec3ui v1, float c)   VEC3_MACRO_FUNCC2(+,v,v1,c)

inline void Vec3uiSub(vec3ui v1, vec3ui v2)             VEC3_MACRO_FUNC(-,v1,v2)
inline void Vec3uiSub2(vec3ui v, vec3ui v1, vec3ui v2)  VEC3_MACRO_FUNC2(-,v,v1,v2)
inline void Vec3uiSubC(vec3ui v, float c)               VEC3_MACRO_FUNCC(-,v,c)
inline void Vec3uiSubC2(vec3ui v, vec3ui v1, float c)   VEC3_MACRO_FUNCC2(-,v,v1,c)

inline void Vec3uiMul(vec3ui v1, vec3ui v2)             VEC3_MACRO_FUNC(*,v1,v2)
inline void Vec3uiMul2(vec3ui v, vec3ui v1, vec3ui v2)  VEC3_MACRO_FUNC2(*,v,v1,v2)
inline void Vec3uiMulC(vec3ui v, float c)               VEC3_MACRO_FUNCC(*,v,c)
inline void Vec3uiMulC2(vec3ui v, vec3ui v1, float c)   VEC3_MACRO_FUNCC2(*,v,v1,c)

inline void Vec3uiDiv(vec3ui v1, vec3ui v2)             VEC3_MACRO_FUNC(/,v1,v2)
inline void Vec3uiDiv2(vec3ui v, vec3ui v1, vec3ui v2)  VEC3_MACRO_FUNC2(/,v,v1,v2)
inline void Vec3uiDivC(vec3ui v, float c)               VEC3_MACRO_FUNCC(/,v,c)
inline void Vec3uiDivC2(vec3ui v, vec3ui v1, float c)   VEC3_MACRO_FUNCC2(/,v,v1,c)

inline void Vec3uiNormalize(vec3ui v)
{
    int l=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
    VEC3_MACRO_FUNCC(/,v,l);
}

inline void Vec3uiCross(vec3ui v, vec3ui v1, vec3ui v2)
{
    v[0]=v1[1]*v2[2]-v1[2]*v2[1];
    v[1]=v1[2]*v2[0]-v1[0]*v2[2];
    v[2]=v1[0]*v2[1]-v1[1]*v2[0];
}

inline unsigned int Vec3uiDot(vec3ui v1, vec3ui v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2];
}
