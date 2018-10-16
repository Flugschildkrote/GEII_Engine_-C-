#if !defined(GEOMETRICPRIMITIVE_H)
#define GEOMETRICPRIMITIVE_H

#include "math\matrix4x4.h"
#include "stdint.h"

typedef struct{
    unsigned int m_IdShape;
    unsigned int m_IdMaterial;
    uint32_t m_IDPicking;
    TMatrix4x4f m_OtoW;         //La matrice de transformation de l'objet dans le monde
}TGeometricPrimitive;

void GeometricPrimitiveCopy(TGeometricPrimitive *pdest, TGeometricPrimitive *psrc);

void GeometricPrimitiveDelete(TGeometricPrimitive *pprim);

#endif // !defined(GEOMETRICPRIMITIVE_H)
