#include "MtlParser.h"

int MtlParserOpenLib(String filename, TMtlLib *pMtlLib, TScene *pScene)
{
    TMtlParser mtldata;
    //Fixe la liste des materiaux
    mtldata.m_pListMtl=pMtlLib;
    //Initialise la liste
    if(!MtlParserInitialize(&mtldata))
    {
        printf("#Error MtlParserOpenLib: can not initialize.\n");
        MtlParserEnd(&mtldata);
        return 0;
    }
    //Commence par ouvrir le fichier
    if(!MtlParserOpenFile(filename,&mtldata))
        return 0;
    float v[16];
    char nametext[4096],nametextfull[MAX_PATH];

    while(MtlParserFindCmd(&mtldata))
    {
        if(strcmp(mtldata.m_pCmd,"newmtl")==0)
        {
            if(!MtlParserCmdnewmtl(&mtldata,pScene))
            {
                printf("#Error MtlParserOpenLib: cmd newmtl.\n");
                MtlParserEnd(&mtldata);
                return 0;
            }
        }
        else if(strcmp(mtldata.m_pCmd,"Ns")==0)
        {
            if(pMtlLib->m_Number==0)
            {
                printf("#Error MtlParserOpenLib: cmd Ns (no material).\n");
                return 0;
            }
            if(sscanf(mtldata.m_pLine,"%f",v)!=1)
            {
                printf("#Error MtlParserOpenLib: cmd Ns.\n");
                return 0;
            }
            mtldata.m_pCurrentMaterial->m_Ns=v[0];
        }
        else if(strcmp(mtldata.m_pCmd,"Kd")==0)
        {
            if(pMtlLib->m_Number==0)
            {
                printf("#Error MtlParserOpenLib: cmd Kd (no material).\n");
                return 0;
            }
            if(sscanf(mtldata.m_pLine,"%f %f %f",v,v+1,v+2)!=3)
            {
                printf("#Error MtlParserOpenLib: cmd Kd.\n");
                return 0;
            }
            mtldata.m_pCurrentMaterial->m_Kd[0]=v[0];
            mtldata.m_pCurrentMaterial->m_Kd[1]=v[1];
            mtldata.m_pCurrentMaterial->m_Kd[2]=v[2];
        }
        else if(strcmp(mtldata.m_pCmd,"Ks")==0)
        {
            if(pMtlLib->m_Number==0)
            {
                printf("#Error MtlParserOpenLib: cmd Ks (no material).\n");
                return 0;
            }
            if(sscanf(mtldata.m_pLine,"%f %f %f",v,v+1,v+2)!=3)
            {
                printf("#Error MtlParserOpenLib: cmd Ks.\n");
                return 0;
            }
            mtldata.m_pCurrentMaterial->m_Ks[0]=v[0];
            mtldata.m_pCurrentMaterial->m_Ks[1]=v[1];
            mtldata.m_pCurrentMaterial->m_Ks[2]=v[2];
        }
        else if(strcmp(mtldata.m_pCmd,"map_Kd")==0) //TODO: gestion d'une meme texture pour plusieurs materiau
        {
            if(pMtlLib->m_Number==0)
            {
                printf("#Error MtlParserOpenLib: cmd map_Kd (no material).\n");
                return 0;
            }
            MtlParserSkipSpace(&mtldata);
            //Cree le lien vers le fichier
            sscanf(mtldata.m_pLine,"%s",nametext);
            strcpy(nametextfull,mtldata.m_FileRep);
            strcat(nametextfull,nametext);
            //Lecture et ajout de la texture.
            TTexture *ptex;
            unsigned int idtex=SceneGetNewTexture(pScene,&ptex);
            if(idtex==SCENE_GET_DATA_ERROR)
            {
                printf("#Error MtlParserOpenLib: cmd map_Kd (can not get a new texture from scene.\n");
                return 0;
            }
            if(!TextureCreateFromFile(ptex,nametextfull,1024))
            {
                printf("#Error MtlParserOpenLib: cmd map_Kd (can not create texture from file.\n");
                return 0;
            }
            if(!MaterialSetTexture(mtldata.m_pCurrentMaterial,idtex))
            {
                printf("#Error MtlParserOpenLib: cmd map_Kd (can not create set texture to material.\n");
                return 0;
            }
        }
        else if(strcmp(mtldata.m_pCmd,"d")==0)
        {
            if(pMtlLib->m_Number==0)
            {
                printf("#Error MtlParserOpenLib: cmd d (no material).\n");
                return 0;
            }
            if(sscanf(mtldata.m_pLine,"%f",v)!=1)
            {
                printf("#Error MtlParserOpenLib: cmd d.\n");
                return 0;
            }
            mtldata.m_pCurrentMaterial->m_Alpha=v[0];
        }
    }
    MtlParserEnd(&mtldata);
    return 1;
}

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int MtlParserInitialize(TMtlParser *pMtlParser)
{
    pMtlParser->m_pListMtl->m_NumberMax=0;
    pMtlParser->m_pListMtl->m_Number=0;
    if(!MtlParserResizeList(pMtlParser))
    {
        printf("#Error MtlParserInitialize: can not create MTL list.\n");
        return 0;
    }
    return 1;
}

