#include "ObjParser.h"

int ObjParserOpenScene(String filename, TScene *pScene)
{
    //La structure pour gerer les donnees
    TObjParser objdata;
    if(!ObjParserInitialize(&objdata))
    {
        printf("#Error ObjParserOpenScene: can not initialize.\n");
        ObjParserEnd(&objdata);
        return 0;
    }
    //Commence par ouvrir le fichier
    if(!ObjParserOpenFile(filename,&objdata))
        return 0;
    //Traiter toutes les commandes
    int fshape=0;    //Un flag pour la gestion des formes
    while(ObjParserFindCmd(&objdata))
    {
        //En fonction de la commande
        while(strcmp(objdata.m_pCmd,"f")==0)//Une face
        {
            if(!ObjParserCmdf(&objdata))
            {
                printf("#Error ObjParserOpenScene: cmd f.\n");
                ObjParserEnd(&objdata);
                return 0;
            }
            fshape=1;
            if(!ObjParserFindCmd(&objdata))//Passe a la prochaine commande
                break;
        }
        if(fshape)//fin de la forme -> on l'ajoute a la scene
        {
            if(!ObjParserCreateGeometricPrimitive(&objdata,pScene))
                return 0;
            objdata.m_Face.m_Number=0;
            fshape=0;
        }
        if(strcmp(objdata.m_pCmd,"v")==0)//Un vertice
        {
            if(!ObjParserCmdv(&objdata))
            {
                printf("#Error ObjParserOpenScene: cmd v.\n");
                ObjParserEnd(&objdata);
                return 0;
            }
        }
        else if(strcmp(objdata.m_pCmd,"vn")==0)//Une normale
        {
            if(!ObjParserCmdvn(&objdata))
            {
                printf("#Error ObjParserOpenScene: cmd vn.\n");
                ObjParserEnd(&objdata);
                return 0;
            }
        }
        else if(strcmp(objdata.m_pCmd,"vt")==0)//Une coordonnee UV
        {
            if(!ObjParserCmdvt(&objdata))
            {
                printf("#Error ObjParserOpenScene: cmd vt.\n");
                ObjParserEnd(&objdata);
                return 0;
            }
        }
        else if(strcmp(objdata.m_pCmd,"usemtl")==0)//Une selection de materiaux
        {
            if(!ObjParserCmdusemtl(&objdata))
            {
                printf("#Error ObjParserOpenScene: cmd usemtl.\n");
                ObjParserEnd(&objdata);
                return 0;
            }
        }
        else if(strcmp(objdata.m_pCmd,"mtllib")==0)//Un fichier pour les materiaux
        {
            if(!ObjParserCmdmtllib(&objdata,pScene))
            {
                printf("#Error ObjParserOpenScene: cmd mtllib.\n");
                ObjParserEnd(&objdata);
                return 0;
            }
        }
    }

    //ObjParserPrint(&objdata); //DEBUG;
    ObjParserEnd(&objdata);
    return 1;
}

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int ObjParserInitialize(TObjParser *pparser)
{
    pparser->m_Stream=NULL;
    pparser->m_FileRep[0]='\0';
    pparser->m_RawLine[0]='\0';
    pparser->m_pLine=0;
    pparser->m_pLineEnd=0;
    pparser->m_pCmd=0;
    pparser->m_IdMaterial=SCENE_GET_DATA_ERROR;
    pparser->m_bComputeNormal=0;
    pparser->m_Vertex.m_NumberMax=0;
    if(!ObjParserResizeVertexList(pparser))
        return 0;
    pparser->m_Normal.m_NumberMax=0;
    if(!ObjParserResizeNormalList(pparser))
        return 0;
    pparser->m_UV.m_NumberMax=0;
    if(!ObjParserResizeUVList(pparser))
        return 0;
    pparser->m_Face.m_NumberMax=0;
    if(!ObjParserResizeFaceList(pparser))
        return 0;
    return 1;
}

