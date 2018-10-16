#include "SphereShape.h"

int SphereCreate(TVBOShape* pvbo, unsigned int stack, unsigned int slice, float radius)
{
    if(!pvbo)
    {
        printf("#Error SphereCreate: pvbo=NULL\n");
        return 0;
    }
    double dp = PI/(double)(stack-1);
    double dt = 2.0f*PI/(double)(slice);
    //Nombre de vertex
    unsigned int size=(slice+1)*stack;
    //Allocation de tableaux pour stocker les vertices, normales, UV
    float *pverticearray, *pnormalarray, *pUVarray;
    pverticearray=malloc(size*3*sizeof(float));
    pnormalarray=malloc(size*3*sizeof(float));
    pUVarray=malloc(size*2*sizeof(float));
    if(pverticearray==NULL || pnormalarray==NULL || pUVarray==NULL)
    {
        free(pverticearray);
        free(pnormalarray);
        free(pUVarray);
        printf("#Error SphereCreate: malloc=NULL\n");
        return 0;
    }
    //vertice; normale; UV
    float phi, theta;
    float cphi,sphi;
    float X,Y,Z;
    unsigned int i,j;
    unsigned int indexVN=0, indexUV=0;
    for(i=0; i<stack; i++)
    {
        phi=i*dp;
        cphi=cos(phi); sphi=sin(phi);
        for(j=0; j<=slice; j++)
        {
            theta=j*dt;
            X=cos(theta)*sphi;
            Y=sin(theta)*sphi;
            Z=cphi;

            pverticearray[indexVN]=radius*X;
            pnormalarray[indexVN++]=X;
            pverticearray[indexVN]=radius*Y;
            pnormalarray[indexVN++]=Y;
            pverticearray[indexVN]=radius*Z;
            pnormalarray[indexVN++]=Z;
            pUVarray[indexUV++]=j/(double)(slice);
            pUVarray[indexUV++]=1.0f-i/(double)(stack-1);
        }
    }
    //Nombre d'indice
    unsigned int indexsize=slice*(stack-1)*6;
    unsigned int *pIndiceArray=malloc(indexsize*sizeof(unsigned int));
    if(pIndiceArray==NULL)
    {
        free(pverticearray);
        free(pnormalarray);
        free(pUVarray);
        printf("#Error SphereCreate: malloc=NULL\n");
        return 0;
    }
    //Pole nord et sud
    unsigned int indexI=0;
    unsigned int indexOffset=slice*3;
    for(i=0; i<slice; i++)
    {
        pIndiceArray[indexI]=i;
        pIndiceArray[indexI+indexOffset]=(slice+1)*(stack-2)+i+1;
        indexI++;
        pIndiceArray[indexI]=(slice+1)+i;
        pIndiceArray[indexI+indexOffset]=(slice+1)*(stack-2)+i;
        indexI++;
        pIndiceArray[indexI]=(slice+1)+i+1;
        pIndiceArray[indexI+indexOffset]=(slice+1)*(stack-1)+i;
        indexI++;
    }
    //Le reste
    indexOffset+=slice*3;
    for(j=1; j<stack-1; j++)
    {
        for(i=0; i<slice; i++)
        {
            pIndiceArray[indexOffset+(i*6)] = (slice+1)*j+i;
            pIndiceArray[indexOffset+(i*6)+1] = (slice+1)*(j+1)+i;
            pIndiceArray[indexOffset+(i*6)+2] = (slice+1)*(j+1)+i+1;

            pIndiceArray[indexOffset+(i*6)+3] = (slice+1)*j+i;
            pIndiceArray[indexOffset+(i*6)+4] = (slice+1)*(j+1)+i+1;
            pIndiceArray[indexOffset+(i*6)+5] = (slice+1)*(j)+i+1;
        }
        indexOffset+=slice*6;
    }
    if(!VBOShapeCreate(pvbo,pverticearray,pnormalarray,pUVarray,size,pIndiceArray,indexsize))
    {
        free(pverticearray);
        free(pnormalarray);
        free(pUVarray);
        free(pIndiceArray);
        printf("#Error SphereCreate: VBOShapeCreate's function return 0.\n");
        return 0;
    }
    //Libere la memoire
    free(pverticearray);
    free(pnormalarray);
    free(pUVarray);
    free(pIndiceArray);

    return 1;
}
