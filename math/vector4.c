#include "vector4.h"

//Macro for fast coding
#define VEC4_MACRO_FUNC(op,v1,v2)       \
    {                                   \
        v1[0] = v1[0] op v2[0];         \
        v1[1] = v1[1] op v2[1];         \
        v1[2] = v1[2] op v2[2];         \
        v1[3] = v1[3] op v2[3];         \
    }

#define VEC4_MACRO_FUNC2(op,v,v1,v2)    \
    {                                   \
        v[0] = v1[0] op v2[0];          \
        v[1] = v1[1] op v2[1];          \
        v[2] = v1[2] op v2[2];          \
        v[3] = v1[3] op v2[3];          \
    }

#define VEC4_MACRO_FUNCC(op,v,c)        \
    {                                   \
        v[0] = v[0] op c;               \
        v[1] = v[1] op c;               \
        v[2] = v[2] op c;               \
        v[3] = v[3] op c;               \
    }

#define VEC4_MACRO_FUNCC2(op,v,v1,c)    \
    {                                   \
        v[0] = v1[0] op c;              \
        v[1] = v1[1] op c;              \
        v[2] = v1[2] op c;              \
        v[3] = v1[3] op c;              \
    }

/// ///////////////////////////
///Vector of size 4, type float
/// ///////////////////////////

inline void Vec4fAdd(vec4f v1, vec4f v2)           VEC4_MACRO_FUNC(+,v1,v2)
inline void Vec4fAdd2(vec4f v, vec4f v1, vec4f v2) VEC4_MACRO_FUNC2(+,v,v1,v2)
inline void Vec4fAddC(vec4f v, float c)            VEC4_MACRO_FUNCC(+,v,c)
inline void Vec4fAddC2(vec4f v, vec4f v1, float c) VEC4_MACRO_FUNCC2(+,v,v1,c)

inline void Vec4fSub(vec4f v1, vec4f v2)           VEC4_MACRO_FUNC(-,v1,v2)
inline void Vec4fSub2(vec4f v, vec4f v1, vec4f v2) VEC4_MACRO_FUNC2(-,v,v1,v2)
inline void Vec4fSubC(vec4f v, float c)            VEC4_MACRO_FUNCC(-,v,c)
inline void Vec4fSubC2(vec4f v, vec4f v1, float c) VEC4_MACRO_FUNCC2(-,v,v1,c)

inline void Vec4fMul(vec4f v1, vec4f v2)           VEC4_MACRO_FUNC(*,v1,v2)
inline void Vec4fMul2(vec4f v, vec4f v1, vec4f v2) VEC4_MACRO_FUNC2(*,v,v1,v2)
inline void Vec4fMulC(vec4f v, float c)            VEC4_MACRO_FUNCC(*,v,c)
inline void Vec4fMulC2(vec4f v, vec4f v1, float c) VEC4_MACRO_FUNCC2(*,v,v1,c)

inline void Vec4fDiv(vec4f v1, vec4f v2)           VEC4_MACRO_FUNC(/,v1,v2)
inline void Vec4fDiv2(vec4f v, vec4f v1, vec4f v2) VEC4_MACRO_FUNC2(/,v,v1,v2)
inline void Vec4fDivC(vec4f v, float c)            VEC4_MACRO_FUNCC(/,v,c)
inline void Vec4fDivC2(vec4f v, vec4f v1, float c) VEC4_MACRO_FUNCC2(/,v,v1,c)

inline void Vec4fNormalize(vec4f v)
{
    float l=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
    VEC4_MACRO_FUNCC(/,v,l);
}

inline float Vec4fDot(vec4f v1, vec4f v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3];
}

/// ///////////////////////////
///Vector of size 4, type int
/// ///////////////////////////

inline void Vec4iAdd(vec4i v1, vec4i v2)           VEC4_MACRO_FUNC(+,v1,v2)
inline void Vec4iAdd2(vec4i v, vec4i v1, vec4i v2) VEC4_MACRO_FUNC2(+,v,v1,v2)
inline void Vec4iAddC(vec4i v, float c)            VEC4_MACRO_FUNCC(+,v,c)
inline void Vec4iAddC2(vec4i v, vec4i v1, float c) VEC4_MACRO_FUNCC2(+,v,v1,c)

inline void Vec4iSub(vec4i v1, vec4i v2)           VEC4_MACRO_FUNC(-,v1,v2)
inline void Vec4iSub2(vec4i v, vec4i v1, vec4i v2) VEC4_MACRO_FUNC2(-,v,v1,v2)
inline void Vec4iSubC(vec4i v, float c)            VEC4_MACRO_FUNCC(-,v,c)
inline void Vec4iSubC2(vec4i v, vec4i v1, float c) VEC4_MACRO_FUNCC2(-,v,v1,c)

inline void Vec4iMul(vec4i v1, vec4i v2)           VEC4_MACRO_FUNC(*,v1,v2)
inline void Vec4iMul2(vec4i v, vec4i v1, vec4i v2) VEC4_MACRO_FUNC2(*,v,v1,v2)
inline void Vec4iMulC(vec4i v, float c)            VEC4_MACRO_FUNCC(*,v,c)
inline void Vec4iMulC2(vec4i v, vec4i v1, float c) VEC4_MACRO_FUNCC2(*,v,v1,c)

inline void Vec4iDiv(vec4i v1, vec4i v2)           VEC4_MACRO_FUNC(/,v1,v2)
inline void Vec4iDiv2(vec4i v, vec4i v1, vec4i v2) VEC4_MACRO_FUNC2(/,v,v1,v2)
inline void Vec4iDivC(vec4i v, float c)            VEC4_MACRO_FUNCC(/,v,c)
inline void Vec4iDivC2(vec4i v, vec4i v1, float c) VEC4_MACRO_FUNCC2(/,v,v1,c)

inline void Vec4iNormalize(vec4i v)
{
    int l=sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]+v[3]*v[3]);
    VEC4_MACRO_FUNCC(/,v,l);
}

inline int Vec4iDot(vec4i v1, vec4i v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2]+v1[3]*v2[3];
}
