#if !defined(MATERIAL_H)
#define MATERIAL_H

#include "math/vector.h"
#include "math/mathutil.h"

#define MATERIAL_NOT_TEXTURE  ((unsigned int)(-1))

typedef struct
{
    vec3f m_Kd;
    vec3f m_Ks;
    float m_Ns;
    float m_Alpha;
    unsigned int m_IdTexture;
}TMaterial;

void MaterialCopy(TMaterial *pdest, TMaterial *psrc);

int MaterialCreate(TMaterial *pmat, vec3f kd, vec3f ks, float ns, unsigned int idtex);
void MaterialDelete(TMaterial *pmat);

int MaterialSetTexture(TMaterial *pmat, unsigned int idtex);

void MaterialSetTransparency(TMaterial *pmat, float alpha);
int MaterialIsTransparent(TMaterial *pmat);

#endif // !defined(MATERIAL_H)