int ObjParserEnd(TObjParser *pparser)
{
    //Ferme le fichier
    fclose(pparser->m_Stream);
    //Supprime les allocations
    if(pparser->m_Vertex.m_NumberMax)
        free(pparser->m_Vertex.m_pVertex);
    if(pparser->m_Normal.m_NumberMax)
        free(pparser->m_Normal.m_pNormal);
    if(pparser->m_Face.m_NumberMax)
        free(pparser->m_Face.m_pIdx);
    if(pparser->m_MtlLib.m_NumberMax)
        free(pparser->m_MtlLib.m_pListMaterial);
    return 1;
}

int ObjParserOpenFile(String filename, TObjParser *pparser)
{
    pparser->m_Stream=fopen(filename,"r");
    if(pparser->m_Stream==NULL)
    {
        printf("#Error ObjParserOpenFile: can not open file.\n");
        return 0;
    }
    //Prend le repertoire de travail
    unsigned int posslash=StringFindLast(filename,'\\');
    if(posslash==(unsigned int)(-1))
        posslash=StringFindLast(filename,'/');
    if(posslash==(unsigned int)(-1))
        strcpy(pparser->m_FileRep,"");
    else
    {
        strncpy(pparser->m_FileRep,filename,posslash+1);
        pparser->m_FileRep[posslash+1]='\0';
    }
    return 1;
}

int ObjParserFindCmd(TObjParser *pparser)
{
    while(fgets(pparser->m_RawLine,4096,pparser->m_Stream)!=NULL)
    {
        //Init les pointeurs de debut et fin de ligne a traiter
        pparser->m_pLine = pparser->m_RawLine;
        pparser->m_pLineEnd = pparser->m_RawLine+strlen(pparser->m_RawLine);
        //Cherche le 1er caractere qui n'est pas un espace
        ObjParserSkipSpace(pparser);
        //La commande de la ligne
        pparser->m_pCmd=pparser->m_pLine;
        //Passe la commande
        ObjParserSkipNoSpace(pparser);
        //Met une fin de ligne apres la commande
        if(pparser->m_pLine<pparser->m_pLineEnd)
        {
            *pparser->m_pLine = '\0';
            pparser->m_pLine++;
        }
        return 1;
    }
    return 0;
}

void ObjParserSkipSpace(TObjParser *pparser)
{
    while(isspace(*pparser->m_pLine) && pparser->m_pLine<pparser->m_pLineEnd)
        pparser->m_pLine++;
}

void ObjParserSkipNoSpace(TObjParser * pparser)
{
    while(!isspace(*pparser->m_pLine) && pparser->m_pLine<pparser->m_pLineEnd)
        pparser->m_pLine++;
}


int ObjParserResizeVertexList(TObjParser *pparser)
{
    //Les anciennes valeurs
    TObjParserV olddata=pparser->m_Vertex;
    if(olddata.m_NumberMax==0) //Nouvelle allocation
    {
        pparser->m_Vertex.m_NumberMax=1024;
        pparser->m_Vertex.m_Number=0;
        pparser->m_Vertex.m_pVertex = malloc(1024*sizeof(vec3f));
        if(pparser->m_Vertex.m_pVertex==NULL)
        {
            printf("#Error ObjParserResizeVertexList: can not allocate new list.\n");
            pparser->m_Vertex.m_NumberMax=0;
            return 0;
        }
        return 1;
    }
    //Change la taille
    pparser->m_Vertex.m_NumberMax=olddata.m_NumberMax*2;
    pparser->m_Vertex.m_pVertex = malloc(pparser->m_Vertex.m_NumberMax*sizeof(vec3f));
    if(pparser->m_Vertex.m_pVertex==NULL)
    {
        printf("#Error ObjParserResizeVertexList: can not reallocate new list.\n");
        free(olddata.m_pVertex);
        pparser->m_Vertex.m_NumberMax=0;
        return 0;
    }
    //Recopie des anciennes valeurs
    unsigned int i;
    for(i=0; i<olddata.m_Number; i++)
        Vec3fCopy(pparser->m_Vertex.m_pVertex[i],olddata.m_pVertex[i]);
    free(olddata.m_pVertex);
    return 1;
}

