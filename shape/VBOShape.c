#include "VBOShape.h"

int VBOShapeCreate(TVBOShape* pvbo,
                   const float *pvertices, const float *pnormals, const float *puv,  unsigned int sizedata,
                   unsigned int *pindex, unsigned int sizeindex)
{
//Test du pointeur pour la forme
    if(pvbo==NULL)
    {
         printf("#Error VBOShapeCreate: pvbo not allocated.\n");
         return 0;
    }
//Creation du conteneur VBO pour les vertices et les normales
//Correspond a l'allocation de la memoire video
    unsigned int sizealldatatovbo=(3+3+2)*sizedata*sizeof(float);
    GLuint iddata=OGLVBOCreate(NULL,sizealldatatovbo,GL_ARRAY_BUFFER,GL_STATIC_DRAW);
    if(iddata==0)
    {
        printf("#Error VBOShapeCreate: can't allocate iddata.\n");
        return 0;
    }
    pvbo->m_Vertex.m_id=iddata;
    pvbo->m_Vertex.m_sizedata=sizedata;
//Remplir la memoire par les donnees
    unsigned int sizeverticetovbo=3*sizedata*sizeof(float);
    unsigned int sizeuvtovbo=2*sizedata*sizeof(float);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeverticetovbo,pvertices);
    glBufferSubData(GL_ARRAY_BUFFER,sizeverticetovbo,sizeverticetovbo,pnormals);
    glBufferSubData(GL_ARRAY_BUFFER,sizeverticetovbo*2,sizeuvtovbo,puv);
//Creation du conteneur VBO pour les indices
    unsigned int sizeindextovbo=sizeindex*sizeof(unsigned int);
    GLuint idindex=OGLVBOCreate(pindex,sizeindextovbo,GL_ELEMENT_ARRAY_BUFFER,GL_STATIC_DRAW);
    if(idindex==0)
    {
        printf("#Error VBOShapeCreate: can't allocate idindex.\n");
        OGLVBODelete(pvbo->m_Vertex.m_id);
        return 0;
    }
    pvbo->m_Index.m_id=idindex;
    pvbo->m_Index.m_sizedata=sizeindex;
//Retourne le nouveau VBO
    return 1;
}

void VBOShapeDelete(TVBOShape* pT)
{
    if(pT==NULL)
        return;
    OGLVBODelete(pT->m_Vertex.m_id);
    OGLVBODelete(pT->m_Index.m_id);
}

void VBOShapeDraw(TVBOShape* pT)
{
    GLuint iddata=pT->m_Vertex.m_id;
    unsigned int sizedata=pT->m_Vertex.m_sizedata;
    unsigned int sizeverticetovbo=3*sizedata*sizeof(float);
//Selectionne le buffer de donnees (vertex, normale, texture) et indique le n° d'attribut pour les shaders
    glBindBuffer(GL_ARRAY_BUFFER,iddata);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,0,((void*)NULL+sizeverticetovbo));
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,0,((void*)NULL+sizeverticetovbo*2));
//Selectionne le buffer d'index
    GLuint idindex=pT->m_Index.m_id;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,idindex);
//Active les attributs pour les shaders
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
//Affiche tous les elements du buffer
    glDrawElements(GL_TRIANGLES,pT->m_Index.m_sizedata, GL_UNSIGNED_INT, 0);
//Desactive les attibuts (pour utiliser autre chose que les shaders, par exemple le mode immediat).
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

int VBOShapeGetTriangleNumber(TVBOShape* pT)
{
    if(pT!=NULL)
        return pT->m_Index.m_sizedata/3;
    return 0;
}

void VBOShapeCopy(TVBOShape* pdest, TVBOShape* psrc)
{
    OGLVBOCopy(&pdest->m_Index,&psrc->m_Index);
    OGLVBOCopy(&pdest->m_Vertex,&psrc->m_Vertex);
}
