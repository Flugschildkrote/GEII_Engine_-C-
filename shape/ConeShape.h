#if !defined(CONESHAPE_H)
#define CONESHAPE_H

//La librairie pour les math (sin, cos, ...)
#include <math.h>

#include "VBOShape.h"
#include "../math/mathutil.h"

int ConeCreate(TVBOShape* pvbo, unsigned int stack, float rad, float height);

#endif // !defined(CONESHAPE_H)
