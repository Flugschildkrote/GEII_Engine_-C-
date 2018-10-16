#if !defined(CYLINDERSHAPE_H)
#define CYLINDERSHAPE_H

//La librairie pour les math (sin, cos, ...)
#include <math.h>

#include "VBOShape.h"
#include "../math/mathutil.h"

int CylinderCreate(TVBOShape* pvbo, unsigned int stack, float rad, float height);

#endif // !defined(CYLINDERSHAPE_H)
