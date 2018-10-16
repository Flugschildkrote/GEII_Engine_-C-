#include "GeometricPrimitive.h"

void GeometricPrimitiveCopy(TGeometricPrimitive *pdest, TGeometricPrimitive *psrc)
{
    pdest->m_IdShape=psrc->m_IdShape;
    pdest->m_IdMaterial=psrc->m_IdMaterial;
    Matrix4x4fCopy(pdest->m_OtoW,psrc->m_OtoW);
}

void GeometricPrimitiveDelete(TGeometricPrimitive *pprim)
{
//RIEN A FAIRE
}