int ObjParserResizeNormalList(TObjParser *pparser)
{
    //Les anciennes valeurs
    TObjParserVn olddata=pparser->m_Normal;
    if(olddata.m_NumberMax==0) //Nouvelle allocation
    {
        pparser->m_Normal.m_NumberMax=1024;
        pparser->m_Normal.m_Number=0;
        pparser->m_Normal.m_pNormal = malloc(1024*sizeof(vec3f));
        if(pparser->m_Normal.m_pNormal==NULL)
        {
            printf("#Error ObjParserResizeNormalList: can not allocate new list.\n");
            pparser->m_Normal.m_NumberMax=0;
            return 0;
        }
        return 1;
    }
    //Change la taille
    pparser->m_Normal.m_NumberMax=olddata.m_NumberMax*2;
    pparser->m_Normal.m_pNormal = malloc(pparser->m_Normal.m_NumberMax*sizeof(vec3f));
    if(pparser->m_Normal.m_pNormal==NULL)
    {
        printf("#Error ObjParserResizeNormalList: can not reallocate new list.\n");
        free(olddata.m_pNormal);
        pparser->m_Normal.m_NumberMax=0;
        return 0;
    }
    //Recopie des anciennes valeurs
    unsigned int i;
    for(i=0; i<olddata.m_Number; i++)
        Vec3fCopy(pparser->m_Normal.m_pNormal[i],olddata.m_pNormal[i]);
    free(olddata.m_pNormal);
    return 1;
}

int ObjParserResizeUVList(TObjParser *pparser)
{
    //Les anciennes valeurs
    TObjParserVt olddata=pparser->m_UV;
    if(olddata.m_NumberMax==0) //Nouvelle allocation
    {
        pparser->m_UV.m_NumberMax=1024;
        pparser->m_UV.m_Number=0;
        pparser->m_UV.m_pUV = malloc(1024*sizeof(vec2f));
        if(pparser->m_UV.m_pUV==NULL)
        {
            printf("#Error ObjParserResizeUVList: can not allocate new list.\n");
            pparser->m_UV.m_NumberMax=0;
            return 0;
        }
        return 1;
    }
    //Change la taille
    pparser->m_UV.m_NumberMax=olddata.m_NumberMax*2;
    pparser->m_UV.m_pUV = malloc(pparser->m_UV.m_NumberMax*sizeof(vec2f));
    if(pparser->m_UV.m_pUV==NULL)
    {
        printf("#Error ObjParserResizeUVList: can not reallocate new list.\n");
        free(olddata.m_pUV);
        pparser->m_UV.m_NumberMax=0;
        return 0;
    }
    //Recopie des anciennes valeurs
    unsigned int i;
    for(i=0; i<olddata.m_Number; i++)
        Vec3fCopy(pparser->m_UV.m_pUV[i],olddata.m_pUV[i]);
    free(olddata.m_pUV);
    return 1;
}

int ObjParserResizeFaceList(TObjParser *pparser)
{
    //Les anciennes valeurs
    TObjParserF olddata=pparser->m_Face;
    if(olddata.m_NumberMax==0) //Nouvelle allocation
    {
        pparser->m_Face.m_NumberMax=1024;
        pparser->m_Face.m_Number=0;
        pparser->m_Face.m_pIdx = malloc(1024*sizeof(vec3ui));
        if(pparser->m_Face.m_pIdx==NULL)
        {
            printf("#Error ObjParserResizeFaceList: can not allocate new list.\n");
            pparser->m_Face.m_NumberMax=0;
            return 0;
        }
        return 1;
    }
    //Change la taille
    pparser->m_Face.m_NumberMax=olddata.m_NumberMax*2;
    pparser->m_Face.m_pIdx = malloc(pparser->m_Face.m_NumberMax*sizeof(vec3ui));
    if(pparser->m_Face.m_pIdx==NULL)
    {
        printf("#Error ObjParserResizeFaceList: can not reallocate new list.\n");
        free(olddata.m_pIdx);
        pparser->m_Face.m_NumberMax=0;
        return 0;
    }
    //Recopie des anciennes valeurs
    unsigned int i;
    for(i=0; i<olddata.m_Number; i++)
        Vec3uiCopy(pparser->m_Face.m_pIdx[i],olddata.m_pIdx[i]);
    free(olddata.m_pIdx);
    return 1;
}

