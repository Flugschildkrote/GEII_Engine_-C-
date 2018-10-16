#if !defined(MTLPARSER_H)
#define MTLPARSER_H

#include <stdio.h>
#include <ctype.h>
#include <windows.h>

#include "Material.h"
#include "String.h"
#include "Scene.h"

typedef struct{
    char m_pName[4096];
    unsigned int m_Id;
}TMtlMaterial;

typedef struct{
    TMtlMaterial *m_pListMaterial;  //La liste des materiaux et le nom de reference
    unsigned int m_Number;
    unsigned int m_NumberMax;
}TMtlLib;

typedef struct{
    FILE *m_Stream;                 //Un pointeur sur le fichier.
    char m_RawLine[4096];           //Un buffer pour la gestion des lignes du fichier.
    char *m_pLine;                  //Un pointeur sur la position de la ligne traitee.
    char *m_pLineEnd;               //Un pointeur sur la fin de la ligne traitee.
    char *m_pCmd;                   //Un pointeur sur la commande actuelle.
    char m_FileRep[MAX_PATH];       //Le repertoire de travail.
    TMaterial *m_pCurrentMaterial;  //Le pointeur le materiau actuellement charge.
    TMtlLib *m_pListMtl;            //La liste des materiaux et le nom de reference.
}TMtlParser;

int MtlParserOpenLib(String filename, TMtlLib *pMtlLib, TScene *pScene);

/// ********************************
/// FONCTIONS INTERNES
/// ********************************
int MtlParserInitialize(TMtlParser *pMtlParser);
int MtlParserOpenFile(String filename, TMtlParser *pMtlParser);
int MtlParserEnd(TMtlParser *pMtlParser);

int MtlParserFindCmd(TMtlParser *pMtlParser);
void MtlParserSkipSpace(TMtlParser *pMtlParser);
void MtlParserSkipNoSpace(TMtlParser *pMtlParser);

int MtlParserCmdnewmtl(TMtlParser *pMtlParser, TScene *pScene);

int MtlParserResizeList(TMtlParser *pMtlParser);

#endif //MTLPARSER_H
