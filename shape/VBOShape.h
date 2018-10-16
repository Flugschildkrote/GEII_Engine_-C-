#if !defined(VBOSHAPE_H)
#define VBOSHAPE_H

#include "../OGL/OGLVBO.h"

typedef struct{
    TVBOData m_Vertex;
    TVBOData m_Index;
}TVBOShape;

int VBOShapeCreate(TVBOShape* pvbo,
                   const float *pvertices, const float *pnormals, const float *puv, unsigned int sizedata,
                   unsigned int *pindex, unsigned int sizeindex);

void VBOShapeDelete(TVBOShape* pT);

void VBOShapeDraw(TVBOShape* pT);

int VBOShapeGetTriangleNumber(TVBOShape* pT);

void VBOShapeCopy(TVBOShape* pdest, TVBOShape* psrc);

#endif //VBOSHAPE_H