int ObjParserCmdmtllib(TObjParser *pparser, TScene *pScene)
{
    char filemtl[MAX_PATH];
    ObjParserSkipSpace(pparser);
    sscanf(pparser->m_pLine,"%s",filemtl);
    char fullfilemtl[MAX_PATH];
    strcpy(fullfilemtl,pparser->m_FileRep);
    strcat(fullfilemtl,filemtl);
    if(!MtlParserOpenLib(fullfilemtl,&pparser->m_MtlLib,pScene))
    {
        printf("#Error ObjParserCmdmtllib : can not process cmd mtllib.\n");
        return 0;
    }
    return 1;
}

int ObjParserCmdv(TObjParser *pparser)
{
    //Lecture des valeurs
    float tmp[4];
    if(sscanf(pparser->m_pLine,"%f %f %f",tmp,tmp+1,tmp+2)!=3)
    {
        printf("#Error ObjParserCmdv : can not read data of cmd v.\n");
        return 0;
    }
    //Ajout a la liste
    TObjParserV *plist=&pparser->m_Vertex;
    if(plist->m_Number==plist->m_NumberMax)
        if(!ObjParserResizeVertexList(pparser))
        {
            printf("#Error ObjParserCmdv : can not resize list.\n");
            return 0;
        }
    vec3f *pdata=plist->m_pVertex+plist->m_Number;
    (*pdata)[0]=tmp[0];(*pdata)[1]=tmp[1];(*pdata)[2]=tmp[2];
    plist->m_Number++;
    return 1;
}

int ObjParserCmdvn(TObjParser *pparser)
{
    //Lecture des valeurs
    float tmp[4];
    if(sscanf(pparser->m_pLine,"%f %f %f",tmp,tmp+1,tmp+2)!=3)
    {
        printf("#Error ObjParserCmdvn : can not read data of cmd vn.\n");
        return 0;
    }
    //Ajout a la liste
    TObjParserVn *plist=&pparser->m_Normal;
    if(plist->m_Number==plist->m_NumberMax)
        if(!ObjParserResizeNormalList(pparser))
        {
            printf("#Error ObjParserCmdvn : can not resize list.\n");
            return 0;
        }
    vec3f *pdata=plist->m_pNormal+plist->m_Number;
    (*pdata)[0]=tmp[0];(*pdata)[1]=tmp[1];(*pdata)[2]=tmp[2];
    plist->m_Number++;
    return 1;
}

int ObjParserCmdvt(TObjParser *pparser)
{
    //Lecture des valeurs
    float tmp[4];
    if(sscanf(pparser->m_pLine,"%f %f",tmp,tmp+1)!=2)
    {
        printf("#Error ObjParserCmdvt : can not read data of cmd vt.\n");
        return 0;
    }
    //Ajout a la liste
    TObjParserVt *plist=&pparser->m_UV;
    if(plist->m_Number==plist->m_NumberMax)
        if(!ObjParserResizeUVList(pparser))
        {
            printf("#Error ObjParserCmdvt : can not resize list.\n");
            return 0;
        }
    vec2f *pdata=plist->m_pUV+plist->m_Number;
    (*pdata)[0]=tmp[0];(*pdata)[1]=tmp[1];
    plist->m_Number++;
    return 1;
}

