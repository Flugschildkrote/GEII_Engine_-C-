#if !defined(LIGHT_H)
#define LIGHT_H

#include "math/vector.h"

typedef struct{
    vec3f m_Ambient;
    vec3f m_Power;
    vec3f m_Position;
}TLight;

int LightCreate(TLight *plight, vec3f ambient, vec3f power, vec3f position);


#endif // !defined(LIGHT_H)
