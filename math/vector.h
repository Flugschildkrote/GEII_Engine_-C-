#if !defined(VECTOR_H)
#define VECTOR_H

/// Include all vector size
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

///Size 2 & 3 conversions
void Vec2fToVec3f(vec3f v, vec2f v1, float c);
void Vec2iToVec3i(vec3i v, vec2i v1, int c);

void Vec3fToVec2f(vec2f v, vec3f v1);
void Vec3iToVec2i(vec2i v, vec3i v1);

///Size 3 & 4 conversions
void Vec3fToVec4f(vec4f v, vec3f v1, float c);
void Vec3iToVec4i(vec4i v, vec3i v1, int c);

void Vec4fToVec3f(vec3f v, vec4f v1);
void Vec4iToVec3i(vec3i v, vec4i v1);

#endif //VECTOR_H