int ObjParserCmdf(TObjParser *pparser)
{
    //Lecture des valeurs
    unsigned int idxV[16],idxVn[16],idxVt[16];
    unsigned int nV=0, nVn=0, nVt=0;
    while(pparser->m_pLine<pparser->m_pLineEnd)
    {
        ObjParserSkipSpace(pparser);
        if(sscanf(pparser->m_pLine,"%d/%d/%d",idxV+nV,idxVt+nVt,idxVn+nVn)==3)//Point/Texture/Normal
        {
            nV++; nVn++; nVt++;
        }
        else if(sscanf(pparser->m_pLine,"%d//%d",idxV+nV,idxVn+nVn)==2)//Point//Normal
        {
            idxVt[nV]=0;
            nV++; nVn++;
        }
        else if(sscanf(pparser->m_pLine,"%d/%d",idxV+nV,idxVt+nVt)==2)//Point/Texture
        {
            idxVn[nV]=0;
            nV++; nVt++;
        }
        else if(sscanf(pparser->m_pLine,"%d",idxV+nV)==1)//Point
        {
            idxVt[nV]=0;
            idxVn[nV]=0;
            nV++;
        }
        else if(pparser->m_pLine<pparser->m_pLineEnd)
        {
            printf("#Error ObjParserCmdf : can not process cmd f.\n");
            return 0;
        }
        ObjParserSkipNoSpace(pparser);
    }
    if(nV==3)//Un triangle
    {
        //Ajout a la liste
        TObjParserF *plist=&pparser->m_Face;
        if((plist->m_Number+3)>=plist->m_NumberMax)
            if(!ObjParserResizeFaceList(pparser))
            {
                printf("#Error ObjParserCmdf : can not resize list.\n");
                return 0;
            }
        vec3ui *pdata=plist->m_pIdx+plist->m_Number;
        (*pdata)[0]=idxV[0];(*pdata)[1]=idxVt[0];(*pdata)[2]=idxVn[0];
        pdata++;
        (*pdata)[0]=idxV[1];(*pdata)[1]=idxVt[1];(*pdata)[2]=idxVn[1];
        pdata++;
        (*pdata)[0]=idxV[2];(*pdata)[1]=idxVt[2];(*pdata)[2]=idxVn[2];
        plist->m_Number+=3;
    }
    else if(nV==4)//Un carre
    {
        //Ajout a la liste
        TObjParserF *plist=&pparser->m_Face;
        if((plist->m_Number+6)>=plist->m_NumberMax)
            if(!ObjParserResizeFaceList(pparser))
            {
                printf("#Error ObjParserCmdf : can not resize list.\n");
                return 0;
            }
        vec3ui *pdata=plist->m_pIdx+plist->m_Number;
        //1er triangle
        (*pdata)[0]=idxV[0];(*pdata)[1]=idxVt[0];(*pdata)[2]=idxVn[0];
        pdata++;
        (*pdata)[0]=idxV[1];(*pdata)[1]=idxVt[1];(*pdata)[2]=idxVn[1];
        pdata++;
        (*pdata)[0]=idxV[2];(*pdata)[1]=idxVt[2];(*pdata)[2]=idxVn[2];
        pdata++;
        //2eme triangle
        (*pdata)[0]=idxV[0];(*pdata)[1]=idxVt[0];(*pdata)[2]=idxVn[0];
        pdata++;
        (*pdata)[0]=idxV[2];(*pdata)[1]=idxVt[2];(*pdata)[2]=idxVn[2];
        pdata++;
        (*pdata)[0]=idxV[3];(*pdata)[1]=idxVt[3];(*pdata)[2]=idxVn[3];
        plist->m_Number+=6;
    }
    else
    {
        //Test si c'est un polygone convexe
        if(!ObjParserIsConvexPolygon(pparser,nV,idxV))
        {
            printf("#Error ObjParserCmdf : can not process cmd f (nV>4 and not convex polygon).\n");
            return 0;
        }
        //Ajout a la liste
        TObjParserF *plist=&pparser->m_Face;
        if((plist->m_Number+(nV-2)*3)>=plist->m_NumberMax)
            if(!ObjParserResizeFaceList(pparser))
            {
                printf("#Error ObjParserCmdf : can not resize list.\n");
                return 0;
            }
        unsigned int i;
        vec3ui *pdata=plist->m_pIdx+plist->m_Number;
        //Triangle fan
        for(i=0; i<(nV-2); i++)
        {
            (*pdata)[0]=idxV[0];(*pdata)[1]=idxVt[0];(*pdata)[2]=idxVn[0];
            pdata++;
            (*pdata)[0]=idxV[i+1];(*pdata)[1]=idxVt[i+1];(*pdata)[2]=idxVn[i+1];
            pdata++;
            (*pdata)[0]=idxV[i+2];(*pdata)[1]=idxVt[i+2];(*pdata)[2]=idxVn[i+2];
            pdata++;
            plist->m_Number+=3;
        }
    }
    return 1;
}

