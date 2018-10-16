#include "mathutil.h"

//*************************************
//Max functions
inline float Max2f(float v1, float v2)
{
    if(v1>v2) return v1;
    else return v2;
}

inline float Max3f(float v1, float v2, float v3)
{
    return Max2f(Max2f(v1,v2),v3);
}

inline float Max4f(float v1, float v2, float v3, float v4)
{
    return Max2f(Max3f(v1,v2,v3),v4);
}

inline int Max2i(int v1, int v2)
{
    if(v1>v2) return v1;
    else return v2;
}

inline int Max3i(int v1, int v2, int v3)
{
    return Max2i(Max2i(v1,v2),v3);
}

inline int Max4i(int v1, int v2, int v3, int v4)
{
    return Max2i(Max3i(v1,v2,v3),v4);
}

inline unsigned int Max2ui(unsigned int v1, unsigned int v2)
{
    if(v1>v2) return v1;
    else return v2;
}

inline unsigned int Max3ui(unsigned int v1, unsigned int v2, unsigned int v3)
{
    return Max2ui(Max2ui(v1,v2),v3);
}

inline unsigned int Max4ui(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4)
{
    return Max2ui(Max3ui(v1,v2,v3),v4);
}

//*************************************
//Min functions
inline float Min2f(float v1, float v2)
{
    if(v1>v2) return v2;
    else return v1;
}

inline float Min3f(float v1, float v2, float v3)
{
    return Min2f(Min2f(v1,v2),v3);
}

inline float Min4f(float v1, float v2, float v3, float v4)
{
    return Min2f(Min3f(v1,v2,v3),v4);
}

inline int Min2i(int v1, int v2)
{
    if(v1>v2) return v2;
    else return v1;
}

inline int Min3i(int v1, int v2, int v3)
{
    return Min2i(Min2i(v1,v2),v3);
}

inline int Min4i(int v1, int v2, int v3, int v4)
{
    return Min2i(Min3i(v1,v2,v3),v4);
}

inline unsigned int Min2ui(unsigned int v1, unsigned int v2)
{
    if(v1>v2) return v2;
    else return v1;
}

inline unsigned int Min3ui(unsigned int v1, unsigned int v2, unsigned int v3)
{
    return Min2ui(Min2ui(v1,v2),v3);
}

inline unsigned int Min4ui(unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4)
{
    return Min2ui(Min3ui(v1,v2,v3),v4);
}

//*************************************
//Clamp function
inline float Clampf(float v, float vmin, float vmax)
{
    return Min2f(vmax,Max2f(vmin,v));
}
