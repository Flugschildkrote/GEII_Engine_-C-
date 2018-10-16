#if !defined(SPHERESHAPE_H)
#define SPHERESHAPE_H

//La librairie pour les math (sin, cos, ...)
#include <math.h>

#include "VBOShape.h"
#include "../math/mathutil.h"

int SphereCreate(TVBOShape* pvbo, unsigned int stack, unsigned int slice, float radius);

#endif // !defined(SPHERESHAPE_H)
