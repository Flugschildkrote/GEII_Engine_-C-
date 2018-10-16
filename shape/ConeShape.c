#include "ConeShape.h"

int ConeCreate(TVBOShape* pvbo, unsigned int stack, float rad, float height)
{
    //Nombre de vertex
    unsigned int size=stack*4+2;
    //Allocation de tableaux pour stocker les vertices, normales, UV
    float *pverta, *pnorma, *pUVa;
    pverta=malloc(size*3*sizeof(float));
    pnorma=malloc(size*3*sizeof(float));
    pUVa=malloc(size*2*sizeof(float));
    if(pverta==NULL || pnorma==NULL || pUVa==NULL)
    {
        free(pverta);
        free(pnorma);
        free(pUVa);
        printf("#Error ConeCreate: malloc=NULL\n");
        return 0;
    }
    //vertice; normale; UV
    double dt = 2.0f*PI/(double)(stack);
    float phi;
    float cphi,sphi;
    unsigned int i;
    unsigned int iVN=0, iUV=0;
    unsigned int os1=stack*2+1;
    float h2=height/2.0f;
    float hn=height/sqrt(height*height+rad*rad);
    float rn=rad/sqrt(height*height+rad*rad);
    float V1=rad/(rad+height);
    float Ustep=1.0f/(float)(stack),U;
    float U12=Ustep*0.5f;
    for(i=0; i<(stack+1); i++)
    {
        phi=dt*i;
        cphi=cos(phi); sphi=sin(phi);
        U=Ustep*(float)(i);
        //UP
        pverta[iVN]=cphi*rad;           pverta[iVN+1]=-h2;          pverta[iVN+2]=sphi*rad;
        pnorma[iVN]=cphi*hn;            pnorma[iVN+1]=rn;           pnorma[iVN+2]=sphi*hn;
        pUVa[iUV]=U;                    pUVa[iUV+1]=V1;
        //DOWN
        pverta[iVN+os1*3]=cphi*rad;     pverta[iVN+os1*3+1]=-h2;    pverta[iVN+os1*3+2]=sphi*rad;
        pnorma[iVN+os1*3]=0.0f;         pnorma[iVN+os1*3+1]=-1.0f;  pnorma[iVN+os1*3+2]=0.0f;
        pUVa[iUV+os1*2]=U;              pUVa[iUV+os1*2+1]=V1;
        //CENTER UP & DOWN
        if(i!=stack)
        {
            pverta[iVN+3]=0.0f;         pverta[iVN+4]=h2;           pverta[iVN+5]=0.0f;
            pnorma[iVN+3]=cphi*hn;      pnorma[iVN+4]=rn;           pnorma[iVN+5]=sphi*hn;
            pUVa[iUV+2]=U12+U;          pUVa[iUV+3]=0.0f;

            pverta[iVN+os1*3+3]=0.0f;   pverta[iVN+os1*3+4]=-h2;    pverta[iVN+os1*3+5]=0.0f;
            pnorma[iVN+os1*3+3]=0.0f;   pnorma[iVN+os1*3+4]=-1.0f;  pnorma[iVN+os1*3+5]=0.0f;
            pUVa[iUV+os1*2+2]=U12+U;    pUVa[iUV+os1*2+3]=1.0f;
        }
        iVN+=6;
        iUV+=4;
    }
    //Nombre d'indice
    unsigned int indexsize=stack*2*3;
    unsigned int *pInda=malloc(indexsize*sizeof(unsigned int));
    if(pInda==NULL)
    {
        free(pverta);
        free(pnorma);
        free(pUVa);
        printf("#Error ConeCreate: pInda=NULL\n");
        return 0;
    }
    unsigned int iI=0;
    for(i=0; i<stack; i++)
    {
        //UP
        pInda[iI]=i*2;          pInda[iI+1]=i*2+1;      pInda[iI+2]=i*2+2;
        //DOWN
        pInda[iI+3]=i*2+os1;    pInda[iI+4]=i*2+os1+1;  pInda[iI+5]=i*2+os1+2;
        iI+=6;
    }
    if(!VBOShapeCreate(pvbo,pverta,pnorma,pUVa,size,pInda,indexsize))
    {
        free(pverta);
        free(pnorma);
        free(pUVa);
        free(pInda);
        printf("#Error ConeCreate: VBOShapeCreate's function return 0.\n");
        return 0;
    }
    //Libere la memoire
    free(pverta);
    free(pnorma);
    free(pUVa);
    free(pInda);
    return 1;
}
