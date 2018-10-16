#if !defined(OGLDRAWIMMEDIATE_H)
#define OGLDRAWIMMEDIATE_H

#include <GL\gl.h>

#include "math/vector.h"

void OGLDrawImmediateOrthonormal(vec3f position, float size,
                                 vec4f xcolor, vec4f ycolor, vec4f zcolor,
                                 float linewidth);

void OGLDrawImmediateLine(vec3f pstart, vec3f pend, vec4f color);

void OGLDrawImmediatePoint(vec3f p, vec4f color);

#endif //OGLDRAWIMMEDIATE_H
