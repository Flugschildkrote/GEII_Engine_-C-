#include "vector2.h"

//Macro for fast coding
#define VEC2_MACRO_FUNC(op,v1,v2)       \
    {                                   \
        v1[0] = v1[0] op v2[0];         \
        v1[1] = v1[1] op v2[1];         \
    }

#define VEC2_MACRO_FUNC2(op,v,v1,v2)    \
    {                                   \
        v[0] = v1[0] op v2[0];          \
        v[1] = v1[1] op v2[1];          \
    }

#define VEC2_MACRO_FUNCC(op,v,c)        \
    {                                   \
        v[0] = v[0] op c;               \
        v[1] = v[1] op c;               \
    }

#define VEC2_MACRO_FUNCC2(op,v,v1,c)    \
    {                                   \
        v[0] = v1[0] op c;              \
        v[1] = v1[1] op c;              \
    }

/// ///////////////////////////
///Vector of size 2, type float
/// ///////////////////////////

inline void Vec2fAdd(vec2f v1, vec2f v2)           VEC2_MACRO_FUNC(+,v1,v2)
inline void Vec2fAdd2(vec2f v, vec2f v1, vec2f v2) VEC2_MACRO_FUNC2(+,v,v1,v2)
inline void Vec2fAddC(vec2f v, float c)            VEC2_MACRO_FUNCC(+,v,c)
inline void Vec2fAddC2(vec2f v, vec2f v1, float c) VEC2_MACRO_FUNCC2(+,v,v1,c)

inline void Vec2fSub(vec2f v1, vec2f v2)           VEC2_MACRO_FUNC(-,v1,v2)
inline void Vec2fSub2(vec2f v, vec2f v1, vec2f v2) VEC2_MACRO_FUNC2(-,v,v1,v2)
inline void Vec2fSubC(vec2f v, float c)            VEC2_MACRO_FUNCC(-,v,c)
inline void Vec2fSubC2(vec2f v, vec2f v1, float c) VEC2_MACRO_FUNCC2(-,v,v1,c)

inline void Vec2fMul(vec2f v1, vec2f v2)           VEC2_MACRO_FUNC(*,v1,v2)
inline void Vec2fMul2(vec2f v, vec2f v1, vec2f v2) VEC2_MACRO_FUNC2(*,v,v1,v2)
inline void Vec2fMulC(vec2f v, float c)            VEC2_MACRO_FUNCC(*,v,c)
inline void Vec2fMulC2(vec2f v, vec2f v1, float c) VEC2_MACRO_FUNCC2(*,v,v1,c)

inline void Vec2fDiv(vec2f v1, vec2f v2)           VEC2_MACRO_FUNC(/,v1,v2)
inline void Vec2fDiv2(vec2f v, vec2f v1, vec2f v2) VEC2_MACRO_FUNC2(/,v,v1,v2)
inline void Vec2fDivC(vec2f v, float c)            VEC2_MACRO_FUNCC(/,v,c)
inline void Vec2fDivC2(vec2f v, vec2f v1, float c) VEC2_MACRO_FUNCC2(/,v,v1,c)

inline void Vec2fNormalize(vec2f v)
{
    float l=sqrt(v[0]*v[0]+v[1]*v[1]);
    VEC2_MACRO_FUNCC(/,v,l);
}

inline float Vec2fDot(vec2f v1, vec2f v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1];
}

/// ///////////////////////////
///Vector of size 2, type int
/// ///////////////////////////

inline void Vec2iAdd(vec2i v1, vec2i v2)           VEC2_MACRO_FUNC(+,v1,v2)
inline void Vec2iAdd2(vec2i v, vec2i v1, vec2i v2) VEC2_MACRO_FUNC2(+,v,v1,v2)
inline void Vec2iAddC(vec2i v, float c)            VEC2_MACRO_FUNCC(+,v,c)
inline void Vec2iAddC2(vec2i v, vec2i v1, float c) VEC2_MACRO_FUNCC2(+,v,v1,c)

inline void Vec2iSub(vec2i v1, vec2i v2)           VEC2_MACRO_FUNC(-,v1,v2)
inline void Vec2iSub2(vec2i v, vec2i v1, vec2i v2) VEC2_MACRO_FUNC2(-,v,v1,v2)
inline void Vec2iSubC(vec2i v, float c)            VEC2_MACRO_FUNCC(-,v,c)
inline void Vec2iSubC2(vec2i v, vec2i v1, float c) VEC2_MACRO_FUNCC2(-,v,v1,c)

inline void Vec2iMul(vec2i v1, vec2i v2)           VEC2_MACRO_FUNC(*,v1,v2)
inline void Vec2iMul2(vec2i v, vec2i v1, vec2i v2) VEC2_MACRO_FUNC2(*,v,v1,v2)
inline void Vec2iMulC(vec2i v, float c)            VEC2_MACRO_FUNCC(*,v,c)
inline void Vec2iMulC2(vec2i v, vec2i v1, float c) VEC2_MACRO_FUNCC2(*,v,v1,c)

inline void Vec2iDiv(vec2i v1, vec2i v2)           VEC2_MACRO_FUNC(/,v1,v2)
inline void Vec2iDiv2(vec2i v, vec2i v1, vec2i v2) VEC2_MACRO_FUNC2(/,v,v1,v2)
inline void Vec2iDivC(vec2i v, float c)            VEC2_MACRO_FUNCC(/,v,c)
inline void Vec2iDivC2(vec2i v, vec2i v1, float c) VEC2_MACRO_FUNCC2(/,v,v1,c)

inline void Vec2iNormalize(vec2i v)
{
    int l=sqrt(v[0]*v[0]+v[1]*v[1]);
    VEC2_MACRO_FUNCC(/,v,l);
}

inline int Vec2iDot(vec2i v1, vec2i v2)
{
    return v1[0]*v2[0]+v1[1]*v2[1];
}