int ObjParserIsConvexPolygon(TObjParser *pparser, unsigned int size, unsigned int *idx)
{
    if(size<4)
    {
        printf("#Error ObjParserIsConvexPolygon : size<4.\n");
        return 0;
    }
    //Calcul la 1er normale
    vec3f pt0,pt1,pt2;
    vec3f v0,v1,vn1,vn2;
    TObjParserV *plistV=&pparser->m_Vertex;
    Vec3fCopy(pt0,plistV->m_pVertex[idx[size-1]-1]);
    Vec3fCopy(pt1,plistV->m_pVertex[idx[0]-1]);
    Vec3fCopy(pt2,plistV->m_pVertex[idx[1]-1]);
    Vec3fSub2(v0,pt0,pt1);
    Vec3fSub2(v1,pt2,pt1);
    Vec3fCross(vn1,v0,v1);
    Vec3fNormalize(vn1);
    //Pour toutes les autres configurations
    unsigned int i;
    for(i=1; i<size; i++)
    {
        Vec3fCopy(pt0,plistV->m_pVertex[idx[i-1]-1]);
        Vec3fCopy(pt1,plistV->m_pVertex[idx[i]-1]);
        Vec3fCopy(pt2,plistV->m_pVertex[idx[(i+1)%size]-1]);
        Vec3fSub2(v0,pt0,pt1);
        Vec3fSub2(v1,pt2,pt1);
        Vec3fCross(vn2,v0,v1);
        Vec3fNormalize(vn2);
        if((vn1[0]-vn2[0])>EPS6 || (vn1[1]-vn2[1])>EPS6 || (vn1[2]-vn2[2])>EPS6)
            return 0;
    }
    return 1;
}

int ObjParserCmdusemtl(TObjParser *pparser)
{
    //Prend le nom du materiau
    char namemtl[4096];
    ObjParserSkipSpace(pparser);
    sscanf(pparser->m_pLine,"%s",namemtl);
    //Cherche dans la liste des materiaux
    TMtlLib *pMtlLib=&pparser->m_MtlLib;
    unsigned int i;
    for(i=0; i<pMtlLib->m_Number; i++)
        if(strcmp(pMtlLib->m_pListMaterial[i].m_pName,namemtl)==0)
        {
            pparser->m_IdMaterial=pMtlLib->m_pListMaterial[i].m_Id;
            break;
        }

    return 1;
}

