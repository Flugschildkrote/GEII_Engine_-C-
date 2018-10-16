#include "TorusShape.h"

int TorusCreate(TVBOShape* pvbo, unsigned int stack, unsigned int slice, float rad, float RAD)
{
    //Nombre de vertex
    unsigned int size=(slice+1)*(stack+1);
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
        printf("#Error CreateTorus: malloc=NULL\n");
        return 0;
    }
    //vertice; normale; UV
    double dp = 2.0f*PI/(double)(slice);
    double dt = 2.0f*PI/(double)(stack);
    float phi, theta;
    float cphi,sphi;
    float ctheta,stheta,Rrctheta;
    float X,Y,Z;
    float Nx,Ny,Nz;
    unsigned int i,j;
    unsigned int indexVN=0, indexUV=0;
    for(i=0; i<=slice; i++)
    {
        phi=(float)i*dp;
        cphi=cos(phi);sphi=sin(phi);
        for(j=0; j<=stack; j++)
        {
           theta=dt*(float)j;
           ctheta=cos(theta);
           stheta=sin(theta);
           Rrctheta=(RAD+rad*ctheta);
           X = Rrctheta*cphi;
           Y = Rrctheta*sphi;
           Z = rad*stheta;
           Nx = cphi*ctheta;
           Ny = -sphi*ctheta;
           Nz = stheta;
           pverticearray[indexVN]=X;
           pnormalarray[indexVN++]=Nx;
           pverticearray[indexVN]=Y;
           pnormalarray[indexVN++]=Ny;
           pverticearray[indexVN]=Z;
           pnormalarray[indexVN++]=Nz;

           pUVarray[indexUV++]=j/(float)(stack);
           pUVarray[indexUV++]=i/(float)(slice);
        }
    }
    //Nombre d'indice
    unsigned int indexsize=size*6;
    unsigned int *pIndiceArray=malloc(indexsize*sizeof(unsigned int));
    if(pIndiceArray==NULL)
    {
        free(pverticearray);
        free(pnormalarray);
        free(pUVarray);
        printf("#Error CreateTorus: malloc=NULL\n");
        return 0;
    }
    unsigned int indexI=0;
    for(i=0; i<slice; i++)
    {
        for(j=0; j<stack; j++)
        {
            //1er triangle
            pIndiceArray[indexI++]=i*(stack+1)+j;
            pIndiceArray[indexI++]=i*(stack+1)+j+1;
            pIndiceArray[indexI++]=(i+1)*(stack+1)+j+1;
            //2eme triangle
            pIndiceArray[indexI++]=i*(stack+1)+j;
            pIndiceArray[indexI++]=(i+1)*(stack+1)+j+1;
            pIndiceArray[indexI++]=(i+1)*(stack+1)+j;
        }
    }
    if(!VBOShapeCreate(pvbo, pverticearray,pnormalarray,pUVarray,size,pIndiceArray,indexsize))
    {
        free(pverticearray);
        free(pnormalarray);
        free(pUVarray);
        free(pIndiceArray);
        printf("#Error CreateTorus: VBOShapeCreate's function return 0.\n");
        return 0;
    }
    //Libere la memoire
    free(pverticearray);
    free(pnormalarray);
    free(pUVarray);
    free(pIndiceArray);

    return 1;
}
