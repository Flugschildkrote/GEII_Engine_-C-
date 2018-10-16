#include "vector.h"

///Size 2 & 3 conversions
inline void Vec2fToVec3f(vec3f v, vec2f v1, float c)
{
    Vec2Copy(v,v1);
    v[2]=c;
}
inline void Vec2iToVec3i(vec3i v, vec2i v1, int c)
{
    Vec2Copy(v,v1);
    v[2]=c;
}

inline void Vec3fToVec2f(vec2f v, vec3f v1)
{
    Vec2Copy(v,v1);
}
inline void Vec3iToVec2i(vec2i v, vec3i v1)
{
    Vec2Copy(v,v1);
}

///Size 3 & 4 conversions
inline void Vec3fToVec4f(vec4f v, vec3f v1, float c)
{
    Vec3Copy(v,v1);
    v[3]=c;
}
inline void Vec3iToVec4i(vec4i v, vec3i v1, int c)
{
    Vec3Copy(v,v1);
    v[3]=c;
}

inline void Vec4fToVec3f(vec3f v, vec4f v1)
{
    Vec3Copy(v,v1);
}
inline void Vec4iToVec3i(vec3i v, vec4i v1)
{
    Vec3Copy(v,v1);
}
