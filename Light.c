#include "Light.h"

int LightCreate(TLight *plight, vec3f ambient, vec3f power, vec3f position)
{
    Vec3fCopy(plight->m_Ambient,ambient);
    Vec3fCopy(plight->m_Power,power);
    Vec3fCopy(plight->m_Position,position);
    return 1;
}