int ObjParserCreateGeometricPrimitive(TObjParser *pparser, TScene *pScene)
{
    //Verification des normales
    if(pparser->m_Normal.m_Number==0 || pparser->m_bComputeNormal)
    {
        pparser->m_bComputeNormal=1;
        if(!ObjParserGenerateNormal(pparser))
        {
            printf("#Error ObjParserCreateGeometricPrimitive: can not generate normal.\n");
            return 0;
        }
    }
    unsigned int sizedata=pparser->m_Face.m_Number;
    unsigned int size=0;
    unsigned int i,j,k;
    unsigned int idxV, idxVn, idxVt, idx;
    //Allocation de tableaux pour stocker les vertices, normales, UV
    float *pverta, *pnorma, *pUVa;
    pverta=malloc(sizedata*3*sizeof(float));
    pnorma=malloc(sizedata*3*sizeof(float));
    pUVa=malloc(sizedata*2*sizeof(float));
    //Allocation de la table des index
    unsigned int *pInda=malloc(sizedata*sizeof(unsigned int));
    //Pour toutes les combinaisons V/Vt/Vn
    //- Cherche dans la table de LUT si elle existe
    //  ->Oui: renseigne la table des indices
    //  ->Non: ajoute la combinaison aux tableaux vertices, normales, UV et renseigne la table des indices
    TObjParserF *plistF=&pparser->m_Face;
    TObjParserV *plistV=&pparser->m_Vertex;
    TObjParserVn *plistVn=&pparser->m_Normal;
    TObjParserVt *plistVt=&pparser->m_UV;
    int bidx;
    for(i=0; i<sizedata; i++)
    {
        idxV=plistF->m_pIdx[i][0];
        idxVt=plistF->m_pIdx[i][1];
        idxVn=plistF->m_pIdx[i][2];
        bidx=0;
        for(j=i; j>0; j--)
        {
            k=j-1;
            if(idxV==plistF->m_pIdx[k][0] && idxVt==plistF->m_pIdx[k][1] && idxVn==plistF->m_pIdx[k][2])
            {
                bidx=1;
                idx=pInda[k];
                break;
            }
        }
        if(bidx) //On a deja les donnees->indique juste l'indice
            pInda[i]=idx;
        else    //On n'a pas les donnees->ajoute aux tableaux
        {
            idxV--;
            pverta[size*3]=plistV->m_pVertex[idxV][0];
            pverta[size*3+1]=plistV->m_pVertex[idxV][1];
            pverta[size*3+2]=plistV->m_pVertex[idxV][2];

            idxVn--;
            pnorma[size*3]=plistVn->m_pNormal[idxVn][0];
            pnorma[size*3+1]=plistVn->m_pNormal[idxVn][1];
            pnorma[size*3+2]=plistVn->m_pNormal[idxVn][2];

            idxVt--;
            pUVa[size*2]=plistVt->m_pUV[idxVt][0];
            pUVa[size*2+1]=plistVt->m_pUV[idxVt][1];

            pInda[i]=size;
            size++;
        }
    }
    //Creation de la forme
    TVBOShape *pshape;
    unsigned int idshape=SceneGetNewShape(pScene,&pshape);
    if(idshape==SCENE_GET_DATA_ERROR)
    {
        printf("#Error ObjParserCreateGeometricPrimitive: can not get a new shape from scene.\n");
        free(pverta);
        free(pnorma);
        free(pUVa);
        free(pInda);
        return 0;
    }
    if(!VBOShapeCreate(pshape,pverta,pnorma,pUVa,size,pInda,sizedata))
    {
        printf("#Error ObjParserCreateGeometricPrimitive: can not create new shape.\n");
        free(pverta);
        free(pnorma);
        free(pUVa);
        free(pInda);
        return 0;
    }
    free(pverta);
    free(pnorma);
    free(pUVa);
    free(pInda);
    //La primitive
    TGeometricPrimitive *pPrim;
    unsigned int idprim=SceneGetNewGeometricPrimitive(pScene,&pPrim);
    if(idprim==SCENE_GET_DATA_ERROR)
    {
        printf("#Error ObjParserCreateGeometricPrimitive: can not get a new primitive from scene.\n");
        return 0;
    }
    pPrim->m_IdShape=idshape;
    //La matrice de transformation
    Matrix4x4fIdentity(pPrim->m_OtoW);
    //Le materiau
    if(pparser->m_IdMaterial==SCENE_GET_DATA_ERROR)
    {
        vec3f kd={1.0f,1.0f,1.0f};
        vec3f ks={0.0f,0.0f,0.0f};
        float ns=1.0f;
        TMaterial *pmat;
        unsigned int idmat=SceneGetNewMaterial(pScene,&pmat);
        if(idmat==SCENE_GET_DATA_ERROR)
        {
            printf("#Error ObjParserCreateGeometricPrimitive: can not get a new material from scene.\n");
            return 0;
        }
        if(!MaterialCreate(pmat,kd,ks,ns,MATERIAL_NOT_TEXTURE))
        {
            printf("#Error ObjParserCreateGeometricPrimitive: can not create a new material.\n");
            return 0;
        }
        pPrim->m_IdMaterial=idmat;
    }
    else
        pPrim->m_IdMaterial=pparser->m_IdMaterial;
    return 1;
}

