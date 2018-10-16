#if !defined(TORUSSHAPE_H)
#define TORUSSHAPE_H

//La librairie pour les math (sin, cos, ...)
#include <math.h>

#include "VBOShape.h"
#include "../math/mathutil.h"

int TorusCreate(TVBOShape* pvbo, unsigned int stack, unsigned int slice, float rad, float RAD);

#endif // !defined(TORUSSHAPE_H)
