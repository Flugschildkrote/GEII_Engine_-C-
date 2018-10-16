#include "Material.h"

void MaterialCopy(TMaterial *pdest, TMaterial *psrc)
{
    Vec3fCopy(pdest->m_Kd,psrc->m_Kd);
    Vec3fCopy(pdest->m_Ks,psrc->m_Ks);
    pdest->m_Ns=psrc->m_Ns;
    pdest->m_Alpha=psrc->m_Alpha;
    pdest->m_IdTexture=psrc->m_IdTexture;
}

int MaterialCreate(TMaterial *pmat, vec3f kd, vec3f ks, float ns, unsigned int idtex)
{
    Vec3fCopy(pmat->m_Kd,kd);
    Vec3fCopy(pmat->m_Ks,ks);
    pmat->m_Ns=ns;
    pmat->m_Alpha=1.0f;
    pmat->m_IdTexture=idtex;
    return 1;
}

inline int MaterialSetTexture(TMaterial *pmat, unsigned int idtex)
{
    pmat->m_IdTexture=idtex;
    return 1;
}

void MaterialDelete(TMaterial *pmat)
{
//RIEN A FAIRE
}

inline int MaterialIsTransparent(TMaterial *pmat)
{
    return !(pmat->m_Alpha>=(1.0f-EPS6));
}

inline void MaterialSetTransparency(TMaterial *pmat, float alpha)
{
    pmat->m_Alpha=alpha;
}