void ObjParserPrint(TObjParser *pparser)
{
    //La liste des vertices
    TObjParserV *plistV=&pparser->m_Vertex;
    unsigned int i=0;
    for(i=0; i<plistV->m_Number; i++)
    {
        printf("vertex (%d) : %f %f %f\n",i,plistV->m_pVertex[i][0],
                                            plistV->m_pVertex[i][1],
                                            plistV->m_pVertex[i][2]);
    }

    //La liste des normales
    TObjParserVn *plistVn=&pparser->m_Normal;
    for(i=0; i<plistVn->m_Number; i++)
    {
        printf("normal (%d) : %f %f %f\n",i,plistVn->m_pNormal[i][0],
                                            plistVn->m_pNormal[i][1],
                                            plistVn->m_pNormal[i][2]);
    }

    //La liste des coordonnees UV
    TObjParserVt *plistVt=&pparser->m_UV;
    for(i=0; i<plistVt->m_Number; i++)
    {
        printf("UV (%d) : %f %f\n",i,plistVt->m_pUV[i][0],plistVt->m_pUV[i][1]);
    }

    //La liste des faces
    TObjParserF *plistF=&pparser->m_Face;
    for(i=0; i<plistF->m_Number; i+=3)
    {
        printf("Face (%d) : \t%d/%d/%d %d/%d/%d %d/%d/%d\n", i/3, plistF->m_pIdx[i][0],plistF->m_pIdx[i][1],plistF->m_pIdx[i][2],
                                                            plistF->m_pIdx[i+1][0],plistF->m_pIdx[i+1][1],plistF->m_pIdx[i+1][2],
                                                            plistF->m_pIdx[i+2][0],plistF->m_pIdx[i+2][1],plistF->m_pIdx[i+2][2]);
    }

    //La liste des materiaux
    TMtlLib *pListMtl=&pparser->m_MtlLib;
    for(i=0; i<pListMtl->m_Number; i++)
    {
        printf("Mtl (%d) : %s\n",i,pListMtl->m_pListMaterial[i].m_pName);
        printf("\tid : %d\n",pListMtl->m_pListMaterial[i].m_Id);
    }
}


int ObjParserGenerateNormal(TObjParser *pparser)
{
    TObjParserF *plistF=&pparser->m_Face;
    TObjParserV *plistV=&pparser->m_Vertex;
    TObjParserVn *plistVn=&pparser->m_Normal;
    //Pour chaque face, on genere une normale
    unsigned int sizeface=pparser->m_Face.m_Number/3;
    unsigned int i;
    vec3f v1,v2,vn;
    vec3f p1,p2,p3;
    for(i=0; i<sizeface; i++)
    {
        //Prend les points
        Vec3fCopy(p1,plistV->m_pVertex[plistF->m_pIdx[i*3][0]-1]);
        Vec3fCopy(p2,plistV->m_pVertex[plistF->m_pIdx[i*3+1][0]-1]);
        Vec3fCopy(p3,plistV->m_pVertex[plistF->m_pIdx[i*3+2][0]-1]);
        Vec3fSub2(v1,p3,p1);
        Vec3fSub2(v2,p2,p1);
        //Produit vectoriel
        Vec3fCross(vn,v2,v1);
        Vec3fNormalize(vn);
        //Ajout a la liste
        if(plistVn->m_Number==plistVn->m_NumberMax)
            if(!ObjParserResizeNormalList(pparser))
            {
                printf("#Error ObjParserGenerateNormal : can not resize list.\n");
                return 0;
            }
        vec3f *pdata=plistVn->m_pNormal+plistVn->m_Number;
        (*pdata)[0]=vn[0];(*pdata)[1]=vn[1];(*pdata)[2]=vn[2];
        plistVn->m_Number++;
        //Mettre a jour les indices
        plistF->m_pIdx[i*3][2]=plistVn->m_Number;
        plistF->m_pIdx[i*3+1][2]=plistVn->m_Number;
        plistF->m_pIdx[i*3+2][2]=plistVn->m_Number;
    }
    return 1;
}