int MtlParserOpenFile(String filename, TMtlParser *pMtlParser)
{
    pMtlParser->m_Stream=fopen(filename,"r");
    if(pMtlParser->m_Stream==NULL)
    {
        printf("#Error MtlParserOpenFile: can not open file.\n");
        return 0;
    }
    //Prend le repertoire de travail
    unsigned int posslash=StringFindLast(filename,'\\');
    if(posslash==(unsigned int)(-1))
        posslash=StringFindLast(filename,'/');
    if(posslash==(unsigned int)(-1))
        strcpy(pMtlParser->m_FileRep,"");
    else
    {
        strncpy(pMtlParser->m_FileRep,filename,posslash+1);
        pMtlParser->m_FileRep[posslash+1]='\0';
    }
    return 1;
}

int MtlParserEnd(TMtlParser *pMtlParser)
{
    //Ferme le fichier
    fclose(pMtlParser->m_Stream);
    return 1;
}

int MtlParserResizeList(TMtlParser *pMtlParser)
{
    //Les anciennes valeurs
    TMtlMaterial *olddata=pMtlParser->m_pListMtl->m_pListMaterial;
    TMtlLib *pMtlLib=pMtlParser->m_pListMtl;
    if(pMtlLib->m_NumberMax==0)//Nouvelle allocation
    {
        pMtlLib->m_NumberMax=1024;
        pMtlLib->m_Number=0;
        pMtlLib->m_pListMaterial=malloc(1024*sizeof(TMtlMaterial));
        if(pMtlLib->m_pListMaterial==NULL)
        {
            printf("#Error MtlParserResizeList: can not allocate new list.\n");
            pMtlLib->m_NumberMax=0;
            return 0;
        }
        return 1;
    }
    //Change la taille
    unsigned int oldsize=pMtlLib->m_NumberMax;
    pMtlLib->m_NumberMax=oldsize*2;
    pMtlLib->m_pListMaterial=malloc(pMtlLib->m_NumberMax*sizeof(TMtlMaterial));
    if(pMtlLib->m_pListMaterial==NULL)
    {
        printf("#Error MtlParserResizeList: can not rallocate new list.\n");
        pMtlLib->m_NumberMax=0;
        free(olddata);
        return 0;
    }
    //Recopie des anciennes valeurs
    unsigned int i;
    for(i=0; i<oldsize; i++)
    {
        strcpy(pMtlLib->m_pListMaterial[i].m_pName,olddata->m_pName);
        pMtlLib->m_pListMaterial[i].m_Id=olddata->m_Id;
    }
    free(olddata);
    return 1;
}

int MtlParserFindCmd(TMtlParser *pMtlParser)
{
    while(fgets(pMtlParser->m_RawLine,4096,pMtlParser->m_Stream)!=NULL)
    {
        //Init les pointeurs de debut et fin de ligne a traiter
        pMtlParser->m_pLine = pMtlParser->m_RawLine;
        pMtlParser->m_pLineEnd = pMtlParser->m_RawLine+strlen(pMtlParser->m_RawLine);
        //Cherche le 1er caractere qui n'est pas un espace
        MtlParserSkipSpace(pMtlParser);
        //La commande de la ligne
        pMtlParser->m_pCmd=pMtlParser->m_pLine;
        //Passe la commande
        MtlParserSkipNoSpace(pMtlParser);
        //Met une fin de ligne apres la commande
        if(pMtlParser->m_pLine<pMtlParser->m_pLineEnd)
        {
            *pMtlParser->m_pLine = '\0';
            pMtlParser->m_pLine++;
        }
        return 1;
    }
    return 0;
}

void MtlParserSkipSpace(TMtlParser *pMtlParser)
{
    while(isspace(*pMtlParser->m_pLine) && pMtlParser->m_pLine<pMtlParser->m_pLineEnd)
        pMtlParser->m_pLine++;
}

void MtlParserSkipNoSpace(TMtlParser *pMtlParser)
{
    while(!isspace(*pMtlParser->m_pLine) && pMtlParser->m_pLine<pMtlParser->m_pLineEnd)
        pMtlParser->m_pLine++;
}

int MtlParserCmdnewmtl(TMtlParser *pMtlParser, TScene *pScene)
{
    TMtlLib *pMtlLib=pMtlParser->m_pListMtl;
    if(pMtlLib->m_Number==pMtlLib->m_NumberMax)
        if(!MtlParserResizeList(pMtlParser))
        {
            printf("#Error MtlParserCmdnewmtl : can not resize list.\n");
            return 0;
        }
    //Lecture du nom
    unsigned int idxmat=pMtlLib->m_Number;
    MtlParserSkipSpace(pMtlParser);
    sscanf(pMtlParser->m_pLine,"%s",pMtlLib->m_pListMaterial[idxmat].m_pName);
    //Prend un nouveau materiau dans la scene
    unsigned int id=SceneGetNewMaterial(pScene,&pMtlParser->m_pCurrentMaterial);
    if(id==SCENE_GET_DATA_ERROR)
    {
        printf("#Error MtlParserCmdnewmtl : can not get new material form scene.\n");
        return 0;
    }
    pMtlParser->m_pCurrentMaterial->m_IdTexture=MATERIAL_NOT_TEXTURE;
    pMtlParser->m_pCurrentMaterial->m_Alpha=1.0f;
    pMtlLib->m_pListMaterial[idxmat].m_Id=id;
    pMtlLib->m_Number++;
    return 1;
}

